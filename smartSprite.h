#include <iostream>
#include "twowaysprite.h"

class SmartSprite : public TwoWaySprite {
public:
  SmartSprite(const std::string&);
  SmartSprite(const std::string&, const TwoWaySprite* p);
  ~SmartSprite();
  void update(Uint32 ticks);
  void goLeft();
  void goRight();
  void goUp();
  void goDown();

  //static void incrSafeDistance() {++safeDistance; }
  //static void decrSafeDistance() { --safeDistance; }
  //static float getSafeDistance() { return safeDistance; }

private:
  enum MODE {NORMAL, EVADE};
  const TwoWaySprite*  enemy;
  const static int safeDistance = 250;
  MODE currentMode;
  SmartSprite(const SmartSprite &);
  SmartSprite& operator=(const SmartSprite &rhs);
};
