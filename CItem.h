/* 
 * File:   CItem.h
 * Author: Neha Gupta
 *
 * Created on September 10, 2013, 3:14 PM
 */

#ifndef CITEM_H
#define	CITEM_H
#include <wx/wx.h>
#include <wx/xml/xml.h>
#include <sstream>
class CAquarium;
class CItem
{

public:
    
    virtual ~CItem();
    
        //! Get the x location of the item
    //! \returns X location
    double GetX() const {return mX;}
    
    //! Get the y location of the item
    //! \returns Y location
    double GetY() const {return mY;}
    
    //! Set the item location
    //! \param x X location
    //! \param y Y location
    void SetLocation(double x, double y) {mX = x; mY = y;}
    
    //! Draw this item
    //! \param dc Device context to draw on
    void Draw(wxDC &dc);
    
        //! Test to see if we clicked on this item
    //! \param x X location
    //! \param y Y location
    //! \returns true if we clicked on the item
    bool HitTest(int x, int y);
    
    
    virtual wxXmlNode* XmlSave();
    
    virtual void XmlLoad(wxXmlNode *node);
    
       //! \brief Handle updates for animation
    //! \param elapsed The time since the last update
    virtual void Update(double elapsed) {};
    
    //! \brief Get the aquarium this item is in
    //! \returns Aquarium pointer
    CAquarium *GetAquarium() {return mAquarium;}
    
    void Mirror(bool mirror);
    
        //! \brief Get the width of the aquarium
    //! \returns Aquarium width
    int GetWidth() const {return mItemBitmap->GetWidth();}
   
    //! \brief Get the height of the aquarium
    //! \returns Aquarium height
    int GetHeight() const {return mItemBitmap->GetHeight();}
    
    //! Set the type of item that this is
    //! \param classname The name of the class
    void SetItemType(std::wstring classname) {mItemType = classname;}

    //! Get the name of the item type
    //! \returns the class name
    std::wstring GetItemType() const {return mItemType;}
    
    virtual CItem* Clone() const = 0;
    
protected:
    CItem(CAquarium *aquarium, const std::wstring &filename);
    
    //! Copy constructor
    CItem(const CItem &);
    
private:
    
        //! Default constructor (disabled)
    CItem();

    
    
        //! The aquarium this item is contained in
    CAquarium   *mAquarium;
    
    // Item location in the aquarium
    double     mX;         //!< X location for the center of the item
    double     mY;         //!< Y location for the center of the item
    
    wxImage *mItemImage;        //!< Pointer to the image of the fish
    wxBitmap *mItemBitmap;      //!< Pointer to a bitmap for the fish
    
    wxImage *mItemImageOrig;    //!< Pointer to the original item image
    
    std::wstring mItemType;     //!<String with name of child class

};

#endif	/* CITEM_H */

