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

#include <windows.h>
#include <iostream>

LPWSTR className = TEXT("ProgramSprzedazowy");
MSG mainMessage;
LRESULT CALLBACK WndProc( HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam );

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

    HWND entryWindow;
    entryWindow = CreateWindowEx( WS_EX_CLIENTEDGE, className, TEXT("Program Sprzedażowy - wybierz tryb pracy"),
            WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 900, 600, NULL, NULL, hInstance, NULL );
    if( entryWindow == NULL ){
        throw std::runtime_error("Problem z utworzeniem okna entryWindow");
    }
    ShowWindow( entryWindow, nCmdShow );
    UpdateWindow( entryWindow );

    HWND openDB = CreateWindowEx( 0, TEXT("BUTTON"), TEXT("Otwórz bazę danych"),
            WS_CHILD | WS_VISIBLE, 5, 5, 200, 30, entryWindow, ( HMENU ) BTN_ENTRY_OPENDB, hInstance, NULL );
    HWND createDB = CreateWindowEx( 0, TEXT("BUTTON"), TEXT("Stwórz nową bazę danych"),
            WS_CHILD | WS_VISIBLE, 5, 40, 200, 30, entryWindow, ( HMENU ) BTN_ENTRY_CREATEDB, hInstance, NULL );
    HWND skipDB = CreateWindowEx( 0, TEXT("BUTTON"), TEXT("Pomiń bazę danych"),
            WS_CHILD | WS_VISIBLE, 5, 75, 200, 30, entryWindow, ( HMENU ) BTN_ENTRY_SKIPDB, hInstance, NULL );
    HWND info = CreateWindowEx( 0, TEXT("BUTTON"), TEXT("Informacje o programie"),
            WS_CHILD | WS_VISIBLE, 5, 110, 200, 30, entryWindow, ( HMENU ) BTN_INFO, hInstance, NULL );

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

        default:
            return DefWindowProc( hwnd, msg, wParam, lParam );
    }

    return 0;
}