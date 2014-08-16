#include <iostream>
#include <cmath>
#include "randMultiSprite.h"
#include "gamedata.h"
#include "frameFactory.h"
#include <vector>
#include "frame.h"

inline int randBetween(int low, int high) {
   return ((rand() % (high - low)) + low);
}

void RandMultiSprite::advanceFrame(Uint32 ticks) {
	timeSinceLastFrame += ticks;
	if (timeSinceLastFrame > frameInterval) {
    currentFrame = (currentFrame+1) % numberOfFrames;
		timeSinceLastFrame = 0;
	}
}

void RandMultiSprite::setFrameInterval(unsigned fi){
   frameInterval = fi;
}

RandMultiSprite::RandMultiSprite( const std::string& name) :
  Drawable(name,
           Vector2f(Gamedata::getInstance().getXmlInt(name+"X"),
                    Gamedata::getInstance().getXmlInt(name+"Y")),
           Vector2f(randBetween(Gamedata::getInstance().getXmlInt(name+"SpeedX"), -30),
                    Gamedata::getInstance().getXmlInt(name+"SpeedY"))
           ),
  frames(FrameFactory::getInstance().getRandFrames(name, velocityX())),
  worldWidth(Gamedata::getInstance().getXmlInt("worldWidth")),
  worldHeight(Gamedata::getInstance().getXmlInt("worldHeight")),

  dt(0),
  currentFrame(0),
  numberOfFrames( Gamedata::getInstance().getXmlInt(name+"Frames") ),
  frameInterval( Gamedata::getInstance().getXmlInt(name+"FrameInterval") ),
  timeSinceLastFrame( 0 ),
  frameWidth(frames[0]->getWidth()),
  frameHeight(frames[0]->getHeight())
{
  // setVelocity(Vector2f(randBetween(velocityX(), -30), 0));
   //FrameFactory::getInstance().getRandFrames(name, velocityX());
   //std::vector<Frame*>::iterator it;
   //std::vector<Frame*> frs = FrameFactory::getInstance().getRandFrames(name, velocityX());
   //it = frs.begin();
   //while(it != frs.end()){
   //   frames.push_back(*it);
   //   ++it;
   //}
}

RandMultiSprite::RandMultiSprite(const std::string& name,
                         const Vector2f& pos, const Vector2f& vel,
                         const std::vector<Frame*>& fms) :
  Drawable(name, pos, vel),
  frames(fms),
  worldWidth(Gamedata::getInstance().getXmlInt("worldWidth")),
  worldHeight(Gamedata::getInstance().getXmlInt("worldHeight")),

  dt(0),
  currentFrame(0),
  numberOfFrames( Gamedata::getInstance().getXmlInt(name+"Frames") ),
  frameInterval( Gamedata::getInstance().getXmlInt(name+"FrameInterval") ),
  timeSinceLastFrame( 0 ),
  frameWidth(fms[0]->getWidth()),
  frameHeight(fms[0]->getHeight())
{ }

RandMultiSprite::RandMultiSprite(const RandMultiSprite& s) :
  Drawable(s.getName(), s.getPosition(), s.getVelocity()),
  frames(s.frames),
  worldWidth( s.worldWidth ),
  worldHeight( s.worldHeight ),
  dt(s.dt),
  currentFrame(s.currentFrame),
  numberOfFrames( s.numberOfFrames ),
  frameInterval( s.frameInterval ),
  timeSinceLastFrame( s.timeSinceLastFrame ),
  frameWidth( s.frameWidth ),
  frameHeight( s.frameHeight )
  { }

void RandMultiSprite::draw() const {
  Uint32 x = static_cast<Uint32>(X());
  Uint32 y = static_cast<Uint32>(Y());
  frames[currentFrame]->draw(x, y);
}

void RandMultiSprite::update(Uint32 ticks) {
  advanceFrame(ticks);

  Vector2f incr = getVelocity() * static_cast<float>(ticks) * 0.001;
  setPosition(getPosition() + incr);

  if ( Y() < 0) {
    velocityY( abs( velocityY() ) );
  }
  if ( Y() > worldHeight-frameHeight) {
    velocityY( -abs( velocityY() ) );
  }

  if ( X() < 0) {
    velocityX( abs( velocityX() ) );
  }
  if ( X() > worldWidth-frameWidth) {
    velocityX( -abs( velocityX() ) );
  }

}
