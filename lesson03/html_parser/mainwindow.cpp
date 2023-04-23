#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <QFile>
#include <QTextStream>
#include <QFileDialog>
#include <QRegularExpression>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    const QString fileName = QFileDialog::getOpenFileName(
            this, ("Open HTML file"), path, ("Text Files (*.htm, *.html)"));
    path = QFileInfo(fileName).path();
    QFile file(fileName);
    file.open(QIODevice::ReadOnly);
    QTextStream stream(&file);
    const QString text = stream.readAll();

    const QRegularExpression re(
            R"---(data-testid="weather-temp">([^>]+)</span>)---");
    auto it = re.globalMatch(text);
    while (it.hasNext()) {
        auto match = it.next();
        ui->tempLineEdit->setText(match.captured(1));
    }

    const QRegularExpression re2(
            R"---(<div\b[^>]*class="rate__currency[^>]*>([\s\S]*?)<\/div>)---");
    it = re2.globalMatch(text);
    if (it.hasNext()) {
        auto match = it.next();
        ui->UsdLineEdit->setText(match.captured(1));
    }
    if (it.hasNext()) {
        auto match = it.next();
        ui->EuroLineEdit->setText(match.captured(1));
    }

    file.close();
}
