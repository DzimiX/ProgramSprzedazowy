#ifndef UNICODE
#define UNICODE
#endif
#ifndef _UNICODE
#define _UNICODE
#endif

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
    entryWindow = CreateWindowEx( WS_EX_CLIENTEDGE, className, TEXT("Program Sprzedażowy"),
            WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 900, 600, NULL, NULL, hInstance, NULL );
    if( entryWindow == NULL ){
        throw std::runtime_error("Problem z utworzeniem okna entryWindow");
    }
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

        default:
            return DefWindowProc( hwnd, msg, wParam, lParam );
    }

    return 0;
}