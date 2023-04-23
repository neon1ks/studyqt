#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <QMap>
#include <QStandardItemModel>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    languages["C++"] = ":/icons/text-x-cpp.png";
    languages["C#"] = ":/icons/text-x-csharp.png";
    languages["Go"] = ":/icons/text-x-go.png";
    languages["Java"] = ":/icons/text-x-java.png";
    languages["JavaScript"] = ":/icons/text-x-javascript.png";
    languages["PHP"] = ":/icons/text-x-php.png";
    languages["Python"] = ":/icons/text-x-python.png";

    model = new QStandardItemModel(languages.size(), 1, this);

    int pos = 0;
    for (auto it = languages.cbegin(); it != languages.cend(); ++it, ++pos) {
        const QModelIndex index = model->index(pos, 0);
        model->setData(index, it.key(), Qt::DisplayRole);
        model->setData(index, QIcon(it.value()), Qt::DecorationRole);
    }

    ui->listView->setModel(model);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_addPushButton_clicked()
{
    const QModelIndex index = ui->listView->currentIndex();
    ui->listView->model()->insertRow(index.row());
    ui->listView->model()->setData(index,
                                   QApplication::style()->standardIcon(QStyle::SP_FileIcon),
                                   Qt::DecorationRole);
    ui->listView->model()->setData(index, tr("New Language"), Qt::DisplayRole);
}

void MainWindow::on_dekPushButton_clicked()
{
    const QModelIndex index = ui->listView->currentIndex();
    if (index.isValid()) {
        ui->listView->model()->removeRow(index.row());
    }
}

void MainWindow::on_checkBox_clicked(bool checked)
{
    if (checked) {
        ui->listView->setViewMode(QListView::IconMode);
    } else {
        ui->listView->setViewMode(QListView::ListMode);
    }
}

void MainWindow::on_upPushButton_clicked()
{
    const QModelIndex index = ui->listView->currentIndex();
    if (index.row() - 1 >= 0) {
        auto *item1 = model->takeItem(index.row());
        auto *item2 = model->takeItem(index.row() - 1);
        model->setItem(index.row() - 1, 0, item1);
        model->setItem(index.row(), 0, item2);
        ui->listView->setCurrentIndex(index);
    }
}

void MainWindow::on_downPushButton_clicked()
{
    const QModelIndex index = ui->listView->currentIndex();
    if (index.row() + 1 < model->rowCount()) {
        auto *item1 = model->takeItem(index.row());
        auto *item2 = model->takeItem(index.row() + 1);
        model->setItem(index.row() + 1, 0, item1);
        model->setItem(index.row(), 0, item2);
        ui->listView->setCurrentIndex(index);
    }
}
