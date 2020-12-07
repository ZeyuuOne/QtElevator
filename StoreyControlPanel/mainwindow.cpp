#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "threadoperation.h"
#include "QThread"
#include "QTimer"

#define ELEVATOR_STOP 0
#define ELEVATOR_RUN 1
#define ELEVATOR_OPEN 2
#define ELEVATOR_CLOSE 3
#define ELEVATOR_WAIT 4

#define DIRECTION_NONE 0
#define DIRECTION_UP 1
#define DIRECTION_DOWN 2

const char* KEY_SHARED_STOREY_COUNT = "Storey";
const char* KEY_SHARED_FLOOR = "Floor";
const char* KEY_SHARED_STATUS = "Status";
const char* KEY_SHARED_DIRECTION = "Direction";

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , sharedStoreyCount(new QSharedMemory(KEY_SHARED_STOREY_COUNT, this))
    , sharedFloor(new QSharedMemory(KEY_SHARED_FLOOR, this))
    , sharedStatus(new QSharedMemory(KEY_SHARED_STATUS, this))
    , sharedDirection(new QSharedMemory(KEY_SHARED_DIRECTION, this))
    , buttonUpDown(0)
    , buttonDownDown(0)
{
    ui->setupUi(this);
    if (!sharedStoreyCount->attach()){
        if (!sharedStoreyCount->create(sizeof(int))) qDebug() << tr("Create Error: ") << sharedStoreyCount->errorString();
        else qDebug() << tr("Create Success");
        int val = 0;
        writeSharedInt(val, sharedStoreyCount);
    }
    incrementAndGetSharedInt(sharedStoreyCount,myFloor);
    this->setWindowTitle("控制面板："+QString::number(myFloor)+"层");
    if (myFloor <= 1 || myFloor > 3) {
        ui->pushButtonDown->setEnabled(0);
        ui->pushButtonDown->setVisible(0);
        ui->pushButtonUp->setGeometry(75,285,50,50);
    }
    if (myFloor >= 3 || myFloor < 1) {
        ui->pushButtonUp->setEnabled(0);
        ui->pushButtonUp->setVisible(0);
        ui->pushButtonDown->setGeometry(75,285,50,50);
    }

    QThread* threadOperation;
    ThreadOperation* objectOperation;
    threadOperation = new QThread();
    objectOperation = new ThreadOperation();
    objectOperation->moveToThread(threadOperation);
    connect(threadOperation,&QThread::finished,threadOperation,&QObject::deleteLater);
    connect(this,&MainWindow::setThreadOperation,objectOperation,&ThreadOperation::setMyFloor);
    connect(ui->pushButtonUp,&QPushButton::clicked,this,&MainWindow::buttonUpClicked);
    connect(ui->pushButtonDown,&QPushButton::clicked,this,&MainWindow::buttonDownClicked);
    connect(this,&MainWindow::up,objectOperation,&ThreadOperation::up);
    connect(this,&MainWindow::down,objectOperation,&ThreadOperation::down);
    connect(this,&MainWindow::upCancel,objectOperation,&ThreadOperation::upCancel);
    connect(this,&MainWindow::downCancel,objectOperation,&ThreadOperation::downCancel);
    connect(this,&MainWindow::open,objectOperation,&ThreadOperation::open);
    threadOperation->start();

    emit setThreadOperation(myFloor);

    QTimer *timer = new QTimer(this);
    connect(timer,&QTimer::timeout,this,&MainWindow::repeatExec);
    timer->start(50);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::readSharedInt(QSharedMemory *src, int& dst){
    if (!src->isAttached() && !src->attach()){
        qDebug() << tr("Attach Error in readSharedInt: ") << src->errorString();
        dst = -1;
        return;
    }
    QBuffer buffer;
    QDataStream bufferStream(&buffer);
    src->lock();
    buffer.setData(static_cast<const char *>(src->constData()), src->size());
    buffer.open(QBuffer::ReadWrite);
    bufferStream >> dst;
    src->unlock();
}

void MainWindow::writeSharedInt(int& src, QSharedMemory* dst){
    if (!dst->isAttached() && !dst->attach()){
        qDebug() << tr("Attach Error in writeSharedInt: ") << dst->errorString();
        return;
    }
    QBuffer buffer;
    QDataStream bufferStream(&buffer);
    buffer.open(QBuffer::ReadWrite);
    bufferStream << src;
    int size = buffer.size();
    dst->lock();
    char *to = static_cast<char *>(dst->data());
    const char *from=buffer.data().constData();
    memcpy(to,from,size);
    dst->unlock();
}

void MainWindow::incrementAndGetSharedInt(QSharedMemory *src, int& dst){
    if (!src->isAttached() && !src->attach()){
        qDebug() << tr("Attach Error in incrementAndGetSharedInt: ") << src->errorString();
        dst = -1;
        return;
    }
    QBuffer readBuffer;
    QDataStream readBufferStream(&readBuffer);
    QBuffer writeBuffer;
    QDataStream writeBufferStream(&writeBuffer);
    writeBuffer.open(QBuffer::ReadWrite);
    src->lock();
    readBuffer.setData(static_cast<const char *>(src->constData()), src->size());
    readBuffer.open(QBuffer::ReadWrite);
    readBufferStream >> dst;
    writeBufferStream << dst + 1;
    char *to = static_cast<char *>(src->data());
    const char *from=writeBuffer.data().constData();
    memcpy(to,from,writeBuffer.size());
    src->unlock();
    dst++;
}

void MainWindow::refreshDisplay(){
    readSharedInt(sharedFloor,floor);
    ui->labelFloor->setText(floor == -1?"E":QString::number(floor));
    readSharedInt(sharedStatus,status);
    readSharedInt(sharedDirection,direction);
    switch (direction){
    case -1:
        ui->labelUp->setVisible(1);
        ui->labelDown->setVisible(1);
        break;
    case DIRECTION_NONE:
        ui->labelUp->setVisible(0);
        ui->labelDown->setVisible(0);
        break;
    case DIRECTION_UP:
        ui->labelUp->setVisible(1);
        ui->labelDown->setVisible(0);
        break;
    case DIRECTION_DOWN:
        ui->labelUp->setVisible(0);
        ui->labelDown->setVisible(1);
        break;
    }
    if (status == ELEVATOR_OPEN && floor == myFloor){
        ui->labelDoorLeft->setText("<<");
        ui->labelDoorRight->setText(">>");
    }
    else if (status == ELEVATOR_WAIT && floor == myFloor){
        ui->labelDoorLeft->setText("|   ");
        ui->labelDoorRight->setText("   |");
    }
    else if ((status == ELEVATOR_CLOSE && floor == myFloor) || status == -1){
        ui->labelDoorLeft->setText(">>");
        ui->labelDoorRight->setText("<<");
    }
    else {
        ui->labelDoorLeft->setText("");
        ui->labelDoorRight->setText("");
    }
}

void MainWindow::buttonUpClicked(){
    if (status == ELEVATOR_WAIT && floor == myFloor){
        emit open();
        return;
    }
    ui->pushButtonUp->setChecked(1);
    if (!buttonUpDown){
        buttonUpDown = 1;
        emit up();
    }
}

void MainWindow::buttonDownClicked(){
    if (status == ELEVATOR_WAIT && floor == myFloor){
        emit open();
        return;
    }
    ui->pushButtonDown->setChecked(1);
    if (!buttonDownDown){
        buttonDownDown = 1;
        emit down();
    }
}

void MainWindow::repeatExec(){
    readSharedInt(sharedFloor,floor);
    readSharedInt(sharedStatus,status);
    readSharedInt(sharedDirection,direction);
    refreshDisplay();
    if (floor == -1 || status == -1 || direction == -1) {
        qDebug()<<"ELEVATOR NOT FOUND";
        return;
    }
    if (floor == myFloor && status == ELEVATOR_WAIT){
        if (direction == DIRECTION_UP){
            if (buttonUpDown) emit upCancel();
            buttonUpDown = 0;
            ui->pushButtonUp->setChecked(0);
        }
        else if (direction == DIRECTION_DOWN){
            if (buttonDownDown) emit downCancel();
            buttonDownDown = 0;
            ui->pushButtonDown->setChecked(0);
        }
        else {
            if (buttonUpDown){
                emit upCancel();
                buttonUpDown = 0;
                ui->pushButtonUp->setChecked(0);
            }
            else if (buttonDownDown){
                emit downCancel();
                buttonDownDown = 0;
                ui->pushButtonDown->setChecked(0);
            }
        }
    }
}
