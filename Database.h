#ifndef DATABASE_H
#define DATABASE_H

#endif // DATABASE_H

#include <sqlite3.h>
#include <QtSql>
#include <iostream>
#include <vector>
class Database{
private:
    QSqlDatabase db;
    void initDb(){
        db.open();
         //CREATE TABLE IF NOT EXISTS some_table (id INTEGER PRIMARY KEY AUTOINCREMENT, ...);
        QStringList tables = db.tables();

        if (!tables.contains("history", Qt::CaseInsensitive)){
                QSqlQuery q;
                q.exec(QLatin1String(R"(create table history(id integer primary key, data varchar, Timestamp DATETIME DEFAULT CURRENT_TIMESTAMP))"));
        }


    }




public:
    Database(){
        db = QSqlDatabase::addDatabase("QSQLITE");
        QDir databasePath;
        QString path = databasePath.currentPath()+"myDb.db";
        db.setDatabaseName(path);
        initDb();

    }
    std::vector<QString> getHistory(){
        std::vector<QString> output;
        QSqlQuery query2;
        query2.exec("SELECT data FROM history order by timestamp");
        while (query2.next()) {
            output.push_back(query2.value(0).toString());
        }
        return output;
    }

    void insertRow(QString const &  input){
       QSqlQuery query;
       query.prepare("INSERT INTO history (data) "
                        "VALUES (:data)");
       query.bindValue(":data",input);
       query.exec();

    }


};
