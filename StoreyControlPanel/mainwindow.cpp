#include "mainwindow.h"
#include "ui_mainwindow.h"

#define ELEVATOR_STOP 0
#define ELEVATOR_UP 1
#define ELEVATOR_DOWN 2
#define ELEVATOR_OPEN 3
#define ELEVATOR_CLOSE 4
#define ELEVATOR_WAIT 5

const char* KEY_SHARED_STOREY_COUNT = "Storey";
const char* KEY_SHARED_FLOOR = "Floor";
const char* KEY_SHARED_STATUS = "Status";
const char* KEY_SHARED_REQUEST = "Request";

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , sharedStoreyCount(new QSharedMemory(KEY_SHARED_STOREY_COUNT, this))
    , sharedFloor(new QSharedMemory(KEY_SHARED_FLOOR, this))
    , sharedStatus(new QSharedMemory(KEY_SHARED_STATUS, this))
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
    readSharedInt(sharedFloor,floor);
    ui->labelFloor->setText(floor == -1?"E":QString::number(floor));
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
