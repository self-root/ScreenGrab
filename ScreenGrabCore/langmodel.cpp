#include "langmodel.h"
#include "utils.h"

LangModel::LangModel(QObject *parent)
    : QAbstractListModel(parent)
{
    languages = scrgrab::Utils::getLanguages();
}

int LangModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return languages.size();
}

QVariant LangModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();
    auto current = languages.at(index.row());
    switch (role) {
    case Roles::Lang:
        return current["model"].toString();
        break;
    case Roles::LangName:
        return current["language"].toString();
        break;
    default:
        break;
    }

    return QVariant();
}

QHash<int, QByteArray> LangModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[Roles::Lang] = "lang";
    roles[Roles::LangName] = "langName";

    return roles;
}

bool LangModel::addLang(const std::filesystem::path &langPath, const QString &langName)
{
    beginInsertRows(QModelIndex(), languages.size(), languages.size());
    QString langModel = scrgrab::Utils::addLang(langPath, langName);
    languages.append(QJsonObject{{"model", langModel}, {"language", langName}});
    endInsertRows();

    return true;
}

bool LangModel::removeLang(int index)
{
    beginRemoveRows(QModelIndex(), index, index);
    languages.removeAt(index);
    scrgrab::Utils::removeLang(languages);
    endRemoveRows();

    return true;
}

QString LangModel::firstModel() const
{
    if (!languages.empty())
        return languages.first()["model"].toString();
    return QString();
}
