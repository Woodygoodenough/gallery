#ifndef PICTUREMODEL_H
#define PICTUREMODEL_H
#include <memory> 
#include <vector> 

#include "Picture.h" 
#include <QAbstractListModel>
#include "gallery-core_global.h"
class Album;
class DatabaseManager;
class AlbumModel;
class GALLERYCORE_EXPORT PictureModel : public QAbstractListModel
    {
    Q_OBJECT
    public:

        enum PictureRole {
            FilePathRole = Qt::UserRole + 1
            };

        PictureModel(const AlbumModel& albumModel, QObject* parent = nullptr);

        QModelIndex addPicture(const Picture& picture);

        int rowCount(const QModelIndex& parent = QModelIndex()) const override;
        QVariant data(const QModelIndex& index, int role) const override;
        bool removeRows(int row, int count, const QModelIndex& parent) override;

        void setAlbumId(int albumId);
        void clearAlbum();

    public slots:
        void deletePicturesForAlbum();

    private:
        void loadPictures(int albumId);
        bool isIndexValid(const QModelIndex& index) const;

    private:
        DatabaseManager& mDb;
        int mAlbumId;
        std::unique_ptr<std::vector<std::unique_ptr<Picture>>> mPictures;
    };

#endif // PICTUREMODEL_H
