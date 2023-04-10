#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "maincontroller.h"
#include "resulttextviewcontroller.h"


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class SelectionScreen;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    MainController *mainController;
    ResultTextViewController *resultTextController;
    QList<SelectionScreen*> selectionScreens;

private slots:
    void startSelection();
    void onCaptureScreen();
    void capture();
    void closeScreens();
};
#endif // MAINWINDOW_H
