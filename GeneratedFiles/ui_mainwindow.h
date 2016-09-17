/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.3.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *OpenImage;
    QAction *SaveImage;
    QAction *ActionExit;
    QAction *ActionDemo;
    QAction *action_5;
    QAction *ActionInfo;
    QAction *Actionhomepage;
    QAction *FreshImage;
    QWidget *centralWidget;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout;
    QFrame *verticalFrame;
    QVBoxLayout *verticalLayout;
    QPushButton *ParameterBtn;
    QPushButton *EnhanceBtn;
    QPushButton *TransformBtn;
    QPushButton *RecoverBtn;
    QPushButton *CodingBtn;
    QGraphicsView *graphicsView;
    QMenuBar *menuBar;
    QMenu *menu;
    QMenu *menu_3;
    QMenu *menu_4;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(800, 600);
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(MainWindow->sizePolicy().hasHeightForWidth());
        MainWindow->setSizePolicy(sizePolicy);
        MainWindow->setMinimumSize(QSize(640, 480));
        MainWindow->setMaximumSize(QSize(1280, 960));
        OpenImage = new QAction(MainWindow);
        OpenImage->setObjectName(QStringLiteral("OpenImage"));
        SaveImage = new QAction(MainWindow);
        SaveImage->setObjectName(QStringLiteral("SaveImage"));
        ActionExit = new QAction(MainWindow);
        ActionExit->setObjectName(QStringLiteral("ActionExit"));
        ActionDemo = new QAction(MainWindow);
        ActionDemo->setObjectName(QStringLiteral("ActionDemo"));
        action_5 = new QAction(MainWindow);
        action_5->setObjectName(QStringLiteral("action_5"));
        ActionInfo = new QAction(MainWindow);
        ActionInfo->setObjectName(QStringLiteral("ActionInfo"));
        Actionhomepage = new QAction(MainWindow);
        Actionhomepage->setObjectName(QStringLiteral("Actionhomepage"));
        FreshImage = new QAction(MainWindow);
        FreshImage->setObjectName(QStringLiteral("FreshImage"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        verticalLayout_2 = new QVBoxLayout(centralWidget);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        verticalFrame = new QFrame(centralWidget);
        verticalFrame->setObjectName(QStringLiteral("verticalFrame"));
        verticalLayout = new QVBoxLayout(verticalFrame);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        ParameterBtn = new QPushButton(verticalFrame);
        ParameterBtn->setObjectName(QStringLiteral("ParameterBtn"));

        verticalLayout->addWidget(ParameterBtn);

        EnhanceBtn = new QPushButton(verticalFrame);
        EnhanceBtn->setObjectName(QStringLiteral("EnhanceBtn"));

        verticalLayout->addWidget(EnhanceBtn);

        TransformBtn = new QPushButton(verticalFrame);
        TransformBtn->setObjectName(QStringLiteral("TransformBtn"));

        verticalLayout->addWidget(TransformBtn);

        RecoverBtn = new QPushButton(verticalFrame);
        RecoverBtn->setObjectName(QStringLiteral("RecoverBtn"));

        verticalLayout->addWidget(RecoverBtn);

        CodingBtn = new QPushButton(verticalFrame);
        CodingBtn->setObjectName(QStringLiteral("CodingBtn"));

        verticalLayout->addWidget(CodingBtn);


        horizontalLayout->addWidget(verticalFrame);

        graphicsView = new QGraphicsView(centralWidget);
        graphicsView->setObjectName(QStringLiteral("graphicsView"));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(graphicsView->sizePolicy().hasHeightForWidth());
        graphicsView->setSizePolicy(sizePolicy1);
        graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
        graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);

        horizontalLayout->addWidget(graphicsView);


        verticalLayout_2->addLayout(horizontalLayout);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 800, 23));
        menu = new QMenu(menuBar);
        menu->setObjectName(QStringLiteral("menu"));
        menu_3 = new QMenu(menuBar);
        menu_3->setObjectName(QStringLiteral("menu_3"));
        menu_4 = new QMenu(menuBar);
        menu_4->setObjectName(QStringLiteral("menu_4"));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        menuBar->addAction(menu->menuAction());
        menuBar->addAction(menu_3->menuAction());
        menuBar->addAction(menu_4->menuAction());
        menu->addAction(OpenImage);
        menu->addAction(SaveImage);
        menu->addAction(FreshImage);
        menu->addSeparator();
        menu->addAction(ActionExit);
        menu_3->addAction(ActionDemo);
        menu_4->addAction(ActionInfo);
        menu_4->addAction(Actionhomepage);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0));
        OpenImage->setText(QApplication::translate("MainWindow", "\346\211\223\345\274\200", 0));
        SaveImage->setText(QApplication::translate("MainWindow", "\344\277\235\345\255\230", 0));
        ActionExit->setText(QApplication::translate("MainWindow", "\345\205\263\351\227\255", 0));
        ActionDemo->setText(QApplication::translate("MainWindow", "\345\256\236\351\252\214\350\257\264\346\230\216", 0));
        action_5->setText(QApplication::translate("MainWindow", "\345\271\263\345\217\260\344\277\241\346\201\257", 0));
        ActionInfo->setText(QApplication::translate("MainWindow", "\345\271\263\345\217\260\344\277\241\346\201\257", 0));
        Actionhomepage->setText(QApplication::translate("MainWindow", "\350\257\276\347\250\213\344\270\273\351\241\265", 0));
        FreshImage->setText(QApplication::translate("MainWindow", "\346\270\205\347\251\272", 0));
        ParameterBtn->setText(QApplication::translate("MainWindow", "\345\233\276\345\203\217\345\217\202\346\225\260\350\277\220\347\256\227", 0));
        EnhanceBtn->setText(QApplication::translate("MainWindow", "\345\233\276\345\203\217\345\242\236\345\274\272", 0));
        TransformBtn->setText(QApplication::translate("MainWindow", "\345\233\276\345\203\217\345\217\230\346\215\242", 0));
        RecoverBtn->setText(QApplication::translate("MainWindow", "\345\233\276\345\203\217\346\201\242\345\244\215", 0));
        CodingBtn->setText(QApplication::translate("MainWindow", "\345\233\276\345\203\217\347\274\226\347\240\201", 0));
        menu->setTitle(QApplication::translate("MainWindow", "\346\226\207\344\273\266", 0));
        menu_3->setTitle(QApplication::translate("MainWindow", "\345\270\256\345\212\251", 0));
        menu_4->setTitle(QApplication::translate("MainWindow", "\345\205\263\344\272\216", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
