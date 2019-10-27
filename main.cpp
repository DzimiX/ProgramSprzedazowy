#ifndef UNICODE
#define UNICODE
#endif
#ifndef _UNICODE
#define _UNICODE
#endif

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

#include <windows.h>
#include <iostream>
#include "lib/sqlite3.h"

LPWSTR className = TEXT("ProgramSprzedazowy");
MSG mainMessage;

LRESULT CALLBACK WndProc( HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam );
int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow );

HWND entryWindow;
HWND openDbWindow;
HWND createDbWindow;
HWND mainWindow;
HWND salesWindow;
HWND suppliesWindow;
HWND clientsWindow;
HWND companyWindow;
HWND productsWindow;

int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow ){
    WNDCLASSEX wc;
    wc.cbSize = sizeof( WNDCLASSEX );
    wc.style = 0;
    wc.lpfnWndProc = WndProc;
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hInstance = hInstance;
    wc.hIcon = LoadIcon( NULL, IDI_APPLICATION );
    wc.hCursor = LoadCursor( NULL, IDC_ARROW );
    wc.hbrBackground =( HBRUSH )( COLOR_WINDOW + 1 );
    wc.lpszMenuName = NULL;
    wc.lpszClassName = className;
    wc.hIconSm = LoadIcon( NULL, IDI_APPLICATION );
    if(!RegisterClassEx( & wc )){
        throw std::runtime_error("Problem z rejestracją klasy");
    }

    entryWindow = CreateWindowEx( WS_EX_CLIENTEDGE, className,
            TEXT("Program Sprzedażowy - wybierz tryb pracy"),
            WS_OVERLAPPEDWINDOW, 10, 50, 900, 600, NULL, NULL, hInstance, NULL );
    if( entryWindow == NULL ){
        throw std::runtime_error("Problem z utworzeniem okna entryWindow");
    }

    openDbWindow = CreateWindowEx( WS_EX_CLIENTEDGE, className,
            TEXT("Program Sprzedażowy - otwieranie bazy danych"),
            WS_OVERLAPPEDWINDOW, 10, 50, 900, 600, NULL, NULL, hInstance, NULL );
    if( openDbWindow == NULL ){
        throw std::runtime_error("Problem z utworzeniem okna openDbWindow");
    }

    createDbWindow = CreateWindowEx( WS_EX_CLIENTEDGE, className,
            TEXT("Program Sprzedażowy - tworzenie bazy danych"),
            WS_OVERLAPPEDWINDOW, 10, 50, 900, 600, NULL, NULL, hInstance, NULL );
    if( openDbWindow == NULL ){
        throw std::runtime_error("Problem z utworzeniem okna createDbWindow");
    }

    mainWindow = CreateWindowEx( WS_EX_CLIENTEDGE, className,
            TEXT("Program Sprzedażowy - praca"),
            WS_OVERLAPPEDWINDOW, 10, 50, 900, 600, NULL, NULL, hInstance, NULL );
    if( openDbWindow == NULL ){
        throw std::runtime_error("Problem z utworzeniem okna mainWindow");
    }

    salesWindow = CreateWindowEx( WS_EX_CLIENTEDGE, className,
            TEXT("Program Sprzedażowy - sprzedaż"),
            WS_OVERLAPPEDWINDOW, 10, 50, 900, 600, NULL, NULL, hInstance, NULL );
    if( openDbWindow == NULL ){
        throw std::runtime_error("Problem z utworzeniem okna salesWindow");
    }

    suppliesWindow = CreateWindowEx( WS_EX_CLIENTEDGE, className,
            TEXT("Program Sprzedażowy - dostawa"),
            WS_OVERLAPPEDWINDOW, 10, 50, 900, 600, NULL, NULL, hInstance, NULL );
    if( openDbWindow == NULL ){
        throw std::runtime_error("Problem z utworzeniem okna suppliesWindow");
    }

    clientsWindow = CreateWindowEx( WS_EX_CLIENTEDGE, className,
            TEXT("Program Sprzedażowy - kontrahenci"),
            WS_OVERLAPPEDWINDOW, 10, 50, 900, 600, NULL, NULL, hInstance, NULL );
    if( openDbWindow == NULL ){
        throw std::runtime_error("Problem z utworzeniem okna clientsWindow");
    }

    productsWindow = CreateWindowEx( WS_EX_CLIENTEDGE, className,
            TEXT("Program Sprzedażowy - produkty"),
            WS_OVERLAPPEDWINDOW, 10, 50, 900, 600, NULL, NULL, hInstance, NULL );
    if( openDbWindow == NULL ){
        throw std::runtime_error("Problem z utworzeniem okna productsWindow");
    }

    companyWindow = CreateWindowEx( WS_EX_CLIENTEDGE, className,
            TEXT("Program Sprzedażowy - firma"),
            WS_OVERLAPPEDWINDOW, 10, 50, 900, 600, NULL, NULL, hInstance, NULL );
    if( openDbWindow == NULL ){
        throw std::runtime_error("Problem z utworzeniem okna companyWindow");
    }


    HWND entry_openDB = CreateWindowEx( 0, TEXT("BUTTON"), TEXT("Otwórz bazę danych"),
            WS_CHILD | WS_VISIBLE, 5, 5, 200, 30, entryWindow, ( HMENU ) BTN_ENTRY_OPENDB, hInstance, NULL );
    HWND entry_createDB = CreateWindowEx( 0, TEXT("BUTTON"), TEXT("Stwórz nową bazę danych"),
            WS_CHILD | WS_VISIBLE, 5, 40, 200, 30, entryWindow, ( HMENU ) BTN_ENTRY_CREATEDB, hInstance, NULL );
    HWND entry_skipDB = CreateWindowEx( 0, TEXT("BUTTON"), TEXT("Pomiń bazę danych"),
            WS_CHILD | WS_VISIBLE, 5, 75, 200, 30, entryWindow, ( HMENU ) BTN_ENTRY_SKIPDB, hInstance, NULL );
    HWND entry_info = CreateWindowEx( 0, TEXT("BUTTON"), TEXT("Informacje o programie"),
            WS_CHILD | WS_VISIBLE, 5, 110, 200, 30, entryWindow, ( HMENU ) BTN_INFO, hInstance, NULL );

    HWND openDB_return = CreateWindowEx( 0, TEXT("BUTTON"), TEXT("Powrót"),
            WS_CHILD | WS_VISIBLE, 5, 520, 200, 30, openDbWindow, ( HMENU ) BTN_ENTRY_RETURN, hInstance, NULL );
    HWND createDB_return = CreateWindowEx( 0, TEXT("BUTTON"), TEXT("Powrót"),
            WS_CHILD | WS_VISIBLE, 5, 520, 200, 30, createDbWindow, ( HMENU ) BTN_ENTRY_RETURN, hInstance, NULL );

    HWND main_sales = CreateWindowEx( 0, TEXT("BUTTON"), TEXT("Sprzedaż"),
            WS_CHILD | WS_VISIBLE, 5, 5, 200, 30, mainWindow, ( HMENU ) BTN_MAIN_SALES, hInstance, NULL );
    HWND main_supplies = CreateWindowEx( 0, TEXT("BUTTON"), TEXT("Dostawa"),
            WS_CHILD | WS_VISIBLE, 5, 40, 200, 30, mainWindow, ( HMENU ) BTN_MAIN_SUPPLIES, hInstance, NULL );
    HWND main_clients = CreateWindowEx( 0, TEXT("BUTTON"), TEXT("Kontrahenci"),
            WS_CHILD | WS_VISIBLE, 5, 75, 200, 30, mainWindow, ( HMENU ) BTN_MAIN_CLIENTS, hInstance, NULL );
    HWND main_products = CreateWindowEx( 0, TEXT("BUTTON"), TEXT("Produkty"),
            WS_CHILD | WS_VISIBLE, 5, 110, 200, 30, mainWindow, ( HMENU ) BTN_MAIN_PRODUCTS, hInstance, NULL );
    HWND main_company = CreateWindowEx( 0, TEXT("BUTTON"), TEXT("Informacje o firmie"),
            WS_CHILD | WS_VISIBLE, 5, 145, 200, 30, mainWindow, ( HMENU ) BTN_MAIN_COMPANY, hInstance, NULL );

    HWND sales_return = CreateWindowEx( 0, TEXT("BUTTON"), TEXT("Powrót"),
            WS_CHILD | WS_VISIBLE, 5, 520, 200, 30, salesWindow, ( HMENU ) BTN_MAIN_RETURN, hInstance, NULL );
    HWND supplies_return = CreateWindowEx( 0, TEXT("BUTTON"), TEXT("Powrót"),
            WS_CHILD | WS_VISIBLE, 5, 520, 200, 30, suppliesWindow, ( HMENU ) BTN_MAIN_RETURN, hInstance, NULL );
    HWND clients_return = CreateWindowEx( 0, TEXT("BUTTON"), TEXT("Powrót"),
            WS_CHILD | WS_VISIBLE, 5, 520, 200, 30, clientsWindow, ( HMENU ) BTN_MAIN_RETURN, hInstance, NULL );
    HWND products_return = CreateWindowEx( 0, TEXT("BUTTON"), TEXT("Powrót"),
            WS_CHILD | WS_VISIBLE, 5, 520, 200, 30, productsWindow, ( HMENU ) BTN_MAIN_RETURN, hInstance, NULL );
    HWND company_return = CreateWindowEx( 0, TEXT("BUTTON"), TEXT("Powrót"),
            WS_CHILD | WS_VISIBLE, 5, 520, 200, 30, companyWindow, ( HMENU ) BTN_MAIN_RETURN, hInstance, NULL );

    ShowWindow( entryWindow, nCmdShow );
    UpdateWindow( entryWindow );

    while( GetMessage( & mainMessage, NULL, 0, 0 ) ){
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
                case BTN_ENTRY_OPENDB: // przejscie do innego okna
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
                                            "v 19.10.27"),
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