#include "threadoperation.h"
#include "QDebug"
#include "QBuffer"
#include "QDataStream"

const char* KEY_SHARED_REQUEST_UP = "RequestUp";
const char* KEY_SHARED_REQUEST_DOWN = "RequestDown";
const char* KEY_SHARED_OPEN = "Open";

ThreadOperation::ThreadOperation(QObject *parent) :
    QObject(parent)
    , myFloor(0)
    , sharedOpen(new QSharedMemory(KEY_SHARED_OPEN, this))
{}

void ThreadOperation::setMyFloor(int _myFloor){
    myFloor = _myFloor;
    sharedRequestUp = new QSharedMemory(KEY_SHARED_REQUEST_UP + QString::number(myFloor), this);
    sharedRequestDown = new QSharedMemory(KEY_SHARED_REQUEST_DOWN + QString::number(myFloor), this);
}

void ThreadOperation::up(){
    int val = 1;
    writeSharedInt(val, sharedRequestUp);
}

void ThreadOperation::down(){
    int val = 1;
    writeSharedInt(val, sharedRequestDown);
}

void ThreadOperation::upCancel(){
    int val = 0;
    writeSharedInt(val, sharedRequestUp);
}

void ThreadOperation::downCancel(){
    int val = 0;
    writeSharedInt(val, sharedRequestDown);
}

void ThreadOperation::open(){
    int val = 1;
    writeSharedInt(val, sharedOpen);
    qDebug()<< "OPEN";
}

void ThreadOperation::writeSharedInt(int& src, QSharedMemory* dst){
    if (!(dst == nullptr) && !dst->isAttached() && !dst->attach()){
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
