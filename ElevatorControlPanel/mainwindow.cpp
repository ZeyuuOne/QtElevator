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

const char* KEY_SHARED_FLOOR = "Floor";
const char* KEY_SHARED_STATUS = "Status";

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , sharedFloor(new QSharedMemory(KEY_SHARED_FLOOR, this))
    , sharedStatus(new QSharedMemory(KEY_SHARED_STATUS, this))
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
    if (status == -1){
        ui->labelUpDown->setText("■");
    }
    else if (status == ELEVATOR_CLOSE_UP || status == ELEVATOR_OPEN_UP || status == ELEVATOR_WAIT_UP || status == ELEVATOR_UP){
        ui->labelUpDown->setText("▲");
    }
    else if (status == ELEVATOR_CLOSE_DOWN || status == ELEVATOR_OPEN_DOWN || status == ELEVATOR_WAIT_DOWN || status == ELEVATOR_DOWN){
        ui->labelUpDown->setText("▼");
    }
    else {
        ui->labelUpDown->setText("");
    }
}

void MainWindow::buttonToClicked(int floor){
    pushButtonTo[floor - 1]->setChecked(1);
    if (!buttonToDown[floor - 1]){
        buttonToDown[floor - 1] = 1;
        emit to(floor);
    }
}
