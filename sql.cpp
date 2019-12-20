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

void sql::printInvoice(int invoiceId){
    QPdfWriter writer("C:/db/test.pdf");
    writer.setPageSize(QPagedPaintDevice::A4);
    writer.setPageMargins(QMargins(30, 30, 30, 30));

    QPainter painter(&writer);
    painter.setPen(Qt::black);
    painter.setFont(QFont("Times", 12));

    QRect r = painter.viewport();

    sql conn;
    conn.dbOpen(conn.location);
    QSqlQuery *query = new QSqlQuery(conn.db);
    query->prepare("SELECT * FROM firma");
    query->exec();
    query->seek(-1);
    query->next();

    QString nazwaFirmy = query->value(0).toString();
    QString nip = query->value(1).toString();
    QString email = query->value(5).toString();
    QString telefon = query->value(6).toString();
    QString adres_miasto = query->value(7).toString();
    QString adres_ulica = query->value(8).toString();
    QString adres_numer = query->value(9).toString();
    QString adres_kodPocztowy = query->value(10).toString();

    QString prawyGorny = "";
    if(adres_miasto != ""){ prawyGorny += adres_miasto+", "; }
    prawyGorny += QDate::currentDate().toString();

    QString lewyGorny = "";
    lewyGorny += "\n\n\nSprzedawca:\n";
    if(nazwaFirmy != ""){ lewyGorny += nazwaFirmy+"\n"; }
    if(nip != "0"){ lewyGorny += "NIP: "+nip+"\n"; }
    if(email != ""){ lewyGorny += "Email: "+email+"\n"; }
    if(telefon != ""){ lewyGorny += "Tel: "+telefon+"\n"; }
    if(adres_kodPocztowy != ""){ lewyGorny += adres_kodPocztowy+" "; }
    if(adres_miasto != ""){ lewyGorny += adres_miasto; }
    lewyGorny += "\n";
    if(adres_ulica != ""){ lewyGorny += adres_ulica+" "; }
    if(adres_numer != ""){ lewyGorny += adres_numer; }
    lewyGorny += "\n";

    query->prepare("SELECT nazwa FROM kontrahenci,faktury WHERE faktury.id_kontrahent=kontrahenci.id AND faktury.id=:id");
    query->bindValue(":id",invoiceId);
    query->exec();
    query->seek(-1);
    query->next();

    QString nazwa = query->value(0).toString();
    prawyGorny += "\n\n\nOdbiorca:\n";
    if(nazwa != ""){ prawyGorny+=nazwa;}

    painter.drawText(r, Qt::AlignLeft, lewyGorny);
    painter.drawText(r, Qt::AlignRight, prawyGorny);
    painter.end();
}
