#include <iostream>
#include <cmath>
#include "sprite.h"
#include "gamedata.h"
#include "frameFactory.h"


int randBetween(int low, int high) {
   return ((rand() % (high - low)) + low);
}

Sprite::Sprite(const std::string& name) :
  Drawable(name,
           Vector2f(Gamedata::getInstance().getXmlInt(name+"SrcX"),
                    Gamedata::getInstance().getXmlInt(name+"SrcY")),
           Vector2f(Gamedata::getInstance().getXmlInt(name+"SpeedX"),
                    Gamedata::getInstance().getXmlInt(name+"SpeedY"))
           ),
  frame( FrameFactory::getInstance().getFrame(name) ),
  frameWidth(frame->getWidth()),
  frameHeight(frame->getHeight()),
  worldWidth(Gamedata::getInstance().getXmlInt("worldWidth")),
  worldHeight(Gamedata::getInstance().getXmlInt("worldHeight")),
  random(Gamedata::getInstance().getXmlBool(name+"Random"))
{
   if(random){
      setPosition(Vector2f(randBetween(0, worldWidth), 0));
      setVelocity(Vector2f(randBetween(0,Gamedata::getInstance().getXmlInt(name+"SpeedX")),Gamedata::getInstance().getXmlInt(name+"SpeedY")));
   }
}

Sprite::Sprite(const std::string& name, const Vector2f& pos, const Vector2f& vel, const Frame* f):
   Drawable(name, pos, vel),
   frame(f),
   frameWidth(frame->getWidth()),
   frameHeight(frame->getHeight()),
   worldWidth(Gamedata::getInstance().getXmlInt("worldWidth")),
   worldHeight(Gamedata::getInstance().getXmlInt("worldHeight")),
   random(false)
{
}


Sprite::Sprite(const std::string& name, const Vector2f& pos) :
   Drawable(name, pos,
           Vector2f(Gamedata::getInstance().getXmlInt(name+"SpeedX"),
                    Gamedata::getInstance().getXmlInt(name+"SpeedY"))),

  frame( FrameFactory::getInstance().getFrame(name) ),
  frameWidth(frame->getWidth()),
  frameHeight(frame->getHeight()),
  worldWidth(Gamedata::getInstance().getXmlInt("worldWidth")),
  worldHeight(Gamedata::getInstance().getXmlInt("worldHeight")),
  random(false)
{ }

Sprite::Sprite(const std::string& name, const Vector2f& pos, const Vector2f& vel):
  Drawable(name, pos, vel),
  frame( FrameFactory::getInstance().getFrame(name) ),
  frameWidth(frame->getWidth()),
  frameHeight(frame->getHeight()),
  worldWidth(Gamedata::getInstance().getXmlInt("worldWidth")),
  worldHeight(Gamedata::getInstance().getXmlInt("worldHeight")),
  random(false)
{ }

Sprite::Sprite(const Sprite& s) :
  Drawable(s.getName(), s.getPosition(), s.getVelocity()),
  frame(s.frame),
  frameWidth(s.getFrame()->getWidth()),
  frameHeight(s.getFrame()->getHeight()),
  worldWidth(Gamedata::getInstance().getXmlInt("worldWidth")),
  worldHeight(Gamedata::getInstance().getXmlInt("worldHeight")),
  random(s.random)
{ }

Sprite& Sprite::operator=(const Sprite& rhs) {
  setName( rhs.getName() );
  setPosition(rhs.getPosition());
  setVelocity(rhs.getVelocity());
  frame = rhs.frame;
  frameWidth = rhs.frameWidth;
  frameHeight = rhs.frameHeight;
  worldWidth = rhs.worldWidth;
  worldHeight = rhs.worldHeight;
  random = rhs.random;
  return *this;
}

void Sprite::draw() const {
  if (!ifDeleted()){
     Uint32 x = static_cast<Uint32>(X());
     Uint32 y = static_cast<Uint32>(Y());
     frame->draw(x, y);
  }
}

int Sprite::getDistance(const Sprite *obj) const {
  return hypot(X()-obj->X(), Y()-obj->Y());
}

void Sprite::update(Uint32 ticks) {
  Vector2f incr = getVelocity() * static_cast<float>(ticks) * 0.001;
  setPosition(getPosition() + incr);

  if ( Y() < 0) {
    markDeleted();
    velocityY( abs( velocityY() ) );
  }
  if ( Y() > worldHeight-frameHeight) {
    markDeleted();
    velocityY( -abs( velocityY() ) );
  }

  if ( X() < 0) {
    markDeleted();
    velocityX( abs( velocityX() ) );
  }
  if ( X() > worldWidth-frameWidth) {
     markDeleted();
    velocityX( -abs( velocityX() ) );
  }
}
