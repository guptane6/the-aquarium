/* 
 * File:   CAquarium.h
 * Author: Neha Gupta
 *
 * Created on September 10, 2013, 1:58 PM
 */

#ifndef CAQUARIUM_H
#define	CAQUARIUM_H

#include <map>
#include <list>
#include <wx/wx.h>
#include <wx/xml/xml.h>
#include <sstream>
#include "CItem.h"
using namespace std;
class CAquarium
{
public:
    CAquarium();
    
    virtual ~CAquarium();
    void OnDraw(wxDC &dc);
    wxImage *GetCachedImage(const std::wstring name);
    void AddItem(CItem* item);
    CItem *HitTest(int x, int y);
    void MoveBack(CItem* item);
    bool IsOverTrashcan(int x, int y); 
    bool AddTrashCan();
    int CountBetas();
    void RemoveItem(CItem* item);
    void Save(const std::wstring &filename);
    void Load(const std::wstring &filename);
    void Clear();
    void Update(double elapsed);
    
    //! \brief Get the width of the aquarium
    //! \returns Aquarium width
    int GetWidth() const {return mBackground.GetWidth();}
   
    //! \brief Get the height of the aquarium
    //! \returns Aquarium height
    int GetHeight() const {return mBackground.GetHeight();}
    
 private:
     CAquarium(const CAquarium& orig);
     wxBitmap mBackground;            //!< Background image to useuse
     wxBitmap mTrashcan;                //!< Trash can image to 
     
  //! The image cache
    std::map<std::wstring, wxImage> mImageCache;
    //! All of the items that populate our aquarium
    std::list<CItem *> mItems;  //!< List of all items currently in aquarium
    bool mTrashCanActive;       //!< If true, then it is visible and things can
                                // be put inside it
    
    
};

#endif	/* CAQUARIUM_H */

