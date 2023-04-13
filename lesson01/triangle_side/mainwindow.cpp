#include "mainwindow.h"

#include <QHBoxLayout>
#include <QVBoxLayout>

#include <QDoubleSpinBox>
#include <QLabel>
#include <QPushButton>
#include <QWidget>
#include <QRadioButton>

#include <cmath>
#include <sstream>

#include <QtMath>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{

    //QLabel *labelSideOne;
    //QDoubleSpinBox *spinBoxSideOne;

    //QLabel *labelSideTwo;
    //QDoubleSpinBox *spinBoxSideTwo;

    //QLabel *labelAngle;
    //QDoubleSpinBox *spinBoxAngle;
    //QRadioButton *radioButtonDeg;
    //QRadioButton *radioButtonRad;

    //QPushButton *PushButton;
    //QLabel *labelAnswer;

    setWindowTitle(tr("Сторона треугольника"));

    auto *mainLayout = new QHBoxLayout();

    auto *verticalLayout = new QVBoxLayout();
    verticalLayout->setMargin(10);
    verticalLayout->setSpacing(20);

    labelInfo = new QLabel(this);
    labelInfo->setText(tr("Нахождение стороны треугольника"));

    verticalLayout->addWidget(labelInfo);

    auto *inputLayoutOne = new QHBoxLayout();

    labelSideOne = new QLabel(this);
    labelSideOne->setText(tr("Сторона 1: "));
    inputLayoutOne->addWidget(labelSideOne);

    spinBoxSideOne = new QDoubleSpinBox(this);
    spinBoxSideOne->setButtonSymbols(QAbstractSpinBox::NoButtons);
    spinBoxSideOne->setMinimumSize(QSize(122, 0));
    spinBoxSideOne->setMinimum(-1'000'000);
    spinBoxSideOne->setMaximum(1'000'000);
    inputLayoutOne->addWidget(spinBoxSideOne);

    labelSideTwo = new QLabel(this);
    labelSideTwo->setText(tr("Сторона 2: "));
    inputLayoutOne->addWidget(labelSideTwo);

    spinBoxSideTwo = new QDoubleSpinBox(this);
    spinBoxSideTwo->setButtonSymbols(QAbstractSpinBox::NoButtons);
    spinBoxSideTwo->setMinimumSize(QSize(122, 0));
    spinBoxSideTwo->setMinimum(-1'000'000);
    spinBoxSideTwo->setMaximum(1'000'000);
    inputLayoutOne->addWidget(spinBoxSideTwo);

    verticalLayout->addLayout(inputLayoutOne);

    auto *inputLayoutTwo = new QHBoxLayout();

    labelAngle = new QLabel(this);
    labelAngle->setText(tr("Угол между сторонами"));
    inputLayoutTwo->addWidget(labelAngle);

    spinBoxAngle = new QDoubleSpinBox(this);
    spinBoxAngle->setMinimumSize(QSize(122, 0));
    spinBoxAngle->setDecimals(4);
    inputLayoutTwo->addWidget(spinBoxAngle);

    radioButtonDeg = new QRadioButton(this);
    radioButtonDeg->setText(tr("Градусы"));
    radioButtonDeg->setChecked(true);
    inputLayoutTwo->addWidget(radioButtonDeg);

    radioButtonRad = new QRadioButton(this);
    radioButtonRad->setChecked(false);
    radioButtonRad->setText(tr("Радианы"));
    inputLayoutTwo->addWidget(radioButtonRad);

    verticalLayout->addLayout(inputLayoutTwo);

    auto *buttonLayout = new QHBoxLayout();

    pushButton = new QPushButton(this);
    pushButton->setText(tr("Расчитать"));
    pushButton->setObjectName(QString::fromUtf8("pushButton"));

    buttonLayout->addWidget(pushButton);

    labelAnswer = new QLabel(this);
    buttonLayout->addWidget(labelAnswer);

    verticalLayout->addLayout(buttonLayout);

    auto *verticalSpacer = new QSpacerItem(
            20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);
    verticalLayout->addItem(verticalSpacer);

    mainLayout->addLayout(verticalLayout);

    auto *horizontalSpacer = new QSpacerItem(
            89, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);
    mainLayout->addItem(horizontalSpacer);

    connect(spinBoxSideOne,
            QOverload<double>::of(&QDoubleSpinBox::valueChanged), this,
            &MainWindow::spinBoxValueChanged);
    connect(spinBoxSideTwo,
            QOverload<double>::of(&QDoubleSpinBox::valueChanged), this,
            &MainWindow::spinBoxValueChanged);
    connect(spinBoxAngle, QOverload<double>::of(&QDoubleSpinBox::valueChanged),
            this, &MainWindow::spinBoxValueChanged);

    connect(radioButtonDeg, &QAbstractButton::toggled, this,
            &MainWindow::radioButtonToggled);

    connect(pushButton, &QAbstractButton::clicked, this,
            &MainWindow::findAnswer);

    auto *widget = new QWidget(this);
    widget->setLayout(mainLayout);

    setCentralWidget(widget);
}

MainWindow::~MainWindow() = default;

void MainWindow::spinBoxValueChanged(double /*value*/)
{
    labelAnswer->setText(tr(""));
}

void MainWindow::findAnswer(bool /*value*/)
{
    const double sideOne = spinBoxSideOne->value();
    const double sideTwo = spinBoxSideTwo->value();

    const double angle =
            (radioButtonDeg->isChecked() ? (spinBoxAngle->value() * M_PI / 180.)
                                         : spinBoxAngle->value());

    const double sideThree = qSqrt(qPow(sideOne, 2) + qPow(sideTwo, 2)
                                   - 2 * sideOne * sideTwo * qCos(angle));

    std::ostringstream ss;
    ss << "side = " << sideThree;
    labelAnswer->setText(QString::fromStdString(ss.str()));
}

void MainWindow::radioButtonToggled(bool checked)
{
    const double angle = spinBoxAngle->value();
    if (checked) {
        spinBoxAngle->setValue(angle * 180. / M_PI);
    } else {
        spinBoxAngle->setValue(angle * M_PI / 180.);
    }
}
