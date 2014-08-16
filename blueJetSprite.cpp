#include "blueJetSprite.h"
#include "gamedata.h"
//#include "stones.h"
#include <cmath>
#include "twowaysprite.h"
#include <iostream>

inline int randBetween(int low, int high) {
   return ((rand() % (high - low)) + low);
}

/*BlueJetSprite::BlueJetSprite(const string& name):
   RandMultiSprite(name),
   player(),
   stones(0),
   xToDrop(0),
   dropped(false)
{
   setPosition(Vector2f(1024, randBetween(20, 150)));
   //setVelocity(Vector2f(randBetween(-100, -30), 0));
}

*/

BlueJetSprite::BlueJetSprite(const string& name, TwoWaySprite* tws, Stones* stones):
   RandMultiSprite(name),
   player(tws),
   stones(stones),
   xToDrop(randBetween(400, 1024)),
   dropped(false)
{
   //std::cout<<"constructing bluejet"<<std::endl;
   //std::cout<<"number of stones"<<stones->countStones()<<std::endl;
   //std::cout<<"position of player"<<tws->getPosition()<<std::endl;
   setPosition(Vector2f(1024, randBetween(20, 150)));
}

BlueJetSprite::BlueJetSprite(const BlueJetSprite& fs):
   RandMultiSprite(fs),
   player(fs.player),
   stones(fs.stones),
   xToDrop(fs.xToDrop),
   dropped(fs.dropped)
{}

void BlueJetSprite::update(Uint32 ticks){
   advanceFrame(ticks);

   Vector2f incr = getVelocity() * static_cast<float>(ticks) * 0.001;
   setPosition(getPosition() + incr);

   //std::cout<<"update bluejet"<<xToDrop<<std::endl;

   if(!dropped){
      if (static_cast<int>(X()) == xToDrop)
         drop();
   }

   if (X() < 0)
      markDeleted();
}

void BlueJetSprite::drop(){
   int speed = Gamedata::getInstance().getXmlInt("stonespeed");
   int xDis = X() - (player->X() + player->getWidth()/2);
   int yDis = player->Y() + player->getHeight()/2 - Y();
   int dis = hypot(xDis, yDis);

   float veloX = static_cast<float>(xDis)/dis * speed;
   float veloY = static_cast<float>(yDis)/dis * speed;

   std::cout<<veloX<<":"<<veloY<<std::endl;

   stones->gen(getPosition(), Vector2f(-veloX, veloY));
   dropped = true;
}
