#include <SDL.h>

#include "ioManager.h"
#include "menu.h"
#include "world.h"

class Clock;

class MenuManager {
public:
  MenuManager ();
  void play();
  //int getStars() const { return numberOfSprites; }

private:
  bool env;
  SDL_Surface *screen;
  const Clock& clock;

  SDL_Color backColor;
  Menu menu;
  int difficulty;

  void drawBackground() const;
  MenuManager(const MenuManager&);
  MenuManager& operator=(const MenuManager&);
  void getDifficulty();
  void getHelp();
  World back;
};
