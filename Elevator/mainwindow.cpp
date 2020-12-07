#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QTimer"
#include "QTime"

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
const char* KEY_SHARED_REQUEST = "Request";

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , sharedFloor(new QSharedMemory(KEY_SHARED_FLOOR, this))
    , sharedStatus(new QSharedMemory(KEY_SHARED_STATUS, this))
    , sharedDirection(new QSharedMemory(KEY_SHARED_DIRECTION, this))
    , floor(1)
    , status(ELEVATOR_STOP)
    , direction(DIRECTION_NONE)
    , nextTime(0)
    , nextStatus(ELEVATOR_STOP)
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
    createSharedInt(direction,sharedDirection);
    for (int i = 0;i < 3;i++) {
        int val = 0;
        createSharedInt(val,sharedRequestUp[i]);
        createSharedInt(val,sharedRequestDown[i]);
        createSharedInt(val,sharedRequestTo[i]);
    }

    QTimer *timer = new QTimer(this);
    connect(timer,&QTimer::timeout,this,&MainWindow::repeatExec);
    timer->start(50);
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

void MainWindow::repeatExec(){
    if (nextTime == 0){
        switch(status){
        case ELEVATOR_STOP:
            for (int i = 0;i < 3;i++){
                if (requestTo[i] == 1 || requestUp[i] == 1 || requestDown[i] == 1){
                    if (i + 1 == floor){
                        status = ELEVATOR_OPEN;
                        nextTime = 10;
                        break;
                    }
                    status = ELEVATOR_RUN;
                    nextTime = 20;
                    direction = i + 1 > floor?DIRECTION_UP:DIRECTION_DOWN;
                    break;
                }
            }
            break;
        case ELEVATOR_RUN:
            if (requestTo[floor - 1] == 1 || requestUp[floor - 1] == 1 || requestDown[floor - 1] == 1){
                status = ELEVATOR_OPEN;
                nextTime = 10;
                break;
            }
            if (direction == DIRECTION_UP){
                bool next = 0;
                for (int i = floor - 1;i < 3;i++) if (requestTo[i] == 1 || requestUp[i] == 1 || requestDown[i] == 1) {
                    next = 1;
                    break;
                }
                if (next == 0){
                    status = ELEVATOR_STOP;
                    break;
                }
                status = ELEVATOR_RUN;
                nextTime = 20;
            }
            break;
        }

    }
    else {
        nextTime--;
    }
}
