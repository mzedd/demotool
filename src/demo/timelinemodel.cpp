#include "timelinemodel.h"

TimelineModel::TimelineModel(QObject *parent)
    : QAbstractListModel(parent)
{
}

TimelineModel::~TimelineModel() {
    for(int i = 0; i < clipList.size(); i++) {
        delete clipList[i];
    }
}

int TimelineModel::rowCount(const QModelIndex&) const
{
    return clipList.size();
}

int TimelineModel::columnCount(const QModelIndex&) const
{
    return 2;
}

QVariant TimelineModel::data(const QModelIndex &index, int role) const
{
    switch(role) {
    case Qt::EditRole:
    case Qt::DisplayRole:
        switch(index.column()) {
        case 0:
            return QString(clipList[index.row()]->getName());
            break;
        case 1:
            return QVariant(clipList[index.row()]->getDuration());
            break;
        case 2:
            return QVariant(clipList[index.row()]->getScene().name);
            break;
        }
        break;
    }
    return QVariant();
}

void TimelineModel::addClip(Clip *clip) {
    clipList.append(clip);
}

Qt::DropActions TimelineModel::supportedDropActions() const
{
    return Qt::MoveAction;
}

bool TimelineModel::swapRows(int i, int j)
{
    Clip *tmp;

    if(i >= 0 && i < clipList.size() && j >= 0 && j < clipList.size()) {
        tmp = clipList[i];
        clipList[i] = clipList[j];
        clipList[j] = tmp;
        return true;
    }

    return false;
}

bool TimelineModel::insertRows(int row, int count, const QModelIndex &parent)
{
    for(int i = 0; i < count; i++) {
        clipList.append(new Clip());
    }
    return true;
}

bool TimelineModel::removeRows(int row, int count, const QModelIndex &parent)
{
    if(!clipList.empty() && row+count <= clipList.size()) {
        for(int i = 0; i < count; i++) {
            delete clipList[row+i];
        }
        clipList.remove(row, count);
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
            clipList[index.row()]->setName(value.toString());
            break;
        case 1:
            clipList[index.row()]->setDuration(value.toFloat());
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
