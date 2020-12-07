#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSharedMemory>
#include <QBuffer>
#include <QDebug>
#include <QPushButton>

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
    void to(int);
    void toCancel(int);
    void open();
    void close();

private:
    Ui::MainWindow *ui;
    QSharedMemory *sharedFloor;
    QSharedMemory *sharedStatus;
    QSharedMemory *sharedDirection;

    QPushButton *pushButtonTo[3];

    int floor;
    int status;
    int direction;

    bool buttonToDown[3];

    void readSharedInt(QSharedMemory *, int&);
    void writeSharedInt(int&, QSharedMemory *);

    void refreshDisplay();

    void buttonToClicked(int);
    void buttonOpenClicked();
    void buttonCloseClicked();

    void repeatExec();
};
#endif // MAINWINDOW_H
