#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
class QLabel;
class QDoubleSpinBox;
class QPushButton;
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    QLabel *labelInfo;

    QLabel *labelA;
    QDoubleSpinBox *spinBoxA;

    QLabel *labelB;
    QDoubleSpinBox *spinBoxB;

    QLabel *labelC;
    QDoubleSpinBox *spinBoxC;

    QPushButton *pushButton;

    QLabel *labelAnswer;

    void spinBoxValueChanged(double value);
    void findAnswer(bool value);
};
#endif // MAINWINDOW_H
