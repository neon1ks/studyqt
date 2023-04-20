#include "mainwindow.h"

#include <QVBoxLayout>
#include <QLabel>
#include <QTextBrowser>
#include <QTextCursor>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{

    verticalLayout = new QVBoxLayout;
    label = new QLabel(this);
    label->setText(
            QString::fromUtf8("Поддерживается: #@COP@  #@PRO@  #@EUR@  #@RUB@"));
    textBrowser = new QTextBrowser(this);
    textBrowser->setReadOnly(false);

    verticalLayout->addWidget(label);
    verticalLayout->addWidget(textBrowser);

    auto *widget = new QWidget(this);
    widget->setLayout(verticalLayout);
    setCentralWidget(widget);

    connect(textBrowser, &QTextEdit::textChanged, this,
            &MainWindow::slotTextChanged);
}

MainWindow::~MainWindow() = default;

void MainWindow::slotTextChanged()
{
    convert.setText(textBrowser->toPlainText(), textBrowser->textCursor().position());
    if (convert.isChanged()) {
        const auto text = convert.getTest();
        int len = text.size();

        textBrowser->setPlainText(text);
        QTextCursor cursor = textBrowser->textCursor();
        const int pos = convert.getPos();

        cursor.setPosition(pos);
        textBrowser->setTextCursor(cursor);
    }
}
