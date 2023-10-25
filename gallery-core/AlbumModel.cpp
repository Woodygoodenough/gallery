#include "AlbumModel.h"

AlbumModel::AlbumModel(QObject* parent) :
    QAbstractListModel(parent),
    mDb(DatabaseManager::instance()),
    mAlbums(mDb.albumDao.albums()) {
    }

int AlbumModel::rowCount(const QModelIndex& parent) const {
    Q_UNUSED(parent);
    return mAlbums->size();
    }

QVariant AlbumModel::data(const QModelIndex& index, int role) const {
    if (!isIndexValid(index)) {
        return QVariant();
        }
    const Album& album = *mAlbums->at(index.row());

    switch (role) {
        case Roles::IdRole:
            return album.id();

        case Roles::NameRole:
        case Qt::DisplayRole:
            return album.name();

        default:
            return QVariant();
        }
    }

QModelIndex AlbumModel::addAlbum(const Album& album) {
    int rowIndex = rowCount();
    beginInsertRows(QModelIndex(), rowIndex, rowIndex);
    auto newAlbum = std::make_unique<Album>(album);
    mDb.albumDao.addAlbum(*newAlbum);
    mAlbums->push_back(move(newAlbum));
    endInsertRows();
    return index(rowIndex, 0);
    }