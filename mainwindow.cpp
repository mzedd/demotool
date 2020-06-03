#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "demo/timelinemodel.h"
#include "demo/timelineview.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    model = new TimelineModel();

    Clip *clip = new Clip("clip1");
    clip->setDuration(25.0f);
    model->addClip(clip);
    clip = new Clip("moin1");
    clip->setDuration(1337.0f);
    model->addClip(clip);


    ui->tableView->setModel(model);
    ui->timelineView->setModel(model);
}

MainWindow::~MainWindow()
{
    delete ui;
}

