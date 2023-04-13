#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
class QPushButton;
class QPlainTextEdit;
QT_END_NAMESPACE

class MainWindow final : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow() final;

private:
    QPlainTextEdit *plainTextOne;
    QPlainTextEdit *plainTextTwo;
    QPushButton *buttonOne;
    QPushButton *buttonTwo;
    QPushButton *buttonThree;

    void buttonOneClicked(bool value);
    void buttonTwoClicked(bool value);
    void buttonThreeClicked(bool value);
};
#endif // MAINWINDOW_H
