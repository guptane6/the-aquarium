/* 
 * File:   CFrame.cpp
 * Author: Neha Gupta
 * 
 * Created on September 9, 2013, 10:23 PM
 */

#include "CFrame.h"
#include <sstream>
BEGIN_EVENT_TABLE(CFrame, wxFrame)
        EVT_MENU(ID_Exit, CFrame::OnExit)
        EVT_MENU(ID_About, CFrame::OnAbout)
        EVT_MENU(ID_Trash, CFrame::OnTrash)
        EVT_MENU(ID_AddFishBeta, CFrame::OnAddFishBeta)
        EVT_MENU(ID_AddFishNemo, CFrame::OnAddFishNemo)
        EVT_MENU(ID_AddFishDory, CFrame::OnAddFishDory)
        EVT_MENU(ID_NumBeta, CFrame::OnNumBeta)
        EVT_MENU(ID_AddTreasure, CFrame::OnAddTreasure)
        EVT_MENU(ID_FileSaveAs, CFrame::OnFileSaveAs)
        EVT_MENU(ID_FileOpen, CFrame::OnFileOpen)
        EVT_TIMER(ID_Timer, CFrame::OnTimer)
        EVT_PAINT(CFrame::OnPaint)
        EVT_LEFT_DOWN(CFrame::OnLeftButtonDown)
        EVT_MOTION(CFrame::OnMouseMove)
        EVT_LEFT_UP(CFrame::OnMouseMove)
END_EVENT_TABLE()
        
using namespace std;
const int FrameDuration = 30;  //! Milliseconds
/*! \brief Default constructor
 * 
 * Creates the frame and sets its initial size and name
 */
CFrame::CFrame() : wxFrame( NULL, -1, L"wxWidgets Application", 
                            wxPoint(20, 20), wxSize(1024,800) ),
                            mTimer(this, ID_Timer)
{
    mGrabbedItem = NULL;
    
         //
     // File menu
     //

     wxMenu *menuFile = new wxMenu;
     menuFile->Append(ID_About, L"&About");
     menuFile->AppendSeparator();
     wxMenuItem *exitItem = menuFile->Append( ID_Exit, L"E&xit" );
     exitItem->SetHelp(L"Exit the program");
     menuFile->AppendSeparator();
     menuFile->Append(ID_Trash, L"&Trash Can");
     menuFile->AppendSeparator();
     menuFile->Append(ID_NumBeta, L"&Count of Beta Fish");
     menuFile->Append(ID_FileSaveAs, L"Save As");
     menuFile->Append(ID_FileOpen, L"Open");

     //
     // Fish menu
     //
     wxMenu *menuFish = new wxMenu;
     menuFish->Append(ID_AddFishBeta, L"&Beta");
     menuFish->Append(ID_AddFishNemo, L"&Nemo");
     menuFish->Append(ID_AddFishDory, L"&Dory");
     
     //
     // Decor menu
     //
     wxMenu *menuDecor = new wxMenu;
     menuDecor->Append(ID_AddTreasure, L"&Treasure Chest");
     
     //
     // Menu Bar
     //

     wxMenuBar *menuBar = new wxMenuBar;
     menuBar->Append( menuFile, L"&File");
     menuBar->Append( menuFish, L"&Add Fish");
     menuBar->Append( menuDecor, L"&Add Decor");
     
     SetMenuBar( menuBar );
     
     CreateStatusBar();
     SetStatusText(L"Status");
     SetBackgroundColour(wxColour(0, 0, 0));
     
     mCurrentTime = wxGetLocalTimeMillis().GetValue();
      mTimer.Start(FrameDuration);
      
    
}

CFrame::CFrame(const CFrame& orig)
{
}

CFrame::~CFrame()
{
}

/*! \brief This function is called when an exit menu item is selected.
 *
 * It closes the main window, which ends the program.
 * \param event An object that describes the event.
 */
void CFrame::OnExit(wxCommandEvent& event)
{
    Close(TRUE);
    mTimer.Stop();
}

/*!  File/About menu option handler
 * \param event  An object that describes the event.
 */ 
void CFrame::OnAbout(wxCommandEvent& event)
{
    wxMessageBox(L"This is a simple wxWidgets application",
                 L"About Step 2",
                  wxOK | wxICON_INFORMATION, this);
}
/*! Add Trash menu option handler
 * \param event  An object that describes the event.
 */ 
void CFrame::OnTrash(wxCommandEvent& event)
{
    mAquarium.AddTrashCan();
    Refresh();
    
}

/*! \brief Function called whenever we need to redraw the window
 *
 * This function is called in response to a drawing message
 * whenever we need to redraw the window on the screen.
 * It is responsible for painting the window.
 * \param event An event associated with the message.
 */
void CFrame::OnPaint(wxPaintEvent& event)
{
    // Handle updates
    long long newTime = wxGetLocalTimeMillis().GetValue();
    double elapsed = (newTime - mCurrentTime) * 0.001;
    mCurrentTime = newTime;
   
    mAquarium.Update(elapsed);
    
    // Create a device context
    wxPaintDC dc(this);

    mAquarium.OnDraw(dc);

    dc.SetPen(wxNullPen);
    dc.SetBrush(wxNullBrush);
    dc.SetFont(wxNullFont);
}

/*! Add Fish/Beta menu option handler
 * \param event  An object that describes the event.
 */ 
void CFrame::OnAddFishBeta(wxCommandEvent& event) 
{
    mAquarium.AddItem(new CFishBeta(&mAquarium));
    Refresh();
}

/*! Add Fish/Nemo menu option handler
 * \param event  An object that describes the event.
 */
void CFrame::OnAddFishNemo(wxCommandEvent& event) 
{
    mAquarium.AddItem(new CFishNemo(&mAquarium));
    Refresh();
}

/*! Add Fish/Dory menu option handler
 * \param event  An object that describes the event.
 */ 
void CFrame::OnAddFishDory(wxCommandEvent& event) 
{
    mAquarium.AddItem(new CFishDory(&mAquarium));
    Refresh(); 
}
/*! Add Treasure menu option handler
 * \param event  An object that describes the event.
 */ 

void CFrame::OnAddTreasure(wxCommandEvent& event) 
{
    mAquarium.AddItem(new CDecorTreasure(&mAquarium));
    Refresh(); 
}
/*! \brief Displays a message that tells a user how many beta fish there are
 */
void CFrame::OnNumBeta(wxCommandEvent& event) 
{
    
    wstringstream str;
    int cnt = mAquarium.CountBetas();
    str << L"Number of beta fish = " << cnt << ends;

    wxMessageBox(str.str().c_str(),
                 L"Astounding Information",
                  wxOK | wxICON_INFORMATION, this);
    Refresh();
}

/*! \brief Left mouse button handler
 *
 * This function is called when the left mouse button is clicked
 * on the window.
 * \param event An event describing the mouse click
 */

void CFrame::OnLeftButtonDown(wxMouseEvent& event)
{
    bool ctrl = event.m_controlDown;			// true if control key is pressed
    //if (ctrl == false)
    //{
        mGrabbedItem = mAquarium.HitTest(event.m_x, event.m_y);
        if(mGrabbedItem != NULL)
        {
            if (ctrl == true)
            {
                CItem *clone = mGrabbedItem->Clone();
                mAquarium.AddItem(clone);
                
            }
                //We have selected an item
                //Move it to the end of the list of items
                //you'll need code here to do that...
                mAquarium.MoveBack(mGrabbedItem);
                Refresh();

        }

}

/*! \brief Mouse move handler
 *
 * This function is called whenever the mouse is 
 * moved over the window.
 * \param event The mouse event
 */
void CFrame::OnMouseMove(wxMouseEvent& event)
{
    // See if an item is currently being moved by the mouse
    if(mGrabbedItem != NULL)
    { 
        // If an item is being moved, we only continue to 
        // move it while the left button is down.
        if(event.m_leftDown)
        {
            mGrabbedItem->SetLocation(event.m_x, event.m_y);
        }
    
        else
        {       
            // When the left button is released, we release the
            // item.
            //mGrabbedItem = NULL;
            
                if (mAquarium.IsOverTrashcan(mGrabbedItem->GetX(),mGrabbedItem->GetY()) == true)
                {
                mAquarium.RemoveItem(mGrabbedItem);
                }

        // Force the screen to redraw
        mGrabbedItem = NULL;
        
        } 
        Refresh();
    }
}
/*! OnFileSaveAs menu option handler
 * \param event  An object that describes the event.
 */ 
void CFrame::OnFileSaveAs(wxCommandEvent& event)
{
        wxFileDialog dlg(this, L"Save File", L"", L"", 
                     L"Aquarium Files (*.aqua)|*.aqua", 
                     wxFD_SAVE | wxFD_OVERWRITE_PROMPT);
    if(dlg.ShowModal() != wxID_OK)
        return;
        
    // Get the filename into a local string
    wstring filename = dlg.GetPath().wc_str();

    // If no suffix is supplied for the file, supply it here
    wstring suffix(L".aqua");
    if(!equal(suffix.rbegin(), suffix.rend(), filename.rbegin()))
    {
        filename += suffix;
    }
    
    mAquarium.Save(filename);
}
/*! OnFileOpen menu option handler
 * \param event  An object that describes the event.
 */ 
void CFrame::OnFileOpen(wxCommandEvent& event)
{
    wxFileDialog dlg(this, L"Open File", L"", L"", 
                     L"Aquarium Files (*.aqua)|*.aqua",
                     wxFD_OPEN | wxFD_FILE_MUST_EXIST);
    if(dlg.ShowModal() != wxID_OK)
        return;

    wstring filename = dlg.GetPath().wc_str();
    
    mAquarium.Load(filename);
    Refresh();
}

/*! \brief Timer handler function
 * 
 * This function is called on a regular basis to invalidate
 * the window, allowing for animation.
 * 
 * \param event The timer event
 */
void CFrame::OnTimer(wxTimerEvent& event)
{
    Refresh();
}
