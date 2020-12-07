#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "threadoperation.h"
#include "QThread"

#define ELEVATOR_STOP 0
#define ELEVATOR_UP 1
#define ELEVATOR_DOWN 2
#define ELEVATOR_OPEN_STOP 3
#define ELEVATOR_OPEN_UP 4
#define ELEVATOR_OPEN_DOWN 5
#define ELEVATOR_CLOSE_STOP 6
#define ELEVATOR_CLOSE_UP 7
#define ELEVATOR_CLOSE_DOWN 8
#define ELEVATOR_WAIT_STOP 9
#define ELEVATOR_WAIT_UP 10
#define ELEVATOR_WAIT_DOWN 11

const char* KEY_SHARED_STOREY_COUNT = "Storey";
const char* KEY_SHARED_FLOOR = "Floor";
const char* KEY_SHARED_STATUS = "Status";

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , sharedStoreyCount(new QSharedMemory(KEY_SHARED_STOREY_COUNT, this))
    , sharedFloor(new QSharedMemory(KEY_SHARED_FLOOR, this))
    , sharedStatus(new QSharedMemory(KEY_SHARED_STATUS, this))
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
    threadOperation->start();

    emit setThreadOperation(myFloor);

    refreshDisplay();

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
    if (status == -1){
        ui->labelUp->setVisible(1);
        ui->labelDown->setVisible(1);
    }
    else if (status == ELEVATOR_CLOSE_UP || status == ELEVATOR_OPEN_UP || status == ELEVATOR_WAIT_UP || status == ELEVATOR_UP){
        ui->labelUp->setVisible(1);
        ui->labelDown->setVisible(0);
    }
    else if (status == ELEVATOR_CLOSE_DOWN || status == ELEVATOR_OPEN_DOWN || status == ELEVATOR_WAIT_DOWN || status == ELEVATOR_DOWN){
        ui->labelUp->setVisible(0);
        ui->labelDown->setVisible(1);
    }
    else {
        ui->labelUp->setVisible(0);
        ui->labelDown->setVisible(0);
    }
}

void MainWindow::buttonUpClicked(){
    ui->pushButtonUp->setChecked(1);
    if (!buttonUpDown){
        buttonUpDown = 1;
        emit up();
    }
}

void MainWindow::buttonDownClicked(){
    ui->pushButtonDown->setChecked(1);
    if (!buttonDownDown){
        buttonDownDown = 1;
        emit down();
    }
}
