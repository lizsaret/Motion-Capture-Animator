#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QString>
#include <QChar>
#include <iostream>
#include <global.h>

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = 0);
    ~Dialog();

private slots:

    void on_sliderContrast_valueChanged(int value);

    void on_sliderBrightness_valueChanged(int value);

    void on_sliderSaturation_valueChanged(int value);

    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

private:
    Ui::Dialog *ui;
    int tempContrast;
    int tempBrightness;
    int tempSaturation;

    Scalar textToScalar(QString textInput);
    QString scalarToText(Scalar scalarInput);
};

#endif // DIALOG_H
