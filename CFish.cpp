/* 
 * File:   CFish.cpp
 * Author: Neha Gupta
 * 
 * Created on September 18, 2013, 10:27 AM
 */

#include "CFish.h"



/*! Constructor
 * \param aquarium The aquarium we are in
 * \param filename Filename for the image we use
 */
CFish::CFish(CAquarium *aquarium, const std::wstring &filename) :
        CItem(aquarium, filename) 
{
    //mSpeedX = ((double)rand() / RAND_MAX) * MaxSpeedX;
    //mSpeedY = ((double)rand() / RAND_MAX) * MaxSpeedY;
    mSpeedX = 0;
    mSpeedY = 0;
}

/*! Copy Constructor = assuming deep copy
 \param beta the beta fish we are copying*/
CFish::CFish(const CFish &original) : CItem(original)
{
    mSpeedX = original.mSpeedX;
    mSpeedY = original.mSpeedY;
}

/*! Destructor*/
CFish::~CFish()
{
}

/*! \brief Handle updates in time of our fish
 * 
 * This is called before we draw and allows us to 
 * move our fish. We add our speed times the amount
 * of time that has elapsed.
 * \param elapsed Time elapsed since the class call
 */
void CFish::Update(double elapsed) 
{
    SetLocation(GetX() + mSpeedX * elapsed, 
                GetY() + mSpeedY * elapsed);
    
    if(mSpeedX > 0 && GetX() >= (GetAquarium()->GetWidth()-50-GetWidth()/2))
    {
        mSpeedX = -mSpeedX;
        Mirror(mSpeedX < 0);
    }
    if (mSpeedX < 0 && GetX() <= (GetWidth()/2 + 50))
    {
        mSpeedX = -mSpeedX;
        Mirror(mSpeedX < 0);
    }
    
    if(mSpeedY > 0 && GetY() >= (GetAquarium()->GetHeight()-50-GetHeight()/2))
    {
        mSpeedY = -mSpeedY;
        //Mirror(mSpeedY < 0);
        int x = GetAquarium()->GetHeight();
        int y = GetHeight();
        int n = GetY();
        int z = 0;
    }
    
    if (mSpeedY < 0 && GetY() <= (GetHeight()/2 + 50))
    {
        mSpeedY = -mSpeedY;
        //Mirror(mSpeedY < 0);
    }
    
}
/*! Create an XML node for this item type
 *
 * Create the XML node using the base class version of 
 * this function and add information to it specific to this
 * derived class. 
 * 
 * \returns The newly created node
 */
wxXmlNode *CFish::XmlSave()
{
    // Use the version in the base class to create the node
    // and include common information
    wxXmlNode *node = CItem::XmlSave();

    node->AddAttribute(L"SpeedX", wxString::Format(L"%f", (double)mSpeedX));
    node->AddAttribute(L"SpeedY", wxString::Format(L"%f", (double)mSpeedY));
    return node;
}
/*!  \brief Load the attributes for an item node. 
 *
 * This is the  base class version that load the attributes 
 * common to all items. Override this to load custom attributes
 * for specific items.
 * 
 * \param node The Xml node we are loading the item from
 */
void CFish::XmlLoad(wxXmlNode *node)
{
    CItem::XmlLoad(node);
    
    mSpeedX = wcstol(node->GetAttribute(L"SpeedX", L"0"), NULL, 10);
    mSpeedY = wcstol(node->GetAttribute(L"SpeedY", L"100"), NULL, 10);
   
}
/*! \brief Sets the initial speeds for a fish.
 * Is used to set
 * custom speeds for each fish type
 * \param the integer min/max bounds
 */
void CFish::SetInit(int bound1, int bound2)
{
    mSpeedX = bound1 + ((double)rand() / RAND_MAX) * (bound2- bound1);
    mSpeedY = bound1 + ((double)rand() / RAND_MAX) * (bound2- bound1);
    //mSpeedX = ((double)rand() / RAND_MAX) * bound1;
    //mSpeedY = ((double)rand() / RAND_MAX) * bound2;
}
