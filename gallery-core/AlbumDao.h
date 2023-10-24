#ifndef ALBUMDAO_H
#define ALBUMDAO_H
#include <QVector>

class QSqlDatabase;
class Album;

class AlbumDao // data access object
    {
    public:
        AlbumDao(QSqlDatabase& database);
        void init() const;

        void addAlbum(Album& album) const;
        void updateAlbum(const Album& album) const;
        void removeAlbum(int id) const;
        std::unique_ptr<std::vector<std::unique_ptr<Album>>> albums() const;

    private:
        QSqlDatabase& mDatabase; // pass by reference means required
    };

#endif // ALBUMDAO_H
