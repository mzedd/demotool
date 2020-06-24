#ifndef TIMELINEVIEW_H
#define TIMELINEVIEW_H

#include <QWidget>
#include <QAbstractItemView>
#include <QContextMenuEvent>
#include <QGraphicsView>
#include <QEvent>

class Clip;

class TimelineView : public QAbstractItemView
{
    Q_OBJECT

public:
    explicit TimelineView(QWidget *parent = nullptr);

protected:
    void paintEvent(QPaintEvent *event) override;
    QRect visualRect(const QModelIndex &index) const override;
    void scrollTo(const QModelIndex &index, ScrollHint hint = EnsureVisible) override;
    QModelIndex indexAt(const QPoint &point) const override;
    QModelIndex moveCursor(CursorAction cursorAction, Qt::KeyboardModifiers modifiers) override;
    int horizontalOffset() const override;
    int verticalOffset() const override;
    bool isIndexHidden(const QModelIndex &index) const override;
    void setSelection(const QRect &rect, QItemSelectionModel::SelectionFlags command) override;
    QRegion visualRegionForSelection(const QItemSelection &selection) const override;

    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void wheelEvent(QWheelEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;

    void contextMenuEvent(QContextMenuEvent *event) override;

private:
    QRect getClipRectangle(QModelIndex &index);
    QRect *cursor;

    void setCursorPosition(const int position);

    float zoom;
    float time;

    enum DragState {
        none,
        cursorDrag,
    };

    DragState dragState;

signals:
    void zoomChanged(QString text);
    void clipSelectionChanged(Clip *clip);

protected slots:
    void dataChanged(const QModelIndex &topLeft, const QModelIndex &bottomRight,
                     const QVector<int> &roles = QVector<int>()) override;
public slots:
    void addClip();
    void removeClip();

};

#endif // TIMELINEVIEW_H
