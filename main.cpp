//#ifndef UNICODE
//#define UNICODE
//#endif
//#ifndef _UNICODE
//#define _UNICODE
//#endif

#define BTN_ENTRY_OPENDB 100
#define BTN_ENTRY_CREATEDB 101
#define BTN_ENTRY_SKIPDB 102
#define BTN_INFO 103
#define BTN_ENTRY_RETURN 104
#define BTN_MAIN_SALES 105
#define BTN_MAIN_SUPPLIES 106
#define BTN_MAIN_CLIENTS 107
#define BTN_MAIN_PRODUCTS 108
#define BTN_MAIN_COMPANY 109
#define BTN_MAIN_RETURN 110

#define MAX_ROWS 10000
#define MAX_COLLUMNS 20

#include <windows.h>
#include <iostream>
#include <string>
#include "lib/sqlite3.h"

//LPWSTR className = TEXT("ProgramSprzedazowy");
LPSTR className = "ProgramSprzedazowy";
MSG mainMessage;

LRESULT CALLBACK WndProc( HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam );
int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow );
static int callback(void *data, int argc, char **argv, char **azColName);

// wyprowadzenie kontroli okien globalnie do płynnej zmiany
HWND entryWindow;
HWND openDbWindow;
HWND createDbWindow;
HWND mainWindow;
HWND salesWindow;
HWND suppliesWindow;
HWND clientsWindow;
HWND companyWindow;
HWND productsWindow;

HWND productsBox;

// wspólna część dla zapytań sql
sqlite3 *db;
char *zErrMsg = 0;
int rc;
char *sql;
std::string content[MAX_ROWS][MAX_COLLUMNS];
char *insert;
int row;
int i;

char buff[5000];
wchar_t wtext[5000];
LPWSTR ptr;

// funkcja obsługująca sql
static int callback(void *data, int argc, char **argv, char **azColName){
    int i;
    for(i = 0; i<argc; i++){
        //strcat(argv[i]," | ");
        content[row][i] = argv[i];
    }

    row++;
    return 0;
}

int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow ){
    // dev sql  https://www.tutorialspoint.com/sqlite/sqlite_c_cpp.htm
    //          https://www.sqlite.org/cintro.html
//    rc = sqlite3_open("db/test.db", &db); //baza musi być w katalogu db tam gdzie build jest odpalany
//    sql = "SELECT * FROM firma;";
//    rc = sqlite3_exec(db, sql, callback, (void*)data, &zErrMsg);
//    sqlite3_close(db);
    // tworzenie klasy dla appki
    WNDCLASSEX wc;
    wc.cbSize = sizeof( WNDCLASSEX );
    wc.style = 0;
    wc.lpfnWndProc = WndProc;
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hInstance = hInstance;
    wc.hIcon = LoadIcon( nullptr, IDI_APPLICATION );
    wc.hCursor = LoadCursor( nullptr, IDC_ARROW );
    wc.hbrBackground =( HBRUSH )( COLOR_WINDOW + 1 );
    wc.lpszMenuName = nullptr;
    wc.lpszClassName = className;
    wc.hIconSm = LoadIcon( nullptr, IDI_APPLICATION );
    if(!RegisterClassEx( & wc )){
        throw std::runtime_error("Problem z rejestracją klasy");
    }

    // tworzenie okien
    entryWindow = CreateWindowEx( WS_EX_CLIENTEDGE, className,
            TEXT("Program Sprzedażowy - wybierz tryb pracy"),
            WS_OVERLAPPEDWINDOW, 10, 50, 900, 600, nullptr, nullptr, hInstance, nullptr );
    if( entryWindow == nullptr ){
        throw std::runtime_error("Problem z utworzeniem okna entryWindow");
    }

    openDbWindow = CreateWindowEx( WS_EX_CLIENTEDGE, className,
            TEXT("Program Sprzedażowy - otwieranie bazy danych"),
            WS_OVERLAPPEDWINDOW, 10, 50, 900, 600, nullptr, nullptr, hInstance, nullptr );
    if( openDbWindow == nullptr ){
        throw std::runtime_error("Problem z utworzeniem okna openDbWindow");
    }

    createDbWindow = CreateWindowEx( WS_EX_CLIENTEDGE, className,
            TEXT("Program Sprzedażowy - tworzenie bazy danych"),
            WS_OVERLAPPEDWINDOW, 10, 50, 900, 600, nullptr, nullptr, hInstance, nullptr );
    if( openDbWindow == nullptr ){
        throw std::runtime_error("Problem z utworzeniem okna createDbWindow");
    }

    mainWindow = CreateWindowEx( WS_EX_CLIENTEDGE, className,
            TEXT("Program Sprzedażowy - praca"),
            WS_OVERLAPPEDWINDOW, 10, 50, 900, 600, nullptr, nullptr, hInstance, nullptr );
    if( openDbWindow == nullptr ){
        throw std::runtime_error("Problem z utworzeniem okna mainWindow");
    }

    salesWindow = CreateWindowEx( WS_EX_CLIENTEDGE, className,
            TEXT("Program Sprzedażowy - sprzedaż"),
            WS_OVERLAPPEDWINDOW, 10, 50, 900, 600, nullptr, nullptr, hInstance, nullptr );
    if( openDbWindow == nullptr ){
        throw std::runtime_error("Problem z utworzeniem okna salesWindow");
    }

    suppliesWindow = CreateWindowEx( WS_EX_CLIENTEDGE, className,
            TEXT("Program Sprzedażowy - dostawa"),
            WS_OVERLAPPEDWINDOW, 10, 50, 900, 600, nullptr, nullptr, hInstance, nullptr );
    if( openDbWindow == nullptr ){
        throw std::runtime_error("Problem z utworzeniem okna suppliesWindow");
    }

    clientsWindow = CreateWindowEx( WS_EX_CLIENTEDGE, className,
            TEXT("Program Sprzedażowy - kontrahenci"),
            WS_OVERLAPPEDWINDOW, 10, 50, 900, 600, nullptr, nullptr, hInstance, nullptr );
    if( openDbWindow == nullptr ){
        throw std::runtime_error("Problem z utworzeniem okna clientsWindow");
    }

    productsWindow = CreateWindowEx( WS_EX_CLIENTEDGE, className,
            TEXT("Program Sprzedażowy - produkty"),
            WS_OVERLAPPEDWINDOW, 10, 50, 900, 600, nullptr, nullptr, hInstance, nullptr );
    if( openDbWindow == nullptr ){
        throw std::runtime_error("Problem z utworzeniem okna productsWindow");
    }

    companyWindow = CreateWindowEx( WS_EX_CLIENTEDGE, className,
            TEXT("Program Sprzedażowy - firma"),
            WS_OVERLAPPEDWINDOW, 10, 50, 900, 600, nullptr, nullptr, hInstance, nullptr );
    if( openDbWindow == nullptr ){
        throw std::runtime_error("Problem z utworzeniem okna companyWindow");
    }

    //tworzenie "statycznej" treści dla okien
    HWND entry_openDB = CreateWindowEx( 0, TEXT("BUTTON"), TEXT("Otwórz bazę danych"),
            WS_CHILD | WS_VISIBLE, 5, 5, 200, 30, entryWindow, ( HMENU ) BTN_ENTRY_OPENDB, hInstance, nullptr );
    HWND entry_createDB = CreateWindowEx( 0, TEXT("BUTTON"), TEXT("Stwórz nową bazę danych"),
            WS_CHILD | WS_VISIBLE, 5, 40, 200, 30, entryWindow, ( HMENU ) BTN_ENTRY_CREATEDB, hInstance, nullptr );
    HWND entry_skipDB = CreateWindowEx( 0, TEXT("BUTTON"), TEXT("Pomiń bazę danych"),
            WS_CHILD | WS_VISIBLE, 5, 75, 200, 30, entryWindow, ( HMENU ) BTN_ENTRY_SKIPDB, hInstance, nullptr );
    HWND entry_info = CreateWindowEx( 0, TEXT("BUTTON"), TEXT("Informacje o programie"),
            WS_CHILD | WS_VISIBLE, 5, 110, 200, 30, entryWindow, ( HMENU ) BTN_INFO, hInstance, nullptr );

    HWND openDB_return = CreateWindowEx( 0, TEXT("BUTTON"), TEXT("Powrót"),
            WS_CHILD | WS_VISIBLE, 5, 520, 200, 30, openDbWindow, ( HMENU ) BTN_ENTRY_RETURN, hInstance, nullptr );
    HWND createDB_return = CreateWindowEx( 0, TEXT("BUTTON"), TEXT("Powrót"),
            WS_CHILD | WS_VISIBLE, 5, 520, 200, 30, createDbWindow, ( HMENU ) BTN_ENTRY_RETURN, hInstance, nullptr );

    HWND main_sales = CreateWindowEx( 0, TEXT("BUTTON"), TEXT("Sprzedaż"),
            WS_CHILD | WS_VISIBLE, 5, 5, 200, 30, mainWindow, ( HMENU ) BTN_MAIN_SALES, hInstance, nullptr );
    HWND main_supplies = CreateWindowEx( 0, TEXT("BUTTON"), TEXT("Dostawa"),
            WS_CHILD | WS_VISIBLE, 5, 40, 200, 30, mainWindow, ( HMENU ) BTN_MAIN_SUPPLIES, hInstance, nullptr );
    HWND main_clients = CreateWindowEx( 0, TEXT("BUTTON"), TEXT("Kontrahenci"),
            WS_CHILD | WS_VISIBLE, 5, 75, 200, 30, mainWindow, ( HMENU ) BTN_MAIN_CLIENTS, hInstance, nullptr );
    HWND main_products = CreateWindowEx( 0, TEXT("BUTTON"), TEXT("Produkty"),
            WS_CHILD | WS_VISIBLE, 5, 110, 200, 30, mainWindow, ( HMENU ) BTN_MAIN_PRODUCTS, hInstance, nullptr );
    HWND main_company = CreateWindowEx( 0, TEXT("BUTTON"), TEXT("Informacje o firmie"),
            WS_CHILD | WS_VISIBLE, 5, 145, 200, 30, mainWindow, ( HMENU ) BTN_MAIN_COMPANY, hInstance, nullptr );

    HWND sales_return = CreateWindowEx( 0, TEXT("BUTTON"), TEXT("Powrót"),
            WS_CHILD | WS_VISIBLE, 5, 520, 200, 30, salesWindow, ( HMENU ) BTN_MAIN_RETURN, hInstance, nullptr );
    HWND supplies_return = CreateWindowEx( 0, TEXT("BUTTON"), TEXT("Powrót"),
            WS_CHILD | WS_VISIBLE, 5, 520, 200, 30, suppliesWindow, ( HMENU ) BTN_MAIN_RETURN, hInstance, nullptr );
    HWND clients_return = CreateWindowEx( 0, TEXT("BUTTON"), TEXT("Powrót"),
            WS_CHILD | WS_VISIBLE, 5, 520, 200, 30, clientsWindow, ( HMENU ) BTN_MAIN_RETURN, hInstance, nullptr );
    HWND products_return = CreateWindowEx( 0, TEXT("BUTTON"), TEXT("Powrót"),
            WS_CHILD | WS_VISIBLE, 5, 520, 200, 30, productsWindow, ( HMENU ) BTN_MAIN_RETURN, hInstance, nullptr );
    HWND company_return = CreateWindowEx( 0, TEXT("BUTTON"), TEXT("Powrót"),
            WS_CHILD | WS_VISIBLE, 5, 520, 200, 30, companyWindow, ( HMENU ) BTN_MAIN_RETURN, hInstance, nullptr );

//    char *buff;
//    std::string name = "stackoverflow";
//    sprintf_s(buff, (size_t) "name is:%s", name.c_str());
//    std::cout << buff;
//    LPCWSTR ws = reinterpret_cast<LPCWSTR>(buff);

    //MessageBox(entryWindow , ptr, L"Msg title", MB_OK | MB_ICONQUESTION);

    productsBox = CreateWindowEx( WS_EX_CLIENTEDGE, TEXT("LISTBOX"), NULL, WS_CHILD | WS_VISIBLE | WS_BORDER,
            210, 5, 450, 505, productsWindow, NULL, hInstance, NULL );

    ShowWindow( entryWindow, nCmdShow );

    while( GetMessage( & mainMessage, nullptr, 0, 0 ) ){
        TranslateMessage( & mainMessage );
        DispatchMessage( & mainMessage );
    }

    return mainMessage.wParam;
}

LRESULT CALLBACK WndProc( HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam ){
    switch( msg ){
        case WM_CLOSE: // zamkniecie
            DestroyWindow( hwnd );
            break;
        case WM_DESTROY: // zniszczenie po zamknieciu(?)
            PostQuitMessage( 0 );
            break;
        case WM_COMMAND: //jakaś akcja na jakimś elemencie
            switch (wParam){ //wParam - element o zdefiniowanym numerze
                case BTN_ENTRY_OPENDB: // obsługa konkretnego buttona (jego odwołania do zdef numeru)
                    ShowWindow( openDbWindow, SW_SHOW );
                    ShowWindow( hwnd, SW_HIDE );
                    break;
                case BTN_ENTRY_CREATEDB:
                    ShowWindow( createDbWindow, SW_SHOW );
                    ShowWindow( hwnd, SW_HIDE );
                    break;
                case BTN_ENTRY_SKIPDB:
                    ShowWindow( mainWindow, SW_SHOW );
                    ShowWindow( hwnd, SW_HIDE );
                    break;
                case BTN_INFO:
                    MessageBoxEx(hwnd, TEXT("Program Sprzedażowy \n"
                                            "Autor: Maciej Dzimira\n"
                                            "v 19.10.28"),
                            TEXT("Informacje o programie"), MB_ICONINFORMATION, NULL);
                    break;
                case BTN_ENTRY_RETURN:
                    ShowWindow( entryWindow, SW_SHOW );
                    ShowWindow( hwnd, SW_HIDE );
                    break;
                case BTN_MAIN_SALES:
                    ShowWindow( salesWindow, SW_SHOW );
                    ShowWindow( hwnd, SW_HIDE );
                    break;
                case BTN_MAIN_SUPPLIES:
                    ShowWindow( suppliesWindow, SW_SHOW );
                    ShowWindow( hwnd, SW_HIDE );
                    break;
                case BTN_MAIN_CLIENTS:
                    ShowWindow( clientsWindow, SW_SHOW );
                    ShowWindow( hwnd, SW_HIDE );
                    break;
                case BTN_MAIN_PRODUCTS:
                    //SetWindowText( productsMessage, TEXT("puste pole") );
                    row = 0; //aktualny wiersz, zerowanie dla nowego sqla
                    rc = sqlite3_open("db/test.db", &db);
                    sql = "SELECT * FROM produkty";
                    rc = sqlite3_exec(db, sql, callback, nullptr, nullptr);
                    sqlite3_close(db);
                    //std::cout << content[0][0] << content[0][1] << content[0][2] << content[0][3] << content[0][4] << std::endl; //testy
                    //std::cout << "wiersze: " << row << std::endl;

                    SendMessage( productsBox, LB_RESETCONTENT, 0, 0); //czyszczenie listy
                    SendMessage( productsBox, LB_ADDSTRING, 0,( LPARAM ) TEXT("ID | NAZWA | JEDNOSTKA | CENA | VAT") );
                    for(i = 0;i<row;i++){
                        strcpy(buff, ""); // zerowanie bufora
                        strcat(buff, content[i][0].c_str());
                        strcat(buff, " | ");
                        strcat(buff, content[i][1].c_str());
                        strcat(buff, " | ");
                        strcat(buff, content[i][2].c_str());
                        strcat(buff, " | ");
                        strcat(buff, content[i][3].c_str());
                        strcat(buff, " | ");
                        strcat(buff, content[i][4].c_str());
                        SendMessage( productsBox, LB_ADDSTRING, 0,( LPARAM ) buff );
                    }

                    //std::cout << "string contentu:: " << content[0][1] << std::endl;
                    //std::cout << "char* contentu:: " << content[0][1].c_str() << std::endl; // c_str() do zamiany stringa na char żeby sklejać
                    //std::cout << "char* buff:: " << buff << std::endl; // ok?

                    //buff += '';


                    //strcat(buff,content[0][1].c_str());
                    //std::cout << "połączone :: " << buff << std::endl; // ok?

                    //buff = "sklejone śmieci z zapytań";
                    mbstowcs(wtext, buff, strlen(buff)+1);//Plus null
                    ptr = wtext;
                    row = 0;
                    //MessageBoxEx(hwnd, ptr, NULL, MB_ICONINFORMATION, NULL);
                    //SetWindowText( productsMessage, ptr );
                    ShowWindow( productsWindow, SW_SHOW );
                    ShowWindow( hwnd, SW_HIDE );
                    break;
                case BTN_MAIN_COMPANY:
                    ShowWindow( companyWindow, SW_SHOW );
                    ShowWindow( hwnd, SW_HIDE );
                    break;
                case BTN_MAIN_RETURN:
                    ShowWindow( mainWindow, SW_SHOW );
                    ShowWindow( hwnd, SW_HIDE );
                    break;
            }
            break;
        default:
            return DefWindowProc( hwnd, msg, wParam, lParam );
    }
    return 0;
}