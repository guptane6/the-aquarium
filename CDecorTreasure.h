/* 
 * File:   CDecorTreasure.h
 * Author: Neha Gupta
 *
 * Created on September 16, 2013, 5:44 PM
 */

#ifndef CDECORTREASURE_H
#define	CDECORTREASURE_H
#include "CItem.h"
class CDecorTreasure : public CItem
{
public:
    CDecorTreasure(CAquarium *aquarium);
    virtual ~CDecorTreasure();
    virtual wxXmlNode* XmlSave();
    CDecorTreasure(const CDecorTreasure&);
    virtual CItem* Clone() const;
private:
    //Default constructor (disabled)
    CDecorTreasure();
    

};

#endif	/* CFISHDORY_H */

