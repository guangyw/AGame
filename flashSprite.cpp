#include "flashSprite.h"
inline int randBetween(int low, int high) {
   return ((rand() % (high - low)) + low);
}

FlashSprite::FlashSprite(const string& name):
   MultiSprite(name),
   frameInterval(randBetween(20, 100))
{
   setPosition(Vector2f(randBetween(0, worldWidth), randBetween(0, 150)));
   setFrameInterval(frameInterval);
}


FlashSprite::FlashSprite(const FlashSprite& fs):
   MultiSprite(fs),
   frameInterval(fs.getFrameInterval())
{setFrameInterval(frameInterval);}

void FlashSprite::update(Uint32 ticks){
   advanceFrame(ticks);
   if (currentFrame == 4)
      markDeleted();
}
