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
                q.exec(QLatin1String(R"(create table history(id integer primary key, data varchar,secondtype varchar, Timestamp DATETIME DEFAULT CURRENT_TIMESTAMP))"));
        }

        if(!tables.contains("settings", Qt::CaseInsensitive)){
            QSqlQuery q;
            q.exec(QLatin1String(R"(create table settings(id integer primary key, name varchar,value varchar))"));
            q.prepare("INSERT INTO settings (name,value) "
                             "VALUES (:name,:value)");
            q.bindValue(":name","secondtype");
            q.bindValue(":value","Nanoseconds");
            q.exec();

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

    QString getSecondType(){
        QSqlQuery query;
        QString output;
        query.exec("SELECT value FROM settings where name = 'secondtype'");
        while(query.next()){
            output = query.value(0).toString();
        }
        return output;
    }
    void setSecondType(QString const & value){
        QSqlQuery query;
        query.prepare("update settings set value = :value where name = 'secondtype'");
        query.bindValue(":value",value);
        query.exec();
    }
    std::vector<QString> getHistory(){
        std::vector<QString> output;
        QSqlQuery query2;
        query2.exec("SELECT data,secondtype FROM history order by timestamp limit 100 ");
        while (query2.next()) {
            auto data = query2.value(0).toString();
            auto second = query2.value(1).toString();

            uint64_t timestamp = data.toLong();
            uint64_t sec;
            if(second == "Nanoseconds"){
                sec = timestamp /  1000000000ULL;
            }
             else if(second == "Milliseconds"){
                 sec = ((timestamp + 500) / 1000);
             }else{
                 sec = timestamp;
             }
             QDateTime qtimestamp = QDateTime::fromTime_t(sec);


            QString historyvalue = second+" " +data+" UTC:"+qtimestamp.toUTC().toString()+ "    Local:"+qtimestamp.toString();

            output.push_back(historyvalue);
        }
        return output;
    }

    void insertRow(QString const &  number,QString const & secondtype){
       QSqlQuery query;

       query.exec("select count(*) FROM history");
       int count = 0;
       while(query.next()){
           count = query.value(0).toInt();
       }

       if (count >100){ // Only allow 100 rows so it doesn't grow to infinity.
           query.exec("DELETE FROM history WHERE id IN (SELECT id FROM history ORDER BY timestamp DESC LIMIT -1 OFFSET 3)");
       }

       query.prepare("INSERT INTO history (data,secondtype) "
                        "VALUES (:data,:secondtype)");
       query.bindValue(":data",number);
       query.bindValue(":secondtype",secondtype);
       query.exec();

    }


};
