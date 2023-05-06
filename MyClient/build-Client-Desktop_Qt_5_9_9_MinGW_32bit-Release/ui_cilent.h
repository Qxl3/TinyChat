/********************************************************************************
** Form generated from reading UI file 'cilent.ui'
**
** Created by: Qt User Interface Compiler version 5.9.9
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CILENT_H
#define UI_CILENT_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Cilent
{
public:
    QLineEdit *LeName;
    QPushButton *PbConnect;
    QListWidget *LwShowFriend;
    QListWidget *LwLog;
    QLabel *LReceive;
    QTextEdit *TeSendMessage;
    QPushButton *PbSend;
    QListWidget *LwShowMessage;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;

    void setupUi(QWidget *Cilent)
    {
        if (Cilent->objectName().isEmpty())
            Cilent->setObjectName(QStringLiteral("Cilent"));
        Cilent->resize(632, 425);
        LeName = new QLineEdit(Cilent);
        LeName->setObjectName(QStringLiteral("LeName"));
        LeName->setGeometry(QRect(100, 30, 181, 31));
        PbConnect = new QPushButton(Cilent);
        PbConnect->setObjectName(QStringLiteral("PbConnect"));
        PbConnect->setGeometry(QRect(290, 30, 61, 31));
        LwShowFriend = new QListWidget(Cilent);
        LwShowFriend->setObjectName(QStringLiteral("LwShowFriend"));
        LwShowFriend->setGeometry(QRect(370, 60, 101, 331));
        LwLog = new QListWidget(Cilent);
        LwLog->setObjectName(QStringLiteral("LwLog"));
        LwLog->setGeometry(QRect(480, 60, 141, 331));
        LReceive = new QLabel(Cilent);
        LReceive->setObjectName(QStringLiteral("LReceive"));
        LReceive->setGeometry(QRect(20, 70, 72, 15));
        TeSendMessage = new QTextEdit(Cilent);
        TeSendMessage->setObjectName(QStringLiteral("TeSendMessage"));
        TeSendMessage->setGeometry(QRect(20, 290, 281, 91));
        PbSend = new QPushButton(Cilent);
        PbSend->setObjectName(QStringLiteral("PbSend"));
        PbSend->setGeometry(QRect(310, 290, 41, 91));
        LwShowMessage = new QListWidget(Cilent);
        LwShowMessage->setObjectName(QStringLiteral("LwShowMessage"));
        LwShowMessage->setGeometry(QRect(20, 90, 331, 192));
        label = new QLabel(Cilent);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(370, 34, 101, 21));
        label_2 = new QLabel(Cilent);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(481, 34, 111, 21));
        label_3 = new QLabel(Cilent);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(20, 30, 81, 31));
        QFont font;
        font.setPointSize(10);
        label_3->setFont(font);

        retranslateUi(Cilent);

        QMetaObject::connectSlotsByName(Cilent);
    } // setupUi

    void retranslateUi(QWidget *Cilent)
    {
        Cilent->setWindowTitle(QApplication::translate("Cilent", "\345\256\242\346\210\267\347\253\257", Q_NULLPTR));
        LeName->setText(QApplication::translate("Cilent", "LXQ", Q_NULLPTR));
        PbConnect->setText(QApplication::translate("Cilent", "\350\277\236\346\216\245", Q_NULLPTR));
        LReceive->setText(QApplication::translate("Cilent", "\346\216\245\346\224\266\357\274\232", Q_NULLPTR));
        PbSend->setText(QApplication::translate("Cilent", "\345\217\221\351\200\201", Q_NULLPTR));
        label->setText(QApplication::translate("Cilent", "\345\245\275\345\217\213\345\210\227\350\241\250", Q_NULLPTR));
        label_2->setText(QApplication::translate("Cilent", "\346\227\245\345\277\227\350\256\260\345\275\225", Q_NULLPTR));
        label_3->setText(QApplication::translate("Cilent", "\347\224\250\346\210\267\345\247\223\345\220\215\357\274\232", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class Cilent: public Ui_Cilent {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CILENT_H
