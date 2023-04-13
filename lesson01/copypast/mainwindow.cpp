#include "mainwindow.h"

#include <QHBoxLayout>
#include <QVBoxLayout>

#include <QDoubleSpinBox>
#include <QLabel>
#include <QPushButton>
#include <QWidget>

#include <QPlainTextEdit>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    setWindowTitle(tr("Копирование и вставка текста"));

    auto *mainLayout = new QVBoxLayout();
    mainLayout->setMargin(10);
    mainLayout->setSpacing(20);

    auto *layoutOne = new QHBoxLayout();

    plainTextOne = new QPlainTextEdit(this);
    layoutOne->addWidget(plainTextOne);

    plainTextTwo = new QPlainTextEdit(this);
    layoutOne->addWidget(plainTextTwo);

    mainLayout->addLayout(layoutOne);

    auto *buttonLayout = new QHBoxLayout();

    buttonOne = new QPushButton(this);
    buttonOne->setText(tr("Слева добавить текст"));
    buttonLayout->addWidget(buttonOne);

    buttonTwo = new QPushButton(this);
    buttonTwo->setText(tr("Справо заменить текст"));
    buttonLayout->addWidget(buttonTwo);

    buttonThree = new QPushButton(this);
    buttonThree->setText(tr("Слева добавить HTML"));
    buttonLayout->addWidget(buttonThree);

    auto *horizontalSpacer = new QSpacerItem(
            40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);
    buttonLayout->addItem(horizontalSpacer);

    mainLayout->addLayout(buttonLayout);

    auto *verticalSpacer = new QSpacerItem(
            20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);
    mainLayout->addItem(verticalSpacer);

    connect(buttonOne, &QAbstractButton::clicked, this,
            &MainWindow::buttonOneClicked);
    connect(buttonTwo, &QAbstractButton::clicked, this,
            &MainWindow::buttonTwoClicked);
    connect(buttonThree, &QAbstractButton::clicked, this,
            &MainWindow::buttonThreeClicked);

    auto *widget = new QWidget(this);
    widget->setLayout(mainLayout);

    setCentralWidget(widget);
}

MainWindow::~MainWindow() = default;

void MainWindow::buttonOneClicked(bool /*value*/)
{

    plainTextOne->appendPlainText(plainTextTwo->toPlainText());
}

void MainWindow::buttonTwoClicked(bool /*value*/)
{
    plainTextTwo->setPlainText(plainTextOne->toPlainText());
}

void MainWindow::buttonThreeClicked(bool /*value*/)
{
    plainTextOne->appendHtml(
            QString::fromUtf8("<font color='red'>Hello</font>"));
}
