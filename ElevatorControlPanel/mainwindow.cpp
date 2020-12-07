#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "threadoperation.h"
#include "QThread"

#define ELEVATOR_STOP 0
#define ELEVATOR_RUN 1
#define ELEVATOR_OPEN 2
#define ELEVATOR_CLOSE 3
#define ELEVATOR_WAIT 4

#define DIRECTION_NONE 0
#define DIRECTION_UP 1
#define DIRECTION_DOWN 2

const char* KEY_SHARED_FLOOR = "Floor";
const char* KEY_SHARED_STATUS = "Status";
const char* KEY_SHARED_DIRECTION = "Direction";

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , sharedFloor(new QSharedMemory(KEY_SHARED_FLOOR, this))
    , sharedStatus(new QSharedMemory(KEY_SHARED_STATUS, this))
    , sharedDirection(new QSharedMemory(KEY_SHARED_DIRECTION, this))
{
    ui->setupUi(this);
    this->setWindowTitle("控制面板：电梯");

    for (int i = 0;i < 3;i++) buttonToDown[i] = 0;
    pushButtonTo[0] = ui->pushButtonFloor1;
    pushButtonTo[1] = ui->pushButtonFloor2;
    pushButtonTo[2] = ui->pushButtonFloor3;

    QThread* threadOperation;
    ThreadOperation* objectOperation;
    threadOperation = new QThread();
    objectOperation = new ThreadOperation();
    objectOperation->moveToThread(threadOperation);
    connect(threadOperation,&QThread::finished,threadOperation,&QObject::deleteLater);
    connect(ui->pushButtonFloor1,&QPushButton::clicked,this,[&](){this->buttonToClicked(1);});
    connect(ui->pushButtonFloor2,&QPushButton::clicked,this,[&](){this->buttonToClicked(2);});
    connect(ui->pushButtonFloor3,&QPushButton::clicked,this,[&](){this->buttonToClicked(3);});
    connect(this,&MainWindow::to,objectOperation,&ThreadOperation::to);
    threadOperation->start();

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

void MainWindow::refreshDisplay(){
    readSharedInt(sharedFloor,floor);
    ui->labelFloor->setText(floor == -1?"E":QString::number(floor));
    readSharedInt(sharedStatus,status);
    readSharedInt(sharedDirection,direction);
    switch (direction){
    case -1:
        ui->labelUpDown->setText("■");
        break;
    case DIRECTION_NONE:
        ui->labelUpDown->setText("");
        break;
    case DIRECTION_UP:
        ui->labelUpDown->setText("▲");
    case DIRECTION_DOWN:
        ui->labelUpDown->setText("▼");
    }
}

void MainWindow::buttonToClicked(int floor){
    pushButtonTo[floor - 1]->setChecked(1);
    if (!buttonToDown[floor - 1]){
        buttonToDown[floor - 1] = 1;
        emit to(floor);
    }
}
