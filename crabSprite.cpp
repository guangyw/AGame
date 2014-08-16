#include "crabSprite.h"
inline int randBetween(int low, int high) {
   return ((rand() % (high - low)) + low);
}

CrabSprite::CrabSprite():
   MultiSprite("crab"),
   out(false)
{
   setPosition(Vector2f(1024, randBetween(350, 860)));
}


CrabSprite::CrabSprite(const CrabSprite& fs):
   MultiSprite(fs),
   out(fs.ifOut())
{}

bool CrabSprite::ifOut() const {return out;}

void CrabSprite::update(Uint32 ticks){
   advanceFrame(ticks);

   Vector2f incr = getVelocity() * static_cast<float>(ticks) * 0.001;
   setPosition(getPosition() + incr);

   if (X() < 0)
      setOut();
}

void CrabSprite::reset(){
   setPosition(Vector2f(1024, randBetween(350, 860)));
   out = false;
}
