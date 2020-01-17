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
        QDir dir(qApp->applicationDirPath()+"/db"); //
        if (!dir.exists()){ //creates directory to make db creation possible
          dir.mkdir(".");   //
        }                   //
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
                "adres_kodPocztowy  TEXT,"
                "motyw              TEXT"
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
            "INSERT INTO firma (nazwa,motyw)"
            "VALUES ('Uzupełnij dane firmy!','Jasny')"
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

void sql::dbCreatePdf(int invoiceId){
    QDir dir(qApp->applicationDirPath()+"/faktury");
    if (!dir.exists()){
      dir.mkdir(".");
    }
    QString fileName = QFileDialog::getSaveFileName(nullptr,
                                                    "Zapisz fakturę",
                                                    qApp->applicationDirPath()+"/faktury/faktura_"+QString::number(invoiceId),
                                                    "Plik PDF (*.pdf)");
    QPrinter printer(QPrinter::PrinterResolution);
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setPaperSize(QPrinter::A4);
    printer.setOutputFileName(fileName);

    sql conn;
    conn.dbOpen(conn.location);
    QSqlQuery *query = new QSqlQuery(conn.db);

    query->prepare("SELECT * FROM firma;");
    query->exec();
    query->seek(0);

    QString faktura_nr = QString::number(invoiceId);
    QString sklep_miasto = query->value(7).toString();
    QString aktualna_data = QDateTime::currentDateTime().toString( "dd/MM/yyyy" );
    QString sprzedawca_nazwa = query->value(0).toString();
    QString sprzedawca_miasto = query->value(7).toString();
    QString sprzedawca_ulica = query->value(8).toString();
    QString sprzedawca_numer = query->value(9).toString();
    QString sprzedawca_kodPocztowy = query->value(10).toString();
    QString sprzedawca_telefon = query->value(6).toString();
    QString sprzedawca_email = query->value(5).toString();

    query->prepare("SELECT kontrahenci.nazwa,"
                       "kontrahenci.adres_miasto,"
                       "kontrahenci.adres_ulica,"
                       "kontrahenci.adres_numer,"
                       "kontrahenci.adres_kodPocztowy,"
                       "kontrahenci.telefon,"
                       "kontrahenci.email,"
                       "faktury.data "
                   "FROM kontrahenci,faktury "
                   "WHERE "
                       "kontrahenci.id=faktury.id_kontrahent "
                       "AND faktury.id=:ID;");
    query->bindValue(":ID", invoiceId);
    query->exec();
    query->seek(0);
    QString nabywca_nazwa = query->value(0).toString();
    QString nabywca_miasto = query->value(1).toString();
    QString nabywca_ulica = query->value(2).toString();
    QString nabywca_numer = query->value(3).toString();
    QString nabywca_kodPocztowy = query->value(4).toString();
    QString nabywca_telefon = query->value(5).toString();
    QString nabywca_email = query->value(6).toString();
    QString faktura_dzien = query->value(7).toString();


    query->prepare("SELECT round(sum(produkty.cena * rozliczenia.ilosc),2),"
                   " round(sum(produkty.cena * produkty.VAT * 0.01 * rozliczenia.ilosc),2),"
                   " round(sum(produkty.cena * rozliczenia.ilosc + produkty.cena * produkty.VAT * 0.01 * rozliczenia.ilosc),2)"
                   " FROM rozliczenia,produkty WHERE rozliczenia.id_faktura=:id_faktura AND rozliczenia.id_produkt=produkty.id");
    query->bindValue(":id_faktura",invoiceId);
    query->exec();
    query->seek(0);

    QString suma_netto = query->value(0).toString();
    QString suma_vat = query->value(1).toString();
    QString suma_brutto = query->value(2).toString();

    query->prepare("SELECT ROW_NUMBER () OVER ( ORDER BY rozliczenia.id ) RowNum, "
                       "produkty.nazwa AS Nazwa,round(produkty.cena,2), "
                       "round(produkty.VAT,2), "
                       "rozliczenia.ilosc, "
                       "round((produkty.cena * rozliczenia.ilosc),2), "
                       "round((produkty.cena * produkty.VAT * 0.01 * rozliczenia.ilosc),2), "
                       "round((produkty.cena * rozliczenia.ilosc + produkty.cena * produkty.VAT * 0.01 * rozliczenia.ilosc),2) "
                   "FROM rozliczenia,produkty "
                   "WHERE "
                       "rozliczenia.id_faktura=:ID "
                       "AND rozliczenia.id_produkt=produkty.id");
    query->bindValue(":ID", invoiceId);
    query->exec();
    query->seek(-1);

    QTextDocument doc;
    QString text("");
    text.append("<html>");
        text.append("<head>");
            text.append("<style>");
                text.append(".right { text-align: right; }");
                text.append("table { border-collapse: collapse; }");
                text.append(".border td, th { border: 1px solid black; }");
            text.append("</style>");
        text.append("</head>");
        text.append("<body>");
            text.append("<table border='0' width='100%' style='margin: 0px;'>");
                text.append("<tr>");
                    text.append("<td>");
                        text.append("Faktura nr ");
                        text.append(faktura_nr);
                        text.append(", z dnia ");
                        text.append(faktura_dzien);
                    text.append("</td>");
                    text.append("<td class='right'>");
                        text.append(sklep_miasto);
                        text.append(", ");
                        text.append(aktualna_data);
                    text.append("</td>");
                text.append("</tr>");
            text.append("</table>");
            text.append("<br><br>");
            text.append("<table border='0' width='100%' style='margin: 0px;'>");
                text.append("<tr>");
                    text.append("<td>");
                        text.append("SPRZEDAWCA:<br>");
                        text.append(sprzedawca_nazwa);
                        text.append("<br>");
                        text.append(sprzedawca_ulica);
                        text.append(" ");
                        text.append(sprzedawca_numer);
                        text.append("<br>");
                        text.append(sprzedawca_kodPocztowy);
                        text.append(" ");
                        text.append(sprzedawca_miasto);
                        if(sprzedawca_telefon!=""){
                            text.append("<br>Telefon: ");
                            text.append(sprzedawca_telefon);
                        }
                        if(sprzedawca_email!=""){
                            text.append("<br>Email: ");
                            text.append(sprzedawca_email);
                        }
                    text.append("</td>");
                    text.append("<td class='right'>");
                        text.append("NABYWCA:<br>");
                        text.append(nabywca_nazwa);
                        text.append("<br>");
                        text.append(nabywca_ulica);
                        text.append(" ");
                        text.append(nabywca_numer);
                        text.append("<br>");
                        text.append(nabywca_kodPocztowy);
                        text.append(" ");
                        text.append(nabywca_miasto);
                        if(nabywca_telefon!=""){
                            text.append("<br>Telefon: ");
                            text.append(nabywca_telefon);
                        }
                        if(nabywca_email!=""){
                            text.append("<br>Email: ");
                            text.append(nabywca_email);
                        }
                    text.append("</td>");
                text.append("</tr>");
            text.append("</table>");
            text.append("<br><br>");
            text.append("W ZAMÓWIENIU:");
            text.append("<table class='border' width='100%' style='margin: 0px;'>");
                text.append("<tr>");
                    text.append("<th>LP</th>");
                    text.append("<th>Nazwa</th>");
                    text.append("<th>Cena</th>");
                    text.append("<th>VAT</th>");
                    text.append("<th>Ilość</th>");
                    text.append("<th>Suma Netto</th>");
                    text.append("<th>Suma VAT</th>");
                    text.append("<th>Suma Brutto</th>");
                text.append("</tr>");
            while(query->next()){
                text.append("<tr>");
                    text.append("<td>");
                        text.append(query->value(0).toString());
                    text.append("</td>");
                    text.append("<td>");
                        text.append(query->value(1).toString());
                    text.append("</td>");
                    text.append("<td>");
                        text.append(query->value(2).toString());
                    text.append("</td>");
                    text.append("<td>");
                        text.append(query->value(3).toString());
                    text.append("</td>");
                    text.append("<td>");
                        text.append(query->value(4).toString());
                    text.append("</td>");
                    text.append("<td>");
                        text.append(query->value(5).toString());
                    text.append("</td>");
                    text.append("<td>");
                        text.append(query->value(6).toString());
                    text.append("</td>");
                    text.append("<td>");
                        text.append(query->value(7).toString());
                    text.append("</td>");
                text.append("</tr>");
            }
            text.append("</table>");
            text.append("<br><br>");
            text.append("<b>DO ZAPŁATY</b>");
            text.append("<br>");
            text.append("SUMA NETTO: ");
            text.append(suma_netto);
            text.append("<br>");
            text.append("SUMA VAT: ");
            text.append(suma_vat);
            text.append("<br>");
            text.append("SUMA BRUTTO: <b>");
            text.append(suma_brutto);
            text.append("</b><br><br><br><table width='100%'><tr><td>________________________<br>(sprzedawca)</td>");
            text.append("<td class='right'>________________________<br>(odbiorca)</td></td></table>");
        text.append("</body>");
    text.append("</html>");

    doc.setHtml(text);
    doc.setPageSize(printer.pageRect().size());
    doc.print(&printer);

    conn.dbClose();
}
