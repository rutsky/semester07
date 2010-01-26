#ifndef __MYLAPP_H__632619789336566350
#define __MYLAPP_H__632619789336566350

/**
  @file     cglapp.h
  @brief    Class cglApp definition
  @date     Created on 10/09/2005
  @project  D3DBase
  @author   Bvs
*/

// *******************************************************************
// includes

#include "library/cglapp.h"

// *******************************************************************
// defines & constants

// *******************************************************************
// classes 

// Application class
class myApp : public cglApp
{
public:
  // Constructor
  myApp(int nW, int nH, void* hInst, int nCmdShow) 
    : cglApp(nW, nH, hInst, nCmdShow)
    , m_nPrevMouseX(-100)
    , m_nPrevMouseY(-100)
  {
    for (int i = 0; i < MAX_KEYS; i++)
      m_keysPressed[i] = false;
  }
  // Destructor
  virtual ~myApp() {}
  // This function performs input processing. Returns true if input is handled
  virtual bool processInput(unsigned int nMsg, int wParam, long lParam);
protected:
  virtual char const *getWindowText();
  virtual void update();
  virtual void renderInternal();
  
private:
  enum
  {
    MAX_KEYS = 128
  };
 
  int   m_nPrevMouseX;  
  int   m_nPrevMouseY;
  bool  m_keysPressed[MAX_KEYS];
  
  void rotate(float dx, float dy);
  void zoom(float dr);
};


// *******************************************************************
// functions 

#endif //__CGLAPP_H__632619789336566350
