#ifndef RECENTIMAGEMODEL_H
#define RECENTIMAGEMODEL_H

#include <QAbstractListModel>
#include <vector>
#include"ScreenGrabCore_global.h"
#include "databaseaccess.h"
#include "image.h"


class SCREENGRABCORE_EXPORT RecentImageModel : public QAbstractListModel
{
    Q_OBJECT

public:

    enum Roles{
        idRole = Qt::UserRole + 1,
        pathRole,
        textRole,
        dateRole
    };

    explicit RecentImageModel(QObject *parent = nullptr);

    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    // Add data:
    bool addImage(Image *image);

    // Remove data:
    bool removeImage(int row, bool withFile=false);

    bool updateImage(Image *image);

    int imageIndex(int imageId);

    QHash<int, QByteArray> roleNames() const override;

    Image *getImage(int index);

public:
    Q_INVOKABLE QString imagePathAt(int index);
    Image *imageAt(int index);

private:
    DatabaseAccess *database;
    std::unique_ptr<std::vector<std::unique_ptr<Image>>> images;
};

#endif // RECENTIMAGEMODEL_H
