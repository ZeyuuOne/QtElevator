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
const char* KEY_SHARED_REQUEST_1 = "Request1";
const char* KEY_SHARED_REQUEST_2 = "Request2";
const char* KEY_SHARED_REQUEST_3 = "Request3";

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , sharedFloor(new QSharedMemory(KEY_SHARED_FLOOR, this))
{
    ui->setupUi(this);

    if (!sharedFloor->attach()){
        qDebug() << tr("Attach Error: ") << sharedFloor->errorString();
    }
    if (!sharedFloor->isAttached()){
        if(sharedFloor->error()!=QSharedMemory::NoError){
            qDebug() << tr("Attach Error: ") << sharedFloor->errorString();
        }
        qDebug()<< tr("Not Attached");
    }
    else{
        QBuffer buffer;
        QDataStream bufferStream(&buffer);
        int floor;
        sharedFloor->lock();
        buffer.setData(static_cast<const char *>(sharedFloor->constData()), sharedFloor->size());
        buffer.open(QBuffer::ReadWrite);
        bufferStream >> floor;
        sharedFloor->unlock();
        ui->labelFloor->setText(QString::number(floor));
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

