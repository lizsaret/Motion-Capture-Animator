#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QMessageBox>
#include <player.h>
#include <dialog.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    //Display video frame in player UI
    void updatePlayerUI(QImage imgInput, QImage imgSticks, QImage imgShapes);
    void restartVideo();
    void readyVideo();
    void on_buttonLoadVid_clicked();
    void on_buttonPlayVid_clicked();

    void on_buttonVidSettings_clicked();

private:
    Ui::MainWindow *ui;
    Player* inputPlayer;
    Dialog settingsDialog;

};

#endif // MAINWINDOW_H
