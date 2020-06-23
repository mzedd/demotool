#include "timelinemodel.h"

#include "demo.h"

TimelineModel::TimelineModel(QObject *parent)
    : QAbstractListModel(parent)
{
}

TimelineModel::~TimelineModel() {
}

int TimelineModel::rowCount(const QModelIndex&) const
{
    return static_cast<int>(Demo::instance().clipCount());
}

int TimelineModel::columnCount(const QModelIndex&) const
{
    return 3;
}

QVariant TimelineModel::data(const QModelIndex &index, int role) const
{
    switch(role) {
    case Qt::EditRole:
    case Qt::DisplayRole:
        switch(index.column()) {
        case 0:
            return QString(Demo::instance().getClip(index.row()).getName());
            break;
        case 1:
            return QVariant(Demo::instance().getClip(index.row()).getDuration());
            break;
        case 2:
            if(Demo::instance().getClip(index.row()).getScene() != nullptr) {
                return Demo::instance().getClip(index.row()).getScene()->name;
            }
            return QVariant(QString());
            break;
        }
        break;
    }
    return QVariant();
}

void TimelineModel::addClip() {
    Demo::instance().addClip();
}

Qt::DropActions TimelineModel::supportedDropActions() const
{
    return Qt::MoveAction;
}

bool TimelineModel::swapRows(int i, int j)
{
    return Demo::instance().swapClips(i,j);
}

bool TimelineModel::insertRows(int row, int count, const QModelIndex &parent)
{
    for(int i = 0; i < count; i++) {
        Demo::instance().addClip();
    }
    return true;
}

bool TimelineModel::removeRows(int row, int count, const QModelIndex &parent)
{
    if(Demo::instance().clipCount() > 0 && row+count <= Demo::instance().clipCount()) {
        Demo::instance().removeClips(row, count);
        return true;
    }
    return false;
}

bool TimelineModel::moveRows(const QModelIndex &sourceParent, int sourceRow, int count, const QModelIndex &destinationParent, int destinationChild)
{
    return swapRows(sourceRow, destinationChild);
}

bool TimelineModel::setData(const QModelIndex &index, const QVariant &value, int role) {
    if(role == Qt::EditRole) {
        switch(index.column()) {
        case 0:
            Demo::instance().getClip(index.row()).setName(value.toString());
            break;
        case 1:
            Demo::instance().getClip(index.row()).setDuration(value.toFloat());
            break;
        }

        emit dataChanged(index, index);
        return true;
    }
    return false;
}

Qt::ItemFlags TimelineModel::flags(const QModelIndex &index) const
{
    return Qt::ItemIsEditable | QAbstractListModel::flags(index);
}
