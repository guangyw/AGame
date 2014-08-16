#include <cmath>
#include "viewport.h"
#include "smartSprite.h"
#include <iostream>

float distance(float x1, float y1, float x2, float y2) {
  float x = x1-x2;
  float y = y1-y2;
  return hypot(x, y);
}

SmartSprite::SmartSprite(const std::string& name):
   TwoWaySprite(name),
   enemy(),
   currentMode(NORMAL)
{}

SmartSprite::SmartSprite(const std::string& name, const TwoWaySprite* p) :
 TwoWaySprite(name),
 enemy(p),
 currentMode(NORMAL)
{setVelocity(Vector2f(200,200));}

SmartSprite::~SmartSprite()
{}

void SmartSprite::goLeft()  {
  if (X() > 1100) velocityX( -abs(velocityX()) );
}
void SmartSprite::goRight() { velocityX( fabs(velocityX()) ); }
void SmartSprite::goUp()    { velocityY( -fabs(velocityY()) ); }
void SmartSprite::goDown()  { velocityY( fabs(velocityY()) ); }

void SmartSprite::update(Uint32 ticks) {
  //TwoWaySprite::update(ticks);
  advanceFrame(ticks);

  Vector2f incr = getVelocity() * static_cast<float>(ticks) * 0.001;
  setPosition(getPosition() + incr);

  float x= X()+getFrame()->getWidth()/2;
  float y= Y()+getFrame()->getHeight()/2;
  float ex= enemy->X()+enemy->getFrame()->getWidth()/2;
  float ey= enemy->Y()+enemy->getFrame()->getHeight()/2;
  float distanceToEnemy = ::distance( x, y, ex, ey );

  if  ( currentMode == NORMAL ) {
    if(distanceToEnemy < safeDistance) currentMode = EVADE;
  }
  else if  ( currentMode == EVADE ) {
    if(distanceToEnemy > safeDistance) currentMode=NORMAL;
    else {
      if ( x < ex ) goLeft();
      if ( x > ex ) goRight();
      if ( y < ey ) goUp();
      if ( y > ey ) goDown();
    }
  }

  if ( Y() < 280) {
    Y(280);
    velocityY( abs( velocityY() ) );
  }
  if ( Y() > worldHeight-frameHeight) {
    velocityY( -abs( velocityY() ) );
  }

  if ( X() < 1100) {
    velocityX( abs( velocityX() ) );
  }
  if ( X() > 2000) {
    velocityX( -abs( velocityX() ) );
  }
}

