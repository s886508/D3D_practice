/********************************************************************************
** Form generated from reading UI file 'd3d_practice_gui.ui'
**
** Created by: Qt User Interface Compiler version 5.11.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_D3D_PRACTICE_GUI_H
#define UI_D3D_PRACTICE_GUI_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSlider>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_d3d_practice_guiClass
{
public:
    QWidget *horizontalLayoutWidget;
    QHBoxLayout *horizontalLayout_3;
    QVBoxLayout *verticalLayout_2;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *label_4;
    QVBoxLayout *verticalLayout;
    QSlider *camera_slider_rotation_x;
    QSlider *camera_slider_rotation_y;
    QSlider *camera_slider_rotation_z;
    QLabel *label;
    QLabel *label_5;
    QWidget *horizontalLayoutWidget_2;
    QHBoxLayout *horizontalLayout_4;
    QVBoxLayout *verticalLayout_3;
    QLabel *label_6;
    QLabel *label_7;
    QLabel *label_8;
    QVBoxLayout *verticalLayout_4;
    QSlider *camera_slider_position_x;
    QSlider *camera_slider_position_y;
    QSlider *camera_slider_position_z;

    void setupUi(QDialog *d3d_practice_guiClass)
    {
        if (d3d_practice_guiClass->objectName().isEmpty())
            d3d_practice_guiClass->setObjectName(QStringLiteral("d3d_practice_guiClass"));
        d3d_practice_guiClass->resize(600, 400);
        horizontalLayoutWidget = new QWidget(d3d_practice_guiClass);
        horizontalLayoutWidget->setObjectName(QStringLiteral("horizontalLayoutWidget"));
        horizontalLayoutWidget->setGeometry(QRect(373, 150, 221, 110));
        horizontalLayout_3 = new QHBoxLayout(horizontalLayoutWidget);
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        horizontalLayout_3->setContentsMargins(0, 0, 0, 0);
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        label_2 = new QLabel(horizontalLayoutWidget);
        label_2->setObjectName(QStringLiteral("label_2"));

        verticalLayout_2->addWidget(label_2);

        label_3 = new QLabel(horizontalLayoutWidget);
        label_3->setObjectName(QStringLiteral("label_3"));

        verticalLayout_2->addWidget(label_3);

        label_4 = new QLabel(horizontalLayoutWidget);
        label_4->setObjectName(QStringLiteral("label_4"));

        verticalLayout_2->addWidget(label_4);


        horizontalLayout_3->addLayout(verticalLayout_2);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        camera_slider_rotation_x = new QSlider(horizontalLayoutWidget);
        camera_slider_rotation_x->setObjectName(QStringLiteral("camera_slider_rotation_x"));
        camera_slider_rotation_x->setMinimum(-360);
        camera_slider_rotation_x->setMaximum(360);
        camera_slider_rotation_x->setOrientation(Qt::Horizontal);

        verticalLayout->addWidget(camera_slider_rotation_x);

        camera_slider_rotation_y = new QSlider(horizontalLayoutWidget);
        camera_slider_rotation_y->setObjectName(QStringLiteral("camera_slider_rotation_y"));
        camera_slider_rotation_y->setMinimum(-360);
        camera_slider_rotation_y->setMaximum(360);
        camera_slider_rotation_y->setOrientation(Qt::Horizontal);

        verticalLayout->addWidget(camera_slider_rotation_y);

        camera_slider_rotation_z = new QSlider(horizontalLayoutWidget);
        camera_slider_rotation_z->setObjectName(QStringLiteral("camera_slider_rotation_z"));
        camera_slider_rotation_z->setMinimum(-360);
        camera_slider_rotation_z->setMaximum(360);
        camera_slider_rotation_z->setOrientation(Qt::Horizontal);

        verticalLayout->addWidget(camera_slider_rotation_z);


        horizontalLayout_3->addLayout(verticalLayout);

        label = new QLabel(d3d_practice_guiClass);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(451, 130, 80, 20));
        label_5 = new QLabel(d3d_practice_guiClass);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setGeometry(QRect(451, 260, 80, 20));
        horizontalLayoutWidget_2 = new QWidget(d3d_practice_guiClass);
        horizontalLayoutWidget_2->setObjectName(QStringLiteral("horizontalLayoutWidget_2"));
        horizontalLayoutWidget_2->setGeometry(QRect(373, 280, 221, 110));
        horizontalLayout_4 = new QHBoxLayout(horizontalLayoutWidget_2);
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        horizontalLayout_4->setContentsMargins(0, 0, 0, 0);
        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        label_6 = new QLabel(horizontalLayoutWidget_2);
        label_6->setObjectName(QStringLiteral("label_6"));

        verticalLayout_3->addWidget(label_6);

        label_7 = new QLabel(horizontalLayoutWidget_2);
        label_7->setObjectName(QStringLiteral("label_7"));

        verticalLayout_3->addWidget(label_7);

        label_8 = new QLabel(horizontalLayoutWidget_2);
        label_8->setObjectName(QStringLiteral("label_8"));

        verticalLayout_3->addWidget(label_8);


        horizontalLayout_4->addLayout(verticalLayout_3);

        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setSpacing(6);
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        camera_slider_position_x = new QSlider(horizontalLayoutWidget_2);
        camera_slider_position_x->setObjectName(QStringLiteral("camera_slider_position_x"));
        camera_slider_position_x->setMinimum(-360);
        camera_slider_position_x->setMaximum(360);
        camera_slider_position_x->setOrientation(Qt::Horizontal);

        verticalLayout_4->addWidget(camera_slider_position_x);

        camera_slider_position_y = new QSlider(horizontalLayoutWidget_2);
        camera_slider_position_y->setObjectName(QStringLiteral("camera_slider_position_y"));
        camera_slider_position_y->setMinimum(-360);
        camera_slider_position_y->setMaximum(360);
        camera_slider_position_y->setOrientation(Qt::Horizontal);

        verticalLayout_4->addWidget(camera_slider_position_y);

        camera_slider_position_z = new QSlider(horizontalLayoutWidget_2);
        camera_slider_position_z->setObjectName(QStringLiteral("camera_slider_position_z"));
        camera_slider_position_z->setMinimum(-360);
        camera_slider_position_z->setMaximum(360);
        camera_slider_position_z->setOrientation(Qt::Horizontal);

        verticalLayout_4->addWidget(camera_slider_position_z);


        horizontalLayout_4->addLayout(verticalLayout_4);


        retranslateUi(d3d_practice_guiClass);

        QMetaObject::connectSlotsByName(d3d_practice_guiClass);
    } // setupUi

    void retranslateUi(QDialog *d3d_practice_guiClass)
    {
        d3d_practice_guiClass->setWindowTitle(QApplication::translate("d3d_practice_guiClass", "d3d_practice_gui", nullptr));
        label_2->setText(QApplication::translate("d3d_practice_guiClass", "X", nullptr));
        label_3->setText(QApplication::translate("d3d_practice_guiClass", "Y", nullptr));
        label_4->setText(QApplication::translate("d3d_practice_guiClass", "Z", nullptr));
        label->setText(QApplication::translate("d3d_practice_guiClass", "Camera Rotation", nullptr));
        label_5->setText(QApplication::translate("d3d_practice_guiClass", "Camera Rotation", nullptr));
        label_6->setText(QApplication::translate("d3d_practice_guiClass", "X", nullptr));
        label_7->setText(QApplication::translate("d3d_practice_guiClass", "Y", nullptr));
        label_8->setText(QApplication::translate("d3d_practice_guiClass", "Z", nullptr));
    } // retranslateUi

};

namespace Ui {
    class d3d_practice_guiClass: public Ui_d3d_practice_guiClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_D3D_PRACTICE_GUI_H
