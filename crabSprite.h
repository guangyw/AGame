#ifndef CRABSPRITE__H
#define CRABSPRITE__H

#include <string>
#include <iostream>
#include <vector>
using std::string;

#include "multisprite.h"

class CrabSprite : public MultiSprite{
public:
   CrabSprite();
   CrabSprite(const CrabSprite&);
   void update(Uint32 ticks);
   bool ifOut() const;
   void setOut(){out = true;}
   void reset();
private:
   bool out;
};


#endif
