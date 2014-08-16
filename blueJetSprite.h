#ifndef BLUEJETSPRITE__H
#define BLUEJETSPRITE__H

#include <string>
#include <iostream>
#include <vector>
#include "stones.h"
using std::string;

#include "randMultiSprite.h"

class TwoWaySprite;
//class Stones;

class BlueJetSprite : public RandMultiSprite{
public:
   BlueJetSprite(const string&);
   BlueJetSprite(const string&, TwoWaySprite*, Stones*);
   BlueJetSprite(const BlueJetSprite&);
   void update(Uint32 ticks);
   void drop();

private:
   TwoWaySprite* player;
   Stones* stones;
   int xToDrop;
   bool dropped;
   BlueJetSprite& operator=(const BlueJetSprite&);
};


#endif
