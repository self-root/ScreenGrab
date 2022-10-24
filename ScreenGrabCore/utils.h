/**
 * A file containing some utility functions used in the main program
 * */

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
    /**
     * @brief saveImage This fuction is not used
     * @param initial
     * @param target
     * @return
     */
    static bool saveImage(const QString &initial, const QString &target)
    {
        if (QFile::copy(initial, target))
        {
            QFile::remove(initial);
            return true;
        }
        return false;

    }

    /**
     * @brief pictureDir Get the picture directory location
     * @return The path is a QString
     */
    static QString pictureDir()
    {
        auto paths = QStandardPaths::standardLocations(QStandardPaths::PicturesLocation);
        return paths.first();
    }

    /**
     * @brief homePath Get home directory path
     * @return The directory path in a QString
     */
    static QString homePath()
    {
        auto p_ = QStandardPaths::standardLocations(QStandardPaths::HomeLocation);
        return p_.first();
    }

    /**
     * @brief imageDefaultName make default name for the picture
     * @return a QString containing the imgage name in form of path_to_picture_dir/ScreenGrab dd-MM-yy hh-mm-ss
     */
    static QString imageDefaultName()
    {
        auto filePath = pictureDir() + "/ScreenGrab ";
        filePath += QDateTime::currentDateTime().toString("dd-MM-yy hh-mm-ss");
        filePath += ".png";

        return filePath;
    }

    /**
     * @brief makeConfigPaths Create the application folder and and the
     * tesseract lang model folder if not exixts
     */
    static void makeConfigPaths()
    {
        QDir config(appConfigPath());
        QDir model(modelPath());

        if (!config.exists())
        {
            config.mkpath(appConfigPath());
        }

        if (!model.exists())
        {
            model.mkpath(modelPath());
        }
    }
    /**
     * @brief appConfigPath Make an App config path based on the operating system
     * @return Path to the app config path
     */
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

    /**
     * @brief modelPath Make the path to the tesseract language models
     * @return The QString path to the tesseract model
     */
    static QString modelPath()
    {
        return appConfigPath() + "models/";
    }

    /**
     * @brief getLanguages Get all saved language model from the app.json config path
     *
     * @return A QJsonArray containing the lanquage names
     */
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

    /**
     * @brief writeSetting: Save settings to the app.json config file.
     * Note: The app.json content will be replaced by the new content
     * @param setting a QJsonObject containing the setting to be saved
     */
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

    /**
     * @brief saveTesseractModel Save tesseract language model provided on the argument and copy it to the app direcotry file(ScreenGrab/models).
     * Split the file name to get the name of the lang model(ex: en.traineddata -> en) and return it.
     * @param modelPath_ the path to the tesseract trained data to be saved
     * @return The lang name
     */
    static QString saveTesseractModel(const std::filesystem::path &modelPath_)
    {
        QString destination = modelPath() + QString::fromStdString(modelPath_.filename().string());
        std::filesystem::copy(modelPath_, std::filesystem::path(destination.toStdString()), std::filesystem::copy_options::update_existing);
        QString fileName = QString::fromStdString(modelPath_.filename().string());
        auto splitted = fileName.split(".");
        return splitted.at(0);
    }

    /**
     * @brief getSettings Simply ready the app.json app config file and return its content
     * @return QJsonObject containing the content of the app.json
     */
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

    /**
     * @brief addLang Add new language model to the app.json config file
     * @param modelPath Path to the tesseract trained data to be saved
     * @param langName Name of th language, for the config file
     * @return Return the lang name (en.traineddata --> en)
     */
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

    /**
     * @brief removeLang Remove a lang model from the config file by providing an new QJsonArray tha contains the list of all lang model
     * @param models QJsonArray tha contains the list of all lang model withou the one that should be removed
     */
    static void removeLang(const QJsonArray &models)
    {
        QJsonObject settings = getSettings();
        settings["models"] = models;

        writeSetting(settings);

    }
};

}


#endif // UTILS_H
