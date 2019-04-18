/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.12.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include <imageviewer.h>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QHBoxLayout *horizontalLayout_6;
    QVBoxLayout *verticalLayout;
    ImageViewer *imageView;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QLineEdit *txtSourcePath;
    QToolButton *toolButton;
    QVBoxLayout *verticalLayout_3;
    QVBoxLayout *verticalLayout_7;
    QGroupBox *groupBox;
    QVBoxLayout *verticalLayout_5;
    QRadioButton *rbFormatOriginal;
    QRadioButton *rbFormatP3;
    QRadioButton *rbFormatP6;
    QGroupBox *groupBox_2;
    QVBoxLayout *verticalLayout_6;
    QRadioButton *rbSqrt;
    QRadioButton *rbAbs;
    QSpacerItem *verticalSpacer;
    QVBoxLayout *verticalLayout_4;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_2;
    QLineEdit *txtThreads;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_3;
    QLineEdit *txtPostfix;
    QCheckBox *cbInterm;
    QPushButton *btnSave;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(427, 384);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        horizontalLayout_6 = new QHBoxLayout(centralWidget);
        horizontalLayout_6->setSpacing(6);
        horizontalLayout_6->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        imageView = new ImageViewer(centralWidget);
        imageView->setObjectName(QString::fromUtf8("imageView"));
        imageView->setDragMode(QGraphicsView::ScrollHandDrag);

        verticalLayout->addWidget(imageView);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label = new QLabel(centralWidget);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout->addWidget(label);

        txtSourcePath = new QLineEdit(centralWidget);
        txtSourcePath->setObjectName(QString::fromUtf8("txtSourcePath"));

        horizontalLayout->addWidget(txtSourcePath);

        toolButton = new QToolButton(centralWidget);
        toolButton->setObjectName(QString::fromUtf8("toolButton"));

        horizontalLayout->addWidget(toolButton);


        verticalLayout->addLayout(horizontalLayout);


        horizontalLayout_6->addLayout(verticalLayout);

        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        verticalLayout_7 = new QVBoxLayout();
        verticalLayout_7->setSpacing(6);
        verticalLayout_7->setObjectName(QString::fromUtf8("verticalLayout_7"));
        groupBox = new QGroupBox(centralWidget);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        QSizePolicy sizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(groupBox->sizePolicy().hasHeightForWidth());
        groupBox->setSizePolicy(sizePolicy);
        verticalLayout_5 = new QVBoxLayout(groupBox);
        verticalLayout_5->setSpacing(6);
        verticalLayout_5->setContentsMargins(11, 11, 11, 11);
        verticalLayout_5->setObjectName(QString::fromUtf8("verticalLayout_5"));
        rbFormatOriginal = new QRadioButton(groupBox);
        rbFormatOriginal->setObjectName(QString::fromUtf8("rbFormatOriginal"));
        rbFormatOriginal->setChecked(true);

        verticalLayout_5->addWidget(rbFormatOriginal);

        rbFormatP3 = new QRadioButton(groupBox);
        rbFormatP3->setObjectName(QString::fromUtf8("rbFormatP3"));

        verticalLayout_5->addWidget(rbFormatP3);

        rbFormatP6 = new QRadioButton(groupBox);
        rbFormatP6->setObjectName(QString::fromUtf8("rbFormatP6"));

        verticalLayout_5->addWidget(rbFormatP6);


        verticalLayout_7->addWidget(groupBox);

        groupBox_2 = new QGroupBox(centralWidget);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        groupBox_2->setEnabled(true);
        sizePolicy.setHeightForWidth(groupBox_2->sizePolicy().hasHeightForWidth());
        groupBox_2->setSizePolicy(sizePolicy);
        verticalLayout_6 = new QVBoxLayout(groupBox_2);
        verticalLayout_6->setSpacing(6);
        verticalLayout_6->setContentsMargins(11, 11, 11, 11);
        verticalLayout_6->setObjectName(QString::fromUtf8("verticalLayout_6"));
        rbSqrt = new QRadioButton(groupBox_2);
        rbSqrt->setObjectName(QString::fromUtf8("rbSqrt"));
        QSizePolicy sizePolicy1(QSizePolicy::Minimum, QSizePolicy::Minimum);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(rbSqrt->sizePolicy().hasHeightForWidth());
        rbSqrt->setSizePolicy(sizePolicy1);
        rbSqrt->setChecked(true);

        verticalLayout_6->addWidget(rbSqrt);

        rbAbs = new QRadioButton(groupBox_2);
        rbAbs->setObjectName(QString::fromUtf8("rbAbs"));

        verticalLayout_6->addWidget(rbAbs);


        verticalLayout_7->addWidget(groupBox_2);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_7->addItem(verticalSpacer);

        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setSpacing(6);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        verticalLayout_4->setSizeConstraint(QLayout::SetMaximumSize);
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        label_2 = new QLabel(centralWidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        horizontalLayout_3->addWidget(label_2);

        txtThreads = new QLineEdit(centralWidget);
        txtThreads->setObjectName(QString::fromUtf8("txtThreads"));
        sizePolicy.setHeightForWidth(txtThreads->sizePolicy().hasHeightForWidth());
        txtThreads->setSizePolicy(sizePolicy);
        txtThreads->setMaximumSize(QSize(50, 16777215));

        horizontalLayout_3->addWidget(txtThreads);


        verticalLayout_4->addLayout(horizontalLayout_3);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        label_3 = new QLabel(centralWidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        QSizePolicy sizePolicy2(QSizePolicy::Maximum, QSizePolicy::Preferred);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(label_3->sizePolicy().hasHeightForWidth());
        label_3->setSizePolicy(sizePolicy2);

        horizontalLayout_2->addWidget(label_3);

        txtPostfix = new QLineEdit(centralWidget);
        txtPostfix->setObjectName(QString::fromUtf8("txtPostfix"));
        sizePolicy.setHeightForWidth(txtPostfix->sizePolicy().hasHeightForWidth());
        txtPostfix->setSizePolicy(sizePolicy);
        txtPostfix->setMaximumSize(QSize(80, 16777215));

        horizontalLayout_2->addWidget(txtPostfix);


        verticalLayout_4->addLayout(horizontalLayout_2);

        cbInterm = new QCheckBox(centralWidget);
        cbInterm->setObjectName(QString::fromUtf8("cbInterm"));
        QSizePolicy sizePolicy3(QSizePolicy::Maximum, QSizePolicy::Fixed);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(cbInterm->sizePolicy().hasHeightForWidth());
        cbInterm->setSizePolicy(sizePolicy3);

        verticalLayout_4->addWidget(cbInterm);

        btnSave = new QPushButton(centralWidget);
        btnSave->setObjectName(QString::fromUtf8("btnSave"));
        btnSave->setEnabled(false);

        verticalLayout_4->addWidget(btnSave);


        verticalLayout_7->addLayout(verticalLayout_4);


        verticalLayout_3->addLayout(verticalLayout_7);


        horizontalLayout_6->addLayout(verticalLayout_3);

        MainWindow->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "Contour Highlighter", nullptr));
        label->setText(QApplication::translate("MainWindow", "Open:", nullptr));
        toolButton->setText(QApplication::translate("MainWindow", "...", nullptr));
        groupBox->setTitle(QApplication::translate("MainWindow", "Output Format", nullptr));
        rbFormatOriginal->setText(QApplication::translate("MainWindow", "As original", nullptr));
        rbFormatP3->setText(QApplication::translate("MainWindow", "P3", nullptr));
        rbFormatP6->setText(QApplication::translate("MainWindow", "P6", nullptr));
#ifndef QT_NO_TOOLTIP
        groupBox_2->setToolTip(QApplication::translate("MainWindow", "<html><head/><body><p>Approximating gradient using <span style=\" font-weight:600;\">absolute value </span>is generally <span style=\" font-weight:600;\">faster</span>, but might be not as precise as square root.</p></body></html>", nullptr));
#endif // QT_NO_TOOLTIP
        groupBox_2->setTitle(QApplication::translate("MainWindow", "Gradient approx.", nullptr));
        rbSqrt->setText(QApplication::translate("MainWindow", "sqrt", nullptr));
#ifndef QT_NO_TOOLTIP
        rbAbs->setToolTip(QString());
#endif // QT_NO_TOOLTIP
        rbAbs->setText(QApplication::translate("MainWindow", "abs", nullptr));
        label_2->setText(QApplication::translate("MainWindow", "Threads:", nullptr));
        txtThreads->setText(QApplication::translate("MainWindow", "1", nullptr));
#ifndef QT_NO_TOOLTIP
        label_3->setToolTip(QApplication::translate("MainWindow", "<html><head/><body><p>This string will be added to the original file's name, like the following:</p><p>pilot<span style=\" font-weight:600;\">_CONT.</span>ppm</p><p>pilot<span style=\" font-weight:600;\">_CONT_h.</span>ppm</p><p>pilot<span style=\" font-weight:600;\">_CONT_v.</span>ppm</p></body></html>", nullptr));
#endif // QT_NO_TOOLTIP
        label_3->setText(QApplication::translate("MainWindow", "File postfix:", nullptr));
#ifndef QT_NO_TOOLTIP
        txtPostfix->setToolTip(QApplication::translate("MainWindow", "<html><head/><body><p>This string will be added to the original file's name, like the following:</p><p>pilot<span style=\" font-weight:600;\">_CONT.</span>ppm</p><p>pilot<span style=\" font-weight:600;\">_CONT_h.</span>ppm</p><p>pilot<span style=\" font-weight:600;\">_CONT_v.</span>ppm</p></body></html>", nullptr));
#endif // QT_NO_TOOLTIP
        txtPostfix->setText(QApplication::translate("MainWindow", "CONT", nullptr));
#ifndef QT_NO_TOOLTIP
        cbInterm->setToolTip(QApplication::translate("MainWindow", "<html><head/><body><p>Vertical and horizontal convolution result images will be saved if this one is checked</p></body></html>", nullptr));
#endif // QT_NO_TOOLTIP
        cbInterm->setText(QApplication::translate("MainWindow", "Save intermediate", nullptr));
        btnSave->setText(QApplication::translate("MainWindow", "Generate Contour", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
