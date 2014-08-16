#ifndef STONES__H
#define STONES__H

#include <list>
#include "vector2f.h"
#include "stonesprite.h"

//class StoneSprite;

class Stones {
   public:
      Stones();
      Stones(const Stones&);
      ~Stones();
      void draw() const;
      void update(Uint32);
      void gen(const Vector2f&, const Vector2f&);
      int countFree() const {return freeList.size();}
      int countStones() const {return stoneList.size();}
      std::list<StoneSprite*> getStones() const{return stoneList;}

   private:
      std::list<StoneSprite*> stoneList;
      std::list<StoneSprite*> freeList;
};

#endif
