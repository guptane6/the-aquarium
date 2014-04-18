/* 
 * File:   CAquarium.cpp
 * Author: Neha R Gupta
 * 
 * Created on September 10, 2013, 1:58 PM
 */

#include "CAquarium.h"
#include "CFishBeta.h"
#include "CFishNemo.h"
#include "CFishDory.h"
#include "CDecorTreasure.h"
#include <iostream>
using namespace std;

const wstring DirectoryContainingImages(L"images/");
const int TrashCanWidth = 51;
const int TrashCanHeight = 70;


/*! \brief Constructor */
CAquarium::CAquarium()
{
    if(!mBackground.LoadFile(L"images/background1.png", wxBITMAP_TYPE_PNG))
        wxMessageBox(L"Failed to open image background1.png");
    

    
    mTrashCanActive = false;
}
/*! \brief Destructor - removes all items in mItems list
 */
CAquarium::~CAquarium()
{
    CAquarium::Clear();
}

/*! \brief Draw the aquarium
 * \param dc The device context to draw onto
 */
void CAquarium::OnDraw(wxDC &dc)
{
     // Create a font
     wxFont font(12, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false);
     dc.SetFont(font);
     dc.SetTextForeground(wxColour(255, 255, 255));

     dc.DrawBitmap(mBackground, 0, 0, true);
     dc.DrawText(L"Under the Sea!", 2, 2);
     
     if (mItems.size() != 0)
     {
     
     for(list<CItem *>::iterator t=mItems.begin(); t!=mItems.end(); t++)
     {
         //cout << "Num items " << mItems.size() << endl;
         CItem *item = *t;
         item->Draw(dc);
         }
         
     }
     if (mTrashCanActive == true)
     {
         dc.DrawBitmap(mTrashcan,0,0);
     }
}

/*! \brief Get an image from the image cache
 *
 * Given a base name for an image file, determine if
 * we have already loaded it. If we have, return a pointer
 * to the wxBitmap object in the cache. If we have not
 * previously loaded it, load it into the cache and then
 * return a pointer to the image.
 * \param name The base name of the image file. We put images/ onto
 * the front of this because that is where the file is located.
 * \returns Pointer to cached image object or NULL if file not found.
 */
wxImage *CAquarium::GetCachedImage(const std::wstring name)
{
    // See if the name exists in the cache already.
    map<wstring, wxImage>::iterator i = mImageCache.find(name);
    if(i != mImageCache.end())
    {
        // If we got here, it does exist and i->second is a
        // reference to the bitmap object.
        return &i->second;
    }

    // We'll add the path to the name of the file here.
    wstring realname = DirectoryContainingImages + name;

    // Create a bitmap image and load the file into it.
    wxImage bitmap;
    if(!bitmap.LoadFile(realname.c_str()))
    {
         wstring msg = wstring(L"Unable to open image ") + realname;
         wxMessageBox(msg.c_str());
         return NULL;
    }

    // Add it to the cache and return it.
    mImageCache[name] = bitmap;
    return &mImageCache[name];
}

/*! \brief Add an item to the aquarium
 * 
 * This automatically centers the new item in the background image.
 * 
 * \param item New item to add
 */
void CAquarium::AddItem(CItem *item)
{
    item->SetLocation(mBackground.GetWidth()/2, mBackground.GetHeight()/2);
    mItems.push_back(item);
}

/*! \brief Test an x,y click location to see if it clicked
 * on some item in the aquarium.
 * \param x X location
 * \param y Y location
 * \returns Pointer item we clicked on or null if none.
 */
CItem *CAquarium::HitTest(int x, int y) 
{
    for(list<CItem *>::reverse_iterator i=mItems.rbegin(); 
            i != mItems.rend();  i++) 
    {
        if((*i)->HitTest(x, y)) 
        {
            return *i;
        }
    }
    return  NULL;
}
/*! \brief Given an item that has been grabbed and moved, move it to the end of 
 *  the list mItems.
 *  \param item the item that has been clicked.
 */
void CAquarium::MoveBack(CItem *item)
{   
    mItems.remove(item);
    mItems.push_back(item);
        //       
}
/*! \brief Given an item, checks it in relation to location of Trashcan to see
 * if it's over the trashcan.
 *  \param x and y locations of an item
 */
bool CAquarium::IsOverTrashcan(int x, int y) 
{
    if(!mTrashCanActive) 
    {
        return false;
    }
    
    return x < TrashCanWidth && y < TrashCanHeight;
}
/*! \brief Ensure that the mTrashCanActive boolean variable is changed each
 * time this function is called.
 */
bool CAquarium::AddTrashCan()
{
        if(!mTrashcan.LoadFile(L"images/trashcan.png", wxBITMAP_TYPE_PNG))
        wxMessageBox(L"Failed to open image trashcan.png");
        
    if (mTrashCanActive == false)
    { 
        mTrashCanActive = true;
        //dc.DrawBitmap(mTrashcan, 0, 0);
    }
    else
    {
        mTrashCanActive = false;
    }
}
/*! \brief Counts the number of beta fish in the aquarium
 * \returns an integer count
 */
int CAquarium::CountBetas()
{
    int num_beta = 0;
    for(list<CItem *>::reverse_iterator i=mItems.rbegin(); i != mItems.rend();  i++) 
        {
                if((*i)->GetItemType() == L"CFishBeta" ) 
                {
                    num_beta++; 
                }
        }   
    
    return num_beta;
}
/*! \brief Removes an item from mItems, the list of items in the aquarium
 * \param CItem is the item to remove
 */
void CAquarium::RemoveItem(CItem* item)
{
    mItems.remove(item);
    delete item;
}

/*! \brief Save the aquarium as a .aqua XML file.
 * 
 * Open an XML file and stream the aquarium data to it.
 * 
 * \param filename - The filename of the file to save the aquarium to
 */
void CAquarium::Save(const std::wstring &filename)
{
    //Create an empty XML Document
    wxXmlDocument xmlDoc;
    
        // Create a root node
    wxXmlNode *root = new wxXmlNode(wxXML_ELEMENT_NODE, L"aqua");
    xmlDoc.SetRoot(root);
    
        // This variable keeps track of the last child node we
    // added. There is not yet, so it is initially NULL.
    wxXmlNode *lastChild = NULL;

    // Iterate over all of the aquarium items so we can save each to the
    // XML document.
    for(list<CItem *>::const_iterator t=mItems.begin(); t!=mItems.end();  t++)
    {
        // And the tile to create a node for itself
        wxXmlNode *node = (*t)->XmlSave();

        // If we have a previous child, add this node after
        // the child.
        if(lastChild == NULL)
        {
            root->AddChild(node);
        }
        else
        {
            lastChild->SetNext(node);
        }

        lastChild = node;
    }
    
       // And save the file to disk
    xmlDoc.Save(filename.c_str());
}

/*! \brief Load the aquarium from a .aqua XML file.
 * 
 * Opens the XML file and reads the nodes, creating items as appropriate.
 * 
 * \param filename The filename of the file to load the aquarium from.
 */
void CAquarium::Load(const std::wstring &filename)
{
    wxXmlDocument xmlDoc;
    if(!xmlDoc.Load(filename.c_str()))
    {
        wstringstream str;
        str << L"Unable to open file " << filename << ends;
        wxMessageBox(str.str().c_str(),
                         L"Error",
                          wxOK | wxICON_ERROR);
        return;
    }

    // Clear our existing aquarium data
    Clear();
    
    wxXmlNode *root = xmlDoc.GetRoot();
    wxXmlNode *child = root->GetChildren();
    while(child != NULL)
    {
        // This is the item we will create
        CItem *item = NULL;

        // We have an item. What type?
        wxString type = child->GetAttribute(L"type", L"");
        if(type == L"beta")
        {
            item = new CFishBeta(this);
        }
        else if(type == L"treasure-chest")
        {
            item = new CDecorTreasure(this);
        }
        else if(type == L"Nemo")
        {
            item = new CFishNemo(this);
        }
        else if(type == L"Dory")
        {
            item = new CFishDory(this);
        }

        if(item != NULL)
        {
            item->XmlLoad(child);
            //if (type == CFishDory || type == CFishNemo || type == CFishBeta)
            //{
                
            //}
            mItems.push_back(item);
        }
        
        // Move to the next child
        child = child->GetNext();
    }
}

/*! \brief Clear the aquarium data.
 * Deletes all known items in the aquarium.
 */
void CAquarium::Clear()
{
    while(!mItems.empty())
    {
        delete mItems.front();
        mItems.pop_front();
    }
}

/*! \brief Handle updates for animation
 * \param elapsed The time since the last update
 */
void CAquarium::Update(double elapsed)
{
    for(list<CItem *>::iterator i=mItems.begin(); 
            i != mItems.end();  i++) 
    {
        CItem *item = *i;
        item->Update(elapsed);
    }
}