#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QMap>
#include <QString>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }

class QStandardItemModel;
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_addPushButton_clicked();
    void on_dekPushButton_clicked();
    void on_checkBox_clicked(bool checked);

    void on_upPushButton_clicked();

    void on_downPushButton_clicked();

private:
    Ui::MainWindow *ui;
    QMap<QString, QString> languages;

    QStandardItemModel *model;
};
#endif // MAINWINDOW_H
