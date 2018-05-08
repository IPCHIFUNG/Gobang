/********************************************************************************
** Form generated from reading UI file 'MainWindow.ui'
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
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindowClass
{
public:
    QWidget *centralWidget;
    QLabel *label;
    QPushButton *Button_PVE;
    QPushButton *Button_PVP;
    QPushButton *Button_Load;
    QPushButton *Button_Ranking;
    QPushButton *Button_Exit;

    void setupUi(QMainWindow *MainWindowClass)
    {
        if (MainWindowClass->objectName().isEmpty())
            MainWindowClass->setObjectName(QStringLiteral("MainWindowClass"));
        MainWindowClass->resize(600, 392);
        centralWidget = new QWidget(MainWindowClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        label = new QLabel(centralWidget);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(200, 20, 191, 41));
        QFont font;
        font.setFamily(QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221"));
        font.setPointSize(28);
        label->setFont(font);
        Button_PVE = new QPushButton(centralWidget);
        Button_PVE->setObjectName(QStringLiteral("Button_PVE"));
        Button_PVE->setGeometry(QRect(230, 90, 121, 41));
        QFont font1;
        font1.setFamily(QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221"));
        font1.setPointSize(18);
        Button_PVE->setFont(font1);
        Button_PVP = new QPushButton(centralWidget);
        Button_PVP->setObjectName(QStringLiteral("Button_PVP"));
        Button_PVP->setGeometry(QRect(230, 150, 121, 41));
        Button_PVP->setFont(font1);
        Button_Load = new QPushButton(centralWidget);
        Button_Load->setObjectName(QStringLiteral("Button_Load"));
        Button_Load->setGeometry(QRect(230, 210, 121, 41));
        Button_Load->setFont(font1);
        Button_Ranking = new QPushButton(centralWidget);
        Button_Ranking->setObjectName(QStringLiteral("Button_Ranking"));
        Button_Ranking->setGeometry(QRect(230, 270, 121, 41));
        Button_Ranking->setFont(font1);
        Button_Exit = new QPushButton(centralWidget);
        Button_Exit->setObjectName(QStringLiteral("Button_Exit"));
        Button_Exit->setGeometry(QRect(230, 330, 121, 41));
        Button_Exit->setFont(font1);
        MainWindowClass->setCentralWidget(centralWidget);

        retranslateUi(MainWindowClass);
        QObject::connect(Button_PVE, SIGNAL(clicked()), MainWindowClass, SLOT(buttonClicked()));

        QMetaObject::connectSlotsByName(MainWindowClass);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindowClass)
    {
        MainWindowClass->setWindowTitle(QApplication::translate("MainWindowClass", "\344\272\224\345\255\220\346\243\213\346\270\270\346\210\217", nullptr));
        label->setText(QApplication::translate("MainWindowClass", "\344\272\224\345\255\220\346\243\213\346\270\270\346\210\217", nullptr));
        Button_PVE->setText(QApplication::translate("MainWindowClass", "\344\272\272\346\234\272\345\257\271\346\210\230", nullptr));
        Button_PVP->setText(QApplication::translate("MainWindowClass", "\345\217\214\344\272\272\345\257\271\346\210\230", nullptr));
        Button_Load->setText(QApplication::translate("MainWindowClass", "\350\257\273\345\217\226\346\270\270\346\210\217", nullptr));
        Button_Ranking->setText(QApplication::translate("MainWindowClass", "\346\216\222\350\241\214\346\246\234", nullptr));
        Button_Exit->setText(QApplication::translate("MainWindowClass", "\351\200\200\345\207\272\346\270\270\346\210\217", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindowClass: public Ui_MainWindowClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
