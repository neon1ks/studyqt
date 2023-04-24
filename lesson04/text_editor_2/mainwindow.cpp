#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <QTranslator>

#include <QApplication>
#include <QLocale>
#include <QTranslator>

#include <QFile>
#include <QTextStream>
#include <QFileDialog>
#include <QMessageBox>

#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    translator = new QTranslator(this);
    translate(Lang::rus);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionOpen_triggered()
{
    const QString fileName = QFileDialog::getOpenFileName(
            this, tr("Open text"), path, (tr("Text Files (*.txt)")));
    if (!fileName.isEmpty()) {
        path = fileName;
        QFile file(fileName);
        file.open(QIODevice::ReadOnly);
        QTextStream textStream(&file);
        ui->plainTextEdit->setPlainText(textStream.readAll());
        file.close();

        ui->plainTextEdit->setReadOnly(false);
        ui->statusbar->showMessage(tr("Normal mode"));
    }
}

void MainWindow::on_actionSaveAs_triggered()
{
    qDebug() << "path = " << path;
    const QString fileName = QFileDialog::getSaveFileName(
            this, tr("Save text"), path, (tr("Text Files (*.txt)")));
    if (!fileName.isEmpty()) {
        QFile file(fileName + ".txt");
        file.open(QIODevice::WriteOnly);
        QTextStream textStream(&file);
        textStream << ui->plainTextEdit->toPlainText();
        file.flush();
        file.close();
    }
}

void MainWindow::on_actionRussian_triggered()
{
    if (curLang != Lang::rus) {
        translate(Lang::rus);
        curLang = Lang::rus;

        ui->actionRussian->setChecked(true);
        ui->actionEnglish->setChecked(false);
    }
}

void MainWindow::on_actionEnglish_triggered()
{
    if (curLang != Lang::eng) {
        translate(Lang::eng);
        curLang = Lang::eng;

        ui->actionRussian->setChecked(false);
        ui->actionEnglish->setChecked(true);
    }
}

void MainWindow::on_actionOpen_read_mode_triggered()
{
    const QString fileName = QFileDialog::getOpenFileName(
            this, tr("Open text"), path, (tr("Text Files (*.txt)")));
    if (!fileName.isEmpty()) {


        path = fileName;
        QFile file(fileName);
        file.open(QIODevice::ReadOnly);
        QTextStream textStream(&file);
        ui->plainTextEdit->setPlainText(textStream.readAll());
        file.close();

        ui->plainTextEdit->setReadOnly(true);
        ui->statusbar->showMessage(tr("Only read mode"));
    }
}

void MainWindow::translate(Lang lang)
{
    switch (lang) {
    case Lang::rus:
        translator->load("://i18n/text_editor_2_ru_RU.qm");
        QApplication::installTranslator(translator);
        break;
    case Lang::eng:
        QApplication::removeTranslator(translator);
        break;
    }
    ui->retranslateUi(this);
}
