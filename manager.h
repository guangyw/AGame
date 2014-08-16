#include <vector>
#include <SDL.h>
#include "ioManager.h"
#include "world.h"
#include "viewport.h"
#include "drawable.h"
#include "twowaysprite.h"
#include "hud.h"
#include "crabs.h"
#include "bullets.h"
#include "bullet.h"
#include "sound.h"
#include "explodingSprite.h"
#include "stones.h"
#include "smartSprite.h"

class Manager {
public:
  Manager ();
  ~Manager ();
  void play();
  void toggleHelp();
  bool checkCollision();
  void checkHit(SDLSound&);
  void updateExplodes(Uint32);
  void pause(){clock.pause();}
  void unpause(){clock.unpause();}
  void setNumSprites(int);
  bool checkWin();
  void setDifficulty(int);

private:
  const bool env;
  const IOManager& io;
  Clock& clock;

  SDL_Surface * const screen;
  World sky;
  World sea;
  World sand;
  Viewport& viewport;

  std::vector<Drawable*> sprites;
  int currentSprite;

  bool help;

  TwoWaySprite* player;
  Drawable* explodingPlayer;
  Drawable* thePlayer;

  Crabs crabs;
  Hud hud;

  Bullets bullets;

  std::list<ExplodingSprite*> explodes;

  void draw() const;
  void update();

  Stones* stones;
  SmartSprite* baby;
  int difficulty;

  Manager(const Manager&);
  Manager& operator=(const Manager&);
};
