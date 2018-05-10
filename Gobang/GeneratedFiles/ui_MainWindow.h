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
    QPushButton *btn_pve;
    QPushButton *btn_load;
    QPushButton *btn_ranking;
    QPushButton *btn_exit;
    QLabel *lbl_chessboard;
    QPushButton *btn_online;
    QPushButton *btn_rules;
    QLabel *lbl_background;

    void setupUi(QMainWindow *MainWindowClass)
    {
        if (MainWindowClass->objectName().isEmpty())
            MainWindowClass->setObjectName(QStringLiteral("MainWindowClass"));
        MainWindowClass->resize(1600, 900);
        centralWidget = new QWidget(MainWindowClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        btn_pve = new QPushButton(centralWidget);
        btn_pve->setObjectName(QStringLiteral("btn_pve"));
        btn_pve->setGeometry(QRect(50, 370, 241, 81));
        QFont font;
        font.setFamily(QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221"));
        font.setPointSize(30);
        btn_pve->setFont(font);
        btn_pve->setStyleSheet(QString::fromUtf8("QPushButton{border-image: url(:/MainWindow/image/\344\277\235\345\255\230\346\243\213\347\233\230.PNG);}\n"
"QPushButton:hover{border-image: url(:/MainWindow/image/\344\277\235\345\255\230\346\243\213\347\233\230\357\274\210\345\270\246\351\230\264\345\275\261\357\274\211.png);}\n"
"QPushButton:pressed{border-image: url(:/MainWindow/image/\344\277\235\345\255\230\346\243\213\347\233\230.PNG);}"));
        btn_load = new QPushButton(centralWidget);
        btn_load->setObjectName(QStringLiteral("btn_load"));
        btn_load->setGeometry(QRect(100, 610, 121, 41));
        QFont font1;
        font1.setFamily(QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221"));
        font1.setPointSize(18);
        btn_load->setFont(font1);
        btn_ranking = new QPushButton(centralWidget);
        btn_ranking->setObjectName(QStringLiteral("btn_ranking"));
        btn_ranking->setGeometry(QRect(1360, 620, 121, 41));
        btn_ranking->setFont(font1);
        btn_exit = new QPushButton(centralWidget);
        btn_exit->setObjectName(QStringLiteral("btn_exit"));
        btn_exit->setGeometry(QRect(1360, 710, 121, 41));
        btn_exit->setFont(font1);
        lbl_chessboard = new QLabel(centralWidget);
        lbl_chessboard->setObjectName(QStringLiteral("lbl_chessboard"));
        lbl_chessboard->setGeometry(QRect(350, 0, 900, 900));
        lbl_chessboard->setPixmap(QPixmap(QString::fromUtf8("image/70\351\200\217\346\230\216\345\272\246\346\243\213\347\233\230.png")));
        lbl_chessboard->setScaledContents(true);
        btn_online = new QPushButton(centralWidget);
        btn_online->setObjectName(QStringLiteral("btn_online"));
        btn_online->setGeometry(QRect(100, 490, 121, 41));
        btn_online->setFont(font1);
        btn_rules = new QPushButton(centralWidget);
        btn_rules->setObjectName(QStringLiteral("btn_rules"));
        btn_rules->setGeometry(QRect(1350, 530, 121, 41));
        btn_rules->setFont(font1);
        lbl_background = new QLabel(centralWidget);
        lbl_background->setObjectName(QStringLiteral("lbl_background"));
        lbl_background->setGeometry(QRect(0, 0, 1600, 900));
        lbl_background->setPixmap(QPixmap(QString::fromUtf8("image/\350\203\214\346\231\257\345\233\276.jpg")));
        lbl_background->setScaledContents(true);
        MainWindowClass->setCentralWidget(centralWidget);
        lbl_background->raise();
        lbl_chessboard->raise();
        btn_pve->raise();
        btn_load->raise();
        btn_ranking->raise();
        btn_exit->raise();
        btn_online->raise();
        btn_rules->raise();

        retranslateUi(MainWindowClass);
        QObject::connect(btn_pve, SIGNAL(clicked()), MainWindowClass, SLOT(buttonClicked()));

        QMetaObject::connectSlotsByName(MainWindowClass);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindowClass)
    {
        MainWindowClass->setWindowTitle(QApplication::translate("MainWindowClass", "\344\272\224\345\255\220\346\243\213\346\270\270\346\210\217", nullptr));
        btn_pve->setText(QString());
        btn_load->setText(QApplication::translate("MainWindowClass", "\350\257\273\345\217\226\346\270\270\346\210\217", nullptr));
        btn_ranking->setText(QApplication::translate("MainWindowClass", "\346\216\222\350\241\214\346\246\234", nullptr));
        btn_exit->setText(QApplication::translate("MainWindowClass", "\351\200\200\345\207\272\346\270\270\346\210\217", nullptr));
        lbl_chessboard->setText(QString());
        btn_online->setText(QApplication::translate("MainWindowClass", "\347\275\221\347\273\234\345\257\271\346\210\230", nullptr));
        btn_rules->setText(QApplication::translate("MainWindowClass", "\346\270\270\346\210\217\350\247\204\345\210\231", nullptr));
        lbl_background->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class MainWindowClass: public Ui_MainWindowClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
