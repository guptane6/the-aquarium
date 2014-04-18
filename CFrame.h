/* 
 * File:   CFrame.h
 * Author: Neha R Gupta
 * Created on September 9, 2013, 10:23 PM
 */

#ifndef CFRAME_H
#define	CFRAME_H
#include <wx/wx.h>
#include "CAquarium.h"
#include "CFishBeta.h"
#include "CFishNemo.h"
#include "CFishDory.h"
#include "CDecorTreasure.h"

//! Program main display frame
class CFrame : public wxFrame
{
public:
    CFrame();
    CFrame(const CFrame &orig);
    virtual ~CFrame();
    
    DECLARE_EVENT_TABLE()
            

    enum Ids {ID_Exit=1, ID_About, ID_Trash, 
        ID_AddFishBeta, ID_AddFishNemo, ID_AddFishDory,
        ID_NumBeta, ID_AddTreasure, ID_FileSaveAs, ID_FileOpen,
        ID_Timer};
    void OnExit(wxCommandEvent& event);
    void OnAbout(wxCommandEvent& event);
    void OnTrash(wxCommandEvent& event);
    void OnPaint(wxPaintEvent &event);
    void OnAddFishBeta(wxCommandEvent& event);
    void OnAddFishNemo(wxCommandEvent& event);
    void OnAddFishDory(wxCommandEvent& event);
    void OnAddTreasure(wxCommandEvent& event);
    void OnLeftButtonDown(wxMouseEvent &event);
    void OnMouseMove(wxMouseEvent &event);
    void OnNumBeta(wxCommandEvent& event);
    void OnFileSaveAs(wxCommandEvent& event);
    void OnFileOpen(wxCommandEvent& event);
    void OnTimer(wxTimerEvent& event);
 private:
    //! An object that describes our aquarium
    CAquarium  mAquarium;
    
    //! Any item we are currently dragging
    CItem     *mGrabbedItem;
    
    //! A timer for animation
    wxTimer mTimer;
    
    //! The current Unix time
    long long mCurrentTime;
};

#endif	/* CFRAME_H */

