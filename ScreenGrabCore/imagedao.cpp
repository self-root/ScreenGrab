#include "imagedao.h"

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>

ImageDao::ImageDao(QSqlDatabase &database)
    : mDatabase(database)
{
    qDebug() << "Database: " << mDatabase.databaseName();
    QSqlQuery query;
    QString queryString("CREATE TABLE IF NOT EXISTS recent("
                      "id INTEGER PRIMARY KEY AUTOINCREMENT, "
                      "imagePath TEXT NOT NULL, "
                      "imageText TEXT, "
                      "savedDate DATETIME DEFAULT CURRENT_TIMESTAMP)");

    if (!query.exec(queryString))
    {
        qDebug() << "ERROR creating table: " << query.lastError().text();
    }
}

bool ImageDao::addImage(Image *image)
{
    QSqlQuery query;
        query.prepare("INSERT INTO recent(imagePath, imageText) "
                      "VALUES(:imagePath, :imageText)");
        query.bindValue(":imagePath", image->imagePath());
        query.bindValue(":imageText", image->imageText());

        if (!query.exec())
        {
            qDebug() << query.lastError();
            return false;
        }

        image->setImageId(query.lastInsertId().toInt());

        return true;
}

std::unique_ptr<std::vector<std::unique_ptr<Image> > > ImageDao::getImages() const
{
    QSqlQuery query("SELECT * FROM recent");
    query.exec();
    std::unique_ptr<std::vector<std::unique_ptr<Image> > > images(new std::vector<std::unique_ptr<Image>>);
    while (query.next())
    {
        std::unique_ptr<Image> image(
                    new Image(
                        query.value("id").toInt(),
                        query.value("imagePath").toString(),
                        query.value("imageText").toString(),
                        query.value("savedDate").toDateTime()
                        )
                    );

        images->push_back(std::move(image));
    }

    return images;
}

bool ImageDao::update(const Image *image)
{
    QSqlQuery query;
    query.prepare("UPDATE recent "
                  "SET "
                  "imagePath = :imagePath, "
                  "imageText = :imageText "
                  "WHERE id = :id");
    query.bindValue(":id", image->imageId());
    query.bindValue(":imagePath", image->imagePath());
    query.bindValue(":imageText", image->imageText());

    if (!query.exec())
    {
        qDebug() << "ERROR while updating " << image->imagePath();
        qDebug() << query.lastError();
        return false;
    }
    return true;
}

bool ImageDao::remove(Image *image)
{
    QSqlQuery query;
    query.prepare("DELETE FROM recent WHERE id = :id");
    query.bindValue(":id", image->imageId());
    if (!query.exec())
    {
        qDebug() << "ERROR while removing image: " << image->imageId();
        qDebug() << query.lastError();
        return false;
    }
    return true;
}
