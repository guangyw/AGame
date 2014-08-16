#include "bullets.h"

int Bullets::countFree() const { return freeList.size();}

int Bullets::countBullet() const {return bulletList.size();}

void Bullets::gen(Vector2f& pos){
   if (freeList.empty()){
      Bullet* temp = new Bullet(pos);
      bulletList.push_back(temp);
   }else{
      Bullet* temp = freeList.front();
      temp->reset(pos);
      freeList.pop_front();
      bulletList.push_back(temp);
   }
}

Bullets::Bullets():
   bulletList(),
   freeList(),
   timeSinceLastFrame(0)
{}

Bullets::Bullets(const Bullets& b):
   bulletList(b.bulletList),
   freeList(b.freeList),
   timeSinceLastFrame(b.timeSinceLastFrame)
{}

void Bullets::update(Uint32 ticks){
   timeSinceLastFrame += ticks;
   std::list<Bullet*>::iterator it = bulletList.begin();
   while(it != bulletList.end()){
      (*it)->update(ticks);
      if ((*it)->ifOut()){
         freeList.push_back(*it);
         it = bulletList.erase(it);
      }else
         ++it;
   }
}

void Bullets::draw() const {
   std::list<Bullet*>::const_iterator it = bulletList.begin();
   while(it!= bulletList.end()){
      (*it)->draw();
      ++it;
   }
}


Bullets::~Bullets(){
   std::list<Bullet*>::iterator it;
   for(it = bulletList.begin(); it != bulletList.end(); ++it){
      delete *it;
   }
   bulletList.clear();
   for(it = freeList.begin(); it != freeList.end(); ++it)
      delete *it;
   freeList.clear();
}

