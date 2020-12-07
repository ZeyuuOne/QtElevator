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
    QPushButton *pushButtonUp;
    QPushButton *pushButtonDown;
    QLabel *labelFloor;
    QLabel *labelUp;
    QLabel *labelDown;
    QLabel *labelDoorLeft;
    QLabel *labelDoorRight;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(200, 400);
        MainWindow->setMinimumSize(QSize(200, 400));
        MainWindow->setMaximumSize(QSize(200, 400));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        centralwidget->setMinimumSize(QSize(0, 0));
        centralwidget->setMaximumSize(QSize(400, 800));
        pushButtonUp = new QPushButton(centralwidget);
        pushButtonUp->setObjectName(QString::fromUtf8("pushButtonUp"));
        pushButtonUp->setGeometry(QRect(75, 250, 50, 50));
        QFont font;
        font.setFamily(QString::fromUtf8("Franklin Gothic Demi Cond"));
        font.setPointSize(18);
        pushButtonUp->setFont(font);
        pushButtonUp->setCheckable(true);
        pushButtonUp->setAutoRepeat(true);
        pushButtonUp->setAutoExclusive(false);
        pushButtonUp->setAutoRepeatDelay(50);
        pushButtonUp->setAutoRepeatInterval(50);
        pushButtonDown = new QPushButton(centralwidget);
        pushButtonDown->setObjectName(QString::fromUtf8("pushButtonDown"));
        pushButtonDown->setGeometry(QRect(75, 320, 50, 50));
        pushButtonDown->setFont(font);
        pushButtonDown->setCheckable(true);
        pushButtonDown->setAutoRepeat(true);
        pushButtonDown->setAutoExclusive(false);
        pushButtonDown->setAutoRepeatDelay(50);
        pushButtonDown->setAutoRepeatInterval(50);
        labelFloor = new QLabel(centralwidget);
        labelFloor->setObjectName(QString::fromUtf8("labelFloor"));
        labelFloor->setGeometry(QRect(40, 30, 120, 190));
        QFont font1;
        font1.setFamily(QString::fromUtf8("Bahnschrift SemiCondensed"));
        font1.setPointSize(60);
        labelFloor->setFont(font1);
        labelFloor->setToolTipDuration(0);
        labelFloor->setAutoFillBackground(false);
        labelFloor->setStyleSheet(QString::fromUtf8("QLabel{background-color:rgb(0,0,0);color:rgb(239, 239, 239)}"));
        labelFloor->setAlignment(Qt::AlignCenter);
        labelFloor->setIndent(0);
        labelUp = new QLabel(centralwidget);
        labelUp->setObjectName(QString::fromUtf8("labelUp"));
        labelUp->setGeometry(QRect(40, 60, 120, 30));
        QFont font2;
        font2.setFamily(QString::fromUtf8("Franklin Gothic Demi Cond"));
        font2.setPointSize(14);
        labelUp->setFont(font2);
        labelUp->setToolTipDuration(0);
        labelUp->setAutoFillBackground(false);
        labelUp->setStyleSheet(QString::fromUtf8("QLabel{background-color:rgb(0,0,0);color:rgb(239, 239, 239)}"));
        labelUp->setAlignment(Qt::AlignCenter);
        labelUp->setIndent(0);
        labelDown = new QLabel(centralwidget);
        labelDown->setObjectName(QString::fromUtf8("labelDown"));
        labelDown->setGeometry(QRect(40, 151, 120, 30));
        labelDown->setFont(font2);
        labelDown->setToolTipDuration(0);
        labelDown->setAutoFillBackground(false);
        labelDown->setStyleSheet(QString::fromUtf8("QLabel{background-color:rgb(0,0,0);color:rgb(239, 239, 239)}"));
        labelDown->setAlignment(Qt::AlignCenter);
        labelDown->setIndent(0);
        labelDoorLeft = new QLabel(centralwidget);
        labelDoorLeft->setObjectName(QString::fromUtf8("labelDoorLeft"));
        labelDoorLeft->setGeometry(QRect(59, 190, 41, 20));
        QFont font3;
        font3.setFamily(QString::fromUtf8("Bahnschrift"));
        font3.setPointSize(20);
        font3.setBold(false);
        font3.setWeight(50);
        labelDoorLeft->setFont(font3);
        labelDoorLeft->setToolTipDuration(0);
        labelDoorLeft->setAutoFillBackground(false);
        labelDoorLeft->setStyleSheet(QString::fromUtf8("QLabel{background-color:rgb(0,0,0);color:rgb(239, 239, 239)}"));
        labelDoorLeft->setAlignment(Qt::AlignCenter);
        labelDoorLeft->setIndent(0);
        labelDoorRight = new QLabel(centralwidget);
        labelDoorRight->setObjectName(QString::fromUtf8("labelDoorRight"));
        labelDoorRight->setGeometry(QRect(100, 190, 41, 20));
        labelDoorRight->setFont(font3);
        labelDoorRight->setToolTipDuration(0);
        labelDoorRight->setAutoFillBackground(false);
        labelDoorRight->setStyleSheet(QString::fromUtf8("QLabel{background-color:rgb(0,0,0);color:rgb(239, 239, 239)}"));
        labelDoorRight->setAlignment(Qt::AlignCenter);
        labelDoorRight->setIndent(0);
        MainWindow->setCentralWidget(centralwidget);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        pushButtonUp->setText(QCoreApplication::translate("MainWindow", "\342\226\262", nullptr));
        pushButtonDown->setText(QCoreApplication::translate("MainWindow", "\342\226\274", nullptr));
        labelFloor->setText(QCoreApplication::translate("MainWindow", "E", nullptr));
        labelUp->setText(QCoreApplication::translate("MainWindow", "\342\226\262", nullptr));
        labelDown->setText(QCoreApplication::translate("MainWindow", "\342\226\274", nullptr));
        labelDoorLeft->setText(QCoreApplication::translate("MainWindow", "<<", nullptr));
        labelDoorRight->setText(QCoreApplication::translate("MainWindow", ">>", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
