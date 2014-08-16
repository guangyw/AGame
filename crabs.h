#ifndef CRABS__H
#define CRABS__H

#include <list>
#include "crabSprite.h"

class Crabs {
   public:
      Crabs();
      Crabs(const Crabs&);
      ~Crabs();
      void draw() const;
      void update(Uint32 ticks);
      void gen();
      int countFree() const;
      int countCrab() const;
      std::list<CrabSprite*> getCrabs() const{return crabList;}
      void deleteOne();

   private:
      std::list<CrabSprite*> crabList;
      std::list<CrabSprite*> freeList;
      float timeSinceLastFrame;
};

#endif
