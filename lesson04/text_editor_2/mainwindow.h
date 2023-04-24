#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QString>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }

class QTranslator;
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_actionOpen_triggered();

    void on_actionSaveAs_triggered();

    void on_actionRussian_triggered();

    void on_actionEnglish_triggered();

    void on_actionOpen_read_mode_triggered();

private:
    enum class Lang {
        rus,
        eng
    };


    Ui::MainWindow *ui;
    QTranslator* translator;
    Lang curLang = Lang::rus;

    QString path;

    void translate(Lang lang);
};
#endif // MAINWINDOW_H
