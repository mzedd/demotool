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
    clip->setDuration(42.0f);
    model->addClip(clip);
    clip = new Clip("Tach");
    clip->setDuration(53.0f);
    model->addClip(clip);


    ui->tableView->setModel(model);
    ui->timelineView->setModel(model);

    connect(ui->pb_addClip, SIGNAL(clicked()), ui->timelineView, SLOT(addClip()));
    connect(ui->pb_deleteClip, SIGNAL(clicked()), ui->timelineView, SLOT(removeClip()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

