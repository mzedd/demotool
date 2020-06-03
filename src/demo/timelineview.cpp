#include "timelineview.h"

#include <QPainter>

TimelineView::TimelineView(QWidget *parent)
    : QAbstractItemView(parent)
{
    currentClip = QModelIndex();
}

void TimelineView::paintEvent(QPaintEvent*) {
    QPainter painter(this->viewport());
    QRectF size(10, 10, this->width()-10, this->width()-10);
    painter.setBrush(Qt::red);
    QRectF background(0,0, 200, 100);
    painter.drawRect(background);

    painter.setBrush(Qt::blue);

    QRectF clip = QRectF();
    clip.setY(10);
    clip.setHeight(50);


    for(int i = 0; i < model()->rowCount(); i++) {
        QModelIndex index = model()->index(i, 1);
        clip = visualRect(index);
        painter.drawRect(clip);
    }
}

QRect TimelineView::visualRect(const QModelIndex &index) const
{
    QRect clip = QRect();
    if(index.row() > 0) {
        QModelIndex newIndex = model()->index(index.row()-1, 1);
        clip.setX(model()->data(newIndex, Qt::DisplayRole).toDouble()+10);
    } else {
        clip.setX(0);
    }
    clip.setY(10);
    clip.setHeight(50);
    clip.setWidth(model()->data(index, Qt::DisplayRole).toDouble());
    return clip;

}

void TimelineView::scrollTo(const QModelIndex &index, QAbstractItemView::ScrollHint hint)
{

}

QModelIndex TimelineView::indexAt(const QPoint &point) const
{
    QRect clip;
    QModelIndex index;
    for(int i = 0; i < model()->rowCount(); i++) {
        index = model()->index(i, 0);
        clip = visualRect(index);
        if(clip.contains(point)) {
            return index;
        }
    }
    return QModelIndex();
}

QModelIndex TimelineView::moveCursor(QAbstractItemView::CursorAction cursorAction, Qt::KeyboardModifiers modifiers)
{
    switch(cursorAction) {
    case QAbstractItemView::CursorAction::MoveRight:
        currentClip = model()->index(currentClip.row()+1,currentClip.column());
        break;
    default:
        break;
    }
    return currentClip;
}

int TimelineView::horizontalOffset() const
{
    return 0;
}

int TimelineView::verticalOffset() const
{
    return 0;
}

bool TimelineView::isIndexHidden(const QModelIndex &index) const
{
    return false;
}

void TimelineView::setSelection(const QRect &rect, QItemSelectionModel::SelectionFlags command)
{

}

QRegion TimelineView::visualRegionForSelection(const QItemSelection &selection) const
{
    return QRegion(viewport()->rect()); //TODO: optimieren
    //return QRegion(0,0,0,0);
}

void TimelineView::dataChanged(const QModelIndex &topLeft, const QModelIndex &bottomRight, const QVector<int> &roles)
{
    viewport()->update();
}
