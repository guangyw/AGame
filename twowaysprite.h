#ifndef TWOWAYSPRITE__H
#define TWOWAYSPRITE__H

#include <string>
#include <iostream>
#include <vector>
#include "collisionStrategy.h"
using std::string;

#include "drawable.h"

class TwoWaySprite : public Drawable {
public:
  TwoWaySprite(const string&);

  TwoWaySprite(const std::string&, const Vector2f& pos, const Vector2f& vel,
              const std::vector<Frame*>& fms);

  TwoWaySprite(const TwoWaySprite&);
  virtual ~TwoWaySprite() { }

  //void reset();
  void draw() const;
  virtual void update(Uint32 ticks);
  const Frame* getFrame() const {
    return frames[currentFrame];
  }


  int getHeight(){
     return frameHeight;
  }

  int getWidth(){
     return frameWidth;
  }

  virtual void goForward();
  virtual void goBack();
  virtual void goUp();
  virtual void goDown();
  virtual void stop();

  bool collideWith(const Drawable* d) const{
    return strategy->execute(*this, *d);
  }


protected:
  const std::vector<Frame *> frames;
  int worldWidth;
  int worldHeight;

  float dt;
  unsigned currentFrame;
  unsigned numberOfFrames;
  unsigned frameInterval;
  float timeSinceLastFrame;
  int frameWidth;
  int frameHeight;
  int speed;
  CollisionStrategy* strategy;

  void advanceFrame(Uint32 ticks);
  TwoWaySprite& operator=(const TwoWaySprite);
};
#endif
