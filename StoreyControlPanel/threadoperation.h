#ifndef THREADOPERATION_H
#define THREADOPERATION_H

#include <QObject>
#include <QSharedMemory>

class ThreadOperation : public QObject
{
    Q_OBJECT
public:
    explicit ThreadOperation(QObject *parent = nullptr);

private:
    int myFloor;
    QSharedMemory *sharedRequestUp;
    QSharedMemory *sharedRequestDown;
    QSharedMemory *sharedOpen;

    void writeSharedInt(int&, QSharedMemory *);

public slots:
    void setMyFloor(int);
    void up();
    void down();
    void upCancel();
    void downCancel();
    void open();

};

#endif // THREADOPERATION_H
