#ifndef FLASHSPRITE__H
#define FLASHSPRITE__H

#include <string>
#include <iostream>
#include <vector>
using std::string;

#include "multisprite.h"

class FlashSprite : public MultiSprite {
public:
   FlashSprite(const string&);
   FlashSprite(const FlashSprite&);
   void update(Uint32 ticks);
   unsigned getFrameInterval() const {return frameInterval;}
//   bool operator<(const FlashSprite& fs){
//      return frameInterval < fs.getFrameInterval();
//   }
private:
   unsigned frameInterval;
};


#endif
