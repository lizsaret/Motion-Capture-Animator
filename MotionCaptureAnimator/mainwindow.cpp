#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "opencv2/opencv.hpp"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    inputPlayer = new Player();
    QObject::connect(inputPlayer, SIGNAL(outputFramesToWindow(QImage, QImage, QImage)),
                     this, SLOT(updatePlayerUI(QImage, QImage, QImage)));
    QObject::connect(inputPlayer, SIGNAL(endOfVideo()),
                     this, SLOT(restartVideo()));
    QObject::connect(inputPlayer, SIGNAL(outputsReady()),
                     this, SLOT(readyVideo()));

    ui->setupUi(this);
}

/*
    update display of videos in window
*/
void MainWindow::updatePlayerUI(QImage img1, QImage img2, QImage img3)
{
    if (!img1.isNull())
    {
        ui->videoInput->setAlignment(Qt::AlignCenter);
        ui->videoInput->setPixmap(QPixmap::fromImage(img1).scaled(ui->videoInput->size(), Qt::KeepAspectRatio, Qt::FastTransformation));
    }
    if (!img2.isNull())
    {
        ui->videoSticks->setAlignment(Qt::AlignCenter);
        ui->videoSticks->setPixmap(QPixmap::fromImage(img2).scaled(ui->videoSticks->size(), Qt::KeepAspectRatio, Qt::FastTransformation));
    }
    if (!img3.isNull())
    {
        ui->videoShapes->setAlignment(Qt::AlignCenter);
        ui->videoShapes->setPixmap(QPixmap::fromImage(img3).scaled(ui->videoShapes->size(), Qt::KeepAspectRatio, Qt::FastTransformation));
    }
}


MainWindow::~MainWindow()
{
    delete inputPlayer;
//    delete settingsDialog;
    delete ui;
}

void MainWindow::on_buttonLoadVid_clicked()
{

    QString filename = QFileDialog::getOpenFileName(this, tr("Open Video"), ".", tr("Video Files (*.avi *.mpg *.mp4)"));
    if (!filename.isEmpty()){

        if (inputPlayer->isReady()){
            ui->videoInput->clear();
            ui->videoSticks->clear();
            ui->videoShapes->clear();

            ui->buttonPlayVid->setText(tr("Animate Video"));
        }

        if (!inputPlayer->loadVideo(filename.toLatin1().data()))
        {
            QMessageBox msgBox;
            msgBox.setText("The selected video could not be opened!");
            msgBox.exec();
        }
    }

}

/*
    processes the input video if output videos are not yet ready,
    handles play/pause of videos
*/
void MainWindow::on_buttonPlayVid_clicked()
{
    if (inputPlayer->isStopped() && inputPlayer->isReady())
    {
        inputPlayer->play();
        ui->buttonPlayVid->setText(tr("Pause"));
    }else if (!inputPlayer->isStopped() && inputPlayer->isReady())
    {
        inputPlayer->stopVideo();
        ui->buttonPlayVid->setText(tr("Play"));
    } else if (inputPlayer->isStopped() && !inputPlayer->isReady())
    {
        ui->buttonPlayVid->setText(tr("Processing"));
        inputPlayer->play();
    }
}

void MainWindow::restartVideo()
{
    ui->buttonPlayVid->setText(tr("Replay"));
    inputPlayer->openVids();
}

void MainWindow::readyVideo()
{
    ui->buttonPlayVid->setText(tr("Pause"));
}

void MainWindow::on_buttonVidSettings_clicked()
{
    settingsDialog.setModal(true);
    settingsDialog.exec();
    if (inputPlayer->isReady()) {

        ui->videoInput->clear();
        ui->videoSticks->clear();
        ui->videoShapes->clear();

        inputPlayer->setReady(false);
        inputPlayer->stopVideo();
        ui->buttonPlayVid->setText(tr("Animate Video"));
    }
}
