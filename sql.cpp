#include "sql.h"

bool sql::dbOpen(QString location){
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(location);
    if(!db.open()){
        return false;
    }else{
        return true;
    }
}
void sql::dbClose(void){
    db.close();
    db.removeDatabase(QSqlDatabase::defaultConnection);
}

bool sql::dbExists(QString location){
    QFile file(location);
    if(QFileInfo::exists(location)){
        return true;
    }else{
        return false;
    }
}

void sql::dbCreate(QString location){
    QFile file(location);
    if(!dbExists(location)){
        if (file.open(QIODevice::ReadWrite)) {
            QTextStream stream(&file);
        }

        //open db conn with file
        //exec create db queries
        //exec init db queries
    }
}
