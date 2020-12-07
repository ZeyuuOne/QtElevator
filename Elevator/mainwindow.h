#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSharedMemory>
#include <QBuffer>
#include <QDebug>
#include <QVector>
#include <QLabel>

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
    QSharedMemory *sharedDirection;
    QSharedMemory *sharedRequestUp[3];
    QSharedMemory *sharedRequestDown[3];
    QSharedMemory *sharedRequestTo[3];
    QSharedMemory *sharedOpen;
    QSharedMemory *sharedClose;

    QLabel *labelFloor[3];
    QLabel *labelRequestTo[3];
    QLabel *labelRequestUp[3];
    QLabel *labelRequestDown[3];

    int floor;
    int status;
    int direction;
    int requestUp[3];
    int requestDown[3];
    int requestTo[3];
    int open;
    int close;
    int nextTime;

    QVector<QString> statusString;
    QVector<QString> directionString;

    void readSharedInt(QSharedMemory *, int&);
    void writeSharedInt(int&, QSharedMemory *);
    void createSharedInt(int&, QSharedMemory *);

    void refreshDisplay();

    void repeatExec();

};
#endif // MAINWINDOW_H
