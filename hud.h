#ifndef HUD__H
#define HUD__H

#include "ioManager.h"
#include "crabs.h"
#include "clock.h"

class Hud {
   public:
      Hud();
      void draw(int, int, int, int) const;

   private:
      IOManager& io;
      SDL_Surface* screen;
      int hudStartX;
      int hudStartY;
      int hudLen;
      int hudHeight;
      Clock& clock;
};


#endif
