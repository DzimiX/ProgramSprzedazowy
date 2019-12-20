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
    if(QFileInfo::exists(location)){
        return true;
    }else{
        return false;
    }
}

void sql::dbCreate(QString location){
    QFile file(location);
    if(!dbExists(location)){
        sql conn;
        conn.dbOpen(conn.location);
        QSqlQuery *query = new QSqlQuery(conn.db);
        //db tables init, query per query, actually performs only once: when db doesn't exist
        query->prepare(
            "CREATE TABLE faktury ("
                "id             INTEGER PRIMARY KEY ASC AUTOINCREMENT NOT NULL UNIQUE,"
                "id_kontrahent  INTEGER REFERENCES kontrahenci (id) NOT NULL,"
                "typ            TEXT,"
                "komentarz      TEXT,"
                "data           DATETIME"
            ");"
        );
        query->exec();
        query->prepare(
            "CREATE TABLE firma ("
                "nazwa              TEXT,"
                "NIP                INTEGER,"
                "REGON              INTEGER,"
                "KRS                INTEGER,"
                "PESEL              INTEGER,"
                "email              TEXT,"
                "telefon            TEXT,"
                "adres_miasto       TEXT,"
                "adres_ulica        TEXT,"
                "adres_numer        TEXT,"
                "adres_kodPocztowy  TEXT"
            ");"
        );
        query->exec();
        query->prepare(
            "CREATE TABLE kontrahenci ("
                "id                 INTEGER PRIMARY KEY ASC AUTOINCREMENT UNIQUE NOT NULL,"
                "nazwa              TEXT UNIQUE NOT NULL,"
                "NIP                BIGINT,"
                "REGON              INTEGER,"
                "KRS                INTEGER,"
                "PESEL              INTEGER,"
                "email              TEXT,"
                "telefon            TEXT,"
                "adres_miasto       TEXT,"
                "adres_ulica        TEXT,"
                "adres_numer        TEXT,"
                "adres_kodPocztowy  TEXT"
            ");"
        );
        query->exec();
        query->prepare(
            "CREATE TABLE produkty ("
                "id        INTEGER PRIMARY KEY ASC AUTOINCREMENT NOT NULL UNIQUE,"
                "nazwa     TEXT UNIQUE NOT NULL,"
                "jednostka TEXT,"
                "cena      DOUBLE,"
                "VAT       DOUBLE"
            ");"
        );
        query->exec();
        query->prepare(
            "CREATE TABLE rozliczenia ("
                    "id         INTEGER PRIMARY KEY ASC AUTOINCREMENT NOT NULL UNIQUE,"
                    "id_produkt INTEGER REFERENCES produkty (id) NOT NULL,"
                    "id_faktura INTEGER REFERENCES faktury (id) NOT NULL,"
                    "ilosc      INTEGER NOT NULL"
            ");"
        );
        query->exec();
        //fill db with essential data
        query->prepare(
            "INSERT INTO firma (nazwa)"
            "VALUES ('Uzupełnij dane firmy!')"
        );
        query->exec();
        query->prepare(
            "INSERT INTO kontrahenci (id, nazwa)"
            "VALUES (1,'DOSTAWA')"
        );
        query->exec();
        query->prepare(
            "INSERT INTO kontrahenci (id, nazwa)"
            "VALUES (2,'PARAGON')"
        );
        query->exec();
        query->prepare(
            "INSERT INTO faktury (id, id_kontrahent, komentarz)"
            "VALUES (1,1,'Dostawa')"
        );
        query->exec();
    }
}

