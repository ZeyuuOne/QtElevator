/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QPushButton *pushButtonFloor1;
    QPushButton *pushButtonFloor2;
    QPushButton *pushButtonFloor3;
    QPushButton *pushButtonOpen;
    QPushButton *pushButtonClose;
    QLabel *labelFloor;
    QLabel *labelUpDown;
    QLabel *labelBackGround;
    QLabel *labelDoorRight;
    QLabel *labelDoorLeft;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(200, 400);
        MainWindow->setMinimumSize(QSize(200, 400));
        MainWindow->setMaximumSize(QSize(200, 400));
        MainWindow->setToolTipDuration(-1);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        pushButtonFloor1 = new QPushButton(centralwidget);
        pushButtonFloor1->setObjectName(QString::fromUtf8("pushButtonFloor1"));
        pushButtonFloor1->setGeometry(QRect(75, 250, 50, 50));
        QFont font;
        font.setFamily(QString::fromUtf8("Bahnschrift SemiLight"));
        font.setPointSize(24);
        font.setKerning(false);
        pushButtonFloor1->setFont(font);
        pushButtonFloor1->setToolTipDuration(-1);
        pushButtonFloor1->setCheckable(true);
        pushButtonFloor1->setChecked(false);
        pushButtonFloor2 = new QPushButton(centralwidget);
        pushButtonFloor2->setObjectName(QString::fromUtf8("pushButtonFloor2"));
        pushButtonFloor2->setGeometry(QRect(75, 185, 50, 50));
        pushButtonFloor2->setFont(font);
        pushButtonFloor2->setToolTipDuration(-1);
        pushButtonFloor2->setCheckable(true);
        pushButtonFloor3 = new QPushButton(centralwidget);
        pushButtonFloor3->setObjectName(QString::fromUtf8("pushButtonFloor3"));
        pushButtonFloor3->setGeometry(QRect(75, 120, 50, 50));
        pushButtonFloor3->setFont(font);
        pushButtonFloor3->setToolTipDuration(-1);
        pushButtonFloor3->setCheckable(true);
        pushButtonOpen = new QPushButton(centralwidget);
        pushButtonOpen->setObjectName(QString::fromUtf8("pushButtonOpen"));
        pushButtonOpen->setGeometry(QRect(40, 320, 50, 50));
        QFont font1;
        font1.setFamily(QString::fromUtf8("Bahnschrift SemiLight"));
        font1.setPointSize(10);
        font1.setKerning(false);
        pushButtonOpen->setFont(font1);
        pushButtonOpen->setToolTipDuration(-1);
        pushButtonOpen->setAutoRepeat(true);
        pushButtonOpen->setAutoRepeatDelay(50);
        pushButtonOpen->setAutoRepeatInterval(50);
        pushButtonClose = new QPushButton(centralwidget);
        pushButtonClose->setObjectName(QString::fromUtf8("pushButtonClose"));
        pushButtonClose->setGeometry(QRect(110, 320, 50, 50));
        pushButtonClose->setFont(font1);
        pushButtonClose->setToolTipDuration(-1);
        pushButtonClose->setAutoRepeat(true);
        pushButtonClose->setAutoRepeatDelay(50);
        pushButtonClose->setAutoRepeatInterval(50);
        labelFloor = new QLabel(centralwidget);
        labelFloor->setObjectName(QString::fromUtf8("labelFloor"));
        labelFloor->setGeometry(QRect(45, 25, 60, 66));
        QFont font2;
        font2.setFamily(QString::fromUtf8("Bahnschrift SemiLight"));
        font2.setPointSize(36);
        labelFloor->setFont(font2);
        labelFloor->setToolTipDuration(0);
        labelFloor->setStyleSheet(QString::fromUtf8("QLabel{background-color:rgb(0, 0, 0);color:rgb(239, 239, 239);}"));
        labelFloor->setAlignment(Qt::AlignCenter);
        labelFloor->setIndent(0);
        labelUpDown = new QLabel(centralwidget);
        labelUpDown->setObjectName(QString::fromUtf8("labelUpDown"));
        labelUpDown->setGeometry(QRect(100, 25, 60, 66));
        QFont font3;
        font3.setFamily(QString::fromUtf8("Franklin Gothic Demi Cond"));
        font3.setPointSize(18);
        labelUpDown->setFont(font3);
        labelUpDown->setToolTipDuration(0);
        labelUpDown->setStyleSheet(QString::fromUtf8("QLabel{background-color:rgb(0, 0, 0);color:rgb(239, 239, 239);}"));
        labelUpDown->setAlignment(Qt::AlignCenter);
        labelUpDown->setIndent(0);
        labelBackGround = new QLabel(centralwidget);
        labelBackGround->setObjectName(QString::fromUtf8("labelBackGround"));
        labelBackGround->setGeometry(QRect(25, 25, 150, 75));
        labelBackGround->setFont(font2);
        labelBackGround->setToolTipDuration(0);
        labelBackGround->setStyleSheet(QString::fromUtf8("QLabel{background-color:rgb(0, 0, 0);color:rgb(239, 239, 239);}"));
        labelBackGround->setAlignment(Qt::AlignCenter);
        labelBackGround->setIndent(0);
        labelDoorRight = new QLabel(centralwidget);
        labelDoorRight->setObjectName(QString::fromUtf8("labelDoorRight"));
        labelDoorRight->setGeometry(QRect(100, 78, 61, 20));
        QFont font4;
        font4.setFamily(QString::fromUtf8("Bahnschrift"));
        font4.setPointSize(16);
        font4.setBold(false);
        font4.setWeight(50);
        labelDoorRight->setFont(font4);
        labelDoorRight->setToolTipDuration(0);
        labelDoorRight->setAutoFillBackground(false);
        labelDoorRight->setStyleSheet(QString::fromUtf8("QLabel{background-color:rgb(0,0,0);color:rgb(239, 239, 239)}"));
        labelDoorRight->setAlignment(Qt::AlignCenter);
        labelDoorRight->setIndent(0);
        labelDoorLeft = new QLabel(centralwidget);
        labelDoorLeft->setObjectName(QString::fromUtf8("labelDoorLeft"));
        labelDoorLeft->setGeometry(QRect(39, 78, 61, 20));
        labelDoorLeft->setFont(font4);
        labelDoorLeft->setToolTipDuration(0);
        labelDoorLeft->setAutoFillBackground(false);
        labelDoorLeft->setStyleSheet(QString::fromUtf8("QLabel{background-color:rgb(0,0,0);color:rgb(239, 239, 239)}"));
        labelDoorLeft->setAlignment(Qt::AlignCenter);
        labelDoorLeft->setIndent(0);
        MainWindow->setCentralWidget(centralwidget);
        labelBackGround->raise();
        pushButtonFloor1->raise();
        pushButtonFloor2->raise();
        pushButtonFloor3->raise();
        pushButtonOpen->raise();
        pushButtonClose->raise();
        labelFloor->raise();
        labelUpDown->raise();
        labelDoorRight->raise();
        labelDoorLeft->raise();

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        pushButtonFloor1->setText(QCoreApplication::translate("MainWindow", "1", nullptr));
        pushButtonFloor2->setText(QCoreApplication::translate("MainWindow", "2", nullptr));
        pushButtonFloor3->setText(QCoreApplication::translate("MainWindow", "3", nullptr));
        pushButtonOpen->setText(QCoreApplication::translate("MainWindow", "OPEN", nullptr));
        pushButtonClose->setText(QCoreApplication::translate("MainWindow", "CLOSE", nullptr));
        labelFloor->setText(QCoreApplication::translate("MainWindow", "E", nullptr));
        labelUpDown->setText(QCoreApplication::translate("MainWindow", "\342\226\262", nullptr));
        labelBackGround->setText(QString());
        labelDoorRight->setText(QCoreApplication::translate("MainWindow", ">>", nullptr));
        labelDoorLeft->setText(QCoreApplication::translate("MainWindow", "<<", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
