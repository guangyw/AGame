#include "stones.h"
#include <iostream>
//#include "stonesprite.h"

Stones::Stones():
   stoneList(),
   freeList()
{}

Stones::Stones(const Stones& ss):
   stoneList(ss.stoneList),
   freeList(ss.freeList)
{}

Stones::~Stones(){
   std::list<StoneSprite*>::iterator it;
   if (!stoneList.empty()){
      it = stoneList.begin();
      while (it != stoneList.end()){
         delete (*it);
         ++it;
      }
   }

   if (!freeList.empty()){
      it = freeList.begin();
      while (it != stoneList.end()){
         delete (*it);
         ++it;
      }
   }
}

void Stones::gen(const Vector2f& pos, const Vector2f& velo){
   std::cout<<pos<<":"<<velo<<std::endl;
   if (freeList.empty()){
      std::cout<<"making new stone"<<std::endl;
      StoneSprite* temp = new StoneSprite(pos, velo);
      stoneList.push_back(temp);
      std::cout<<"stonelist size:"<<stoneList.size()<<std::endl;
   }else{
      StoneSprite* temp = freeList.front();
      temp->reset(pos, velo);
      freeList.pop_front();
      stoneList.push_back(temp);
   }
}

void Stones::update(Uint32 ticks){
   std::list<StoneSprite*>::iterator it = stoneList.begin();
   while(it != stoneList.end()){
      (*it)->update(ticks);
      if ((*it)->ifOut()){
         freeList.push_back(*it);
         it = stoneList.erase(it);
      }else{
         ++it;
      }
   }
}

void Stones::draw() const {
   std::list<StoneSprite*>::const_iterator it = stoneList.begin();
   while (it != stoneList.end()){
      (*it)->draw();
      ++it;
   }
}

