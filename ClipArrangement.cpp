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


    // memory leaks
    Scene *s = new Scene();
    s->name = QString("erste Scene");
    Clip *clip = new Clip("clip1");
    clip->setDuration(25.0f);
    clip->attachScene(s);
    model->addClip(clip);
    clip = new Clip("moin1");
    clip->setDuration(42.0f);
    s = new Scene();
    s->name = QString("zweite Scene");
    clip->attachScene(s);
    model->addClip(clip);
    clip = new Clip("Tach");
    clip->setDuration(53.0f);
    s = new Scene();
    s->name = QString("dritte Scene");
    clip->attachScene(s);
    model->addClip(clip);

    ui->timelineView->setModel(model);

    connect(ui->timelineView, SIGNAL(zoomChanged(QString)), ui->lbl_zoom, SLOT(setText(QString)));
    connect(ui->timelineView, SIGNAL(clipSelectionChanged()), this, SLOT(updateInspector()));
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
