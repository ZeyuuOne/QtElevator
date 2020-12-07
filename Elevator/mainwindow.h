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
    QSharedMemory *sharedRequestUp[3];
    QSharedMemory *sharedRequestDown[3];
    QSharedMemory *sharedRequestTo[3];

    int floor;
    int status;
    int requestUp[3];
    int requestDown[3];
    int requestTo[3];

    void writeSharedInt(int&, QSharedMemory *);
    void createSharedInt(int&, QSharedMemory *);

};
#endif // MAINWINDOW_H
