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
    QSharedMemory *sharedFloor;
    QSharedMemory *sharedStatus;
    QSharedMemory *sharedRequest[6];

    int floor;
    int status;
    bool request[6];

    void writeSharedInt(int&, QSharedMemory *);

};
#endif // MAINWINDOW_H