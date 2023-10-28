#include "PictureModel.h"
#include "DatabaseManager.h"
#include "AlbumModel.h"

PictureModel::PictureModel(const AlbumModel& albumModel, QObject* parent) :
    QAbstractListModel(parent),
    mDb(DatabaseManager::instance()),
    mAlbumId(-1),
    mPictures(std::make_unique<std::vector<std::unique_ptr<Picture>>>()) {
    connect(&albumModel, &AlbumModel::rowsRemoved,
        this, &PictureModel::deletePicturesForAlbum);
    }


QModelIndex PictureModel::addPicture(const Picture& picture) {
    int rowIndex = rowCount();
    beginInsertRows(QModelIndex(), rowIndex, rowIndex);
    auto newPicture = std::make_unique<Picture>(Picture(picture));
    mDb.pictureDao.addPicture(mAlbumId, *newPicture);
    mPictures->push_back(std::move(newPicture));
    endInsertRows();
    //qDebug() << "In PictureModel::addPicture, finish add Picture";
    return index(rowIndex, 0);
    }

int PictureModel::rowCount(const QModelIndex& parent) const {
    Q_UNUSED(parent);
    return mPictures->size();
    }

QVariant PictureModel::data(const QModelIndex& index, int role) const {
    if (!isIndexValid(index)) {
        return QVariant();
        }
    const Picture& picture = *mPictures->at(index.row());
    switch (role) {
        case Qt::DisplayRole:
            return picture.fileUrl().fileName();
        case PictureRole::FilePathRole:
            return picture.fileUrl().toLocalFile();
        default:
            return QVariant();
        }
    }

bool PictureModel::removeRows(int row, int count, const QModelIndex& parent) {
    if (row < 0
        || row >= rowCount()
        || count < 0
        || (row + count) > rowCount()) {
        return false;
        }
    beginRemoveRows(parent, row, row + count - 1);
    mPictures->erase(mPictures->begin() + row,
        mPictures->begin() + row + count);
    mDb.pictureDao.removePicturesForAlbum(mAlbumId);
    endRemoveRows();
    return true;
    }

void PictureModel::setAlbumId(int albumId) {
    beginResetModel();
    mAlbumId = albumId;
    loadPictures(mAlbumId);
    endResetModel();
    }

void PictureModel::clearAlbum() {
    setAlbumId(-1);
    }

void PictureModel::deletePicturesForAlbum() {
    mDb.pictureDao.removePicturesForAlbum(mAlbumId);
    clearAlbum();
    }

void PictureModel::loadPictures(int albumId) {
    if (albumId <= 0) {
        mPictures.reset(new std::vector<std::unique_ptr<Picture>>);
        return;
        }
    mPictures = mDb.pictureDao.picturesForAlbum(albumId);
    }


bool PictureModel::isIndexValid(const QModelIndex& index) const {
    return index.row() >= 0 && index.row() < rowCount() && index.isValid();
    }
