/* 
 * File:   CFishNemo.h
 * Author: Neha Gupta
 *
 * Created on September 12, 2013, 11:16 AM
 */

#ifndef CFISHNEMO_H
#define	CFISHNEMO_H
#include "CItem.h"
#include "CFish.h"

class CFishNemo : public CFish
{
public:
    CFishNemo(CAquarium *aquarium);
    virtual ~CFishNemo();
    virtual wxXmlNode* XmlSave();
    CFishNemo(const CFishNemo& );
    virtual CItem* Clone() const;
private:
    CFishNemo(); //!default ctor - private
    
    
};

#endif	/* CFISHNEMO_H */

