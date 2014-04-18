/* 
 * File:   CFishDory.h
 * Author: Neha Gupta
 *
 * Created on September 12, 2013, 2:25 PM
 */

#ifndef CFISHDORY_H
#define	CFISHDORY_H
#include "CItem.h"
#include "CFish.h"
class CFishDory : public CFish
{
public:
    CFishDory(CAquarium *aquarium);
    virtual ~CFishDory();

    virtual wxXmlNode* XmlSave();
    
    CFishDory(const CFishDory&);
    virtual CItem* Clone() const;
private:
    //Default ctor - disabled
    CFishDory(); 
    

};

#endif	/* CFISHDORY_H */

