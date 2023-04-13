#include "mainwindow.h"

#include <QHBoxLayout>
#include <QVBoxLayout>

#include <QDoubleSpinBox>
#include <QLabel>
#include <QPushButton>
#include <QWidget>

#include <cmath>
#include <sstream>

constexpr double Zero = 0.000000000001;

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    setWindowTitle(tr("Квадратное уравнение"));

    auto *mainLayout = new QHBoxLayout();

    auto *verticalLayout = new QVBoxLayout();
    verticalLayout->setMargin(10);
    verticalLayout->setSpacing(20);

    labelInfo = new QLabel(this);
    labelInfo->setText(
            tr("Введите параметры квадраного уравнения A*x^2 + B*x + C = 0 :"));

    verticalLayout->addWidget(labelInfo);

    auto *inputLayout = new QHBoxLayout();

    labelA = new QLabel(this);
    labelA->setText(tr("A: "));
    inputLayout->addWidget(labelA);

    spinBoxA = new QDoubleSpinBox(this);
    spinBoxA->setButtonSymbols(QAbstractSpinBox::NoButtons);
    spinBoxA->setFixedWidth(150);
    spinBoxA->setMinimum(-1'000'000);
    spinBoxA->setMaximum(1'000'000);
    inputLayout->addWidget(spinBoxA);

    labelB = new QLabel(this);
    labelB->setText(tr("B: "));
    inputLayout->addWidget(labelB);

    spinBoxB = new QDoubleSpinBox(this);
    spinBoxB->setButtonSymbols(QAbstractSpinBox::NoButtons);
    spinBoxB->setFixedWidth(150);
    spinBoxB->setMinimum(-1'000'000);
    spinBoxB->setMaximum(1'000'000);
    inputLayout->addWidget(spinBoxB);

    labelC = new QLabel(this);
    labelC->setText(tr("C: "));
    inputLayout->addWidget(labelC);

    spinBoxC = new QDoubleSpinBox(this);
    spinBoxC->setButtonSymbols(QAbstractSpinBox::NoButtons);
    spinBoxC->setFixedWidth(150);
    spinBoxC->setMinimum(-1'000'000);
    spinBoxC->setMaximum(1'000'000);
    inputLayout->addWidget(spinBoxC);

    verticalLayout->addLayout(inputLayout);

    auto *buttonLayout = new QHBoxLayout();

    auto *horizontalSpacer1 = new QSpacerItem(
            40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

    buttonLayout->addItem(horizontalSpacer1);

    pushButton = new QPushButton(this);
    pushButton->setText(tr("Решить"));
    pushButton->setObjectName(QString::fromUtf8("pushButton"));

    buttonLayout->addWidget(pushButton);

    auto *horizontalSpacer2 = new QSpacerItem(
            40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);
    buttonLayout->addItem(horizontalSpacer2);

    verticalLayout->addLayout(buttonLayout);

    labelAnswer = new QLabel(this);
    verticalLayout->addWidget(labelAnswer);

    auto *verticalSpacer = new QSpacerItem(
            20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);
    verticalLayout->addItem(verticalSpacer);

    mainLayout->addLayout(verticalLayout);

    auto *horizontalSpacer = new QSpacerItem(
            89, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);
    mainLayout->addItem(horizontalSpacer);

    connect(spinBoxA, QOverload<double>::of(&QDoubleSpinBox::valueChanged),
            this, &MainWindow::spinBoxValueChanged);
    connect(spinBoxB, QOverload<double>::of(&QDoubleSpinBox::valueChanged),
            this, &MainWindow::spinBoxValueChanged);
    connect(spinBoxC, QOverload<double>::of(&QDoubleSpinBox::valueChanged),
            this, &MainWindow::spinBoxValueChanged);

    connect(pushButton, &QAbstractButton::clicked, this,
            &MainWindow::findAnswer);

    auto *widget = new QWidget(this);
    widget->setLayout(mainLayout);

    setCentralWidget(widget);
}

MainWindow::~MainWindow() { }

void MainWindow::spinBoxValueChanged(double /*value*/)
{
    labelAnswer->setText(tr(""));
}

void MainWindow::findAnswer(bool /*value*/)
{
    const double a = spinBoxA->value();
    const double b = spinBoxB->value();
    const double c = spinBoxC->value();

    if (std::abs(a) > Zero) {
        const double d = std::sqrt(b * b - 4 * a * c);
        if (d > 0) {
            const double x1 = (-b + d) / (2 * a);
            const double x2 = (-b - d) / (2 * a);

            std::ostringstream ss;
            ss << "x1 = " << x1 << ", x2 = " << x2;
            labelAnswer->setText(QString::fromStdString(ss.str()));

        } else if (std::abs(d) <= Zero) {
            const double x = (-b) / (2 * a);

            std::ostringstream ss;
            ss << "x = " << x;
            labelAnswer->setText(QString::fromStdString(ss.str()));

        } else {
            labelAnswer->setText(tr("Корней нету"));
        }
    } else if (std::abs(b) > Zero) {
        const double x = (-c) / b;

        std::ostringstream ss;
        ss << "x = " << x;
        labelAnswer->setText(QString::fromStdString(ss.str()));
    }
}
