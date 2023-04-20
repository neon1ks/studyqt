#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "convert.h"

QT_BEGIN_NAMESPACE
class QVBoxLayout;
class QLabel;
class QTextBrowser;
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;

private slots:
    void slotTextChanged();

private:
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QTextBrowser *textBrowser;

    Convert convert;
};
#endif // MAINWINDOW_H
