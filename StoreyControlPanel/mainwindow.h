#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSharedMemory>
#include <QBuffer>
#include <QDebug>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QSharedMemory *sharedStoreyCount;
    QSharedMemory *sharedFloor;
    QSharedMemory *sharedStatus;
    QSharedMemory *sharedRequest[2];

    int myFloor;
    int floor;
    int status;
    bool request[2];

    void readSharedInt(QSharedMemory *, int&);
    void writeSharedInt(int&, QSharedMemory *);
    void incrementAndGetSharedInt(QSharedMemory *, int&);
};
#endif // MAINWINDOW_H
