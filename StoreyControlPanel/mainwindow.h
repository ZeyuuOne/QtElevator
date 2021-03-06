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

signals:
    void setThreadOperation(int);
    void up();
    void down();
    void upCancel();
    void downCancel();
    void open();

private:
    Ui::MainWindow *ui;
    QSharedMemory *sharedStoreyCount;
    QSharedMemory *sharedFloor;
    QSharedMemory *sharedStatus;
    QSharedMemory *sharedDirection;

    int myFloor;
    int floor;
    int status;
    int direction;
    bool buttonUpDown;
    bool buttonDownDown;

    void readSharedInt(QSharedMemory *, int&);
    void writeSharedInt(int&, QSharedMemory *);
    void incrementAndGetSharedInt(QSharedMemory *, int&);

    void refreshDisplay();

    void buttonUpClicked();
    void buttonDownClicked();

    void repeatExec();
};
#endif // MAINWINDOW_H
