/*****************************************************************************
IsoHex2_1.cpp
Ernest S. Pazera
12MAY2000
Start a WIN32 Application Workspace, add in this file
No other libs are required
*****************************************************************************/
#define TRACEFILENAME "IsoHex3_1.trc"

// turn TRACING on.
#define TRACING 1
#include <fstrTracer.h>


//////////////////////////////////////////////////////////////////////////////
//INCLUDES
//////////////////////////////////////////////////////////////////////////////
#define WIN32_LEAN_AND_MEAN  

#include <windows.h> 
#include <STRSTREA.H>

#include <managedc.h>
#include <gdi_utils.h>

//////////////////////////////////////////////////////////////////////////////
//DEFINES
//////////////////////////////////////////////////////////////////////////////
//name for our window class
#define WINDOWCLASS "ISOHEX3"
//title of the application
#define WINDOWTITLE "IsoHex 3-1"

//////////////////////////////////////////////////////////////////////////////
//PROTOTYPES
//////////////////////////////////////////////////////////////////////////////
bool Prog_Init();//game data initalizer
void Prog_Loop();//main game loop
void Prog_Done();//game clean up

//////////////////////////////////////////////////////////////////////////////
//GLOBALS
//////////////////////////////////////////////////////////////////////////////
HINSTANCE hInstMain=NULL;//main application handle
HWND hWndMain=NULL;//handle to our main window

#define FONTNAME "Cour.ttf"
HFONT hfntNew = NULL;
HFONT hfntOld = NULL;
HPEN  hpenNew = NULL;
HPEN  hpenOld = NULL;

const unsigned int	 windowHorizontalSize = 800;
const unsigned int   windowVerticalSize = 600;
const short          MAX_BUFFER_SZ = 1000;
char                 cBuffer[MAX_BUFFER_SZ];
short                cBufferOfst = 0;


//////////////////////////////////////////////////////////////////////////////
//WINDOWPROC
//////////////////////////////////////////////////////////////////////////////
LRESULT CALLBACK TheWindowProc(HWND hwnd,UINT uMsg,WPARAM wParam,LPARAM lParam)
{
   //which message did we get?
   switch(uMsg)
   {
      case WM_CHAR:
         {
            TRACE("in WM_CHAR");
            if (     (     (wParam >='a')			//woohoo!
                        && (wParam <='z') )
                  || (     (wParam >='A')
                        && (wParam <='Z') )
                  || (     (wParam >='0')
                        && (wParam <='9') )
                        
               )
            { 
               TRACE("found a valid character");

               if (cBufferOfst + 2 < MAX_BUFFER_SZ)
               {
                  cBuffer[cBufferOfst] = wParam;
                  cBufferOfst++;
                  cBuffer[cBufferOfst] = 0;
                  
                  ostrstream BufferContents;
                  BufferContents << "cBuffer>>" << cBuffer << "<<" << ends;
                  TRACE(BufferContents.str());
                  BufferContents.rdbuf()->freeze(0);
                       
                  // invalidate the entire window to 
                  // force a redraw                                      
                  InvalidateRect(0,0,1);
               }
            }
            return(0);
         }
         break;
      case WM_DESTROY://the window is being destroyed
         {
      
            //tell the application we are quitting
            PostQuitMessage(0);
      
            //handled message, so return 0
            return(0);
      
         }
         break;
      case WM_PAINT://the window needs repainting
         {
            //a variable needed for painting information
            PAINTSTRUCT ps;
            
            TRACE("PAINT CALLED");            
            //start painting
            HDC hdc=BeginPaint(hwnd,&ps);
      
            ShowProgInfo(  hdc,
                           WINDOWTITLE,
                           windowHorizontalSize,
                           windowVerticalSize);
      
            TextOut(hdc,0,60,cBuffer,strlen(cBuffer));
      
                                    
            /////////////////////////////
            //painting code would go here
            /////////////////////////////
            
            //end painting
            EndPaint(hwnd,&ps);
                     
            //handled message, so return 0
            return(0);
         }
         break;
      
//   case WM_LBUTTONDOWN :
//      {
//         // move to starting point for drawing..
//         int x = LOWORD(lParam);
//         int y = HIWORD(lParam);
//         {
//            ManageDC aDC(hWndMain);
//            
//            // retrieve it to save time..
//            HDC hdc = aDC.borrowedDC();
//            MoveToEx(hdc,x,y,NULL);
//         }
//         return(0);
//      }
//      break;
//   case WM_MOUSEMOVE :
//      {
//         // draw while mouse button is down..
//         if (wParam & MK_LBUTTON)
//         {
//            int x = LOWORD(lParam);
//            int y = HIWORD(lParam);
//            {
//               ManageDC aDC(hWndMain);
//               
//               // retrieve it to save time..
//               HDC hdc = aDC.borrowedDC();
//               LineTo(hdc,x,y);
//            }
//         }
//         return(0);
//      }
//      break;
   }

   //pass along any other message to default message handler
   return(DefWindowProc(hwnd,uMsg,wParam,lParam));
}


//////////////////////////////////////////////////////////////////////////////
//WINMAIN
//////////////////////////////////////////////////////////////////////////////
int WINAPI WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance,LPSTR lpCmdLine,int nShowCmd)
{
#ifdef TRACING
   startTracing(TRACEFILENAME);
#endif

   cBuffer[cBufferOfst] = 0;

   TRACE ("Start of Session___");
   
   //assign instance to global variable
   hInstMain=hInstance;

   //create window class
   WNDCLASSEX wcx;

   //set the size of the structure
   wcx.cbSize=sizeof(WNDCLASSEX);

   //class style
   wcx.style=CS_OWNDC | CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS;

   //window procedure
   wcx.lpfnWndProc=TheWindowProc;

   //class extra
   wcx.cbClsExtra=0;

   //window extra
   wcx.cbWndExtra=0;

   //application handle
   wcx.hInstance=hInstMain;

   //icon
   wcx.hIcon=LoadIcon(NULL,IDI_APPLICATION);

   //cursor
   wcx.hCursor=LoadCursor(NULL,IDC_ARROW);

   //background color
   wcx.hbrBackground=(HBRUSH)GetStockObject(BLACK_BRUSH);

   //menu
   wcx.lpszMenuName=NULL;

   //class name
   wcx.lpszClassName=WINDOWCLASS;

   //small icon
   wcx.hIconSm=NULL;

   //register the window class, return 0 if not successful
   if(!RegisterClassEx(&wcx)) return(0);

   //create main window
   hWndMain=CreateWindowEx(0,
                           WINDOWCLASS,
                           WINDOWTITLE, 
                           WS_BORDER | WS_SYSMENU | WS_VISIBLE,
                           0,
                           0,
                           windowHorizontalSize,
                           windowVerticalSize,
                           NULL,
                           NULL,
                           hInstMain,
                           NULL);

   //error check
   if(!hWndMain)
   {
      return(0);
   }

   //if program initialization failed, then return with 0
   if(!Prog_Init()) 
   {
      return(0);
   }

   //message structure
   MSG msg;
   TRACE("start message pump..");

   //message pump
   for(;;)   
   {
      //look for a message
      if(PeekMessage(&msg,NULL,0,0,PM_REMOVE))
      {
         //there is a message

         //check that we arent quitting
         if(msg.message==WM_QUIT) 
         {
            break;
         }
         
         //translate message
         TranslateMessage(&msg);

         //dispatch message
         DispatchMessage(&msg);
      }

      //run main game loop
      Prog_Loop();
   }
   
   //clean up program data
   Prog_Done();

#ifdef TRACING
   stopTracing();
#endif

   //return the wparam from the WM_QUIT message
   return(msg.wParam);
}

//////////////////////////////////////////////////////////////////////////////
//INITIALIZATION
//////////////////////////////////////////////////////////////////////////////
bool Prog_Init()
{
   AddFontResource(FONTNAME);
   
   hfntNew = CreateFont(-40,0,0,0,0,0,0,0,0,0,0,0,0,"cour");
   hpenNew = CreatePen(PS_SOLID,0,RGB(255,255,255));
   
   
   //add the font to the DC
   {
      ManageDC aDC(hWndMain);
      
      // retrieve it to save time..
      HDC hdc = aDC.borrowedDC();
      
      // put new font into DC, save off old..
      hfntOld = (HFONT) SelectObject(hdc,hfntNew);
      hpenOld = (HPEN) SelectObject(hdc,hpenNew);
      
      SetBkMode(hdc,TRANSPARENT);
      SetTextColor(hdc,RGB(255,255,255)); // white for now
      ShowProgInfo(  hdc,
                     WINDOWTITLE,
                     windowHorizontalSize,
                     windowVerticalSize);
   }

   //rectangle into which we will place the desired client RECT
   RECT rc;
   SetRect(&rc,0,0,windowHorizontalSize,windowVerticalSize);

   //get the window rect based on our style and extended style
   AdjustWindowRectEx(&rc,WS_BORDER | WS_SYSMENU | WS_CAPTION | WS_VISIBLE,FALSE,0);

   //use movewindow to resize the window
   MoveWindow(hWndMain,0,0,rc.right-rc.left,rc.bottom-rc.top,TRUE);
   
   return(true);//return success
}

//////////////////////////////////////////////////////////////////////////////
//CLEANUP
//////////////////////////////////////////////////////////////////////////////
void Prog_Done()
{

   // sub block for managing a Device Context
   {
      ManageDC aDC(hWndMain);
      HDC hdc = aDC.borrowedDC();

      // slap the old on back into the DC
      SelectObject(hdc,hfntOld);
      SelectObject(hdc,hpenOld);
      
      // make sure we clean up after ourselves..
      DeleteObject(hfntNew);
      DeleteObject(hpenNew);
      
      RemoveFontResource(FONTNAME);
   }
   //////////////////////////
   //clean up code goes here
   //////////////////////////
}

//////////////////////////////////////////////////////////////////////////////
//MAIN GAME LOOP
//////////////////////////////////////////////////////////////////////////////
void Prog_Loop()
{
   ///////////////////////////
   //main game logic goes here
   ///////////////////////////
}
