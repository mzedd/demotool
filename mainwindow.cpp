#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "demo/timelinemodel.h"
#include "demo/timelineview.h"

#include <QGraphicsScene>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setFont(QFont("Fira Mono"));
}

MainWindow::~MainWindow()
{
    delete ui;
}

