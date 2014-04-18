/* 
 * File:   CFishNemo.cpp
 * Author: Neha Gupta
 * 
 * Created on September 12, 2013, 11:16 AM
 */

#include "CFishNemo.h"
#include "CAquarium.h"
#include <string>
using namespace std;

//! Fish filename 
const wstring FishNemoImageName(L"nemo.png");

/*! Constructor
 */
CFishNemo::CFishNemo(CAquarium *aquarium) : CFish(aquarium, FishNemoImageName)
{   
    SetInit(30, 60);
    SetItemType(L"CFishNemo");
}

/*!Copy Constructor - makes deep copy*/
CFishNemo::CFishNemo(const CFishNemo &original) : CFish(original)
{
    
}

/*! Destructor
 */
CFishNemo::~CFishNemo()
{
}

/*! Create an XML node for this item type
 *
 * Create the XML node using the base class version of 
 * this function and add information to it specific to this
 * derived class. 
 * 
 * \returns The newly created node
 */
wxXmlNode *CFishNemo::XmlSave()
{
    // Use the version in the base class to create the node
    // and include common information
    wxXmlNode *node = CFish::XmlSave();
    
    node->AddAttribute(L"type", L"Nemo");
    return node;
}
/*! \brief Clone of this object
 * returns an allocated copy of this object
 */
CItem *CFishNemo::Clone() const
{ 
    //CFishBeta *newFish = new CFishBeta();
    //newFish->SetLocation(GetX(), GetY());
    //return newFish;
    return new CFishNemo(*this);
}

                