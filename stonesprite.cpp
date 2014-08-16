#include "stonesprite.h"
#include "vector2f.h"
#include <iostream>

StoneSprite::StoneSprite(const Vector2f& pos, const Vector2f& speed):
   Sprite("stone", pos, speed),
   out(false)
{
   //std::cout<<getPosition()<<":"<<getVelocity()<<std::endl;
   //setPosition(pos);
   //setVelocity(speed);
}

StoneSprite::StoneSprite(const StoneSprite& ss):
   Sprite(ss),
   out(ss.ifOut())
{}

bool StoneSprite::ifOut() const{return out;}

void StoneSprite::update(Uint32 ticks){
   //advanceFrame(ticks);

   Vector2f incr = getVelocity() * static_cast<float>(ticks) * 0.001;
   setPosition(getPosition() + incr);

   if (Y() > 960)
      setOut();
   if (X() < 0)
      setOut();
}

void StoneSprite::reset(const Vector2f& pos, const Vector2f& velo){
   setPosition(pos);
   setVelocity(velo);
   out = false;
}
