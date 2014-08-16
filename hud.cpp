#include "aaline.h"
#include "hud.h"
#include "gamedata.h"

Hud::Hud():
   io(IOManager::getInstance()),
   screen(io.getScreen()),
   hudStartX(Gamedata::getInstance().getXmlInt("hudStartX")),
   hudStartY(Gamedata::getInstance().getXmlInt("hudStartY")),
   hudLen(Gamedata::getInstance().getXmlInt("hudLen")),
   hudHeight(Gamedata::getInstance().getXmlInt("hudHeight")),
   clock( Clock::getInstance())
{}

void Hud::draw(int free, int crabs, int freestones, int stones) const{
     const Uint32 RED = SDL_MapRGB(screen->format, 0xff, 0, 0);
     Draw_AALine(screen, hudStartX, hudStartY, hudStartX + hudLen, hudStartY, RED);
     Draw_AALine(screen, hudStartX, hudStartY, hudStartX, hudStartY + hudHeight, RED);
     Draw_AALine(screen, hudStartX + hudLen, hudStartY, hudStartX + hudLen, hudStartY + hudHeight, RED);
     Draw_AALine(screen, hudStartX, hudStartY + hudHeight, hudStartX + hudLen, hudStartY + hudHeight,RED);
     io.printMessageValueAt("Seconds: ", clock.getSeconds(), hudStartX + 5, hudStartY + 10);
     io.printMessageValueAt("fps: ", clock.getFps(), hudStartX + 5, hudStartY + 30);
     io.printMessageAt("Press space to fire", hudStartX + 5, hudStartY + 50);
     io.printMessageAt("Arrow keys to control your player", hudStartX + 5, hudStartY + 70);
     io.printMessageAt("That's all you can do", hudStartX + 5, hudStartY + 90);
     io.printMessageValueAt("Number of Crabs in free list: ", free, hudStartX + 5, hudStartY + 110);
     io.printMessageValueAt("Number of Crabs: ", crabs, hudStartX + 5, hudStartY + 130);

     io.printMessageValueAt("Number of stones in free list: ", freestones , hudStartX + 5, hudStartY + 150);

     io.printMessageValueAt("Number of stones: ", stones , hudStartX + 5, hudStartY + 170);
}
