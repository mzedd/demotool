#ifndef TIMELINEMODEL_H
#define TIMELINEMODEL_H

#include <QAbstractListModel>
#include <QVector>
#include "Clip.h"

class TimelineModel : public QAbstractListModel
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
    Qt::DropActions supportedDropActions() const override;


    bool swapRows(int i, int j);

    bool insertRows(int row, int count, const QModelIndex &parent = QModelIndex()) override;
    bool removeRows(int row, int count, const QModelIndex &parent = QModelIndex()) override;
    bool moveRows(const QModelIndex &sourceParent, int sourceRow, int count, const QModelIndex &destinationParent, int destinatioChild) override;

private:
    QVector<Clip*> clipList;
    //QVector<PostProcessingEffect> ppList;
};

#endif // TIMELINEMODEL_H
