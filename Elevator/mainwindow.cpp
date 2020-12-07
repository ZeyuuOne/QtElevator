#include "mainwindow.h"
#include "ui_mainwindow.h"

#define ELEVATOR_STOP 0
#define ELEVATOR_UP 1
#define ELEVATOR_DOWN 2
#define ELEVATOR_OPEN 3
#define ELEVATOR_CLOSE 4
#define ELEVATOR_WAIT 5

const char* KEY_SHARED_FLOOR = "Floor";
const char* KEY_SHARED_STATUS = "Status";
const char* KEY_SHARED_REQUEST = "Request";

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , sharedFloor(new QSharedMemory(KEY_SHARED_FLOOR, this))
    , sharedStatus(new QSharedMemory(KEY_SHARED_STATUS, this))
{
    ui->setupUi(this);

    floor = 1;
    status = ELEVATOR_STOP;
    for (int i = 0;i < 6;i++) request[i] = 0;

    if (sharedFloor->attach()) sharedFloor->detach();
    if (!sharedFloor->create(sizeof(int))) qDebug() << tr("Create Error: ") << sharedFloor->errorString();
    writeSharedInt(floor,sharedFloor);
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

