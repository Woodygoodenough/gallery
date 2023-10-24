#include "PictureDao.h"
#include "Picture.h"
#include "album.h"
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QVariant>
PictureDao::PictureDao(QSqlDatabase& database):
    mDatabase(database)
{
}
void PictureDao::init() const
{
    if(!mDatabase.tables().contains("pictures")){
        QSqlQuery query(mDatabase);
        query.exec(QString("CREATE TABLE picturs ")+
                   "("+
                   "id INTEGER PRIMARY KEY AUTOINCREMENT, "+
                   "fileurl TEXT, "+
                   "albumid INTEGER"
                   +")");
    }
}

void PictureDao::addPicture(Album& album, Picture& picture) const
{
    QSqlQuery query(mDatabase);
    query.prepare("INSERT INTO pictures (fileurl, albumid) VALUES (:fileurl, :albumid)");
    query.bindValue(":fileurl", picture.fileUrl());
    query.bindValue(":albumid", picture.albumId());
    query.exec();
    picture.setId(query.lastInsertId().toInt());
}
