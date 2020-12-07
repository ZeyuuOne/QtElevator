#include "threadoperation.h"
#include "QDebug"
#include "QBuffer"
#include "QDataStream"

const char* KEY_SHARED_REQUEST_TO = "RequestTo";
const char* KEY_SHARED_OPEN = "Open";
const char* KEY_SHARED_CLOSE = "Close";

ThreadOperation::ThreadOperation(QObject *parent) : QObject(parent)
  , sharedOpen(new QSharedMemory(KEY_SHARED_OPEN, this))
  , sharedClose(new QSharedMemory(KEY_SHARED_CLOSE, this))
{
    for (int i = 0;i < 3;i++) sharedRequestTo[i] = new QSharedMemory(KEY_SHARED_REQUEST_TO + QString::number(i+1), this);
}

void ThreadOperation::to(int floor){
    int val = 1;
    writeSharedInt(val, sharedRequestTo[floor - 1]);
    qDebug()<< "TO " + QString::number(floor);
}

void ThreadOperation::toCancel(int floor){
    int val = 0;
    writeSharedInt(val, sharedRequestTo[floor - 1]);
    qDebug()<< "TO " + QString::number(floor) + " DONE";
}

void ThreadOperation::open(){
    int val = 1;
    writeSharedInt(val, sharedOpen);
    qDebug()<< "OPEN";
}

void ThreadOperation::close(){
    int val = 1;
    writeSharedInt(val, sharedClose);
    qDebug()<< "CLOSE";
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
