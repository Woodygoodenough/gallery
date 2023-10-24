#ifndef PICTUREDAO_H
#define PICTUREDAO_H

#include <QVector>

class QSqlDatabase;
class Album;
class Picture;

class PictureDao
    {
    public:
        PictureDao(QSqlDatabase& database);
        void init() const;

        void addPicture(int albumId, Picture& picture) const;
        void removePicture(int id) const;
        void removePicturesForAlbum(int albumId) const;
        QVector<Picture*> picturesForAlbum(int albumId) const;

    private:
        QSqlDatabase& mDatabase;
    };

#endif // PICTUREDAO_H
