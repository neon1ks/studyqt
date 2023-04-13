#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class QLabel;
class QDoubleSpinBox;
class QRadioButton;
class QPushButton;

class MainWindow final: public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow() final;


private:
    QLabel *labelInfo;

    QLabel *labelSideOne;
    QDoubleSpinBox *spinBoxSideOne;

    QLabel *labelSideTwo;
    QDoubleSpinBox *spinBoxSideTwo;

    QLabel *labelAngle;
    QDoubleSpinBox *spinBoxAngle;
    QRadioButton *radioButtonDeg;
    QRadioButton *radioButtonRad;

    QPushButton *pushButton;
    QLabel *labelAnswer;

    void spinBoxValueChanged(double value);
    void findAnswer(bool value);
    void radioButtonToggled(bool checked);
};
#endif // MAINWINDOW_H
