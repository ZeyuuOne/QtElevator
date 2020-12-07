#include "mainwindow.h"
#include "ui_mainwindow.h"

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
const char* KEY_SHARED_REQUEST = "Request";

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , sharedFloor(new QSharedMemory(KEY_SHARED_FLOOR, this))
    , sharedStatus(new QSharedMemory(KEY_SHARED_STATUS, this))
    , floor(1)
    , status(ELEVATOR_STOP)
{
    ui->setupUi(this);

    for (int i = 0;i < 3;i++) {
        sharedRequestUp[i] = new QSharedMemory(KEY_SHARED_REQUEST + QString("Up") + QString::number(i + 1), this);
        sharedRequestDown[i] = new QSharedMemory(KEY_SHARED_REQUEST + QString("Down") + QString::number(i + 1), this);
        sharedRequestTo[i] = new QSharedMemory(KEY_SHARED_REQUEST + QString("To") + QString::number(i + 1), this);
    }

    for (int i = 0;i < 3;i++){
        requestUp[i] = 0;
        requestDown[i] = 0;
        requestTo[i] = 0;
    }

    createSharedInt(floor,sharedFloor);
    createSharedInt(status,sharedStatus);
    for (int i = 0;i < 3;i++) {
        int val = 0;
        createSharedInt(val,sharedRequestUp[i]);
        createSharedInt(val,sharedRequestDown[i]);
        createSharedInt(val,sharedRequestTo[i]);
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::writeSharedInt(int& src, QSharedMemory* dst){
    if (!dst->isAttached() && !dst->attach()){
        qDebug() << tr("Attach Error: ") << dst->errorString();
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

void MainWindow::createSharedInt(int& src, QSharedMemory* dst){
    if (dst->attach()) dst->detach();
    if (!dst->create(sizeof(int))) qDebug() << tr("Create Error: ") << dst->errorString();
    writeSharedInt(src,dst);
}
