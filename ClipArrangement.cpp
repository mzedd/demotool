#include "ClipArrangement.h"
#include "ui_cliparrangement.h"

#include "src/demo/timelinemodel.h"

#include <QModelIndex>

#include "src/scene/Scene.h"

ClipArrangement::ClipArrangement(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ClipArrangement)
{
    ui->setupUi(this);

    model = new TimelineModel(); 
    ui->timelineView->setModel(model);

    connect(ui->timelineView, SIGNAL(zoomChanged(QString)), ui->lbl_zoom, SLOT(setText(QString)));
    connect(ui->timelineView, SIGNAL(clipSelectionChanged(Clip*)), this, SLOT(updateInspector()));
    connect(ui->timelineView, SIGNAL(clipSelectionChanged(Clip*)), ui->openGLWidget, SLOT(clipSelectionChanged(Clip*)));
    connect(ui->pb_play_pause, SIGNAL(clicked()), ui->openGLWidget, SLOT(togglePlay()));
    connect(ui->timelineView, SIGNAL(cursorUpdated(float)), ui->openGLWidget, SLOT(cursorChanged(float)));
    connect(ui->openGLWidget, SIGNAL(timeChanged(float)), this, SLOT(updateTime(float)));
    connect(ui->timelineView, SIGNAL(cursorUpdated(float)), this, SLOT(updateTime(float)));
    connect(ui->openGLWidget, SIGNAL(timeChanged(float)), ui->timelineView, SLOT(updateCursor(float)));
}

ClipArrangement::~ClipArrangement()
{
    delete ui;
}

void ClipArrangement::updateInspector()
{
    QModelIndex index = model->index(ui->timelineView->currentIndex().row(), 0);
    ui->le_clip_name->setText(model->data(index).toString());

    QModelIndex sceneIndex = model->index(ui->timelineView->currentIndex().row(), 2);
    ui->cb_sceneSelector->clear();
    ui->cb_sceneSelector->addItem(model->data(sceneIndex).toString());
}

void ClipArrangement::updateTime(float time)
{
    ui->lbl_time->setText(QString("%1").arg(time));
}
