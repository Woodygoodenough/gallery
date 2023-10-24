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

    void addPicture(Album& album, Picture& picture) const;
    void updatePicture(const Picture& picture) const;
    void removePicture(int id);
private:
    QSqlDatabase& mDatabase;
};

#endif // PICTUREDAO_H
