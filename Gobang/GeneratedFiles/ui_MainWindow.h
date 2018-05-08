/********************************************************************************
** Form generated from reading UI file 'MainWindow.ui'
**
** Created by: Qt User Interface Compiler version 5.10.0
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
    QPushButton *Button_PVE;
    QPushButton *Button_PVP;
    QPushButton *Button_Load;
    QPushButton *Button_Ranking;
    QPushButton *Button_Exit;
    QLabel *label;
    QPushButton *Button_Online;
    QPushButton *Button_Rules;
    QLabel *label_2;

    void setupUi(QMainWindow *MainWindowClass)
    {
        if (MainWindowClass->objectName().isEmpty())
            MainWindowClass->setObjectName(QStringLiteral("MainWindowClass"));
        MainWindowClass->resize(1600, 900);
        centralWidget = new QWidget(MainWindowClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        Button_PVE = new QPushButton(centralWidget);
        Button_PVE->setObjectName(QStringLiteral("Button_PVE"));
        Button_PVE->setGeometry(QRect(1300, 390, 261, 111));
        QFont font;
        font.setFamily(QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221"));
        font.setPointSize(30);
        Button_PVE->setFont(font);
        Button_PVE->setStyleSheet(QString::fromUtf8("QPushButton{border-image: url(:/MainWindow/image/\344\277\235\345\255\230\346\243\213\347\233\230.PNG);}\n"
"QPushButton:hover{border-image: url(:/MainWindow/image/\344\277\235\345\255\230\346\243\213\347\233\230\357\274\210\345\270\246\351\230\264\345\275\261\357\274\211.png);}\n"
"QPushButton:pressed{border-image: url(:/MainWindow/image/\344\277\235\345\255\230\346\243\213\347\233\230.PNG);}"));
        Button_PVP = new QPushButton(centralWidget);
        Button_PVP->setObjectName(QStringLiteral("Button_PVP"));
        Button_PVP->setGeometry(QRect(1320, 520, 200, 60));
        Button_PVP->setFont(font);
        Button_Load = new QPushButton(centralWidget);
        Button_Load->setObjectName(QStringLiteral("Button_Load"));
        Button_Load->setGeometry(QRect(1350, 660, 121, 41));
        QFont font1;
        font1.setFamily(QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221"));
        font1.setPointSize(18);
        Button_Load->setFont(font1);
        Button_Ranking = new QPushButton(centralWidget);
        Button_Ranking->setObjectName(QStringLiteral("Button_Ranking"));
        Button_Ranking->setGeometry(QRect(1350, 760, 121, 41));
        Button_Ranking->setFont(font1);
        Button_Exit = new QPushButton(centralWidget);
        Button_Exit->setObjectName(QStringLiteral("Button_Exit"));
        Button_Exit->setGeometry(QRect(1350, 820, 121, 41));
        Button_Exit->setFont(font1);
        label = new QLabel(centralWidget);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(350, 0, 900, 900));
        label->setPixmap(QPixmap(QString::fromUtf8("image/70\351\200\217\346\230\216\345\272\246\346\243\213\347\233\230.png")));
        label->setScaledContents(true);
        Button_Online = new QPushButton(centralWidget);
        Button_Online->setObjectName(QStringLiteral("Button_Online"));
        Button_Online->setGeometry(QRect(1330, 610, 121, 41));
        Button_Online->setFont(font1);
        Button_Rules = new QPushButton(centralWidget);
        Button_Rules->setObjectName(QStringLiteral("Button_Rules"));
        Button_Rules->setGeometry(QRect(1350, 710, 121, 41));
        Button_Rules->setFont(font1);
        label_2 = new QLabel(centralWidget);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(0, 0, 1600, 900));
        label_2->setPixmap(QPixmap(QString::fromUtf8("image/\350\203\214\346\231\257\345\233\276.jpg")));
        label_2->setScaledContents(true);
        MainWindowClass->setCentralWidget(centralWidget);
        label_2->raise();
        label->raise();
        Button_PVE->raise();
        Button_PVP->raise();
        Button_Load->raise();
        Button_Ranking->raise();
        Button_Exit->raise();
        Button_Online->raise();
        Button_Rules->raise();

        retranslateUi(MainWindowClass);
        QObject::connect(Button_PVE, SIGNAL(clicked()), MainWindowClass, SLOT(buttonClicked()));

        QMetaObject::connectSlotsByName(MainWindowClass);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindowClass)
    {
        MainWindowClass->setWindowTitle(QApplication::translate("MainWindowClass", "\344\272\224\345\255\220\346\243\213\346\270\270\346\210\217", nullptr));
        Button_PVE->setText(QString());
        Button_PVP->setText(QApplication::translate("MainWindowClass", "\345\217\214\344\272\272\345\257\271\346\210\230", nullptr));
        Button_Load->setText(QApplication::translate("MainWindowClass", "\350\257\273\345\217\226\346\270\270\346\210\217", nullptr));
        Button_Ranking->setText(QApplication::translate("MainWindowClass", "\346\216\222\350\241\214\346\246\234", nullptr));
        Button_Exit->setText(QApplication::translate("MainWindowClass", "\351\200\200\345\207\272\346\270\270\346\210\217", nullptr));
        label->setText(QString());
        Button_Online->setText(QApplication::translate("MainWindowClass", "\347\275\221\347\273\234\345\257\271\346\210\230", nullptr));
        Button_Rules->setText(QApplication::translate("MainWindowClass", "\346\270\270\346\210\217\350\247\204\345\210\231", nullptr));
        label_2->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class MainWindowClass: public Ui_MainWindowClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
