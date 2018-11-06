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
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_d3d_practice_guiClass
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QDialog *d3d_practice_guiClass)
    {
        if (d3d_practice_guiClass->objectName().isEmpty())
            d3d_practice_guiClass->setObjectName(QStringLiteral("d3d_practice_guiClass"));
        d3d_practice_guiClass->resize(600, 400);

        retranslateUi(d3d_practice_guiClass);

        QMetaObject::connectSlotsByName(d3d_practice_guiClass);
    } // setupUi

    void retranslateUi(QDialog *d3d_practice_guiClass)
    {
        d3d_practice_guiClass->setWindowTitle(QApplication::translate("d3d_practice_guiClass", "d3d_practice_gui", nullptr));
    } // retranslateUi

};

namespace Ui {
    class d3d_practice_guiClass: public Ui_d3d_practice_guiClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_D3D_PRACTICE_GUI_H
