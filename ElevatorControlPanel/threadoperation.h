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

    void writeSharedInt(int&, QSharedMemory *);

signals:

public slots:
    void to(int);

};

#endif // THREADOPERATION_H
