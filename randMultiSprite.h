#ifndef RANDMULTISPRITE__H
#define RANDMULTISPRITE__H

#include <string>
#include <iostream>
#include <vector>
using std::string;

#include "drawable.h"

class RandMultiSprite : public Drawable {
public:
  RandMultiSprite(const string&);

  RandMultiSprite(const std::string&, const Vector2f& pos, const Vector2f& vel,
              const std::vector<Frame*>& fms);

  RandMultiSprite(const RandMultiSprite&);
  virtual ~RandMultiSprite() { }

  virtual void draw() const;
  virtual void update(Uint32 ticks);
  virtual const Frame* getFrame() const {
    return frames[currentFrame];
  }

  void setFrameInterval(unsigned);

protected:
  std::vector<Frame *> frames;
  int worldWidth;
  int worldHeight;

  float dt;
  unsigned currentFrame;
  unsigned numberOfFrames;
  unsigned frameInterval;
  float timeSinceLastFrame;
  int frameWidth;
  int frameHeight;

  void advanceFrame(Uint32 ticks);
};
#endif
