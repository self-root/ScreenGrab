#include "recentimagemodel.h"
#include <QFile>

RecentImageModel::RecentImageModel(QObject *parent)
    : QAbstractListModel(parent)
{
    database = DatabaseAccess::instance();
    images = database->imageDao->getImages();
}

int RecentImageModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)

    return images->size();
}

QVariant RecentImageModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    const Image &image = *images->at(index.row());

    switch (role) {
    case Roles::idRole:
        return image.imageId();
        break;
    case Roles::pathRole:
        return image.imagePath();
        break;
    case Roles::textRole:
        return image.imageText();
        break;
    case Roles::dateRole:
        return image.savedDate();
        break;
    default:
        return QVariant();
        break;
    }
}


bool RecentImageModel::addImage(Image *image)
{
    beginInsertRows(QModelIndex(), images->size(), images->size());
    if (!database->imageDao->addImage(image))
        return false;
    images->push_back(
        std::unique_ptr<Image>(
            new Image(
                image->imageId(),
                image->imagePath(),
                image->imageText(),
                image->savedDate()
                )
            )
        );
    endInsertRows();
    return true;
}

bool RecentImageModel::removeImage(int row, bool withFile)
{
    beginRemoveRows(QModelIndex(), row, row);
    Image *image = images->at(row).get();
    if (!database->imageDao->remove(image))
        return false;
    if (withFile)
        QFile::remove(image->imagePath());
    images->erase(images->cbegin() + row);
    endRemoveRows();
    return true;
}

bool RecentImageModel::updateImage(Image *image)
{
    int imageRow = imageIndex(image->imageId());
    qDebug() << "Image ROW: " << imageRow;
    if (database->imageDao->update(image))
    {
        images->at(imageRow) = std::unique_ptr<Image>(new Image(image->imageId(),
                                                                image->imagePath(),
                                                                image->imageText(),
                                                                image->savedDate()));
        emit dataChanged(QModelIndex(), QModelIndex());
        return true;
    }
    return false;
}

int RecentImageModel::imageIndex(int imageId)
{
    auto it = std::find_if(images->cbegin(), images->cend(), [imageId](const std::unique_ptr<Image> &img){
        return img->imageId() == imageId;
    });

    if (it != images->cend())
    {
        return std::distance(images->cbegin(), it);
    }

    return -1;
}


QHash<int, QByteArray> RecentImageModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[Roles::idRole] = "imageId";
    roles[Roles::pathRole] = "imagePath";
    roles[Roles::textRole] = "imageText";
    roles[Roles::dateRole] = "imageDate";

    return roles;
}

Image *RecentImageModel::getImage(int index)
{
    return images->at(index).get();
}

QString RecentImageModel::imagePathAt(int index)
{
    return images->at(index)->imagePath();
}

Image *RecentImageModel::imageAt(int index)
{
    return images->at(index).get();
}
