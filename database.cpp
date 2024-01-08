#include "database.h"

Database::Database(QString DBName)
{
    m_DBName = DBName;
    m_db = QSqlDatabase::addDatabase("QSQLITE");
    m_db.setDatabaseName(m_DBName);

    if (m_db.open()) {
        qDebug() << "Database opened successfully.";
    } else {
        qDebug() << "Error opening database:" << m_db.lastError().text();
    }
}

int Database::isDBOpen()
{
    return m_db.isOpen();
}

QSqlQuery Database::execute(QString query)
{
    QSqlQuery sqlQuery;
    if (sqlQuery.exec(query)) {
        qDebug() << "Query executed successfully.";
    } else {
        qDebug() << "Error executing query:" << sqlQuery.lastError().text();
    }

    return sqlQuery;
}

QSqlDatabase Database::getDB()
{
    return m_db;
}
