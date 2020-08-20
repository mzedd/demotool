#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "demo/timelinemodel.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    TimelineModel* model;
};
#endif // MAINWINDOW_H
