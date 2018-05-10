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
    QPushButton *btn_retract;
    QPushButton *btn_load;
    QLabel *lbl_chessboard;
    QPushButton *btn_online;
    QLabel *lbl_background;
    QPushButton *btn_save;
    QPushButton *btn_pve;
    QPushButton *btn_ranking;
    QPushButton *btn_pve_5;
    QPushButton *btn_exit;
    QPushButton *btn_prompt;
    QPushButton *btn_giveUp;
    QPushButton *btn_restart;
    QPushButton *btn_team;
    QPushButton *btn_return;

    void setupUi(QMainWindow *MainWindowClass)
    {
        if (MainWindowClass->objectName().isEmpty())
            MainWindowClass->setObjectName(QStringLiteral("MainWindowClass"));
        MainWindowClass->resize(1600, 900);
        centralWidget = new QWidget(MainWindowClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        btn_retract = new QPushButton(centralWidget);
        btn_retract->setObjectName(QStringLiteral("btn_retract"));
        btn_retract->setGeometry(QRect(50, 580, 241, 81));
        QFont font;
        font.setFamily(QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221"));
        font.setPointSize(30);
        btn_retract->setFont(font);
        btn_retract->setStyleSheet(QString::fromUtf8("QPushButton{border-image: url(:/MainWindow/image/\346\202\224\346\243\213.PNG);}\n"
"QPushButton:hover{border-image: url(:/MainWindow/image/\346\202\224\346\243\213\357\274\210\345\270\246\351\230\264\345\275\261\357\274\211.png);}\n"
"QPushButton:pressed{border-image: url(:/MainWindow/image/\346\202\224\346\243\213.PNG);}"));
        btn_load = new QPushButton(centralWidget);
        btn_load->setObjectName(QStringLiteral("btn_load"));
        btn_load->setGeometry(QRect(50, 730, 241, 81));
        QFont font1;
        font1.setFamily(QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221"));
        font1.setPointSize(18);
        btn_load->setFont(font1);
        btn_load->setStyleSheet(QString::fromUtf8("QPushButton{border-image: url(:/MainWindow/image/\350\257\273\345\217\226\346\243\213\347\233\230.PNG);}\n"
"QPushButton:hover{border-image: url(:/MainWindow/image/\350\257\273\345\217\226\346\243\213\347\233\230\357\274\210\345\270\246\351\230\264\345\275\261\357\274\211.png);}\n"
"QPushButton:pressed{border-image: url(:/MainWindow/image/\350\257\273\345\217\226\346\243\213\347\233\230.PNG);}"));
        lbl_chessboard = new QLabel(centralWidget);
        lbl_chessboard->setObjectName(QStringLiteral("lbl_chessboard"));
        lbl_chessboard->setGeometry(QRect(350, 0, 900, 900));
        lbl_chessboard->setPixmap(QPixmap(QString::fromUtf8("image/70\351\200\217\346\230\216\345\272\246\346\243\213\347\233\230.png")));
        lbl_chessboard->setScaledContents(true);
        btn_online = new QPushButton(centralWidget);
        btn_online->setObjectName(QStringLiteral("btn_online"));
        btn_online->setGeometry(QRect(50, 580, 241, 81));
        btn_online->setFont(font1);
        btn_online->setStyleSheet(QString::fromUtf8("QPushButton{border-image: url(:/MainWindow/image/\350\201\224\346\234\272\345\257\271\346\210\230.PNG);}\n"
"QPushButton:hover{border-image: url(:/MainWindow/image/\350\201\224\346\234\272\345\257\271\346\210\230\357\274\210\345\270\246\351\230\264\345\275\261\357\274\211.png);}\n"
"QPushButton:pressed{border-image: url(:/MainWindow/image/\350\201\224\346\234\272\345\257\271\346\210\230.PNG);}"));
        lbl_background = new QLabel(centralWidget);
        lbl_background->setObjectName(QStringLiteral("lbl_background"));
        lbl_background->setGeometry(QRect(0, 0, 1600, 900));
        lbl_background->setPixmap(QPixmap(QString::fromUtf8("image/\350\203\214\346\231\257\345\233\276.jpg")));
        lbl_background->setScaledContents(true);
        btn_save = new QPushButton(centralWidget);
        btn_save->setObjectName(QStringLiteral("btn_save"));
        btn_save->setGeometry(QRect(50, 760, 241, 81));
        btn_save->setFont(font);
        btn_save->setStyleSheet(QString::fromUtf8("QPushButton{border-image: url(:/MainWindow/image/\344\277\235\345\255\230\346\243\213\347\233\230.PNG);}\n"
"QPushButton:hover{border-image: url(:/MainWindow/image/\344\277\235\345\255\230\346\243\213\347\233\230\357\274\210\345\270\246\351\230\264\345\275\261\357\274\211.png);}\n"
"QPushButton:pressed{border-image: url(:/MainWindow/image/\344\277\235\345\255\230\346\243\213\347\233\230.PNG);}"));
        btn_pve = new QPushButton(centralWidget);
        btn_pve->setObjectName(QStringLiteral("btn_pve"));
        btn_pve->setGeometry(QRect(50, 430, 241, 81));
        btn_pve->setFont(font);
        btn_pve->setStyleSheet(QString::fromUtf8("QPushButton{border-image: url(:/MainWindow/image/\344\272\272\346\234\272\345\257\271\346\210\230.PNG);}\n"
"QPushButton:hover{border-image: url(:/MainWindow/image/\344\272\272\346\234\272\345\257\271\346\210\230\357\274\210\345\270\246\351\230\264\345\275\261\357\274\211.png);}\n"
"QPushButton:pressed{border-image: url(:/MainWindow/image/\344\272\272\346\234\272\345\257\271\346\210\230.PNG);}"));
        btn_ranking = new QPushButton(centralWidget);
        btn_ranking->setObjectName(QStringLiteral("btn_ranking"));
        btn_ranking->setGeometry(QRect(1300, 400, 241, 81));
        btn_ranking->setFont(font);
        btn_ranking->setStyleSheet(QString::fromUtf8("QPushButton{border-image: url(:/MainWindow/image/\346\216\222\350\241\214\346\246\234.PNG);}\n"
"QPushButton:hover{border-image: url(:/MainWindow/image/\346\216\222\350\241\214\346\246\234\357\274\210\345\270\246\351\230\264\345\275\261\357\274\211.png);}\n"
"QPushButton:pressed{border-image: url(:/MainWindow/image/\346\216\222\350\241\214\346\246\234.PNG);}"));
        btn_pve_5 = new QPushButton(centralWidget);
        btn_pve_5->setObjectName(QStringLiteral("btn_pve_5"));
        btn_pve_5->setGeometry(QRect(1300, 580, 241, 81));
        btn_pve_5->setFont(font);
        btn_pve_5->setStyleSheet(QString::fromUtf8("QPushButton{border-image: url(:/MainWindow/image/\346\270\270\346\210\217\350\247\204\345\210\231.PNG);}\n"
"QPushButton:hover{border-image: url(:/MainWindow/image/\346\270\270\346\210\217\350\247\204\345\210\231\357\274\210\345\270\246\351\230\264\345\275\261\357\274\211.png);}\n"
"QPushButton:pressed{border-image: url(:/MainWindow/image/\346\270\270\346\210\217\350\247\204\345\210\231.PNG);}"));
        btn_exit = new QPushButton(centralWidget);
        btn_exit->setObjectName(QStringLiteral("btn_exit"));
        btn_exit->setGeometry(QRect(1300, 760, 241, 81));
        btn_exit->setFont(font);
        btn_exit->setStyleSheet(QString::fromUtf8("QPushButton{border-image: url(:/MainWindow/image/\351\200\200\345\207\272.PNG);}\n"
"QPushButton:hover{border-image: url(:/MainWindow/image/\351\200\200\345\207\272\357\274\210\345\270\246\351\230\264\345\275\261\357\274\211.png);}\n"
"QPushButton:pressed{border-image: url(:/MainWindow/image/\351\200\200\345\207\272.PNG);}"));
        btn_prompt = new QPushButton(centralWidget);
        btn_prompt->setObjectName(QStringLiteral("btn_prompt"));
        btn_prompt->setGeometry(QRect(50, 490, 241, 81));
        btn_prompt->setFont(font);
        btn_prompt->setStyleSheet(QString::fromUtf8("QPushButton{border-image: url(:/MainWindow/image/\346\217\220\347\244\272.PNG);}\n"
"QPushButton:hover{border-image: url(:/MainWindow/image/\346\217\220\347\244\272\357\274\210\345\270\246\351\230\264\345\275\261\357\274\211.png);}\n"
"QPushButton:pressed{border-image: url(:/MainWindow/image/\346\217\220\347\244\272.PNG);}"));
        btn_giveUp = new QPushButton(centralWidget);
        btn_giveUp->setObjectName(QStringLiteral("btn_giveUp"));
        btn_giveUp->setGeometry(QRect(50, 670, 241, 81));
        btn_giveUp->setFont(font);
        btn_giveUp->setStyleSheet(QString::fromUtf8("QPushButton{border-image: url(:/MainWindow/image/\350\256\244\350\276\223.PNG);}\n"
"QPushButton:hover{border-image: url(:/MainWindow/image/\350\256\244\350\276\223\357\274\210\345\270\246\351\230\264\345\275\261\357\274\211.png);}\n"
"QPushButton:pressed{border-image: url(:/MainWindow/image/\350\256\244\350\276\223.PNG);}"));
        btn_restart = new QPushButton(centralWidget);
        btn_restart->setObjectName(QStringLiteral("btn_restart"));
        btn_restart->setGeometry(QRect(50, 400, 241, 81));
        btn_restart->setFont(font);
        btn_restart->setStyleSheet(QString::fromUtf8("QPushButton{border-image: url(:/MainWindow/image/\351\207\215\346\226\260\345\274\200\345\247\213.PNG);}\n"
"QPushButton:hover{border-image: url(:/MainWindow/image/\351\207\215\346\226\260\345\274\200\345\247\213\357\274\210\345\270\246\351\230\264\345\275\261\357\274\211.png);}\n"
"QPushButton:pressed{border-image: url(:/MainWindow/image/\351\207\215\346\226\260\345\274\200\345\247\213.PNG);}"));
        btn_team = new QPushButton(centralWidget);
        btn_team->setObjectName(QStringLiteral("btn_team"));
        btn_team->setGeometry(QRect(1300, 490, 241, 81));
        btn_team->setFont(font);
        btn_team->setStyleSheet(QString::fromUtf8("QPushButton{border-image: url(:/MainWindow/image/\345\210\266\344\275\234\345\233\242\351\230\237.PNG);}\n"
"QPushButton:hover{border-image: url(:/MainWindow/image/\345\210\266\344\275\234\345\233\242\351\230\237\357\274\210\345\270\246\351\230\264\345\275\261\357\274\211.png);}\n"
"QPushButton:pressed{border-image: url(:/MainWindow/image/\345\210\266\344\275\234\345\233\242\351\230\237.PNG);}"));
        btn_return = new QPushButton(centralWidget);
        btn_return->setObjectName(QStringLiteral("btn_return"));
        btn_return->setGeometry(QRect(1300, 670, 241, 81));
        btn_return->setFont(font);
        btn_return->setStyleSheet(QString::fromUtf8("QPushButton{border-image: url(:/MainWindow/image/\346\216\222\350\241\214\346\246\234.PNG);}\n"
"QPushButton:hover{border-image: url(:/MainWindow/image/\346\216\222\350\241\214\346\246\234\357\274\210\345\270\246\351\230\264\345\275\261\357\274\211.png);}\n"
"QPushButton:pressed{border-image: url(:/MainWindow/image/\346\216\222\350\241\214\346\246\234.PNG);}"));
        MainWindowClass->setCentralWidget(centralWidget);
        lbl_background->raise();
        lbl_chessboard->raise();
        btn_retract->raise();
        btn_load->raise();
        btn_online->raise();
        btn_save->raise();
        btn_pve->raise();
        btn_ranking->raise();
        btn_pve_5->raise();
        btn_exit->raise();
        btn_prompt->raise();
        btn_giveUp->raise();
        btn_restart->raise();
        btn_team->raise();
        btn_return->raise();

        retranslateUi(MainWindowClass);
        QObject::connect(btn_retract, SIGNAL(clicked()), MainWindowClass, SLOT(buttonClicked()));

        QMetaObject::connectSlotsByName(MainWindowClass);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindowClass)
    {
        MainWindowClass->setWindowTitle(QApplication::translate("MainWindowClass", "\344\272\224\345\255\220\346\243\213\346\270\270\346\210\217", nullptr));
        btn_retract->setText(QString());
        btn_load->setText(QString());
        lbl_chessboard->setText(QString());
        btn_online->setText(QString());
        lbl_background->setText(QString());
        btn_save->setText(QString());
        btn_pve->setText(QString());
        btn_ranking->setText(QString());
        btn_pve_5->setText(QString());
        btn_exit->setText(QString());
        btn_prompt->setText(QString());
        btn_giveUp->setText(QString());
        btn_restart->setText(QString());
        btn_team->setText(QString());
        btn_return->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class MainWindowClass: public Ui_MainWindowClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
