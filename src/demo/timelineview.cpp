#include "timelineview.h"

#include <QPainter>
#include <QMouseEvent>
#include <QDebug>

TimelineView::TimelineView(QWidget *parent)
    : QAbstractItemView(parent)
{
    cursor.setLine(100, this->y(), 100, this->height()+200);

    setSelectionMode(QAbstractItemView::SelectionMode::SingleSelection);
    setSelectionBehavior(QAbstractItemView::SelectionBehavior::SelectItems);
}

void TimelineView::paintEvent(QPaintEvent*) {
    QPainter painter(this->viewport());
    painter.setBrush(Qt::red);
    painter.drawRect(viewport()->rect());

    QPen pen;
    pen.setColor(Qt::black);
    pen.setStyle(Qt::PenStyle::SolidLine);
    pen.setWidth(2);
    painter.setPen(pen);

    // draw vertical lines
    float y = 80;
    QVector<QLineF> lines;
    for(int i = 0; i < 5; i++) {
        y = 80 + i*20;
        lines.append(QLineF(0, y, viewport()->rect().width(), y));
    }
    painter.drawLines(lines);

    // draw clips
    QRectF clip = QRectF();
    clip.setY(10);
    clip.setHeight(50); 
    for(int i = 0; i < model()->rowCount(); i++) {
        QModelIndex index = model()->index(i, 0);

        if(currentIndex() == index) {
            painter.setBrush(Qt::red);
        } else {
            painter.setBrush(Qt::blue);
        }

        clip = visualRect(index);
        painter.drawRect(clip);
    }

    qDebug() << currentIndex().row();

    // draw cursor
    painter.drawLine(cursor);
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
    clip.setWidth(model()->data(model()->index(index.row(), 1), Qt::DisplayRole).toDouble());
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
    QModelIndex current = currentIndex();
    QModelIndex tmp;

    switch(cursorAction) {
    case MoveRight:
        tmp = model()->index(current.row()+1, current.column());
        break;
    case MoveLeft:
        tmp = model()->index(current.row()-1, current.column());
        break;
    default:
        break;
    }

    if(tmp.isValid())
        return tmp;

    return current;
}

int TimelineView::horizontalOffset() const
{
    return 0;
}

int TimelineView::verticalOffset() const
{
    return 0;
}

bool TimelineView::isIndexHidden(const QModelIndex& /*index*/) const
{
    return false;
}

void TimelineView::setSelection(const QRect &rect, QItemSelectionModel::SelectionFlags command)
{

}

QRegion TimelineView::visualRegionForSelection(const QItemSelection& /*selection*/) const
{
    return QRegion(viewport()->rect()); //TODO: optimieren
    //return QRegion(0,0,0,0);
}

void TimelineView::mousePressEvent(QMouseEvent *event)
{
    switch(event->button()) {
    case Qt::LeftButton:
        viewport()->update();
        break;
    default:
        break;
    }
}

void TimelineView::dataChanged(const QModelIndex &topLeft, const QModelIndex &bottomRight, const QVector<int> &roles)
{
    viewport()->update();
}
