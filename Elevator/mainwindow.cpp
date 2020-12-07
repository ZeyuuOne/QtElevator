#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QTimer"
#include "QVector"

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
const char* KEY_SHARED_OPEN = "Open";
const char* KEY_SHARED_CLOSE = "Close";

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , sharedFloor(new QSharedMemory(KEY_SHARED_FLOOR, this))
    , sharedStatus(new QSharedMemory(KEY_SHARED_STATUS, this))
    , sharedDirection(new QSharedMemory(KEY_SHARED_DIRECTION, this))
    , sharedOpen(new QSharedMemory(KEY_SHARED_OPEN, this))
    , sharedClose(new QSharedMemory(KEY_SHARED_CLOSE, this))
    , floor(1)
    , status(ELEVATOR_STOP)
    , direction(DIRECTION_NONE)
    , open(0)
    , close(0)
    , nextTime(0)
{
    ui->setupUi(this);
    this->setWindowTitle("电梯");

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

    labelFloor[0] = ui->label1Floor;
    labelFloor[1] = ui->label2Floor;
    labelFloor[2] = ui->label3Floor;
    labelRequestTo[0] = ui->label1RequestTo;
    labelRequestTo[1] = ui->label2RequestTo;
    labelRequestTo[2] = ui->label3RequestTo;
    labelRequestUp[0] = ui->label1RequestUp;
    labelRequestUp[1] = ui->label2RequestUp;
    labelRequestUp[2] = ui->label3RequestUp;
    labelRequestDown[0] = ui->label1RequestDown;
    labelRequestDown[1] = ui->label2RequestDown;
    labelRequestDown[2] = ui->label3RequestDown;

    statusString.append("STOPPED");
    statusString.append("RUNNING");
    statusString.append("OPENING");
    statusString.append("CLOSING");
    statusString.append("WAITING");

    directionString.append("NONE");
    directionString.append("UP");
    directionString.append("DOWN");

    createSharedInt(floor,sharedFloor);
    createSharedInt(status,sharedStatus);
    createSharedInt(direction,sharedDirection);
    for (int i = 0;i < 3;i++) {
        int val = 0;
        createSharedInt(val,sharedRequestUp[i]);
        createSharedInt(val,sharedRequestDown[i]);
        createSharedInt(val,sharedRequestTo[i]);
    }
    createSharedInt(open,sharedOpen);
    createSharedInt(close,sharedClose);

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

void MainWindow::refreshDisplay(){
    ui->labelStatus->setText(statusString[status]);
    ui->labelDirection->setText(directionString[direction]);
    for (int i = 0;i < 3;i++){
        labelRequestTo[i]->setVisible(requestTo[i] == 1);
        labelRequestUp[i]->setVisible(requestUp[i] == 1);
        labelRequestDown[i]->setVisible(requestDown[i] == 1);
        if (i + 1 == floor) labelFloor[i]->setVisible(1); else labelFloor[i]->setVisible(0);
    }
}

void MainWindow::repeatExec(){
    if (nextTime == 0){
        for (int i = 0;i < 3;i++){
            readSharedInt(sharedRequestTo[i],requestTo[i]);
            readSharedInt(sharedRequestUp[i],requestUp[i]);
            readSharedInt(sharedRequestDown[i],requestDown[i]);
        }
        switch(status){
        case ELEVATOR_STOP:
            readSharedInt(sharedOpen,open);
            if (open == 1){
                status = ELEVATOR_OPEN;
                nextTime = 10;
                int val = 0;
                writeSharedInt(val, sharedOpen);
                break;
            }
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
            floor += direction == DIRECTION_UP?1:-1;
            if (floor == 1) direction = DIRECTION_UP;
            if (floor == 3) direction = DIRECTION_DOWN;
            if (requestTo[floor - 1] == 1 || (direction == DIRECTION_UP && requestUp[floor - 1] == 1) || (direction == DIRECTION_DOWN && requestDown[floor - 1] == 1)){
                status = ELEVATOR_OPEN;
                nextTime = 10;
                break;
            }
            if (direction == DIRECTION_UP){
                bool next = 0;
                for (int i = floor;i < 3;i++) if (requestTo[i] == 1 || requestUp[i] == 1  || requestDown[i] == 1) {
                    next = 1;
                    break;
                }
                if (next == 0){
                    status = ELEVATOR_STOP;
                    direction = DIRECTION_NONE;
                    break;
                }
                status = ELEVATOR_RUN;
                nextTime = 20;
            }
            else {
                bool next = 0;
                for (int i = floor - 2;i > -1;i--) if (requestTo[i] == 1 || requestUp[i] == 1 || requestDown[i] == 1) {
                    next = 1;
                    break;
                }
                if (next == 0){
                    status = ELEVATOR_STOP;
                    direction = DIRECTION_NONE;
                    break;
                }
                status = ELEVATOR_RUN;
                nextTime = 20;
            }
            break;
        case ELEVATOR_OPEN:
            status = ELEVATOR_WAIT;
            nextTime = 20;
            break;
        case ELEVATOR_WAIT:
            status = ELEVATOR_CLOSE;
            nextTime = 10;
            break;
        case ELEVATOR_CLOSE:
            if (direction == DIRECTION_UP){
                bool next = 0;
                for (int i = floor;i < 3;i++) if (requestTo[i] == 1 || requestUp[i] == 1 || requestDown[i] == 1) {
                    next = 1;
                    break;
                }
                if (next == 0){
                    status = ELEVATOR_STOP;
                    direction = DIRECTION_NONE;
                    break;
                }
                status = ELEVATOR_RUN;
                nextTime = 20;
            }
            else if (direction == DIRECTION_DOWN){
                bool next = 0;
                for (int i = floor - 2;i > -1;i--) if (requestTo[i] == 1 || requestUp[i] == 1 || requestDown[i] == 1) {
                    next = 1;
                    break;
                }
                if (next == 0){
                    status = ELEVATOR_STOP;
                    direction = DIRECTION_NONE;
                    break;
                }
                status = ELEVATOR_RUN;
                nextTime = 20;
            }
            else {
                status = ELEVATOR_STOP;
                direction = DIRECTION_NONE;
                break;
            }
            break;
        }
        writeSharedInt(floor,sharedFloor);
        writeSharedInt(status, sharedStatus);
        writeSharedInt(direction, sharedDirection);
        refreshDisplay();
        qDebug()<<"FLOOR "<<floor<<" STATUS "<<status<<" DIRECTION "<<direction;
    }
    else {
        nextTime--;
        if (status == ELEVATOR_WAIT){
            readSharedInt(sharedOpen,open);
            readSharedInt(sharedClose,close);
            if (open == 1){
                nextTime = 20;
                int val = 0;
                writeSharedInt(val, sharedOpen);
            }
            else if (close == 1){
                nextTime = 0;
                int val = 0;
                writeSharedInt(val, sharedClose);
            }
        }
    }
}
