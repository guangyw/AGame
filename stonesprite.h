#ifndef STONESPRITE__H
#define STONESPRITE__H

#include <string>
#include <vector>

#include "sprite.h"

class Vector2f;

class StoneSprite : public Sprite{
public:
   StoneSprite();
   StoneSprite(const StoneSprite&);
   StoneSprite(const Vector2f&, const Vector2f&);
   ~StoneSprite(){};
   void update(Uint32 ticks);
   bool ifOut() const;
   void setOut(){out = true;}
   void reset(const Vector2f&, const Vector2f&);

private:
   bool out;
};

#endif
