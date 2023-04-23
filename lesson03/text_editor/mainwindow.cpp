#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <QFile>
#include <QTextStream>
#include <QFileDialog>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_openPushButton_clicked()
{
    const QString fileName = QFileDialog::getOpenFileName(
            this, tr("Open text"), path, (tr("Text Files (*.txt)")));
    path = QFileInfo(fileName).path();
    QFile file(fileName);
    file.open(QIODevice::ReadOnly);
    QTextStream textStream(&file);
    ui->plainTextEdit->setPlainText(textStream.readAll());
    file.close();
}

void MainWindow::on_savePushButton_clicked()
{
    const QString fileName = QFileDialog::getSaveFileName(
            this, tr("Save text"), path, (tr("Text Files (*.txt)")));
    QFile file(fileName + ".txt");
    file.open(QIODevice::WriteOnly);
    QTextStream textStream(&file);
    textStream << ui->plainTextEdit->toPlainText();
    file.flush();
    file.close();
}

void MainWindow::on_helpPushButton_clicked()
{
    QFile file(":/help.txt");
    file.open(QIODevice::ReadOnly);
    QTextStream in(&file);

    QMessageBox msgBox;
    msgBox.setWindowTitle("Help");
    msgBox.setText(in.readAll());
    msgBox.exec();

    file.close();
}
