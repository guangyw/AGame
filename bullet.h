#ifndef BULLET__H
#define BULLET__H

#include "sprite.h"
#include "vector2f.h"
#include "collisionStrategy.h"
#include "drawable.h"

class Bullet : public Sprite{
   public:
      Bullet(Vector2f&);
      Bullet(const Bullet&);
      void update(Uint32 ticks);
      bool ifOut() const {return out;}
      void setOut() {out = true;}
      void reset(Vector2f&);
      bool collideWith(const Drawable* d) const{
         return strategy->execute(*this, *d);
      }

   private:
      bool out;
      CollisionStrategy* strategy;
      Bullet& operator=(const Bullet);
};

#endif
