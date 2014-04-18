/* 
 * File:   CFishBeta.cpp
 * Author: Neha Gupta
 * 
 * Created on September 11, 2013, 7:58 PM
 */

#include "CFishBeta.h"
#include "CAquarium.h"
#include <string>
using namespace std;

//! Fish filename 
const wstring FishBetaImageName(L"beta.png");


/*! Constructor
 */
CFishBeta::CFishBeta(CAquarium *aquarium) : CFish(aquarium, FishBetaImageName)
{   
    SetInit(10, 50);
    SetItemType(L"CFishBeta");
    
}
/*!Destructor
 */
CFishBeta::~CFishBeta()
{
}

/*!Copy Constructor - makes deep copy*/
CFishBeta::CFishBeta(const CFishBeta &original) : CFish(original)
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
wxXmlNode *CFishBeta::XmlSave()
{
    // Use the version in the base class to create the node
    // and include common information
    wxXmlNode *node = CFish::XmlSave();
    
    node->AddAttribute(L"type", L"beta");
    return node;
}

/*! \brief Clone of this object
 * returns an allocated copy of this object
 */
CItem *CFishBeta::Clone() const
{ 
    return new CFishBeta(*this);
}





