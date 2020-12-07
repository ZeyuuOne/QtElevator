/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.12.10
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QLabel *labelStatusTitle;
    QLabel *labelStatus;
    QLabel *labelDirectionTitle;
    QLabel *labelDirection;
    QLabel *label3Title;
    QLabel *label3RequestTo;
    QLabel *label3Floor;
    QLabel *label3RequestDown;
    QLabel *label3RequestUp;
    QLabel *label2RequestTo;
    QLabel *label2Floor;
    QLabel *label2RequestUp;
    QLabel *label2Title;
    QLabel *label2RequestDown;
    QLabel *label1RequestTo;
    QLabel *label1Title;
    QLabel *label1RequestUp;
    QLabel *label1RequestDown;
    QLabel *label1Floor;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(200, 190);
        MainWindow->setMinimumSize(QSize(200, 190));
        MainWindow->setMaximumSize(QSize(200, 190));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        centralwidget->setStyleSheet(QString::fromUtf8("QWidget{background-color:rgb(0, 0, 0)}"));
        labelStatusTitle = new QLabel(centralwidget);
        labelStatusTitle->setObjectName(QString::fromUtf8("labelStatusTitle"));
        labelStatusTitle->setGeometry(QRect(10, 20, 60, 20));
        QFont font;
        font.setFamily(QString::fromUtf8("Bahnschrift"));
        font.setPointSize(14);
        font.setBold(false);
        font.setWeight(50);
        labelStatusTitle->setFont(font);
        labelStatusTitle->setStyleSheet(QString::fromUtf8("QLabel{color:rgb(239,239,239)}"));
        labelStatus = new QLabel(centralwidget);
        labelStatus->setObjectName(QString::fromUtf8("labelStatus"));
        labelStatus->setGeometry(QRect(69, 20, 121, 20));
        labelStatus->setFont(font);
        labelStatus->setStyleSheet(QString::fromUtf8("QLabel{color:rgb(239,239,239)}"));
        labelStatus->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        labelDirectionTitle = new QLabel(centralwidget);
        labelDirectionTitle->setObjectName(QString::fromUtf8("labelDirectionTitle"));
        labelDirectionTitle->setGeometry(QRect(10, 45, 100, 20));
        labelDirectionTitle->setFont(font);
        labelDirectionTitle->setStyleSheet(QString::fromUtf8("QLabel{color:rgb(239,239,239)}"));
        labelDirection = new QLabel(centralwidget);
        labelDirection->setObjectName(QString::fromUtf8("labelDirection"));
        labelDirection->setGeometry(QRect(109, 45, 81, 20));
        labelDirection->setFont(font);
        labelDirection->setStyleSheet(QString::fromUtf8("QLabel{color:rgb(239,239,239)}"));
        labelDirection->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        label3Title = new QLabel(centralwidget);
        label3Title->setObjectName(QString::fromUtf8("label3Title"));
        label3Title->setGeometry(QRect(10, 70, 16, 30));
        QFont font1;
        font1.setFamily(QString::fromUtf8("Bahnschrift"));
        font1.setPointSize(20);
        font1.setBold(false);
        font1.setWeight(50);
        label3Title->setFont(font1);
        label3Title->setStyleSheet(QString::fromUtf8("QLabel{color:rgb(239,239,239)}"));
        label3Title->setAlignment(Qt::AlignCenter);
        label3RequestTo = new QLabel(centralwidget);
        label3RequestTo->setObjectName(QString::fromUtf8("label3RequestTo"));
        label3RequestTo->setGeometry(QRect(160, 70, 15, 30));
        QFont font2;
        font2.setFamily(QString::fromUtf8("Franklin Gothic Heavy"));
        font2.setPointSize(12);
        font2.setBold(false);
        font2.setWeight(50);
        label3RequestTo->setFont(font2);
        label3RequestTo->setStyleSheet(QString::fromUtf8("QLabel{color:rgb(239,239,239)}"));
        label3RequestTo->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        label3Floor = new QLabel(centralwidget);
        label3Floor->setObjectName(QString::fromUtf8("label3Floor"));
        label3Floor->setGeometry(QRect(29, 70, 130, 30));
        QFont font3;
        font3.setFamily(QString::fromUtf8("Bahnschrift"));
        font3.setPointSize(14);
        font3.setBold(true);
        font3.setWeight(75);
        label3Floor->setFont(font3);
        label3Floor->setStyleSheet(QString::fromUtf8("QLabel{color:rgb(239,239,239)}"));
        label3Floor->setAlignment(Qt::AlignCenter);
        label3RequestDown = new QLabel(centralwidget);
        label3RequestDown->setObjectName(QString::fromUtf8("label3RequestDown"));
        label3RequestDown->setGeometry(QRect(175, 85, 15, 15));
        QFont font4;
        font4.setFamily(QString::fromUtf8("Franklin Gothic Heavy"));
        font4.setPointSize(10);
        font4.setBold(false);
        font4.setWeight(50);
        label3RequestDown->setFont(font4);
        label3RequestDown->setStyleSheet(QString::fromUtf8("QLabel{color:rgb(239,239,239)}"));
        label3RequestDown->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        label3RequestUp = new QLabel(centralwidget);
        label3RequestUp->setObjectName(QString::fromUtf8("label3RequestUp"));
        label3RequestUp->setGeometry(QRect(175, 70, 15, 15));
        label3RequestUp->setFont(font4);
        label3RequestUp->setStyleSheet(QString::fromUtf8("QLabel{color:rgb(239,239,239)}"));
        label3RequestUp->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        label2RequestTo = new QLabel(centralwidget);
        label2RequestTo->setObjectName(QString::fromUtf8("label2RequestTo"));
        label2RequestTo->setGeometry(QRect(160, 105, 15, 30));
        label2RequestTo->setFont(font2);
        label2RequestTo->setStyleSheet(QString::fromUtf8("QLabel{color:rgb(239,239,239)}"));
        label2RequestTo->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        label2Floor = new QLabel(centralwidget);
        label2Floor->setObjectName(QString::fromUtf8("label2Floor"));
        label2Floor->setGeometry(QRect(29, 105, 130, 30));
        label2Floor->setFont(font3);
        label2Floor->setStyleSheet(QString::fromUtf8("QLabel{color:rgb(239,239,239)}"));
        label2Floor->setAlignment(Qt::AlignCenter);
        label2RequestUp = new QLabel(centralwidget);
        label2RequestUp->setObjectName(QString::fromUtf8("label2RequestUp"));
        label2RequestUp->setGeometry(QRect(175, 105, 15, 15));
        label2RequestUp->setFont(font4);
        label2RequestUp->setStyleSheet(QString::fromUtf8("QLabel{color:rgb(239,239,239)}"));
        label2RequestUp->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        label2Title = new QLabel(centralwidget);
        label2Title->setObjectName(QString::fromUtf8("label2Title"));
        label2Title->setGeometry(QRect(10, 105, 16, 30));
        label2Title->setFont(font1);
        label2Title->setStyleSheet(QString::fromUtf8("QLabel{color:rgb(239,239,239)}"));
        label2Title->setAlignment(Qt::AlignCenter);
        label2RequestDown = new QLabel(centralwidget);
        label2RequestDown->setObjectName(QString::fromUtf8("label2RequestDown"));
        label2RequestDown->setGeometry(QRect(175, 120, 15, 15));
        label2RequestDown->setFont(font4);
        label2RequestDown->setStyleSheet(QString::fromUtf8("QLabel{color:rgb(239,239,239)}"));
        label2RequestDown->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        label1RequestTo = new QLabel(centralwidget);
        label1RequestTo->setObjectName(QString::fromUtf8("label1RequestTo"));
        label1RequestTo->setGeometry(QRect(160, 140, 15, 30));
        label1RequestTo->setFont(font2);
        label1RequestTo->setStyleSheet(QString::fromUtf8("QLabel{color:rgb(239,239,239)}"));
        label1RequestTo->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        label1Title = new QLabel(centralwidget);
        label1Title->setObjectName(QString::fromUtf8("label1Title"));
        label1Title->setGeometry(QRect(10, 140, 16, 30));
        label1Title->setFont(font1);
        label1Title->setStyleSheet(QString::fromUtf8("QLabel{color:rgb(239,239,239)}"));
        label1Title->setAlignment(Qt::AlignCenter);
        label1RequestUp = new QLabel(centralwidget);
        label1RequestUp->setObjectName(QString::fromUtf8("label1RequestUp"));
        label1RequestUp->setGeometry(QRect(175, 140, 15, 15));
        label1RequestUp->setFont(font4);
        label1RequestUp->setStyleSheet(QString::fromUtf8("QLabel{color:rgb(239,239,239)}"));
        label1RequestUp->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        label1RequestDown = new QLabel(centralwidget);
        label1RequestDown->setObjectName(QString::fromUtf8("label1RequestDown"));
        label1RequestDown->setGeometry(QRect(175, 155, 15, 15));
        label1RequestDown->setFont(font4);
        label1RequestDown->setStyleSheet(QString::fromUtf8("QLabel{color:rgb(239,239,239)}"));
        label1RequestDown->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        label1Floor = new QLabel(centralwidget);
        label1Floor->setObjectName(QString::fromUtf8("label1Floor"));
        label1Floor->setGeometry(QRect(29, 140, 130, 30));
        label1Floor->setFont(font3);
        label1Floor->setStyleSheet(QString::fromUtf8("QLabel{color:rgb(239,239,239)}"));
        label1Floor->setAlignment(Qt::AlignCenter);
        MainWindow->setCentralWidget(centralwidget);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", nullptr));
        labelStatusTitle->setText(QApplication::translate("MainWindow", "STATUS", nullptr));
        labelStatus->setText(QApplication::translate("MainWindow", "OPENING", nullptr));
        labelDirectionTitle->setText(QApplication::translate("MainWindow", "DIRECTION", nullptr));
        labelDirection->setText(QApplication::translate("MainWindow", "UP", nullptr));
        label3Title->setText(QApplication::translate("MainWindow", "3", nullptr));
        label3RequestTo->setText(QApplication::translate("MainWindow", "\342\227\217 ", nullptr));
        label3Floor->setText(QApplication::translate("MainWindow", "\342\226\240 ", nullptr));
        label3RequestDown->setText(QApplication::translate("MainWindow", "\342\226\274", nullptr));
        label3RequestUp->setText(QApplication::translate("MainWindow", "\342\226\262", nullptr));
        label2RequestTo->setText(QApplication::translate("MainWindow", "\342\227\217 ", nullptr));
        label2Floor->setText(QApplication::translate("MainWindow", "\342\226\240 ", nullptr));
        label2RequestUp->setText(QApplication::translate("MainWindow", "\342\226\262", nullptr));
        label2Title->setText(QApplication::translate("MainWindow", "2", nullptr));
        label2RequestDown->setText(QApplication::translate("MainWindow", "\342\226\274", nullptr));
        label1RequestTo->setText(QApplication::translate("MainWindow", "\342\227\217 ", nullptr));
        label1Title->setText(QApplication::translate("MainWindow", "1", nullptr));
        label1RequestUp->setText(QApplication::translate("MainWindow", "\342\226\262", nullptr));
        label1RequestDown->setText(QApplication::translate("MainWindow", "\342\226\274", nullptr));
        label1Floor->setText(QApplication::translate("MainWindow", "\342\226\240 ", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
