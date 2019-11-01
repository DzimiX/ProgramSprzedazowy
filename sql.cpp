#include "sql.h"


bool sql::dbOpen(void){
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("C:/db/test.db");
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

void sql::dbCreate(QString location){
    //not yet implemented
}
