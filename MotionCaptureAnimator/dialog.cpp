#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    ui->sliderContrast->setValue((int)contrastVal);
    ui->sliderBrightness->setValue(brightnessVal);
    ui->sliderSaturation->setValue((int)saturationVal);

    ui->headLowerHSV->document()->setPlainText(scalarToText(RED_LOWER_HSV));
    ui->neckLowerHSV->document()->setPlainText(scalarToText(BLUE_LOWER_HSV));
    ui->hipsLowerHSV->document()->setPlainText(scalarToText(YELLOW_LOWER_HSV));
    ui->lhfLowerHSV->document()->setPlainText(scalarToText(GREEN_LOWER_HSV));
    ui->lekLowerHSV->document()->setPlainText(scalarToText(ORANGE_LOWER_HSV));
    ui->rhfLowerHSV->document()->setPlainText(scalarToText(PURPLE_LOWER_HSV));
    ui->rekLowerHSV->document()->setPlainText(scalarToText(PINK_LOWER_HSV));

    ui->headUpperHSV->document()->setPlainText(scalarToText(RED_UPPER_HSV));
    ui->neckUpperHSV->document()->setPlainText(scalarToText(BLUE_UPPER_HSV));
    ui->hipsUpperHSV->document()->setPlainText(scalarToText(YELLOW_UPPER_HSV));
    ui->lhfUpperHSV->document()->setPlainText(scalarToText(GREEN_UPPER_HSV));
    ui->lekUpperHSV->document()->setPlainText(scalarToText(ORANGE_UPPER_HSV));
    ui->rhfUpperHSV->document()->setPlainText(scalarToText(PURPLE_UPPER_HSV));
    ui->rekUpperHSV->document()->setPlainText(scalarToText(PINK_UPPER_HSV));

    tempContrast = contrastVal;
    tempBrightness = brightnessVal;
    tempSaturation = saturationVal;
}

QString Dialog::scalarToText(Scalar scalarInput)
{
    String tempTextOutput;
    QString textOutput;

    tempTextOutput = "( " + std::to_string((int)scalarInput[0]) + " , "
            + std::to_string((int)scalarInput[1]) + " , " + std::to_string((int)scalarInput[2]) + " )";

    textOutput = QString::fromStdString(tempTextOutput);
    return textOutput;
}

Scalar Dialog::textToScalar(QString textInput)
{
    Scalar scalarOutput;
    QStringList valueList;

    textInput.remove(QChar(' ', Qt::CaseInsensitive));
    textInput.remove(QChar('(', Qt::CaseInsensitive));
    textInput.remove(QChar(')', Qt::CaseInsensitive));
    valueList = textInput.split(",",  QString::SkipEmptyParts);

    scalarOutput = Scalar(valueList[0].toDouble(), valueList[1].toDouble(), valueList[2].toDouble());

    return scalarOutput;
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::on_sliderContrast_valueChanged(int value)
{
    tempContrast = (double)value;
}

void Dialog::on_sliderBrightness_valueChanged(int value)
{
    tempBrightness = value;
}

void Dialog::on_sliderSaturation_valueChanged(int value)
{
    tempSaturation = (double)value;
}

void Dialog::on_buttonBox_accepted()
{
    contrastVal = tempContrast;
    saturationVal = tempSaturation;
    brightnessVal = tempBrightness;

    RED_LOWER_HSV = textToScalar(ui->headLowerHSV->document()->toPlainText());
    RED_UPPER_HSV = textToScalar(ui->headUpperHSV->document()->toPlainText());
    BLUE_LOWER_HSV = textToScalar(ui->neckLowerHSV->document()->toPlainText());
    BLUE_UPPER_HSV = textToScalar(ui->neckUpperHSV->document()->toPlainText());
    YELLOW_LOWER_HSV = textToScalar(ui->hipsLowerHSV->document()->toPlainText());
    YELLOW_UPPER_HSV = textToScalar(ui->hipsUpperHSV->document()->toPlainText());
    GREEN_LOWER_HSV = textToScalar(ui->lhfLowerHSV->document()->toPlainText());
    GREEN_UPPER_HSV = textToScalar(ui->lhfUpperHSV->document()->toPlainText());
    PURPLE_LOWER_HSV = textToScalar(ui->rhfLowerHSV->document()->toPlainText());
    PURPLE_UPPER_HSV = textToScalar(ui->rhfUpperHSV->document()->toPlainText());
    ORANGE_LOWER_HSV = textToScalar(ui->lekLowerHSV->document()->toPlainText());
    ORANGE_UPPER_HSV = textToScalar(ui->lekUpperHSV->document()->toPlainText());
    PINK_LOWER_HSV = textToScalar(ui->rekLowerHSV->document()->toPlainText());
    PINK_UPPER_HSV = textToScalar(ui->rekUpperHSV->document()->toPlainText());

    if (ui->characterSimple->isChecked())
        characterChoice = 0;
    else if (ui->characterMickey->isChecked())
        characterChoice = 1;
    else if (ui->characterMorty->isChecked())
        characterChoice = 2;

    if (ui->rotateVideo->isChecked())
        rotateFrames = true;

    close();
}

void Dialog::on_buttonBox_rejected()
{
    ui->sliderContrast->setValue((int)contrastVal);
    ui->sliderBrightness->setValue(brightnessVal);
    ui->sliderSaturation->setValue((int)saturationVal);

    ui->headLowerHSV->document()->setPlainText(scalarToText(RED_LOWER_HSV));
    ui->neckLowerHSV->document()->setPlainText(scalarToText(BLUE_LOWER_HSV));
    ui->hipsLowerHSV->document()->setPlainText(scalarToText(YELLOW_LOWER_HSV));
    ui->lhfLowerHSV->document()->setPlainText(scalarToText(GREEN_LOWER_HSV));
    ui->lekLowerHSV->document()->setPlainText(scalarToText(PURPLE_LOWER_HSV));
    ui->rhfLowerHSV->document()->setPlainText(scalarToText(ORANGE_LOWER_HSV));
    ui->rekLowerHSV->document()->setPlainText(scalarToText(PINK_LOWER_HSV));

    ui->headUpperHSV->document()->setPlainText(scalarToText(RED_UPPER_HSV));
    ui->neckUpperHSV->document()->setPlainText(scalarToText(BLUE_UPPER_HSV));
    ui->hipsUpperHSV->document()->setPlainText(scalarToText(YELLOW_UPPER_HSV));
    ui->lhfUpperHSV->document()->setPlainText(scalarToText(GREEN_UPPER_HSV));
    ui->lekUpperHSV->document()->setPlainText(scalarToText(PURPLE_UPPER_HSV));
    ui->rhfUpperHSV->document()->setPlainText(scalarToText(ORANGE_UPPER_HSV));
    ui->rekUpperHSV->document()->setPlainText(scalarToText(PINK_UPPER_HSV));

    if (characterChoice == 0)
        ui->characterSimple->setChecked(true);
    else if (characterChoice == 1)
        ui->characterMickey->setChecked(true);
    else if (characterChoice == 2)
        ui->characterMorty->setChecked(true);

    if (rotateFrames == true)
        ui->rotateVideo->setChecked(true);
    else ui->rotateVideo->setChecked(false);

    close();
}
