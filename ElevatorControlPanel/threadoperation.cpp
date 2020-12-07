#include "threadoperation.h"
#include "QDebug"
#include "QBuffer"
#include "QDataStream"

const char* KEY_SHARED_REQUEST_TO = "RequestTo";

ThreadOperation::ThreadOperation(QObject *parent) : QObject(parent)
{
    for (int i = 0;i < 3;i++) sharedRequestTo[i] = new QSharedMemory(KEY_SHARED_REQUEST_TO + QString::number(i+1), this);
}

void ThreadOperation::to(int floor){
    int val = 1;
    writeSharedInt(val, sharedRequestTo[floor - 1]);
    qDebug()<< "TO " + QString::number(floor);
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
