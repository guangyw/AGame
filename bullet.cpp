#include "bullet.h"

Bullet::Bullet(Vector2f& pos):
   Sprite("bullet", pos),
   out(false),
   strategy(new RectangularCollisionStrategy())
{}

Bullet::Bullet(const Bullet& b):
   Sprite(b),
   out(b.ifOut()),
   strategy(b.strategy)
{}

void Bullet::update(Uint32 ticks){
   Vector2f incr = getVelocity() * static_cast<float>(ticks) * 0.001;
   setPosition(getPosition() + incr);

   if( X() < 0)
      setOut();
   if (X() > 1024)
      setOut();
}

void Bullet::reset(Vector2f& pos) {
   setPosition(pos);
   out = false;
}
