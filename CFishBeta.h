/* 
 * File:   CFishBeta.h
 * Author: Neha Gupta
 *
 * Created on September 11, 2013, 7:58 PM
 */

#ifndef CFISHBETA_H
#define	CFISHBETA_H
#include "CItem.h"
#include "CFish.h"

class CFishBeta : public CFish
{
public:
    CFishBeta(CAquarium *aquarium);
    
    virtual ~CFishBeta();
   

    virtual wxXmlNode* XmlSave();
    
    virtual CItem* Clone() const;
    
    //! Copy constructor 
    CFishBeta(const CFishBeta &);
    
private:
    //! Default constructor (disabled)
    CFishBeta();

    
    
      

};

#endif	/* CFISHBETA_H */

