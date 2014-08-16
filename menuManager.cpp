#include <cmath>
#include <iostream>
#include <string>
#include <sstream>
#include "menuManager.h"
#include "manager.h"
#include "world.h"

MenuManager::MenuManager() :
  env( SDL_putenv(const_cast<char*>("SDL_VIDEO_CENTERED=center")) ),
  screen( IOManager::getInstance().getScreen() ),
  clock( Clock::getInstance() ),
  backColor(),
  menu(),
  difficulty(1),
  back("back",1)
{
  if (SDL_Init(SDL_INIT_VIDEO) != 0) {
    throw string("Unable to initialize SDL: ");
  }
  backColor.r = Gamedata::getInstance().getXmlInt("backRed");
  backColor.g = Gamedata::getInstance().getXmlInt("backGreen");
  backColor.b = Gamedata::getInstance().getXmlInt("backBlue");
  atexit(SDL_Quit);
}

void MenuManager::getHelp(){
   IOManager& io = IOManager::getInstance().getInstance();
   SDL_Event event;
   bool done = false;
   while (not done){
      Uint8 *keystate = SDL_GetKeyState(NULL);
      if (SDL_PollEvent(&event))
         switch(event.type){
            case SDL_KEYDOWN:{
               if (keystate[SDLK_ESCAPE] || keystate[SDLK_q]) {
                  done = true;
                  break;
               }
               io.buildString(event);
            }
         }
      drawBackground();
      io.printMessageAt("The goal is to find the female alligator", 600, 70);
      io.printMessageAt("The female alligator is on the other side of the map", 600, 100);
      io.printMessageAt("You have to avoid or shoot the crabs", 600, 130);
      io.printMessageAt("You have to avoid the stones thrown by the bird", 600, 160);
      io.printMessageAt("You can do nothing to the bird. This is life", 600, 190);
      io.printMessageAt("Press F1 and you will learn the skills for you to live", 600, 220);
      io.printMessageAt("The rest is on you, good luck!", 600, 250);
      SDL_Flip(screen);
   }
}

void MenuManager::drawBackground() const {
  SDL_FillRect( screen, NULL,
    SDL_MapRGB(screen->format, backColor.r, backColor.g, backColor.b) );
  SDL_Rect dest = {0, 0, 0, 0};
  SDL_BlitSurface( screen, NULL, screen, &dest );
  back.draw();
}

void MenuManager::getDifficulty() {
   IOManager& io = IOManager::getInstance().getInstance();
   SDL_Event event;
   bool done = false;
   bool diffDone = false;
   const string msg1("Please select the difficulty level: ");
   const string msg2("1: Easy 2: Normal 3: Hard 4: Insane");
   io.clearString();
   while( not done ){
      Uint8 *keystate = SDL_GetKeyState(NULL);
      if (SDL_PollEvent(&event))
         switch (event.type) {
            case SDL_KEYDOWN: {
               if (keystate[SDLK_ESCAPE] || keystate[SDLK_q]){
                  done = true;
                  break;
               }
               if (keystate[SDLK_RETURN])
                  diffDone = true;
               io.buildString(event);
            }
         }
      drawBackground();
      io.printStringAfterMessage(msg1, 660, 100);
      io.printStringAfterMessage(msg2, 660, 150);

      if(diffDone){
         std::string diff = io.getString();
         io.clearString();
         std::stringstream strm;
         strm << diff;
         strm >>difficulty;
         std::cout<<difficulty<<std::endl;
         SDL_Delay(250);
         done = true;
      }
      SDL_Flip(screen);
   }
}


void MenuManager::play() {
  bool keyCatch = false; // To get only 1 key per keydown
  SDL_Event event;
  bool done = false;

  // Here, we need to create an instance of the Manager,
  // the one that manages the game:
  Manager manager;
  manager.pause();

  while ( not done ) {

    drawBackground();
    menu.draw();
    SDL_Flip(screen);

    SDL_PollEvent(&event);
    if (event.type ==  SDL_QUIT) { break; }
    if(event.type == SDL_KEYDOWN) {
      switch ( event.key.keysym.sym ) {
        case SDLK_ESCAPE :
        case SDLK_q : {
          done = true;
          break;
        }
        case SDLK_RETURN : {
          if ( !keyCatch ) {
            menu.lightOn();
            if ( menu.getIconClicked() == "Start Game" ) {
              // Here is where we call the play() function in Manager:
              std::cout << "Starting game ..." << std::endl;
               Manager manager;
               manager.setDifficulty(difficulty);
               manager.unpause();
               manager.play();
               manager.pause();
            }
            if ( menu.getIconClicked() == "Difficulty" ) {
              getDifficulty();
              // After we get the number, we must pass it to Manager:
              std::cout<<difficulty<<std::endl;
              manager.setDifficulty(difficulty);
            }
            if ( menu.getIconClicked() == "Help" ) {
              // Here is where we explain how to play the game"
              std::cout << "Give help  ..." << std::endl;
              getHelp();
            }
            if ( menu.getIconClicked() == "Exit" ) {
              drawBackground();
              menu.draw();
              SDL_Flip(screen);
              SDL_Delay(250);
              done = true;
            }
          }
          break;
        }
        case SDLK_DOWN   : {
          if ( !keyCatch ) {
            menu.increment();
          }
          break;
        }
        case SDLK_UP   : {
          if ( !keyCatch ) {
            menu.decrement();
          }
          break;
        }
        default          : break;
      }
      keyCatch = true;
    }
    if(event.type == SDL_KEYUP) {
      keyCatch = false;
      menu.lightOff();
    }
  }
}
