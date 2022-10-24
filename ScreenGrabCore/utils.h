#ifndef UTILS_H
#define UTILS_H

#include <QString>
#include <QFile>
#include <QDir>
#include <QStandardPaths>
#include <QDateTime>
#include <QJsonArray>
#include <QFile>
#include <QJsonObject>
#include <QJsonDocument>
#include <filesystem>

namespace scrgrab {

Q_GLOBAL_STATIC(QString, version, "1.0.0")
#ifdef __linux__
Q_GLOBAL_STATIC(QString, configPath, ".config/ScreenGrab/")
#elif _WIN32
Q_GLOBAL_STATIC(QString, configPath, "/ScreenGrab/")
#else
#error "OS not supported"
#endif

class Utils
{
public:
    static bool saveImage(const QString &initial, const QString &target)
    {
        if (QFile::copy(initial, target))
        {
            QFile::remove(initial);
            return true;
        }
        return false;

    }

    static QString pictureDir()
    {
        auto paths = QStandardPaths::standardLocations(QStandardPaths::PicturesLocation);
        return paths.first();
    }

    static QString homePath()
    {
        auto p_ = QStandardPaths::standardLocations(QStandardPaths::HomeLocation);
        return p_.first();
    }

    static QString imageDefaultName()
    {
        auto filePath = pictureDir() + "/ScreenGrab ";
        filePath += QDateTime::currentDateTime().toString("dd-MM-yy hh-mm-ss");
        filePath += ".png";

        return filePath;
    }

    static void makeConfigPaths()
    {
        QDir config(appConfigPath());
        QDir model(modelPath());
        //qDebug() << "Making path: " << appConfigPath();
        //qDebug() << "Making path: " << model.path();
        if (!config.exists())
        {
            config.mkpath(appConfigPath());
        }

        if (!model.exists())
        {
            qDebug() << "Making path: " << model.path();
            model.mkpath(modelPath());
        }
    }

    static QString appConfigPath()
    {
#ifdef __linux__
        auto paths = QDir::homePath() + "/";
#elif _WIN32
        auto paths = QStandardPaths::standardLocations(QStandardPaths::DocumentsLocation).first();
#endif
        paths.append(configPath->data());
        return paths;
    }

    static QString modelPath()
    {
        return appConfigPath() + "models/";
    }

    static QJsonArray getLanguages()
    {
        QFile file(appConfigPath() + "app.json");
        if (file.open(QIODevice::ReadWrite))
        {
            auto l = file.readAll();
            QJsonDocument jDoc = QJsonDocument::fromJson(l);
            QJsonObject json = jDoc.object();
            file.close();
            return json["models"].toArray();
        }

        return QJsonArray();
    }
    static void writeSetting(const QJsonObject &setting)
    {
        QFile file(appConfigPath() + "app.json");
        if (file.open(QIODevice::WriteOnly))
        {
            QJsonDocument jDoc(setting);

            file.write(jDoc.toJson());
            file.close();
        }
    }
    static QString saveTesseractModel(const std::filesystem::path &modelPath_)
    {
        QString destination = modelPath() + QString::fromStdString(modelPath_.filename().string());
        std::filesystem::copy(modelPath_, std::filesystem::path(destination.toStdString()), std::filesystem::copy_options::update_existing);
        QString fileName = QString::fromStdString(modelPath_.filename().string());
        auto splitted = fileName.split(".");
        return splitted.at(0);
    }

    static QJsonObject getSettings()
    {
        QFile file(appConfigPath() + "app.json");
        if (file.open(QIODevice::ReadOnly))
        {
            auto fileContent = file.readAll();
            file.close();
            QJsonDocument jDoc = QJsonDocument::fromJson(fileContent);
            QJsonObject settings = jDoc.object();

            return settings;
        }
        return QJsonObject();
    }
    static QString addLang(const std::filesystem::path &modelPath, const QString &langName)
    {

        auto settings = getSettings();

        QString lang = saveTesseractModel(modelPath);
        auto langArr = settings["models"].toArray();
        langArr.append(QJsonValue({{"model",lang}, {"language", langName}}));

        settings["models"] = langArr;
        writeSetting(settings);
        return lang;
    }

    static void removeLang(const QJsonArray &models)
    {
        QJsonObject settings = getSettings();
        settings["models"] = models;

        writeSetting(settings);

    }
};

}


#endif // UTILS_H
