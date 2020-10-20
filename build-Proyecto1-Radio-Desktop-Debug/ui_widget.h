/********************************************************************************
** Form generated from reading UI file 'widget.ui'
**
** Created by: Qt User Interface Compiler version 5.15.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WIDGET_H
#define UI_WIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListView>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Widget
{
public:
    QCheckBox *checkBox;
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout_2;
    QToolButton *toolButton;
    QLabel *label_9;
    QListView *listView_2;
    QWidget *layoutWidget1;
    QVBoxLayout *verticalLayout_3;
    QLabel *label_10;
    QProgressBar *progressBar;
    QLabel *label;
    QPushButton *PlayB;
    QListView *listView;
    QWidget *layoutWidget2;
    QHBoxLayout *horizontalLayout;
    QLabel *label_5;
    QLabel *label_8;
    QLabel *label_7;
    QLabel *label_6;
    QPushButton *PlayB_2;

    void setupUi(QWidget *Widget)
    {
        if (Widget->objectName().isEmpty())
            Widget->setObjectName(QString::fromUtf8("Widget"));
        Widget->resize(869, 623);
        Widget->setStyleSheet(QString::fromUtf8(""));
        checkBox = new QCheckBox(Widget);
        checkBox->setObjectName(QString::fromUtf8("checkBox"));
        checkBox->setGeometry(QRect(690, 540, 92, 23));
        layoutWidget = new QWidget(Widget);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(20, 40, 258, 481));
        verticalLayout_2 = new QVBoxLayout(layoutWidget);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        toolButton = new QToolButton(layoutWidget);
        toolButton->setObjectName(QString::fromUtf8("toolButton"));

        verticalLayout_2->addWidget(toolButton);

        label_9 = new QLabel(layoutWidget);
        label_9->setObjectName(QString::fromUtf8("label_9"));
        label_9->setStyleSheet(QString::fromUtf8("border-color: rgb(0, 0, 0);\n"
"background-color: rgba(255, 255, 255, 28)"));

        verticalLayout_2->addWidget(label_9);

        listView_2 = new QListView(layoutWidget);
        listView_2->setObjectName(QString::fromUtf8("listView_2"));
        listView_2->setStyleSheet(QString::fromUtf8("border-color: rgba(255, 255, 255, 28);\n"
"background-color: rgba(255, 255, 255, 28);"));

        verticalLayout_2->addWidget(listView_2);

        layoutWidget1 = new QWidget(Widget);
        layoutWidget1->setObjectName(QString::fromUtf8("layoutWidget1"));
        layoutWidget1->setGeometry(QRect(560, 540, 111, 73));
        verticalLayout_3 = new QVBoxLayout(layoutWidget1);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        verticalLayout_3->setContentsMargins(0, 0, 0, 0);
        label_10 = new QLabel(layoutWidget1);
        label_10->setObjectName(QString::fromUtf8("label_10"));
        label_10->setStyleSheet(QString::fromUtf8("border-color: rgb(0, 0, 0);\n"
"background-color: rgba(255, 255, 255, 28)"));

        verticalLayout_3->addWidget(label_10);

        progressBar = new QProgressBar(layoutWidget1);
        progressBar->setObjectName(QString::fromUtf8("progressBar"));
        progressBar->setValue(24);

        verticalLayout_3->addWidget(progressBar);

        label = new QLabel(Widget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(310, 420, 471, 81));
        label->setStyleSheet(QString::fromUtf8("background-color: rgba(41, 31, 89, 161);"));
        PlayB = new QPushButton(Widget);
        PlayB->setObjectName(QString::fromUtf8("PlayB"));
        PlayB->setGeometry(QRect(500, 450, 91, 31));
        PlayB->setStyleSheet(QString::fromUtf8(""));
        PlayB->setIconSize(QSize(111, 111));
        listView = new QListView(Widget);
        listView->setObjectName(QString::fromUtf8("listView"));
        listView->setGeometry(QRect(296, 66, 501, 451));
        layoutWidget2 = new QWidget(Widget);
        layoutWidget2->setObjectName(QString::fromUtf8("layoutWidget2"));
        layoutWidget2->setGeometry(QRect(296, 41, 501, 20));
        horizontalLayout = new QHBoxLayout(layoutWidget2);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        label_5 = new QLabel(layoutWidget2);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setStyleSheet(QString::fromUtf8("border-color: rgb(0, 0, 0);\n"
"background-color: rgba(255, 255, 255, 28)"));

        horizontalLayout->addWidget(label_5);

        label_8 = new QLabel(layoutWidget2);
        label_8->setObjectName(QString::fromUtf8("label_8"));
        label_8->setStyleSheet(QString::fromUtf8("border-color: rgb(0, 0, 0);\n"
"background-color:  rgba(255, 255, 255, 28)"));

        horizontalLayout->addWidget(label_8);

        label_7 = new QLabel(layoutWidget2);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        label_7->setStyleSheet(QString::fromUtf8("border-color: rgb(0, 0, 0);\n"
"background-color:  rgba(255, 255, 255, 28)"));

        horizontalLayout->addWidget(label_7);

        label_6 = new QLabel(layoutWidget2);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setStyleSheet(QString::fromUtf8("border-color: rgb(0, 0, 0);\n"
"background-color: rgba(255, 255, 255, 28)"));

        horizontalLayout->addWidget(label_6);

        PlayB_2 = new QPushButton(Widget);
        PlayB_2->setObjectName(QString::fromUtf8("PlayB_2"));
        PlayB_2->setGeometry(QRect(380, 450, 91, 31));
        PlayB_2->setStyleSheet(QString::fromUtf8(""));
        PlayB_2->setIconSize(QSize(111, 111));
        listView->raise();
        label->raise();
        checkBox->raise();
        layoutWidget2->raise();
        layoutWidget2->raise();
        layoutWidget2->raise();
        PlayB->raise();
        PlayB_2->raise();
        QWidget::setTabOrder(checkBox, listView);
        QWidget::setTabOrder(listView, listView_2);

        retranslateUi(Widget);

        QMetaObject::connectSlotsByName(Widget);
    } // setupUi

    void retranslateUi(QWidget *Widget)
    {
        Widget->setWindowTitle(QCoreApplication::translate("Widget", "Widget", nullptr));
        checkBox->setText(QCoreApplication::translate("Widget", "Paginaci\303\263n", nullptr));
        toolButton->setText(QCoreApplication::translate("Widget", "...", nullptr));
        label_9->setText(QCoreApplication::translate("Widget", "Directorios", nullptr));
        label_10->setText(QCoreApplication::translate("Widget", "Memoria en uso", nullptr));
        label->setText(QString());
        PlayB->setText(QCoreApplication::translate("Widget", "Play ", nullptr));
        label_5->setText(QCoreApplication::translate("Widget", "Nombre", nullptr));
        label_8->setText(QCoreApplication::translate("Widget", "Artista", nullptr));
        label_7->setText(QCoreApplication::translate("Widget", "Longitud", nullptr));
        label_6->setText(QCoreApplication::translate("Widget", "G\303\251nero", nullptr));
        PlayB_2->setText(QCoreApplication::translate("Widget", "Stop", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Widget: public Ui_Widget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIDGET_H
