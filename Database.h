

#include <QtSql>
#include <iostream>
#include <vector>
#include <QListWidgetItem>
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
        QString Location = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
        if(!QDir(Location).exists()){
            QDir().mkdir(Location);
        }
        QString path = Location+"/timestampConverter.db";
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
    std::vector<std::pair<QString,QString>> getHistory(){
        std::vector<std::pair<QString,QString>> output;
        QSqlQuery query2;
        query2.exec("SELECT id, data,secondtype FROM history order by timestamp limit 100 ");
        while (query2.next()) {
            auto id = query2.value(0).toString();
            auto data = query2.value(1).toString();
            auto second = query2.value(2).toString();

            long long timestamp = data.toLong();
            long long sec;
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

            output.push_back({historyvalue,id});
        }
        return output;
    }
    std::pair<QString,QString> getHistoryItem(QString id){
        std::pair<QString,QString> retVal = {"",""};
        QSqlQuery query;
        query.prepare("select data,secondtype from history where id = :id");
        query.bindValue(":id",id);
        query.exec();
        while(query.next()){
            retVal.first = query.value(0).toString();
            retVal.second = query.value(1).toString();
        }
        return retVal;

    }

    void deleteHistoryItem(QString id){
        QSqlQuery query;
        query.prepare("delete from history where id = :id");
        query.bindValue(":id",id);
        query.exec();
        return;
    }

    QString insertRow(QString const &  number,QString const & secondtype){
       QSqlQuery query;

       query.exec("select count(*) FROM history");
       int count = 0;
       while(query.next()){
           count = query.value(0).toInt();
       }

       if (count >100){ // Only allow 100 rows so it doesn't grow to infinity.
           query.exec("DELETE FROM history WHERE id IN (SELECT id FROM history ORDER BY timestamp DESC LIMIT -1 OFFSET 100)");
       }

       query.prepare("INSERT INTO history (data,secondtype) "
                        "VALUES (:data,:secondtype)");
       query.bindValue(":data",number);
       query.bindValue(":secondtype",secondtype);
       query.exec();

       //SELECT last_insert_rowid()
       query.exec("select last_insert_rowid()");
       QString retVal;
       while (query.next()){
           retVal = query.value(0).toString();
       }
      return retVal;

    }


};
