/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.10.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QLabel *videoInput;
    QLabel *videoSticks;
    QLabel *videoShapes;
    QWidget *layoutWidget;
    QFormLayout *formLayout;
    QPushButton *buttonLoadVid;
    QPushButton *buttonPlayVid;
    QPushButton *buttonVidSettings;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(1310, 760);
        MainWindow->setMinimumSize(QSize(1310, 760));
        MainWindow->setMaximumSize(QSize(1310, 760));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        videoInput = new QLabel(centralWidget);
        videoInput->setObjectName(QStringLiteral("videoInput"));
        videoInput->setGeometry(QRect(60, 30, 350, 420));
        videoInput->setAutoFillBackground(false);
        videoInput->setStyleSheet(QStringLiteral("Background-color: #000;"));
        videoSticks = new QLabel(centralWidget);
        videoSticks->setObjectName(QStringLiteral("videoSticks"));
        videoSticks->setGeometry(QRect(490, 30, 350, 420));
        videoSticks->setAutoFillBackground(false);
        videoSticks->setStyleSheet(QStringLiteral("Background-color: #000;"));
        videoShapes = new QLabel(centralWidget);
        videoShapes->setObjectName(QStringLiteral("videoShapes"));
        videoShapes->setGeometry(QRect(920, 30, 350, 420));
        videoShapes->setAutoFillBackground(false);
        videoShapes->setStyleSheet(QStringLiteral("Background-color: #000;"));
        layoutWidget = new QWidget(centralWidget);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(490, 520, 351, 161));
        formLayout = new QFormLayout(layoutWidget);
        formLayout->setSpacing(6);
        formLayout->setContentsMargins(11, 11, 11, 11);
        formLayout->setObjectName(QStringLiteral("formLayout"));
        formLayout->setContentsMargins(0, 0, 0, 0);
        buttonLoadVid = new QPushButton(layoutWidget);
        buttonLoadVid->setObjectName(QStringLiteral("buttonLoadVid"));

        formLayout->setWidget(0, QFormLayout::SpanningRole, buttonLoadVid);

        buttonPlayVid = new QPushButton(layoutWidget);
        buttonPlayVid->setObjectName(QStringLiteral("buttonPlayVid"));

        formLayout->setWidget(1, QFormLayout::SpanningRole, buttonPlayVid);

        buttonVidSettings = new QPushButton(layoutWidget);
        buttonVidSettings->setObjectName(QStringLiteral("buttonVidSettings"));

        formLayout->setWidget(2, QFormLayout::SpanningRole, buttonVidSettings);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1310, 22));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "Motion Capture and Animation", nullptr));
        videoInput->setText(QString());
        videoSticks->setText(QString());
        videoShapes->setText(QString());
        buttonLoadVid->setText(QApplication::translate("MainWindow", "Load Input", nullptr));
        buttonPlayVid->setText(QApplication::translate("MainWindow", "Animate Video", nullptr));
        buttonVidSettings->setText(QApplication::translate("MainWindow", "Video Settings", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
