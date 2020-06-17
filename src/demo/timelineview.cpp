#include "timelineview.h"

#include <QPainter>
#include <QMouseEvent>
#include <QDebug>
#include <QMenu>
#include <QDrag>
#include <QRubberBand>
#include <QHBoxLayout>

constexpr int PIXELS_PER_SECOND = 10;
constexpr int TIMEAXIS_HEIGHT = 30;
constexpr int TIMEAXIS_TICK_PER_SECOND = 1;
constexpr float CLIP_HEIGHT = 50.0f;
constexpr float SCROLL_TO_ZOOM_SCALE = 0.001f;
constexpr float MIN_ZOOM = 0.5f;
constexpr float MAX_ZOOM = 10.0f;
constexpr int CURSOR_WIDTH = 2;

TimelineView::TimelineView(QWidget *parent)
    : QAbstractItemView(parent)
{
    setSelectionMode(QAbstractItemView::SelectionMode::SingleSelection);
    setSelectionBehavior(QAbstractItemView::SelectionBehavior::SelectItems);

    zoom = 1.0f;

    cursor = new QRect(20, 0, 3, 300);

    dragState = DragState::none;

    setMouseTracking(true);
}

void TimelineView::paintEvent(QPaintEvent*) {
    QPainter painter(this->viewport());

    QPen pen;
    pen.setColor(Qt::black);
    pen.setStyle(Qt::PenStyle::SolidLine);
    pen.setWidth(1);
    painter.setPen(pen);

    // time axis
    int maxTickCount = width()/(PIXELS_PER_SECOND*zoom);
    QLine bigTick = QLine(0, 0, 0, TIMEAXIS_HEIGHT);

    for(int x = 0; x < maxTickCount; x++) {
        bigTick.translate(PIXELS_PER_SECOND*zoom,0);

        if(x % 10) {
            pen.setWidth(1);
        } else {
            pen.setWidth(2);
        }
        painter.setPen(pen);
        painter.drawLine(bigTick);
    }


    // draw vertical lines
    float y = 0.0f;
    QVector<QLineF> lines;
    int maxLineCount = (int)(height()/CLIP_HEIGHT);
    for(int i = 0; i < maxLineCount; i++) {
        y = i*CLIP_HEIGHT + 2.0f + TIMEAXIS_HEIGHT;
        lines.append(QLineF(0, y, width(), y));
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

        painter.drawText(clip.topLeft()+QPoint(0,10), model()->data(index).toString());
    }

    // draw cursor
    painter.drawRect(*cursor);
}

QRect TimelineView::visualRect(const QModelIndex &index) const
{
    QRect clip = QRect();

    float offset = 0.0f;
    for(int i = 0; i < model()->rowCount(); i++) {
        if(index.row() == i) {
            break;
        } else {
            offset += model()->data(model()->index(i, 1), Qt::DisplayRole).toFloat();
        }
    }

    clip.setX(offset*zoom);
    clip.setY(TIMEAXIS_HEIGHT);
    clip.setHeight(50);
    clip.setWidth(model()->data(model()->index(index.row(), 1), Qt::DisplayRole).toDouble()*zoom);
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

QModelIndex TimelineView::moveCursor(QAbstractItemView::CursorAction cursorAction, Qt::KeyboardModifiers /*modifiers*/)
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
    return QRegion(rect()); //TODO: optimieren
    //return QRegion(0,0,0,0);
}

void TimelineView::mousePressEvent(QMouseEvent *event)
{
    QModelIndex index = indexAt(event->pos());
    switch(event->button()) {
        case Qt::LeftButton:
        // first check for cursor selection
        if(cursor->contains(event->pos())) {
            dragState = DragState::cursorDrag;
        } else if(event->pos().y() <= TIMEAXIS_HEIGHT) {
            qDebug() << "scrubb";
            setCursorPosition(event->pos().x());
            viewport()->update();
        } else {
            qDebug() << "select";
            setCurrentIndex(index);
            if(index.isValid()) {
                setCursor(Qt::ClosedHandCursor);
            }
            viewport()->update();
        }
        break;
    default:
        break;
    }

    QAbstractItemView::mousePressEvent(event);
}

void TimelineView::mouseMoveEvent(QMouseEvent* event)
{
    QPoint p = event->pos();

    switch(dragState) {
    case none:
        if(cursor->contains(p)) {
            setCursor(Qt::SizeHorCursor);
        } else {
            setCursor(Qt::ArrowCursor);
        }
        break;
    case cursorDrag:
        setCursorPosition(p.x());
        viewport()->update();
        break;
    }
}

void TimelineView::mouseReleaseEvent(QMouseEvent *event)
{
    switch(event->button()) {
    case Qt::LeftButton:
        if(event->pos().y() > TIMEAXIS_HEIGHT) {
            QModelIndex index = indexAt(event->pos());
            if(index != currentIndex()) {
                model()->moveRow(currentIndex(), currentIndex().row(), index, index.row());
            }
            setCursor(Qt::ArrowCursor);
            viewport()->update();
        }

        switch(dragState) {
        case none:
            break;
        case cursorDrag:
            dragState = DragState::none;
            setCursorPosition(Qt::ArrowCursor);
            break;
        }
        break;
    default:
        break;
    }
}

void TimelineView::wheelEvent(QWheelEvent *event)
{
    zoom += SCROLL_TO_ZOOM_SCALE*event->delta();
    zoom = qBound(MIN_ZOOM, zoom, MAX_ZOOM);
    viewport()->update();
    emit zoomChanged(QString("Zoom: %1 \%").arg((int)(zoom*100.0f),3));
    QAbstractItemView::wheelEvent(event);
}

void TimelineView::keyPressEvent(QKeyEvent *event)
{
    switch (event->key()) {
    case Qt::Key_Delete:
        model()->removeRow(currentIndex().row());
        viewport()->update();
        break;
    case Qt::Key_Left:
        if(event->modifiers().testFlag(Qt::ShiftModifier) && currentIndex().isValid()) {
        }
    }
}

void TimelineView::contextMenuEvent(QContextMenuEvent *event)
{
    QMenu menu(this);
    menu.addAction("Add Scene");
}

void TimelineView::setCursorPosition(const int position)
{
    cursor->setX(qBound(0, position, width()-CURSOR_WIDTH));
    cursor->setWidth(CURSOR_WIDTH);
}

void TimelineView::dataChanged(const QModelIndex &topLeft, const QModelIndex &bottomRight, const QVector<int> &roles)
{
    viewport()->update();
}

void TimelineView::addClip()
{
    model()->insertRow(model()->rowCount());
    viewport()->update();
}

void TimelineView::removeClip()
{
    if(currentIndex().isValid()) {
        if(!model()->removeRow(currentIndex().row())) {
            setCurrentIndex(QModelIndex());
        }
        viewport()->update();
    }
}
