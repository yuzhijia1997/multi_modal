/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.2.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QWidget>
#include <mymenu.h>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *accelerateAction;
    QAction *saveAction;
    QAction *aboutAction;
    QAction *exitAction;
    QWidget *centralwidget;
    QWidget *SelectWidget;
    QLabel *selectlabel;
    QRadioButton *radioButton_face;
    QRadioButton *radioButton_fp;
    QRadioButton *radioButton_pixel;
    QRadioButton *radioButton_iris;
    QRadioButton *radioButton_feature;
    QRadioButton *radioButton_score;
    QRadioButton *radioButton_optimal;
    QWidget *ResultWidget;
    QTextBrowser *textBrowser;
    QWidget *TestWidget;
    QLabel *label;
    QGraphicsView *graphicsView_face;
    QGraphicsView *graphicsView_iris;
    QGraphicsView *graphicsView_fp;
    QPushButton *pushButtond_face;
    QPushButton *pushButtond_iris;
    QPushButton *pushButtond_fp;
    QWidget *GalleryWidget;
    QLabel *label_2;
    QGraphicsView *graphicsView_face_g;
    QGraphicsView *graphicsView_iris_g;
    QGraphicsView *graphicsView_fp_g;
    QLabel *label_3;
    QWidget *FunctionWidget;
    QPushButton *pushButtond_gallery;
    QLabel *label_4;
    QTextBrowser *galleryTextBrowser;
    QPushButton *pushButtond_up;
    QPushButton *pushButtond_down;
    QLabel *label_5;
    QLabel *label_6;
    QLabel *label_7;
    QSpinBox *spinBox;
    QPushButton *pushButtond_res;
    QMenuBar *menubar;
    QMenu *helpMenu;
    MyMenu *settingMenu;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(960, 780);
        accelerateAction = new QAction(MainWindow);
        accelerateAction->setObjectName(QString::fromUtf8("accelerateAction"));
        accelerateAction->setCheckable(true);
        saveAction = new QAction(MainWindow);
        saveAction->setObjectName(QString::fromUtf8("saveAction"));
        saveAction->setCheckable(true);
        aboutAction = new QAction(MainWindow);
        aboutAction->setObjectName(QString::fromUtf8("aboutAction"));
        aboutAction->setCheckable(false);
        exitAction = new QAction(MainWindow);
        exitAction->setObjectName(QString::fromUtf8("exitAction"));
        exitAction->setCheckable(false);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        SelectWidget = new QWidget(centralwidget);
        SelectWidget->setObjectName(QString::fromUtf8("SelectWidget"));
        SelectWidget->setGeometry(QRect(20, 120, 250, 300));
        SelectWidget->setStyleSheet(QString::fromUtf8(""));
        selectlabel = new QLabel(SelectWidget);
        selectlabel->setObjectName(QString::fromUtf8("selectlabel"));
        selectlabel->setGeometry(QRect(-1, 0, 250, 40));
        QFont font;
        font.setFamilies({QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221")});
        font.setPointSize(21);
        font.setBold(true);
        selectlabel->setFont(font);
        selectlabel->setAlignment(Qt::AlignHCenter|Qt::AlignTop);
        radioButton_face = new QRadioButton(SelectWidget);
        radioButton_face->setObjectName(QString::fromUtf8("radioButton_face"));
        radioButton_face->setGeometry(QRect(10, 70, 120, 30));
        QFont font1;
        font1.setPointSize(16);
        radioButton_face->setFont(font1);
        radioButton_face->setChecked(true);
        radioButton_fp = new QRadioButton(SelectWidget);
        radioButton_fp->setObjectName(QString::fromUtf8("radioButton_fp"));
        radioButton_fp->setGeometry(QRect(10, 130, 120, 30));
        radioButton_fp->setFont(font1);
        radioButton_pixel = new QRadioButton(SelectWidget);
        radioButton_pixel->setObjectName(QString::fromUtf8("radioButton_pixel"));
        radioButton_pixel->setGeometry(QRect(130, 130, 120, 30));
        radioButton_pixel->setFont(font1);
        radioButton_pixel->setChecked(false);
        radioButton_iris = new QRadioButton(SelectWidget);
        radioButton_iris->setObjectName(QString::fromUtf8("radioButton_iris"));
        radioButton_iris->setGeometry(QRect(130, 70, 120, 30));
        radioButton_iris->setFont(font1);
        radioButton_feature = new QRadioButton(SelectWidget);
        radioButton_feature->setObjectName(QString::fromUtf8("radioButton_feature"));
        radioButton_feature->setGeometry(QRect(10, 190, 120, 30));
        radioButton_feature->setFont(font1);
        radioButton_score = new QRadioButton(SelectWidget);
        radioButton_score->setObjectName(QString::fromUtf8("radioButton_score"));
        radioButton_score->setGeometry(QRect(130, 190, 120, 30));
        radioButton_score->setFont(font1);
        radioButton_score->setChecked(false);
        radioButton_optimal = new QRadioButton(SelectWidget);
        radioButton_optimal->setObjectName(QString::fromUtf8("radioButton_optimal"));
        radioButton_optimal->setGeometry(QRect(10, 250, 120, 30));
        radioButton_optimal->setFont(font1);
        ResultWidget = new QWidget(centralwidget);
        ResultWidget->setObjectName(QString::fromUtf8("ResultWidget"));
        ResultWidget->setGeometry(QRect(20, 420, 250, 300));
        textBrowser = new QTextBrowser(ResultWidget);
        textBrowser->setObjectName(QString::fromUtf8("textBrowser"));
        textBrowser->setGeometry(QRect(10, 10, 230, 280));
        QFont font2;
        font2.setFamilies({QString::fromUtf8("\347\255\211\347\272\277")});
        font2.setPointSize(12);
        textBrowser->setFont(font2);
        TestWidget = new QWidget(centralwidget);
        TestWidget->setObjectName(QString::fromUtf8("TestWidget"));
        TestWidget->setGeometry(QRect(280, 120, 660, 280));
        label = new QLabel(TestWidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(0, 0, 660, 40));
        label->setFont(font);
        label->setAlignment(Qt::AlignHCenter|Qt::AlignTop);
        graphicsView_face = new QGraphicsView(TestWidget);
        graphicsView_face->setObjectName(QString::fromUtf8("graphicsView_face"));
        graphicsView_face->setGeometry(QRect(30, 50, 160, 160));
        graphicsView_iris = new QGraphicsView(TestWidget);
        graphicsView_iris->setObjectName(QString::fromUtf8("graphicsView_iris"));
        graphicsView_iris->setGeometry(QRect(250, 50, 160, 160));
        graphicsView_fp = new QGraphicsView(TestWidget);
        graphicsView_fp->setObjectName(QString::fromUtf8("graphicsView_fp"));
        graphicsView_fp->setGeometry(QRect(470, 50, 160, 160));
        pushButtond_face = new QPushButton(TestWidget);
        pushButtond_face->setObjectName(QString::fromUtf8("pushButtond_face"));
        pushButtond_face->setGeometry(QRect(50, 220, 120, 30));
        pushButtond_face->setBaseSize(QSize(0, 0));
        QFont font3;
        font3.setPointSize(14);
        pushButtond_face->setFont(font3);
        pushButtond_face->setStyleSheet(QString::fromUtf8("border-color: rgb(0, 0, 0);\n"
"border-width: 2px;\n"
""));
        pushButtond_iris = new QPushButton(TestWidget);
        pushButtond_iris->setObjectName(QString::fromUtf8("pushButtond_iris"));
        pushButtond_iris->setGeometry(QRect(270, 220, 120, 30));
        pushButtond_iris->setBaseSize(QSize(0, 0));
        pushButtond_iris->setFont(font3);
        pushButtond_iris->setStyleSheet(QString::fromUtf8("border-color: rgb(0, 0, 0);\n"
"border-width: 2px;\n"
""));
        pushButtond_fp = new QPushButton(TestWidget);
        pushButtond_fp->setObjectName(QString::fromUtf8("pushButtond_fp"));
        pushButtond_fp->setGeometry(QRect(490, 220, 120, 30));
        pushButtond_fp->setBaseSize(QSize(0, 0));
        pushButtond_fp->setFont(font3);
        pushButtond_fp->setStyleSheet(QString::fromUtf8("border-color: rgb(0, 0, 0);\n"
"border-width: 2px;\n"
""));
        GalleryWidget = new QWidget(centralwidget);
        GalleryWidget->setObjectName(QString::fromUtf8("GalleryWidget"));
        GalleryWidget->setGeometry(QRect(280, 410, 660, 220));
        label_2 = new QLabel(GalleryWidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(0, 0, 660, 40));
        label_2->setFont(font);
        label_2->setAlignment(Qt::AlignHCenter|Qt::AlignTop);
        graphicsView_face_g = new QGraphicsView(GalleryWidget);
        graphicsView_face_g->setObjectName(QString::fromUtf8("graphicsView_face_g"));
        graphicsView_face_g->setGeometry(QRect(30, 50, 160, 160));
        graphicsView_iris_g = new QGraphicsView(GalleryWidget);
        graphicsView_iris_g->setObjectName(QString::fromUtf8("graphicsView_iris_g"));
        graphicsView_iris_g->setGeometry(QRect(250, 50, 160, 160));
        graphicsView_fp_g = new QGraphicsView(GalleryWidget);
        graphicsView_fp_g->setObjectName(QString::fromUtf8("graphicsView_fp_g"));
        graphicsView_fp_g->setGeometry(QRect(470, 50, 160, 160));
        label_3 = new QLabel(centralwidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(0, 20, 960, 70));
        QFont font4;
        font4.setFamilies({QString::fromUtf8("\351\273\221\344\275\223")});
        font4.setPointSize(28);
        label_3->setFont(font4);
        label_3->setAlignment(Qt::AlignCenter);
        FunctionWidget = new QWidget(centralwidget);
        FunctionWidget->setObjectName(QString::fromUtf8("FunctionWidget"));
        FunctionWidget->setGeometry(QRect(280, 640, 660, 80));
        pushButtond_gallery = new QPushButton(FunctionWidget);
        pushButtond_gallery->setObjectName(QString::fromUtf8("pushButtond_gallery"));
        pushButtond_gallery->setGeometry(QRect(550, 46, 90, 30));
        pushButtond_gallery->setBaseSize(QSize(0, 0));
        QFont font5;
        font5.setPointSize(13);
        pushButtond_gallery->setFont(font5);
        pushButtond_gallery->setStyleSheet(QString::fromUtf8("border-color: rgb(0, 0, 0);\n"
"border-width: 2px;\n"
""));
        label_4 = new QLabel(FunctionWidget);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(10, 46, 80, 30));
        QFont font6;
        font6.setPointSize(12);
        label_4->setFont(font6);
        galleryTextBrowser = new QTextBrowser(FunctionWidget);
        galleryTextBrowser->setObjectName(QString::fromUtf8("galleryTextBrowser"));
        galleryTextBrowser->setGeometry(QRect(85, 46, 460, 30));
        QFont font7;
        font7.setPointSize(8);
        galleryTextBrowser->setFont(font7);
        pushButtond_up = new QPushButton(FunctionWidget);
        pushButtond_up->setObjectName(QString::fromUtf8("pushButtond_up"));
        pushButtond_up->setGeometry(QRect(460, 10, 70, 30));
        pushButtond_up->setBaseSize(QSize(0, 0));
        pushButtond_up->setFont(font5);
        pushButtond_up->setStyleSheet(QString::fromUtf8("border-color: rgb(0, 0, 0);\n"
"border-width: 2px;\n"
""));
        pushButtond_down = new QPushButton(FunctionWidget);
        pushButtond_down->setObjectName(QString::fromUtf8("pushButtond_down"));
        pushButtond_down->setGeometry(QRect(570, 10, 70, 30));
        pushButtond_down->setBaseSize(QSize(0, 0));
        pushButtond_down->setFont(font5);
        pushButtond_down->setStyleSheet(QString::fromUtf8("border-color: rgb(0, 0, 0);\n"
"border-width: 2px;\n"
""));
        label_5 = new QLabel(FunctionWidget);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setGeometry(QRect(540, 15, 20, 20));
        label_5->setFont(font6);
        label_5->setAlignment(Qt::AlignBottom|Qt::AlignHCenter);
        label_6 = new QLabel(FunctionWidget);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setGeometry(QRect(20, 10, 70, 30));
        label_6->setFont(font5);
        label_6->setAlignment(Qt::AlignCenter);
        label_7 = new QLabel(FunctionWidget);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        label_7->setGeometry(QRect(140, 10, 100, 30));
        label_7->setFont(font5);
        label_7->setAlignment(Qt::AlignCenter);
        spinBox = new QSpinBox(FunctionWidget);
        spinBox->setObjectName(QString::fromUtf8("spinBox"));
        spinBox->setGeometry(QRect(90, 12, 50, 25));
        spinBox->setFont(font5);
        spinBox->setFocusPolicy(Qt::NoFocus);
        spinBox->setMinimum(1);
        spinBox->setMaximum(10);
        pushButtond_res = new QPushButton(FunctionWidget);
        pushButtond_res->setObjectName(QString::fromUtf8("pushButtond_res"));
        pushButtond_res->setGeometry(QRect(300, 10, 90, 30));
        pushButtond_res->setBaseSize(QSize(0, 0));
        pushButtond_res->setFont(font5);
        pushButtond_res->setStyleSheet(QString::fromUtf8("border-color: rgb(0, 0, 0);\n"
"border-width: 2px;\n"
""));
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 960, 22));
        helpMenu = new QMenu(menubar);
        helpMenu->setObjectName(QString::fromUtf8("helpMenu"));
        settingMenu = new MyMenu(menubar);
        settingMenu->setObjectName(QString::fromUtf8("settingMenu"));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        menubar->addAction(settingMenu->menuAction());
        menubar->addAction(helpMenu->menuAction());
        helpMenu->addAction(aboutAction);
        helpMenu->addAction(exitAction);
        settingMenu->addAction(accelerateAction);
        settingMenu->addAction(saveAction);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "\345\244\232\346\250\241\346\200\201\347\224\237\347\211\251\347\211\271\345\276\201\350\257\206\345\210\253\350\275\257\344\273\266v1.0", nullptr));
        accelerateAction->setText(QCoreApplication::translate("MainWindow", "\345\212\240\351\200\237\346\250\241\345\274\217", nullptr));
        saveAction->setText(QCoreApplication::translate("MainWindow", "\344\277\235\345\255\230\347\273\223\346\236\234", nullptr));
        aboutAction->setText(QCoreApplication::translate("MainWindow", "\345\205\263\344\272\216", nullptr));
        exitAction->setText(QCoreApplication::translate("MainWindow", "\351\200\200\345\207\272", nullptr));
        selectlabel->setText(QCoreApplication::translate("MainWindow", "  \346\250\241\345\274\217\351\200\211\346\213\251", nullptr));
        radioButton_face->setText(QCoreApplication::translate("MainWindow", "\344\272\272\350\204\270\350\257\206\345\210\253", nullptr));
        radioButton_fp->setText(QCoreApplication::translate("MainWindow", "\346\214\207\347\272\271\350\257\206\345\210\253", nullptr));
        radioButton_pixel->setText(QCoreApplication::translate("MainWindow", "\345\203\217\347\264\240\350\236\215\345\220\210", nullptr));
        radioButton_iris->setText(QCoreApplication::translate("MainWindow", "\350\231\271\350\206\234\350\257\206\345\210\253", nullptr));
        radioButton_feature->setText(QCoreApplication::translate("MainWindow", "\347\211\271\345\276\201\350\236\215\345\220\210", nullptr));
        radioButton_score->setText(QCoreApplication::translate("MainWindow", "\345\210\206\346\225\260\350\236\215\345\220\210", nullptr));
        radioButton_optimal->setText(QCoreApplication::translate("MainWindow", "\346\234\200\344\274\230\350\236\215\345\220\210", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "\346\265\213\350\257\225\346\225\260\346\215\256", nullptr));
        pushButtond_face->setText(QCoreApplication::translate("MainWindow", "\351\200\211\346\213\251\345\233\276\347\211\207", nullptr));
        pushButtond_iris->setText(QCoreApplication::translate("MainWindow", "\351\200\211\346\213\251\345\233\276\347\211\207", nullptr));
        pushButtond_fp->setText(QCoreApplication::translate("MainWindow", "\351\200\211\346\213\251\345\233\276\347\211\207", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "\345\214\271\351\205\215\347\273\223\346\236\234", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", "\345\237\272\344\272\216\346\267\261\345\272\246\345\255\246\344\271\240\347\256\227\346\263\225\347\232\204\345\244\232\346\250\241\346\200\201\347\224\237\347\211\251\347\211\271\345\276\201\350\257\206\345\210\253\347\263\273\347\273\237", nullptr));
        pushButtond_gallery->setText(QCoreApplication::translate("MainWindow", "\351\200\211\346\213\251\345\272\225\345\272\223", nullptr));
        label_4->setText(QCoreApplication::translate("MainWindow", "\345\275\223\345\211\215\345\272\225\345\272\223:", nullptr));
        pushButtond_up->setText(QCoreApplication::translate("MainWindow", "\344\270\212\344\270\200\344\270\252", nullptr));
        pushButtond_down->setText(QCoreApplication::translate("MainWindow", "\344\270\213\344\270\200\344\270\252", nullptr));
        label_5->setText(QCoreApplication::translate("MainWindow", "1", nullptr));
        label_6->setText(QCoreApplication::translate("MainWindow", "\345\261\225\347\244\272\345\211\215", nullptr));
        label_7->setText(QCoreApplication::translate("MainWindow", "\344\270\252\345\214\271\351\205\215\347\273\223\346\236\234", nullptr));
        pushButtond_res->setText(QCoreApplication::translate("MainWindow", "\347\224\237\346\210\220\347\273\223\346\236\234", nullptr));
        helpMenu->setTitle(QCoreApplication::translate("MainWindow", "\345\270\256\345\212\251", nullptr));
        settingMenu->setTitle(QCoreApplication::translate("MainWindow", "\350\256\276\347\275\256", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
