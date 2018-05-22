/********************************************************************************
** Form generated from reading UI file 'ServerDialog.ui'
**
** Created by: Qt User Interface Compiler version 5.10.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SERVERDIALOG_H
#define UI_SERVERDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ServerDialog
{
public:
    QVBoxLayout *verticalLayout_2;
    QTabWidget *tabWidget;
    QWidget *tab_online;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *hl_online_id;
    QLabel *lbl_online_id;
    QLineEdit *le_online_id;
    QHBoxLayout *hi_online_pwd;
    QLabel *lbl_online_pwd;
    QLineEdit *le_online_pwd;
    QWidget *tab_server;
    QVBoxLayout *_2;
    QHBoxLayout *hl_server_port;
    QLabel *lbl_server_port;
    QLineEdit *le_server_port;
    QWidget *tab_client;
    QVBoxLayout *verticalLayout_4;
    QHBoxLayout *hl_client_ip;
    QLabel *lbl_ip;
    QLineEdit *le_ip;
    QHBoxLayout *hl_client_port;
    QLabel *lbl_client_port;
    QLineEdit *le_client_port;
    QHBoxLayout *btn_group;
    QSpacerItem *spacerItem;
    QPushButton *btn_ok;
    QPushButton *btn_cancel;

    void setupUi(QDialog *ServerDialog)
    {
        if (ServerDialog->objectName().isEmpty())
            ServerDialog->setObjectName(QStringLiteral("ServerDialog"));
        ServerDialog->resize(400, 200);
        QSizePolicy sizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(ServerDialog->sizePolicy().hasHeightForWidth());
        ServerDialog->setSizePolicy(sizePolicy);
        verticalLayout_2 = new QVBoxLayout(ServerDialog);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        tabWidget = new QTabWidget(ServerDialog);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));
        tab_online = new QWidget();
        tab_online->setObjectName(QStringLiteral("tab_online"));
        verticalLayout = new QVBoxLayout(tab_online);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        hl_online_id = new QHBoxLayout();
        hl_online_id->setObjectName(QStringLiteral("hl_online_id"));
        lbl_online_id = new QLabel(tab_online);
        lbl_online_id->setObjectName(QStringLiteral("lbl_online_id"));

        hl_online_id->addWidget(lbl_online_id);

        le_online_id = new QLineEdit(tab_online);
        le_online_id->setObjectName(QStringLiteral("le_online_id"));

        hl_online_id->addWidget(le_online_id);

        hl_online_id->setStretch(0, 1);
        hl_online_id->setStretch(1, 4);

        verticalLayout->addLayout(hl_online_id);

        hi_online_pwd = new QHBoxLayout();
        hi_online_pwd->setObjectName(QStringLiteral("hi_online_pwd"));
        lbl_online_pwd = new QLabel(tab_online);
        lbl_online_pwd->setObjectName(QStringLiteral("lbl_online_pwd"));

        hi_online_pwd->addWidget(lbl_online_pwd);

        le_online_pwd = new QLineEdit(tab_online);
        le_online_pwd->setObjectName(QStringLiteral("le_online_pwd"));

        hi_online_pwd->addWidget(le_online_pwd);

        hi_online_pwd->setStretch(0, 1);
        hi_online_pwd->setStretch(1, 4);

        verticalLayout->addLayout(hi_online_pwd);

        tabWidget->addTab(tab_online, QString());
        tab_server = new QWidget();
        tab_server->setObjectName(QStringLiteral("tab_server"));
        _2 = new QVBoxLayout(tab_server);
        _2->setObjectName(QStringLiteral("_2"));
        hl_server_port = new QHBoxLayout();
        hl_server_port->setObjectName(QStringLiteral("hl_server_port"));
        lbl_server_port = new QLabel(tab_server);
        lbl_server_port->setObjectName(QStringLiteral("lbl_server_port"));

        hl_server_port->addWidget(lbl_server_port);

        le_server_port = new QLineEdit(tab_server);
        le_server_port->setObjectName(QStringLiteral("le_server_port"));

        hl_server_port->addWidget(le_server_port);


        _2->addLayout(hl_server_port);

        tabWidget->addTab(tab_server, QString());
        tab_client = new QWidget();
        tab_client->setObjectName(QStringLiteral("tab_client"));
        verticalLayout_4 = new QVBoxLayout(tab_client);
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        hl_client_ip = new QHBoxLayout();
        hl_client_ip->setObjectName(QStringLiteral("hl_client_ip"));
        lbl_ip = new QLabel(tab_client);
        lbl_ip->setObjectName(QStringLiteral("lbl_ip"));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(lbl_ip->sizePolicy().hasHeightForWidth());
        lbl_ip->setSizePolicy(sizePolicy1);

        hl_client_ip->addWidget(lbl_ip);

        le_ip = new QLineEdit(tab_client);
        le_ip->setObjectName(QStringLiteral("le_ip"));

        hl_client_ip->addWidget(le_ip);

        hl_client_ip->setStretch(0, 1);
        hl_client_ip->setStretch(1, 4);

        verticalLayout_4->addLayout(hl_client_ip);

        hl_client_port = new QHBoxLayout();
        hl_client_port->setObjectName(QStringLiteral("hl_client_port"));
        lbl_client_port = new QLabel(tab_client);
        lbl_client_port->setObjectName(QStringLiteral("lbl_client_port"));
        sizePolicy1.setHeightForWidth(lbl_client_port->sizePolicy().hasHeightForWidth());
        lbl_client_port->setSizePolicy(sizePolicy1);

        hl_client_port->addWidget(lbl_client_port);

        le_client_port = new QLineEdit(tab_client);
        le_client_port->setObjectName(QStringLiteral("le_client_port"));

        hl_client_port->addWidget(le_client_port);

        hl_client_port->setStretch(0, 1);
        hl_client_port->setStretch(1, 4);

        verticalLayout_4->addLayout(hl_client_port);

        tabWidget->addTab(tab_client, QString());

        verticalLayout_2->addWidget(tabWidget);

        btn_group = new QHBoxLayout();
        btn_group->setSpacing(6);
        btn_group->setObjectName(QStringLiteral("btn_group"));
        btn_group->setContentsMargins(0, 0, 0, 0);
        spacerItem = new QSpacerItem(131, 31, QSizePolicy::Expanding, QSizePolicy::Minimum);

        btn_group->addItem(spacerItem);

        btn_ok = new QPushButton(ServerDialog);
        btn_ok->setObjectName(QStringLiteral("btn_ok"));
        QSizePolicy sizePolicy2(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(btn_ok->sizePolicy().hasHeightForWidth());
        btn_ok->setSizePolicy(sizePolicy2);
        btn_ok->setMinimumSize(QSize(100, 0));

        btn_group->addWidget(btn_ok);

        btn_cancel = new QPushButton(ServerDialog);
        btn_cancel->setObjectName(QStringLiteral("btn_cancel"));
        sizePolicy2.setHeightForWidth(btn_cancel->sizePolicy().hasHeightForWidth());
        btn_cancel->setSizePolicy(sizePolicy2);
        btn_cancel->setMinimumSize(QSize(100, 0));

        btn_group->addWidget(btn_cancel);


        verticalLayout_2->addLayout(btn_group);


        retranslateUi(ServerDialog);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(ServerDialog);
    } // setupUi

    void retranslateUi(QDialog *ServerDialog)
    {
        ServerDialog->setWindowTitle(QApplication::translate("ServerDialog", "Dialog", nullptr));
        lbl_online_id->setText(QApplication::translate("ServerDialog", "\345\270\220\345\217\267\357\274\232", nullptr));
        lbl_online_pwd->setText(QApplication::translate("ServerDialog", "\345\257\206\347\240\201\357\274\232", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_online), QApplication::translate("ServerDialog", "\347\231\273\345\275\225\346\270\270\346\210\217\345\244\247\345\216\205", nullptr));
        lbl_server_port->setText(QApplication::translate("ServerDialog", "\346\234\215\345\212\241\347\253\257\345\217\243\357\274\232", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_server), QApplication::translate("ServerDialog", "\344\275\234\344\270\272\345\261\200\345\237\237\347\275\221\344\270\273\346\234\272\345\274\200\345\247\213\346\270\270\346\210\217", nullptr));
        lbl_ip->setText(QApplication::translate("ServerDialog", "\344\270\273\346\234\272IP\357\274\232", nullptr));
        lbl_client_port->setText(QApplication::translate("ServerDialog", "\344\270\273\346\234\272\347\253\257\345\217\243\357\274\232", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_client), QApplication::translate("ServerDialog", "\350\277\236\346\216\245\350\207\263\345\261\200\345\237\237\347\275\221\344\270\273\346\234\272", nullptr));
        btn_ok->setText(QApplication::translate("ServerDialog", "\347\231\273\345\275\225", nullptr));
        btn_cancel->setText(QApplication::translate("ServerDialog", "\345\217\226\346\266\210", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ServerDialog: public Ui_ServerDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SERVERDIALOG_H
