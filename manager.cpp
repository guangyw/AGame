#include <iostream>
#include <string>
#include "sprite.h"
#include "multisprite.h"
#include "twowaysprite.h"
#include "gamedata.h"
#include "manager.h"
#include "vector2f.h"
#include "aaline.h"
#include "flashSprite.h"
#include <algorithm>
#include "crabSprite.h"
#include "blueJetSprite.h"
#include "explodingSprite.h"

class SpritesLess {
   public:
      bool operator()(const Drawable* a, const Drawable* b) const{
         return pow(a->velocityX(), 2) + pow(a->velocityY(), 2) <  pow(b->velocityX(),2) + pow(b->velocityY(), 2);
      }
};

void Manager::setNumSprites(int n){
  int crabCount = crabs.countCrab();
  if (n > crabCount){
     for(int i= 0; i < n - crabCount; ++i){
        crabs.gen();
     }
  }else{
     for(int i = 0; i < crabCount - n; ++i){
         crabs.deleteOne();
     }
   }
}

Manager::~Manager() {
  // These deletions eliminate "definitely lost" and
  // "still reachable"s in Valgrind.
  for (unsigned i = 0; i < sprites.size(); ++i) {
    delete sprites[i];
  }
  delete player;
  delete explodingPlayer;
  //if(!explodes.empty()){
   //  std::list<ExplodingSprite*>::iterator it = explodes.begin();
   //  while(it != explodes.end()){
   //     delete *it;
   //     ++it;
   //  }
  //}
  //delete stones;
  delete baby;

}

Manager::Manager() :
  env( SDL_putenv(const_cast<char*>("SDL_VIDEO_CENTERED=center")) ),
  io( IOManager::getInstance() ),
  clock( Clock::getInstance() ),
  screen( io.getScreen() ),
  sky("sky", Gamedata::getInstance().getXmlInt("skyFactor") ),
  sea("sea", Gamedata::getInstance().getXmlInt("seaFactor") ),
  sand("sand", Gamedata::getInstance().getXmlInt("sandFactor") ),
  viewport( Viewport::getInstance() ),
  sprites(),
  currentSprite(0),
  help(true),
  player(new TwoWaySprite("alligator")),
  explodingPlayer(new ExplodingSprite(*player)),
  thePlayer(player),
  crabs(),
  hud(),
  bullets(),
  explodes(),
  stones(new Stones()),
  baby(new SmartSprite("femalealligator", player)),
  difficulty(1)
{
  if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO)!= 0) {
    throw string("Unable to initialize SDL: ");
  }
  atexit(SDL_Quit);
  viewport.setObjectToTrack(player);
  baby->setPosition(Vector2f(1100,500));
  //sprites.push_back(player);
}

void Manager::setDifficulty(int n) {
   std::cout<<"difficulty: "<<difficulty<<std::endl;
   if (n == 4)
      n = 6;
   difficulty = n;
}

void Manager::draw() const {
  sky.draw();
  sea.draw();
  sand.draw();
  for (unsigned i = 0; i < sprites.size(); ++i) {
    sprites[i]->draw();
  }
  bullets.draw();
  crabs.draw();
  stones->draw();

  thePlayer->draw();
  baby->draw();
  if(explodes.size() > 0){
    std::list<ExplodingSprite*>::const_iterator it = explodes.begin();
    for(; it != explodes.end(); ++it)
       (*it)->draw();
  }

  if(help) {
     hud.draw(crabs.countFree(), crabs.countCrab(), stones->countFree(), stones->countStones());
  }
  SDL_Flip(screen);
}

void Manager::update() {
  ++clock;
  static int countTicks = 0;
  static int countCrabTicks = 0;
  static int countBluejetTicks = 0;
  int frequency =Gamedata::getInstance().getXmlInt("flashFrequency");
  int crabFreq = Gamedata::getInstance().getXmlInt("crabFrequency")/difficulty;
  int bluejetFreq = Gamedata::getInstance().getXmlInt("blueJetFrequency")/difficulty;
  Uint32 ticks = clock.getElapsedTicks();
  for (unsigned int i = 0; i < sprites.size(); ++i) {
    sprites[i]->update(ticks);
    if (sprites[i]-> ifDeleted())
    {
       delete sprites[i];
       sprites.erase(sprites.begin()+i);
    }
  }

  crabs.update(ticks);
  stones->update(ticks);
  bullets.update(ticks);
  updateExplodes(ticks);

  thePlayer->update(ticks);
  baby->update(ticks);
  countTicks +=ticks;
  countCrabTicks += ticks;
  countBluejetTicks += ticks;
  if (countTicks > frequency)
  {
     sprites.push_back(new FlashSprite("flash"));
     countTicks = 0;
  }
  if (countCrabTicks > crabFreq)
  {
     crabs.gen();
     //sprites.push_back(new CrabSprite("crab"));
     countCrabTicks = 0;
  }
  if (countBluejetTicks > bluejetFreq){
     sprites.push_back(new BlueJetSprite("blueJet", player, stones));
     countBluejetTicks = 0;
  }

  std::sort(sprites.begin(), sprites.end(), SpritesLess());
  sky.update();
  sea.update();
  sand.update();
  viewport.update(); // always update viewport last
}

bool Manager::checkWin(){
   if(player->collideWith(baby))
      return true;
   return false;
}

bool Manager::checkCollision(){
   //check if hit a crab
   std::list<CrabSprite*> temp = crabs.getCrabs();
   if(!temp.empty()){
      std::list<CrabSprite*>::const_iterator it = temp.begin();
      for(; it != temp.end(); ++it){
         if(player->collideWith(*it)){
            return true;
         }
      }
   }

   //check if hit by a stone
   std::list<StoneSprite*> stoneList = stones->getStones();
   if(!stoneList.empty()){
      std::list<StoneSprite*>::const_iterator it = stoneList.begin();
      for(; it != stoneList.end(); ++it){
         if(player->collideWith(*it))
            return true;
      }
   }
   return false;
}

void Manager::checkHit(SDLSound& sound){
   if(bullets.countBullet() > 0){
      Bullet* tBullet;
      std::list<CrabSprite*> temp = crabs.getCrabs();
      if(!temp.empty()){
         std::list<CrabSprite*>::const_iterator it;
         for(it = temp.begin(); it != temp.end(); ++it){
            if((tBullet=bullets.collideWith(*it)) != NULL){
               ExplodingSprite* temp = new ExplodingSprite(**it);
               temp->reset((*it)->getPosition());
               //explodes.push_back(new ExplodingSprite(**it));
               explodes.push_back(temp);
               temp = new ExplodingSprite(*tBullet);
               temp->reset((*it)->getPosition());
               explodes.push_back(temp);
               tBullet->setOut();
               (*it)->setOut();
               sound[1];
               break;
            }
         }
      }
   }
}

void Manager::updateExplodes(Uint32 ticks){
   if(explodes.size()>0){
      std::list<ExplodingSprite*>::iterator it = explodes.begin();
      while(it != explodes.end()){
         if( (*it)->chunkCount() == 0){
            delete *it;
            it = explodes.erase(it);
         }else{
            (*it)->update(ticks);
            ++it;
         }
      }
   }
}

void Manager::play() {
  SDL_Event event;

  bool done = false;
  bool keyCatch = false;
  bool fireCatch = false;
  bool exploded = false;

  SDLSound sound;

  while ( not done ) {
    if(checkWin()){
      done = true;
      sound[3];
      SDL_Delay(1000);
      sound[2];
      SDL_Delay(4000);
      break;
    }
    if(exploded){
      if (static_cast<ExplodingSprite*>(thePlayer)->chunkCount()==0){
         thePlayer = player;
         exploded = false;
         done = true;
         break;
      }
    }
    if(!exploded){
       exploded = checkCollision();
      if(exploded == true){
         sound[1];
         static_cast<ExplodingSprite*>(explodingPlayer)->reset(thePlayer->getPosition());
         thePlayer = explodingPlayer;
      }
    }
    SDL_PollEvent(&event);
    Uint8 *keystate = SDL_GetKeyState(NULL);
    if (event.type ==  SDL_QUIT) { done = true; break; }
    if(event.type == SDL_KEYUP) {
      keyCatch = false;
      fireCatch = false;

      if (!keystate[SDLK_DOWN] && !keystate[SDLK_UP] && !keystate[SDLK_RIGHT] && !keystate[SDLK_LEFT]){
         player->stop();
      }
    }
    if(event.type == SDL_KEYDOWN) {
      if (keystate[SDLK_ESCAPE] || keystate[SDLK_q]) {
        done = true;
        break;
      }
     //if (keystate[SDLK_t] && !keyCatch) {
     //  keyCatch = true;
     //   currentSprite = (currentSprite+1) % sprites.size();
     //   viewport.setObjectToTrack(sprites[currentSprite]);
     // }
      if (keystate[SDLK_s] && !keyCatch) {
        keyCatch = true;
        clock.toggleSloMo();
      }

      if (keystate[SDLK_p] && !keyCatch){
         keyCatch = true;
         if(clock.isPaused())
            clock.unpause();
         else
            clock.pause();
      }

      if (keystate[SDLK_F1] && !keyCatch) {
         keyCatch = true;
         toggleHelp();
      }

      if (keystate[SDLK_RIGHT]) {
         keyCatch = true;
         player->goForward();
      }


      if (keystate[SDLK_LEFT]) {
         keyCatch = true;
         player->goBack();
      }


      if (keystate[SDLK_UP]) {
         keyCatch = true;
         player->goUp();
      }

      if (keystate[SDLK_DOWN]) {
         keyCatch = true;
         player->goDown();
      }

      if (keystate[SDLK_SPACE] && !fireCatch && player->velocityX() >=0) {
         fireCatch = true;
         sound[0];
         Vector2f pos = player->getPosition();
         pos[0] += player->getWidth();
         pos[1] += player->getHeight()/2;
         bullets.gen(pos);
         //sprites.push_back( new Sprite("bullet", pos));
      }
    }

    checkHit(sound);
    update();
    draw();
  }
}

void Manager::toggleHelp() {
   if (!help)
      help = true;
   else
      help = false;
}
