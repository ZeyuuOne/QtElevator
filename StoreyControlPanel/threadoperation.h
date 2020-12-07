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

    void writeSharedInt(int&, QSharedMemory *);

signals:
    void upCancel();
    void downCancel();

public slots:
    void setMyFloor(int);
    void up();
    void down();

};

#endif // THREADOPERATION_H
