/********************************************************************************
** Form generated from reading UI file 'UserInterface.ui'
**
** Created by: Qt User Interface Compiler version 5.2.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_USERINTERFACE_H
#define UI_USERINTERFACE_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_UserInterface
{
public:
    QWidget *centralWidget;
    QVBoxLayout *verticalLayout;
    QLabel *overlay;
    QHBoxLayout *workspace;
    QFrame *view;
    QVBoxLayout *rightbar;
    QRadioButton *rbn_flame1;
    QRadioButton *rbn_smoke1;
    QFrame *line;
    QLabel *lbl_visc;
    QSlider *reg_visc;
    QLabel *lbl_diff;
    QSlider *reg_diff;
    QLabel *lbl_dt;
    QSlider *reg_dt;
    QLabel *lbl_dens_src;
    QSlider *reg_dens_src;
    QLabel *lbl_v_up;
    QSlider *reg_v_up;
    QLabel *lbl_v_side;
    QSlider *reg_v_side;
    QLabel *lbl_v_flucts;
    QSlider *reg_v_flucts;
    QLabel *lbl_u_flucts;
    QSlider *reg_u_flucts;
    QFrame *line_2;
    QHBoxLayout *buttons;
    QPushButton *btn_save;
    QPushButton *btn_restore;
    QPushButton *btn_launch;
    QSpacerItem *spc;

    void setupUi(QMainWindow *UserInterface)
    {
        if (UserInterface->objectName().isEmpty())
            UserInterface->setObjectName(QStringLiteral("UserInterface"));
        UserInterface->resize(641, 732);
        QFont font;
        font.setPointSize(14);
        UserInterface->setFont(font);
        centralWidget = new QWidget(UserInterface);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        verticalLayout = new QVBoxLayout(centralWidget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        overlay = new QLabel(centralWidget);
        overlay->setObjectName(QStringLiteral("overlay"));
        overlay->setStyleSheet(QStringLiteral("color: rgb(226, 13, 13);"));

        verticalLayout->addWidget(overlay);

        workspace = new QHBoxLayout();
        workspace->setSpacing(6);
        workspace->setObjectName(QStringLiteral("workspace"));
        view = new QFrame(centralWidget);
        view->setObjectName(QStringLiteral("view"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(view->sizePolicy().hasHeightForWidth());
        view->setSizePolicy(sizePolicy);
        view->setFrameShape(QFrame::StyledPanel);
        view->setFrameShadow(QFrame::Raised);

        workspace->addWidget(view);

        rightbar = new QVBoxLayout();
        rightbar->setSpacing(6);
        rightbar->setObjectName(QStringLiteral("rightbar"));
        rbn_flame1 = new QRadioButton(centralWidget);
        rbn_flame1->setObjectName(QStringLiteral("rbn_flame1"));

        rightbar->addWidget(rbn_flame1);

        rbn_smoke1 = new QRadioButton(centralWidget);
        rbn_smoke1->setObjectName(QStringLiteral("rbn_smoke1"));

        rightbar->addWidget(rbn_smoke1);

        line = new QFrame(centralWidget);
        line->setObjectName(QStringLiteral("line"));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);

        rightbar->addWidget(line);

        lbl_visc = new QLabel(centralWidget);
        lbl_visc->setObjectName(QStringLiteral("lbl_visc"));

        rightbar->addWidget(lbl_visc);

        reg_visc = new QSlider(centralWidget);
        reg_visc->setObjectName(QStringLiteral("reg_visc"));
        QSizePolicy sizePolicy1(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(reg_visc->sizePolicy().hasHeightForWidth());
        reg_visc->setSizePolicy(sizePolicy1);
        reg_visc->setMinimumSize(QSize(260, 0));
        reg_visc->setMinimum(1);
        reg_visc->setMaximum(100);
        reg_visc->setOrientation(Qt::Horizontal);

        rightbar->addWidget(reg_visc);

        lbl_diff = new QLabel(centralWidget);
        lbl_diff->setObjectName(QStringLiteral("lbl_diff"));

        rightbar->addWidget(lbl_diff);

        reg_diff = new QSlider(centralWidget);
        reg_diff->setObjectName(QStringLiteral("reg_diff"));
        sizePolicy1.setHeightForWidth(reg_diff->sizePolicy().hasHeightForWidth());
        reg_diff->setSizePolicy(sizePolicy1);
        reg_diff->setMinimumSize(QSize(260, 0));
        reg_diff->setMinimum(1);
        reg_diff->setMaximum(100);
        reg_diff->setOrientation(Qt::Horizontal);

        rightbar->addWidget(reg_diff);

        lbl_dt = new QLabel(centralWidget);
        lbl_dt->setObjectName(QStringLiteral("lbl_dt"));

        rightbar->addWidget(lbl_dt);

        reg_dt = new QSlider(centralWidget);
        reg_dt->setObjectName(QStringLiteral("reg_dt"));
        sizePolicy1.setHeightForWidth(reg_dt->sizePolicy().hasHeightForWidth());
        reg_dt->setSizePolicy(sizePolicy1);
        reg_dt->setMinimumSize(QSize(260, 0));
        reg_dt->setMinimum(1);
        reg_dt->setMaximum(100);
        reg_dt->setOrientation(Qt::Horizontal);

        rightbar->addWidget(reg_dt);

        lbl_dens_src = new QLabel(centralWidget);
        lbl_dens_src->setObjectName(QStringLiteral("lbl_dens_src"));

        rightbar->addWidget(lbl_dens_src);

        reg_dens_src = new QSlider(centralWidget);
        reg_dens_src->setObjectName(QStringLiteral("reg_dens_src"));
        sizePolicy1.setHeightForWidth(reg_dens_src->sizePolicy().hasHeightForWidth());
        reg_dens_src->setSizePolicy(sizePolicy1);
        reg_dens_src->setMinimumSize(QSize(260, 0));
        reg_dens_src->setMinimum(1);
        reg_dens_src->setMaximum(100);
        reg_dens_src->setOrientation(Qt::Horizontal);

        rightbar->addWidget(reg_dens_src);

        lbl_v_up = new QLabel(centralWidget);
        lbl_v_up->setObjectName(QStringLiteral("lbl_v_up"));

        rightbar->addWidget(lbl_v_up);

        reg_v_up = new QSlider(centralWidget);
        reg_v_up->setObjectName(QStringLiteral("reg_v_up"));
        sizePolicy1.setHeightForWidth(reg_v_up->sizePolicy().hasHeightForWidth());
        reg_v_up->setSizePolicy(sizePolicy1);
        reg_v_up->setMinimumSize(QSize(260, 0));
        reg_v_up->setMinimum(1);
        reg_v_up->setMaximum(100);
        reg_v_up->setOrientation(Qt::Horizontal);

        rightbar->addWidget(reg_v_up);

        lbl_v_side = new QLabel(centralWidget);
        lbl_v_side->setObjectName(QStringLiteral("lbl_v_side"));

        rightbar->addWidget(lbl_v_side);

        reg_v_side = new QSlider(centralWidget);
        reg_v_side->setObjectName(QStringLiteral("reg_v_side"));
        sizePolicy1.setHeightForWidth(reg_v_side->sizePolicy().hasHeightForWidth());
        reg_v_side->setSizePolicy(sizePolicy1);
        reg_v_side->setMinimumSize(QSize(260, 0));
        reg_v_side->setMinimum(1);
        reg_v_side->setMaximum(100);
        reg_v_side->setOrientation(Qt::Horizontal);

        rightbar->addWidget(reg_v_side);

        lbl_v_flucts = new QLabel(centralWidget);
        lbl_v_flucts->setObjectName(QStringLiteral("lbl_v_flucts"));

        rightbar->addWidget(lbl_v_flucts);

        reg_v_flucts = new QSlider(centralWidget);
        reg_v_flucts->setObjectName(QStringLiteral("reg_v_flucts"));
        sizePolicy1.setHeightForWidth(reg_v_flucts->sizePolicy().hasHeightForWidth());
        reg_v_flucts->setSizePolicy(sizePolicy1);
        reg_v_flucts->setMinimumSize(QSize(260, 0));
        reg_v_flucts->setMinimum(1);
        reg_v_flucts->setMaximum(100);
        reg_v_flucts->setOrientation(Qt::Horizontal);

        rightbar->addWidget(reg_v_flucts);

        lbl_u_flucts = new QLabel(centralWidget);
        lbl_u_flucts->setObjectName(QStringLiteral("lbl_u_flucts"));

        rightbar->addWidget(lbl_u_flucts);

        reg_u_flucts = new QSlider(centralWidget);
        reg_u_flucts->setObjectName(QStringLiteral("reg_u_flucts"));
        sizePolicy1.setHeightForWidth(reg_u_flucts->sizePolicy().hasHeightForWidth());
        reg_u_flucts->setSizePolicy(sizePolicy1);
        reg_u_flucts->setMinimumSize(QSize(260, 0));
        reg_u_flucts->setMinimum(1);
        reg_u_flucts->setMaximum(100);
        reg_u_flucts->setOrientation(Qt::Horizontal);

        rightbar->addWidget(reg_u_flucts);

        line_2 = new QFrame(centralWidget);
        line_2->setObjectName(QStringLiteral("line_2"));
        line_2->setFrameShape(QFrame::HLine);
        line_2->setFrameShadow(QFrame::Sunken);

        rightbar->addWidget(line_2);

        buttons = new QHBoxLayout();
        buttons->setSpacing(6);
        buttons->setObjectName(QStringLiteral("buttons"));
        btn_save = new QPushButton(centralWidget);
        btn_save->setObjectName(QStringLiteral("btn_save"));

        buttons->addWidget(btn_save);

        btn_restore = new QPushButton(centralWidget);
        btn_restore->setObjectName(QStringLiteral("btn_restore"));

        buttons->addWidget(btn_restore);


        rightbar->addLayout(buttons);

        btn_launch = new QPushButton(centralWidget);
        btn_launch->setObjectName(QStringLiteral("btn_launch"));

        rightbar->addWidget(btn_launch);

        spc = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        rightbar->addItem(spc);


        workspace->addLayout(rightbar);


        verticalLayout->addLayout(workspace);

        UserInterface->setCentralWidget(centralWidget);

        retranslateUi(UserInterface);

        QMetaObject::connectSlotsByName(UserInterface);
    } // setupUi

    void retranslateUi(QMainWindow *UserInterface)
    {
        UserInterface->setWindowTitle(QApplication::translate("UserInterface", "\320\230\320\243-7. \320\232\321\203\321\200\321\201\320\276\320\262\320\276\320\271 \320\277\321\200\320\276\320\265\320\272\321\202", 0));
        overlay->setText(QString());
        rbn_flame1->setText(QApplication::translate("UserInterface", "\320\236\320\263\320\276\320\275\321\214", 0));
        rbn_smoke1->setText(QApplication::translate("UserInterface", "\320\224\321\213\320\274", 0));
        lbl_visc->setText(QApplication::translate("UserInterface", "\320\222\321\217\320\267\320\272\320\276\321\201\321\202\321\214:", 0));
        lbl_diff->setText(QApplication::translate("UserInterface", "\320\224\320\270\321\204\321\204\321\203\320\267\320\270\321\217:", 0));
        lbl_dt->setText(QApplication::translate("UserInterface", "dT:", 0));
        lbl_dens_src->setText(QApplication::translate("UserInterface", "\320\230\321\201\321\202\320\276\321\207\320\275\320\270\320\272 \320\262\320\265\321\211\320\265\321\201\321\202\320\262\320\260:", 0));
        lbl_v_up->setText(QApplication::translate("UserInterface", "\320\241\320\272\320\276\321\200\320\276\321\201\321\202\321\214 \320\277\320\276\320\264\321\212\320\265\320\274\320\260:", 0));
        lbl_v_side->setText(QApplication::translate("UserInterface", "\320\221\320\276\320\272\320\276\320\262\321\213\320\265 \321\201\320\272\320\276\321\200\320\276\321\201\321\202\320\270:", 0));
        lbl_v_flucts->setText(QApplication::translate("UserInterface", "\320\244\320\273\321\203\320\272\321\202\321\203\320\260\321\206\320\270\320\270 (OY):", 0));
        lbl_u_flucts->setText(QApplication::translate("UserInterface", "\320\244\320\273\321\203\320\272\321\202\321\203\320\260\321\206\320\270\320\270 (OX):", 0));
        btn_save->setText(QApplication::translate("UserInterface", "\320\241\320\276\321\205\321\200\320\260\320\275\320\270\321\202\321\214", 0));
        btn_restore->setText(QApplication::translate("UserInterface", "\320\227\320\260\320\263\321\200\321\203\320\267\320\270\321\202\321\214", 0));
        btn_launch->setText(QApplication::translate("UserInterface", "\320\227\320\260\320\277\321\203\321\201\320\272 / \320\237\320\260\321\203\320\267\320\260", 0));
    } // retranslateUi

};

namespace Ui {
    class UserInterface: public Ui_UserInterface {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_USERINTERFACE_H
