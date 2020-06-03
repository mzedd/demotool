#include "timelinemodel.h"

TimelineModel::TimelineModel(QObject *parent)
    : QAbstractTableModel(parent)
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
        }
        break;
    }
    return QVariant();
}

void TimelineModel::addClip(Clip *clip) {
    clipList.append(clip);
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
    return Qt::ItemIsEditable | QAbstractTableModel::flags(index);
}
