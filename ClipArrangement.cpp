#include "ClipArrangement.h"
#include "ui_cliparrangement.h"

#include "src/demo/timelinemodel.h"

ClipArrangement::ClipArrangement(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ClipArrangement)
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

    ui->timelineView->setModel(model);
    ui->inspector->setModel(model);

    ui->lbl_zoom->setFont(QFont("Fira Mono"));

    connect(ui->timelineView, SIGNAL(zoomChanged(QString)), ui->lbl_zoom, SLOT(setText(QString)));
}

ClipArrangement::~ClipArrangement()
{
    delete ui;
}
