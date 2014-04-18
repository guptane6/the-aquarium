/* 
 * File:   CApp.cpp
 * Author: Neha Gupta
 * 
 * Created on September 9, 2013, 10:18 PM
 */

#include "CApp.h"
#include "CFrame.h"
IMPLEMENT_APP(CApp)
CApp::CApp()
{
    srand(time(NULL)); //invoke randomness to be used for fish speeds later
}

CApp::CApp(const CApp& orig)
{
}

CApp::~CApp()
{
}

/*! Application initialization function
 *
 * This function is called once when the
 * application is started. It creates the main frame for
 * the program and displays it.
 * \returns true
 */
bool CApp::OnInit()
{
    wxInitAllImageHandlers();
    CFrame *frame = new CFrame();
    frame->Show(true);
    SetTopWindow(frame);
    return true;
}
