/* 
 * File:   CApp.h
 * Author: Neha R Gupta
 *
 * Created on September 9, 2013, 10:18 PM
 */

#ifndef CAPP_H
#define	CAPP_H
#include <wx/wx.h>
//! Application main class
class CApp : public wxApp
{
public:
    CApp();
    CApp(const CApp &orig);
    virtual ~CApp();

    virtual bool OnInit();
};

#endif	/* CAPP_H */

