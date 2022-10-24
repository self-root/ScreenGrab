#ifndef LANGMODEL_H
#define LANGMODEL_H

#include <QAbstractListModel>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <filesystem>

#include "ScreenGrabCore_global.h"

class SCREENGRABCORE_EXPORT LangModel : public QAbstractListModel
{
    Q_OBJECT

public:
    enum Roles{
        Lang = Qt::UserRole + 1,
        LangName
    };
    explicit LangModel(QObject *parent = nullptr);

    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    QHash<int,QByteArray> roleNames() const override;

    QString firstModel() const;

public slots:
    bool addLang(const std::filesystem::path &langPath,  const QString &langName);

    bool removeLang(int index);

private:
    QJsonArray languages;
};

#endif // LANGMODEL_H
