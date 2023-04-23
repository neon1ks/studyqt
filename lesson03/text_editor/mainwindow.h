#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QString>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;

    MainWindow(const MainWindow &obj) = delete;
    MainWindow &operator=(const MainWindow &obj) = delete;
    MainWindow(MainWindow &&obj) = delete;
    MainWindow &operator=(MainWindow &&obj) = delete;

private slots:
    void on_openPushButton_clicked();
    void on_savePushButton_clicked();
    void on_helpPushButton_clicked();

private:
    Ui::MainWindow *ui;
    QString path;
};
#endif // MAINWINDOW_H
