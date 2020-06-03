#ifndef TIMELINEMODEL_H
#define TIMELINEMODEL_H

#include <QAbstractTableModel>
#include <QVector>
#include "Clip.h"

class TimelineModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    TimelineModel(QObject *parent = nullptr);
    ~TimelineModel();
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override;
    Qt::ItemFlags flags(const QModelIndex &index) const override;
    void addClip(Clip *clip);
private:
    QVector<Clip*> clipList;
    //QVector<PostProcessingEffect> ppList;
};

#endif // TIMELINEMODEL_H
