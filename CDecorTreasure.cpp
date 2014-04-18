/* 
 * File:   CDecorTreasure.cpp
 * Author: Neha Gupta
 * 
 * Created on September 12, 2013, 2:25 PM
 */

#include "CDecorTreasure.h"
#include "CAquarium.h"
#include <string>

//! Image filename 
const wstring DecorTreasureImageName(L"treasure-chest.png");

/*! Constructor
 */
CDecorTreasure::CDecorTreasure(CAquarium *aquarium) : CItem(aquarium, DecorTreasureImageName)
{   
        SetItemType(L"CDecorTreasure");
}

/*!Copy Constructor - makes deep copy*/
CDecorTreasure::CDecorTreasure(const CDecorTreasure &original) : CItem(original)
{
    
}

/*!Destructor
 */
CDecorTreasure::~CDecorTreasure()
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
wxXmlNode *CDecorTreasure::XmlSave()
{
    // Use the version in the base class to create the node
    // and include common information
    wxXmlNode *node = CItem::XmlSave();
    
    node->AddAttribute(L"type", L"treasure-chest");
    return node;
}
/*! Calls the copy constructor so that a copy of an object of this type can
 *  be made
 * \returns A newly created CDecorTreasure
 */
CItem *CDecorTreasure::Clone() const
{ 
 
    return new CDecorTreasure(*this);
}