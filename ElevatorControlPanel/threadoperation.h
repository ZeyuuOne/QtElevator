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
    QSharedMemory *sharedRequestTo[3];
    QSharedMemory *sharedOpen;
    QSharedMemory *sharedClose;

    void writeSharedInt(int&, QSharedMemory *);

signals:

public slots:
    void to(int);
    void toCancel(int);
    void open();
    void close();

};

#endif // THREADOPERATION_H
