#ifndef SPRITE__H
#define SPRITE__H

#include <string>
#include <iostream>
#include "drawable.h"

class Sprite : public Drawable {
public:
  Sprite(const std::string&);

  //to add a sprte at a specific location
  Sprite(const std::string&, const Vector2f&);

  Sprite(const std::string&, const Vector2f&, const Vector2f&, const Frame*);

  Sprite(const Sprite& s);
  virtual ~Sprite() { }
  Sprite& operator=(const Sprite&);

  virtual const Frame* getFrame() const { return frame; }
  virtual void draw() const;

  virtual void update(Uint32 ticks);
  Sprite(const std::string&, const Vector2f&, const Vector2f&);

private:
  const Frame * frame;
  int frameWidth;
  int frameHeight;
  int worldWidth;
  int worldHeight;
  int getDistance(const Sprite*) const;
  bool random;
};
#endif
