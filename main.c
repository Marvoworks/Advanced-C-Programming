#include <windows.h>
#include <commctrl.h>
#include <commdlg.h>
#include <wchar.h>
#include "defines.h"

/*  Declare Windows procedure  */
LRESULT CALLBACK WindowProcedure (HWND, UINT, WPARAM, LPARAM);
void LoadMyImage(HWND);
HICON hIcon, hIconSm;
HANDLE g_Inst;
/*  Make the class name into a global variable  */
char szClassName[ ] = "MSD";

int WINAPI WinMain (HINSTANCE hThisInstance,
                    HINSTANCE hPrevInstance,
                    LPSTR lpszArgument,
                    int nFunsterStil)

{
    HWND hwnd;               /* This is the handle for our window */
    MSG messages;            /* Here messages to the application are saved */
    WNDCLASSEX wincl;        /* Data structure for the windowclass */

    /* The Window structure */
    wincl.hInstance = hThisInstance;
    wincl.lpszClassName = szClassName;
    wincl.lpfnWndProc = WindowProcedure;      /* This function is called by windows */
    wincl.style = CS_DBLCLKS;                 /* Catch double-clicks */
    wincl.cbSize = sizeof (WNDCLASSEX);

    /* Use default icon and mouse-pointer */
    wincl.hIcon = LoadIcon (NULL, IDI_APPLICATION);
    wincl.hIconSm = LoadIcon (NULL, IDI_APPLICATION);
    wincl.hCursor = LoadCursor (NULL, IDC_ARROW);
    wincl.lpszMenuName = NULL;                 /* No menu */
    wincl.cbClsExtra = 0;                      /* No extra bytes after the window class */
    wincl.cbWndExtra = 0;                      /* structure or the window instance */
    /* Use Windows's default color as the background of the window */
    wincl.hbrBackground = (HBRUSH) CreateSolidBrush(RGB(0, 0, 0));

    /* Register the window class, and if it fails quit the program */
    if (!RegisterClassEx (&wincl))
        return 0;

    /* The class is registered, let's create the program*/
    hwnd = CreateWindowEx (
           0,                   /* Extended possibilites for variation */
           szClassName,         /* Classname */
           "MSD TAB API",       /* Title Text */
           WS_OVERLAPPEDWINDOW|WS_CLIPSIBLINGS, /* default window */
           CW_USEDEFAULT,       /* Windows decides the position */
           CW_USEDEFAULT,       /* where the window ends up on the screen */
           544,                 /* The programs width */
           375,                 /* and height in pixels */
           HWND_DESKTOP,        /* The window is a child-window to desktop */
           NULL,                /* No menu */
           hThisInstance,       /* Program Instance handler */
           NULL                 /* No Window Creation data */
           );

    /* Make the window visible on the screen */
    ShowWindow (hwnd, nFunsterStil);

    /* Run the message loop. It will run until GetMessage() returns 0 */
    while (GetMessage (&messages, NULL, 0, 0))
    {
        /* Translate virtual-key messages into character messages */
        TranslateMessage(&messages);
        /* Send message to WindowProcedure */
        DispatchMessage(&messages);
    }

    /* The program return-value is 0 - The value that PostQuitMessage() gave */
    return messages.wParam;
}


/*  This function is called by the Windows function DispatchMessage()  */

LRESULT CALLBACK WindowProcedure (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    HFONT hFot;            
        
    switch (message)                  /* handle the messages */
    {
        case WM_CREATE:
        {
            LoadMyImage(hwnd); 
             
            HWND Tab;
            TCITEM tie;
            HFONT hFont = GetStockObject(DEFAULT_GUI_FONT);
            Tab = CreateWindow(WC_TABCONTROL, "", WS_CHILD|WS_CLIPSIBLINGS|WS_VISIBLE|DS_3DLOOK, 0,0,529,300, hwnd, (HMENU)TABCONTROL, g_Inst, NULL);
            tie.mask = TCIF_TEXT | TCIF_IMAGE;
            tie.iImage = -1;
            tie.pszText = "Version";
            TabCtrl_InsertItem(Tab, FCTRLP, &tie); 
            tie.pszText = "Authors";
            TabCtrl_InsertItem(Tab, SCTRLP, &tie);
            tie.pszText = "Thanks";
            TabCtrl_InsertItem(Tab, TCTRLP, &tie);
            SendMessage(Tab, WM_SETFONT, (WPARAM)hFont, (LPARAM)TRUE);
            HWND hwndStatic = CreateWindow(WC_STATIC, "", WS_CHILD | WS_VISIBLE|WS_BORDER, 0, 22, 526, 275, hwnd, (HMENU)STATICTRL, g_Inst, NULL);
                                                                            
                                               hFot = CreateFont(18, 0, 0, 0, FW_MEDIUM, 0, 0, 0, 0, 0, 0, 0, 0, "Georgia");
                                               char szTextF[ ] = "\n          Welcome to MSD Tabbed Window Example.\n\n          Application Version: 0.0.1.";                                            
                                               SendMessage(hwndStatic, WM_SETFONT, (WPARAM)hFot, (LPARAM)TRUE);
                                               SendMessage(hwndStatic, WM_SETTEXT, 0, (LPARAM)szTextF);
                                               HWND hsti = CreateWindow("Static", "", WS_CHILD | WS_VISIBLE | SS_ICON, 28, 105, 100, 100, hwndStatic, (HMENU) MSD_IMG, NULL, NULL);
                                               SendMessage(hsti, STM_SETIMAGE,(WPARAM) IMAGE_ICON, (LPARAM) hIcon);                                                
                                                            
            HWND hwndBtn = CreateWindow("Button", "Close", WS_CHILD | WS_VISIBLE|WS_BORDER, 420, 303, 100, 30, hwnd, (HMENU)BTNCTRL, g_Inst, NULL);                          
         }
        case WM_NOTIFY:
        {
             switch(((LPNMHDR)lParam)->code)
             {
                    case TCN_SELCHANGING:
                         {
                               return FALSE;
                         }
                         break; 
                    case TCN_SELCHANGE:
                         {
                                HWND Tab = GetDlgItem(hwnd, TABCONTROL);
                                int iPage = TabCtrl_GetCurSel(Tab);
                                switch(iPage)
                                {
                                       case FCTRLP:
                                            {
                                               HWND hwndStatic = GetDlgItem(hwnd, STATICTRL);                                                      
                                               hFot = CreateFont(18, 0, 0, 0, FW_MEDIUM, 0, 0, 0, 0, 0, 0, 0, 0, "Georgia");
                                               char szTextF[ ] = "\n          Welcome to MSD Tabbed Window Example.\n\n          Application Version: 0.0.1.";                                            
                                               SendMessage(hwndStatic, WM_SETFONT, (WPARAM)hFot, (LPARAM)TRUE);
                                               SendMessage(hwndStatic, WM_SETTEXT, 0, (LPARAM)szTextF);
                                                                                             
                                               HWND hsti = CreateWindow("Static", "", WS_CHILD | WS_VISIBLE | SS_ICON, 28, 105, 100, 100, hwndStatic, (HMENU) MSD_IMG, NULL, NULL);
                                               SendMessage(hsti, STM_SETIMAGE,(WPARAM) IMAGE_ICON, (LPARAM) hIcon);                                                                                                                                                                                                   
                                            }
                                            break;
                                       case SCTRLP:
                                            {
                                                   HWND hwndStatic = GetDlgItem(hwnd, STATICTRL); 
                                                   HDC hdc;
                                                   PAINTSTRUCT ps;
                                                   hdc = BeginPaint(hwndStatic, &ps);
                                                                                                                                                       
                                               hFot = CreateFont(18, 0, 0, 0, FW_MEDIUM, 0, 0, 0, 0, 0, 0, 0, 0, "Georgia");
                                               char szTextF[ ] = "\n          Application designed and Complied by:\n\n          Devmarvo Kikomeko\n          Also known as Raggamarvin Kiomeko on Facebook\n";                                            
                                               SendMessage(hwndStatic, WM_SETFONT, (WPARAM)hFot, (LPARAM)TRUE);
                                               SendMessage(hwndStatic, WM_SETTEXT, 0, (LPARAM)szTextF); 
                                               
                                               HWND hsti = CreateWindow("Static", "", WS_CHILD | WS_VISIBLE | SS_ICON, 28, 105, 100, 100, hwndStatic, (HMENU) MSD_IMG, NULL, NULL);
                                               SendMessage(hsti, STM_SETIMAGE,(WPARAM) IMAGE_ICON, (LPARAM) hIcon);                                                                                                      
                                            }                                            
                                            break;
                                       case TCTRLP:
                                       {
                                                   HWND hwndStatic = GetDlgItem(hwnd, STATICTRL); 
                                                   
                                        }     
                                            break;
                                       default:
                                               MessageBox(hwnd, "Current Tab Selected has no info", "Interaction", MB_OK|MB_ICONINFORMATION);
                                            break;      
                                }       
                         }
                         break;                       
             }
         }
           break;        
           break;
        case WM_COMMAND:
             {
                        switch(LOWORD(wParam))
                        {
                                case BTNCTRL:
                                             SendMessage(hwnd, WM_CLOSE, 0, 0);
                                     break;              
                        }
             }
             break; 
        case WM_CTLCOLORSTATIC:
             {
               HBRUSH g_hbrBackground = CreateSolidBrush(RGB(255, 255, 255));                
               HDC hdcStatic = (HDC)wParam;
               SetTextColor(hdcStatic, RGB(0, 0, 0));
               SetBkMode(hdcStatic, TRANSPARENT);
               return (LONG)g_hbrBackground;
            } 
             break; 
        case WM_CLOSE:
             {
           if (MessageBox(hwnd, "Pressing ok terminates program.\n\nWhat's your choice.", "MSD", MB_ICONINFORMATION|MB_YESNOCANCEL) == IDYES) 
           PostMessage(hwnd, WM_DESTROY, 0, 0);                       
             }
             break;     
        case WM_DESTROY:
            PostQuitMessage (0);       /* send a WM_QUIT to the message queue */
            break;
        default:                      /* for messages that we don't deal with */
            return DefWindowProc (hwnd, message, wParam, lParam);
    }

    return 0;
}
void LoadMyImage(HWND hwnd) 
{
  hIcon = LoadImage(NULL, "mg/MSN.ICO", IMAGE_ICON, 32, 32, LR_LOADFROMFILE);
 if(hIcon)
 SendMessage(hwnd, WM_SETICON, ICON_BIG, (LPARAM)hIcon);
 else
 MessageBox(hwnd, "Could not load large icon!", "Error", MB_OK | MB_ICONERROR);
 hIconSm = LoadImage(NULL, "mg/MSN.ICO", IMAGE_ICON, 16, 16, LR_LOADFROMFILE);
 if(hIconSm)
 SendMessage(hwnd, WM_SETICON, ICON_SMALL, (LPARAM)hIconSm);
 else
 MessageBox(hwnd, "Could not load small icon!", "Error", MB_OK | MB_ICONERROR);
}

