#include "PictureDao.h"
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QVariant>
#include "DatabaseManager.h"
#include "Picture.h"
PictureDao::PictureDao(QSqlDatabase& database) : mDatabase(database) {
    }
void PictureDao::init() const {
    if (!mDatabase.tables().contains("pictures")) {
        QSqlQuery query(mDatabase);
        query.exec(QString("CREATE TABLE pictures ") + "(" + "id INTEGER PRIMARY KEY AUTOINCREMENT, "
                   + "fileurl TEXT, " + "albumid INTEGER" + ")");
    }
}

void PictureDao::addPicture(int albumId, Picture &picture) const
{
    QSqlQuery query(mDatabase);
    query.prepare(QString("INSERT INTO pictures") + " (albumid, fileurl)" + " VALUES ("
                  + ":albumid, " + ":fileurl" + ")");
    query.bindValue(":albumid", albumId);
    query.bindValue(":fileurl", picture.fileUrl());
    query.exec();
    DatabaseManager::debugQuery(query);
    picture.setId(query.lastInsertId().toInt());
    picture.setAlbumId(albumId);
}

void PictureDao::removePicture(int id) const {
    QSqlQuery query(mDatabase);
    query.prepare("DELETE FROM pictures WHERE id = :id");
    query.bindValue(":id", id);
    query.exec();
    }

void PictureDao::removePicturesForAlbum(int albumId) const {
    QSqlQuery query(mDatabase);
    query.prepare("DELETE FROM pictures WHERE albumid = :albumid");
    query.bindValue(":albumid", albumId);
    query.exec();
    }


std::unique_ptr<std::vector<std::unique_ptr<Picture>>> PictureDao::picturesForAlbum(int albumId) const {
    QSqlQuery query(mDatabase);
    query.prepare("SELECT * FROM pictures WHERE albumid = :albumid");
    query.bindValue(":albumid", albumId);
    query.exec();
    std::unique_ptr<std::vector<std::unique_ptr<Picture>>> list(new std::vector<std::unique_ptr<Picture>>());
    while (query.next()) {
        std::unique_ptr<Picture> picture(new Picture());
        picture->setId(query.value("id").toInt());
        picture->setAlbumId(query.value("albumid").toInt());
        picture->setFileUrl(query.value("fileurl").toString());
        list->push_back(std::move(picture));
        }
    return list;
    }
