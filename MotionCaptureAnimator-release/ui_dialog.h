/********************************************************************************
** Form generated from reading UI file 'dialog.ui'
**
** Created by: Qt User Interface Compiler version 5.10.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIALOG_H
#define UI_DIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Dialog
{
public:
    QWidget *gridLayoutWidget;
    QGridLayout *gridLayout;
    QLabel *label_3;
    QLabel *label_2;
    QLabel *label;
    QSlider *sliderContrast;
    QSlider *sliderSaturation;
    QSlider *sliderBrightness;
    QWidget *gridLayoutWidget_2;
    QGridLayout *gridLayout_2;
    QPlainTextEdit *headUpperHSV;
    QPlainTextEdit *lekLowerHSV;
    QPlainTextEdit *neckLowerHSV;
    QPlainTextEdit *headLowerHSV;
    QPlainTextEdit *rhfLowerHSV;
    QPlainTextEdit *lekUpperHSV;
    QLabel *label_10;
    QLabel *label_11;
    QLabel *label_8;
    QLabel *label_9;
    QLabel *label_7;
    QLabel *label_6;
    QLabel *label_12;
    QLabel *label_15;
    QLabel *label_14;
    QPlainTextEdit *hipsUpperHSV;
    QPlainTextEdit *neckUpperHSV;
    QPlainTextEdit *hipsLowerHSV;
    QPlainTextEdit *lhfLowerHSV;
    QPlainTextEdit *rekLowerHSV;
    QPlainTextEdit *lhfUpperHSV;
    QPlainTextEdit *rekUpperHSV;
    QPlainTextEdit *rhfUpperHSV;
    QLabel *label_4;
    QLabel *label_5;
    QDialogButtonBox *buttonBox;
    QLabel *label_13;
    QRadioButton *characterSimple;
    QRadioButton *characterMickey;
    QCheckBox *rotateVideo;
    QRadioButton *characterMorty;

    void setupUi(QDialog *Dialog)
    {
        if (Dialog->objectName().isEmpty())
            Dialog->setObjectName(QStringLiteral("Dialog"));
        Dialog->setEnabled(true);
        Dialog->resize(626, 530);
        gridLayoutWidget = new QWidget(Dialog);
        gridLayoutWidget->setObjectName(QStringLiteral("gridLayoutWidget"));
        gridLayoutWidget->setGeometry(QRect(30, 360, 271, 80));
        gridLayout = new QGridLayout(gridLayoutWidget);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        label_3 = new QLabel(gridLayoutWidget);
        label_3->setObjectName(QStringLiteral("label_3"));

        gridLayout->addWidget(label_3, 2, 0, 1, 1);

        label_2 = new QLabel(gridLayoutWidget);
        label_2->setObjectName(QStringLiteral("label_2"));

        gridLayout->addWidget(label_2, 0, 0, 1, 1);

        label = new QLabel(gridLayoutWidget);
        label->setObjectName(QStringLiteral("label"));

        gridLayout->addWidget(label, 1, 0, 1, 1);

        sliderContrast = new QSlider(gridLayoutWidget);
        sliderContrast->setObjectName(QStringLiteral("sliderContrast"));
        sliderContrast->setMinimum(1);
        sliderContrast->setMaximum(3);
        sliderContrast->setSingleStep(1);
        sliderContrast->setOrientation(Qt::Horizontal);

        gridLayout->addWidget(sliderContrast, 0, 2, 1, 1);

        sliderSaturation = new QSlider(gridLayoutWidget);
        sliderSaturation->setObjectName(QStringLiteral("sliderSaturation"));
        sliderSaturation->setMinimum(1);
        sliderSaturation->setMaximum(100);
        sliderSaturation->setOrientation(Qt::Horizontal);

        gridLayout->addWidget(sliderSaturation, 2, 2, 1, 1);

        sliderBrightness = new QSlider(gridLayoutWidget);
        sliderBrightness->setObjectName(QStringLiteral("sliderBrightness"));
        sliderBrightness->setMinimum(1);
        sliderBrightness->setMaximum(50);
        sliderBrightness->setOrientation(Qt::Horizontal);

        gridLayout->addWidget(sliderBrightness, 1, 2, 1, 1);

        gridLayoutWidget_2 = new QWidget(Dialog);
        gridLayoutWidget_2->setObjectName(QStringLiteral("gridLayoutWidget_2"));
        gridLayoutWidget_2->setGeometry(QRect(30, 40, 550, 272));
        gridLayout_2 = new QGridLayout(gridLayoutWidget_2);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        gridLayout_2->setContentsMargins(0, 0, 0, 0);
        headUpperHSV = new QPlainTextEdit(gridLayoutWidget_2);
        headUpperHSV->setObjectName(QStringLiteral("headUpperHSV"));
        headUpperHSV->setMaximumSize(QSize(170, 28));

        gridLayout_2->addWidget(headUpperHSV, 1, 2, 1, 1);

        lekLowerHSV = new QPlainTextEdit(gridLayoutWidget_2);
        lekLowerHSV->setObjectName(QStringLiteral("lekLowerHSV"));
        lekLowerHSV->setMaximumSize(QSize(170, 28));

        gridLayout_2->addWidget(lekLowerHSV, 6, 1, 1, 1);

        neckLowerHSV = new QPlainTextEdit(gridLayoutWidget_2);
        neckLowerHSV->setObjectName(QStringLiteral("neckLowerHSV"));
        neckLowerHSV->setMaximumSize(QSize(170, 28));

        gridLayout_2->addWidget(neckLowerHSV, 2, 1, 1, 1);

        headLowerHSV = new QPlainTextEdit(gridLayoutWidget_2);
        headLowerHSV->setObjectName(QStringLiteral("headLowerHSV"));
        headLowerHSV->setMaximumSize(QSize(170, 28));

        gridLayout_2->addWidget(headLowerHSV, 1, 1, 1, 1);

        rhfLowerHSV = new QPlainTextEdit(gridLayoutWidget_2);
        rhfLowerHSV->setObjectName(QStringLiteral("rhfLowerHSV"));
        rhfLowerHSV->setMaximumSize(QSize(170, 28));

        gridLayout_2->addWidget(rhfLowerHSV, 7, 1, 1, 1);

        lekUpperHSV = new QPlainTextEdit(gridLayoutWidget_2);
        lekUpperHSV->setObjectName(QStringLiteral("lekUpperHSV"));
        lekUpperHSV->setMaximumSize(QSize(170, 28));

        gridLayout_2->addWidget(lekUpperHSV, 6, 2, 1, 1);

        label_10 = new QLabel(gridLayoutWidget_2);
        label_10->setObjectName(QStringLiteral("label_10"));

        gridLayout_2->addWidget(label_10, 6, 0, 1, 1);

        label_11 = new QLabel(gridLayoutWidget_2);
        label_11->setObjectName(QStringLiteral("label_11"));

        gridLayout_2->addWidget(label_11, 7, 0, 1, 1);

        label_8 = new QLabel(gridLayoutWidget_2);
        label_8->setObjectName(QStringLiteral("label_8"));

        gridLayout_2->addWidget(label_8, 3, 0, 1, 1);

        label_9 = new QLabel(gridLayoutWidget_2);
        label_9->setObjectName(QStringLiteral("label_9"));

        gridLayout_2->addWidget(label_9, 5, 0, 1, 1);

        label_7 = new QLabel(gridLayoutWidget_2);
        label_7->setObjectName(QStringLiteral("label_7"));

        gridLayout_2->addWidget(label_7, 2, 0, 1, 1);

        label_6 = new QLabel(gridLayoutWidget_2);
        label_6->setObjectName(QStringLiteral("label_6"));

        gridLayout_2->addWidget(label_6, 1, 0, 1, 1);

        label_12 = new QLabel(gridLayoutWidget_2);
        label_12->setObjectName(QStringLiteral("label_12"));

        gridLayout_2->addWidget(label_12, 8, 0, 1, 1);

        label_15 = new QLabel(gridLayoutWidget_2);
        label_15->setObjectName(QStringLiteral("label_15"));
        label_15->setAlignment(Qt::AlignCenter);

        gridLayout_2->addWidget(label_15, 0, 2, 1, 1);

        label_14 = new QLabel(gridLayoutWidget_2);
        label_14->setObjectName(QStringLiteral("label_14"));
        label_14->setAlignment(Qt::AlignCenter);

        gridLayout_2->addWidget(label_14, 0, 1, 1, 1);

        hipsUpperHSV = new QPlainTextEdit(gridLayoutWidget_2);
        hipsUpperHSV->setObjectName(QStringLiteral("hipsUpperHSV"));
        hipsUpperHSV->setMaximumSize(QSize(170, 28));

        gridLayout_2->addWidget(hipsUpperHSV, 3, 2, 1, 1);

        neckUpperHSV = new QPlainTextEdit(gridLayoutWidget_2);
        neckUpperHSV->setObjectName(QStringLiteral("neckUpperHSV"));
        neckUpperHSV->setMaximumSize(QSize(170, 28));

        gridLayout_2->addWidget(neckUpperHSV, 2, 2, 1, 1);

        hipsLowerHSV = new QPlainTextEdit(gridLayoutWidget_2);
        hipsLowerHSV->setObjectName(QStringLiteral("hipsLowerHSV"));
        hipsLowerHSV->setMaximumSize(QSize(170, 28));

        gridLayout_2->addWidget(hipsLowerHSV, 3, 1, 1, 1);

        lhfLowerHSV = new QPlainTextEdit(gridLayoutWidget_2);
        lhfLowerHSV->setObjectName(QStringLiteral("lhfLowerHSV"));
        lhfLowerHSV->setMaximumSize(QSize(170, 28));

        gridLayout_2->addWidget(lhfLowerHSV, 5, 1, 1, 1);

        rekLowerHSV = new QPlainTextEdit(gridLayoutWidget_2);
        rekLowerHSV->setObjectName(QStringLiteral("rekLowerHSV"));
        rekLowerHSV->setMaximumSize(QSize(170, 28));

        gridLayout_2->addWidget(rekLowerHSV, 8, 1, 1, 1);

        lhfUpperHSV = new QPlainTextEdit(gridLayoutWidget_2);
        lhfUpperHSV->setObjectName(QStringLiteral("lhfUpperHSV"));
        lhfUpperHSV->setMaximumSize(QSize(170, 28));

        gridLayout_2->addWidget(lhfUpperHSV, 5, 2, 1, 1);

        rekUpperHSV = new QPlainTextEdit(gridLayoutWidget_2);
        rekUpperHSV->setObjectName(QStringLiteral("rekUpperHSV"));
        rekUpperHSV->setMaximumSize(QSize(170, 28));
        rekUpperHSV->setLineWidth(1);

        gridLayout_2->addWidget(rekUpperHSV, 8, 2, 1, 1);

        rhfUpperHSV = new QPlainTextEdit(gridLayoutWidget_2);
        rhfUpperHSV->setObjectName(QStringLiteral("rhfUpperHSV"));
        rhfUpperHSV->setMaximumSize(QSize(170, 28));

        gridLayout_2->addWidget(rhfUpperHSV, 7, 2, 1, 1);

        label_4 = new QLabel(Dialog);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(30, 330, 181, 17));
        label_5 = new QLabel(Dialog);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setGeometry(QRect(30, 10, 351, 17));
        buttonBox = new QDialogButtonBox(Dialog);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setGeometry(QRect(430, 490, 166, 25));
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Save);
        label_13 = new QLabel(Dialog);
        label_13->setObjectName(QStringLiteral("label_13"));
        label_13->setGeometry(QRect(320, 330, 131, 17));
        characterSimple = new QRadioButton(Dialog);
        characterSimple->setObjectName(QStringLiteral("characterSimple"));
        characterSimple->setGeometry(QRect(340, 360, 112, 23));
        characterMickey = new QRadioButton(Dialog);
        characterMickey->setObjectName(QStringLiteral("characterMickey"));
        characterMickey->setGeometry(QRect(340, 390, 121, 23));
        characterMickey->setChecked(true);
        rotateVideo = new QCheckBox(Dialog);
        rotateVideo->setObjectName(QStringLiteral("rotateVideo"));
        rotateVideo->setGeometry(QRect(30, 460, 191, 23));
        characterMorty = new QRadioButton(Dialog);
        characterMorty->setObjectName(QStringLiteral("characterMorty"));
        characterMorty->setGeometry(QRect(340, 420, 112, 23));

        retranslateUi(Dialog);

        QMetaObject::connectSlotsByName(Dialog);
    } // setupUi

    void retranslateUi(QDialog *Dialog)
    {
        Dialog->setWindowTitle(QApplication::translate("Dialog", "Video Settings", nullptr));
        label_3->setText(QApplication::translate("Dialog", "Saturation", nullptr));
        label_2->setText(QApplication::translate("Dialog", "Contrast", nullptr));
        label->setText(QApplication::translate("Dialog", "Brightness", nullptr));
        label_10->setText(QApplication::translate("Dialog", "Left Elbow&Knee", nullptr));
        label_11->setText(QApplication::translate("Dialog", "Right Hand&Foot", nullptr));
        label_8->setText(QApplication::translate("Dialog", "Hips ", nullptr));
        label_9->setText(QApplication::translate("Dialog", "Left Hand&Foot", nullptr));
        label_7->setText(QApplication::translate("Dialog", "Neck ", nullptr));
        label_6->setText(QApplication::translate("Dialog", "Head ", nullptr));
        label_12->setText(QApplication::translate("Dialog", "Right Elbow&Knee", nullptr));
        label_15->setText(QApplication::translate("Dialog", "UPPER HSV", nullptr));
        label_14->setText(QApplication::translate("Dialog", "Lower HSV", nullptr));
        label_4->setText(QApplication::translate("Dialog", "Adjust Input Video", nullptr));
        label_5->setText(QApplication::translate("Dialog", "Adjust Color HSV Thresholds (0-179, 0-255, 0-255)", nullptr));
        label_13->setText(QApplication::translate("Dialog", "Choose Character", nullptr));
        characterSimple->setText(QApplication::translate("Dialog", "Simple", nullptr));
        characterMickey->setText(QApplication::translate("Dialog", "Mickey Mouse", nullptr));
        rotateVideo->setText(QApplication::translate("Dialog", "Rotate video 90 degrees", nullptr));
        characterMorty->setText(QApplication::translate("Dialog", "Morty", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Dialog: public Ui_Dialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOG_H
