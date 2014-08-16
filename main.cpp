// Brian Malloy        Game Construction

#include "menuManager.h"

int main(int, char*[]) {
   try {

      MenuManager menu_manager;
      menu_manager.play();
   }
   catch (const string& msg) { std::cout << msg << std::endl; }
   catch (...) {
      std::cout << "Oops, someone threw an exception!" << std::endl;
   }
   return 0;
}
