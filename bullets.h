#ifndef BULLETS__H
#define BULLETS__H

#include <list>
#include "bullet.h"
#include "vector2f.h"

class Bullets {
   public:
      Bullets();
      Bullets(const Bullets&);
      ~Bullets();
      void draw() const;
      void update(Uint32 ticks);
      void gen(Vector2f&);
      int countFree() const;
      int countBullet() const;
      Bullet* collideWith(const Drawable* d) const{
         std::list<Bullet*>::const_iterator it = bulletList.begin();
         for(; it != bulletList.end(); ++it){
            if( (*it)->collideWith(d))
               return *it;
         }
         return NULL;
      }
   private:
      std::list<Bullet*> bulletList;
      std::list<Bullet*> freeList;
      float timeSinceLastFrame;
};

#endif
