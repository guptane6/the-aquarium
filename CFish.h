/* 
 * File:   CFish.h
 * Author: student
 *
 * Created on September 18, 2013, 10:27 AM
 */

#ifndef CFISH_H
#define	CFISH_H
#include "CItem.h"
#include "CAquarium.h"

/*! \brief Base class for a fish
 * This applies to all of the fish, but not the decor
 * items in the aquarium.
 */
class CFish : public CItem
{
public:
    virtual ~CFish();
    virtual void Update(double elapsed);
    
    //! Get the x speed of the item
    //! \returns X speed
    double GetSpeedX() const {return mSpeedX;}
    
    //! Get the y speed of the item
    //! \returns Y speed
     double GetSpeedY() const {return mSpeedY;}
     
     virtual wxXmlNode* XmlSave();
     
     virtual void XmlLoad(wxXmlNode *node);
     
     void SetInit(int bound1, int bound2);
    
    //virtual CItem* Clone() const = 0;
    
protected:
    CFish(CAquarium *aquarium, const std::wstring &filename);
    
    //! Copy constructor
    CFish(const CFish &); 
    
  
private:
    
      //! Default constructor (disabled)
    CFish();
    
    //! Fish speed in the X direction
    double mSpeedX;
    
    //! Fish speed in the Y direction
    double mSpeedY;
};

#endif	/* CFISH_H */

