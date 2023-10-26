#ifndef ALBUMMODEL_H
#define ALBUMMODEL_H

#include <QAbstractListModel>
#include <QHash>
#include <vector>
#include <memory>

#include "gallery-core_global.h"
#include "album.h"
#include "DatabaseManager.h"

class GALLERYCORE_EXPORT AlbumModel : public QAbstractListModel
    {
    Q_OBJECT
    public:

        enum Roles {
            IdRole = Qt::UserRole + 1,
            NameRole,
            }; // used by views to access data

        AlbumModel(QObject* parent = nullptr);

        QModelIndex addAlbum(const Album& album); // QModelIndex is an identifier to access data within the model 
        QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;
        bool setData(const QModelIndex& index, const QVariant& value, int role) override;
        bool removeRows(int row, int count, const QModelIndex& parent) override;
        QHash<int, QByteArray> roleNames() const override;

        int rowCount(const QModelIndex& parent = QModelIndex()) const override;

    private:
        bool isIndexValid(const QModelIndex& index) const;

    private:
        DatabaseManager& mDb;
        std::unique_ptr<std::vector<std::unique_ptr<Album>>> mAlbums; //memory buffer, copy of data from database table
    };

#endif // ALBUMMODEL_H
