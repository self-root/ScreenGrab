#include "databaseaccess.h"

#include <QDebug>
#include <QSqlDatabase>
#include <QSqlError>
#include "utils.h"

DatabaseAccess *DatabaseAccess::_instance = nullptr;

DatabaseAccess::DatabaseAccess()
    : mDatabase(new QSqlDatabase(QSqlDatabase::addDatabase("QSQLITE")))
{
    mDatabase->setDatabaseName(scrgrab::Utils::appConfigPath() + dbName);
    qDebug() << "DatabaseName: " << mDatabase->databaseName();
    if (!mDatabase->open())
        qDebug() << "Error while opening database: " << dbName << " E: " << mDatabase->lastError();
    imageDao = new ImageDao(*mDatabase);
}

DatabaseAccess *DatabaseAccess::instance()
{
    if (_instance == nullptr)
        _instance = new DatabaseAccess;
    return _instance;
}

DatabaseAccess::~DatabaseAccess()
{
    delete imageDao;
}
