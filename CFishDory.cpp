/* 
 * File:   CFishDory.cpp
 * Author: Neha Gupta
 * 
 * Created on September 12, 2013, 2:25 PM
 */

#include "CFishDory.h"
#include "CAquarium.h"
#include <string>

//! Fish filename 
const wstring FishDoryImageName(L"dory.png");

/*! Constructor
 */
CFishDory::CFishDory(CAquarium *aquarium) : CFish(aquarium, FishDoryImageName)
{   
    SetInit(3, 20);
    SetItemType(L"CFishDory");
}

/*!Copy Constructor - makes deep copy*/
CFishDory::CFishDory(const CFishDory &original) : CFish(original)
{

}

/*!Destructor
 */
CFishDory::~CFishDory()
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
wxXmlNode *CFishDory::XmlSave()
{
    // Use the version in the base class to create the node
    // and include common information
    wxXmlNode *node = CFish::XmlSave();
    
    node->AddAttribute(L"type", L"Dory");
    return node;
}
/*! \brief Clone of this object
 * returns an allocated copy of this object
 */
CItem *CFishDory::Clone() const
{ 

    return new CFishDory(*this);
}
