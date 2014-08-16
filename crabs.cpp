#include "crabs.h"
#include <iostream>

int Crabs::countFree() const{
   return freeList.size();
}

int Crabs::countCrab() const{
   return crabList.size();
}

void Crabs::gen(){
   if (freeList.empty()){
      CrabSprite* temp = new CrabSprite();
      crabList.push_back(temp);
   }else{
      CrabSprite* temp = freeList.front();
      temp->reset();
      freeList.pop_front();
      crabList.push_back(temp);
   }
}

Crabs::Crabs():
   crabList(),
   freeList(),
   timeSinceLastFrame(0)
{}

Crabs::Crabs(const Crabs& c):
   crabList(c.crabList),
   freeList(c.freeList),
   timeSinceLastFrame(c.timeSinceLastFrame)
{}


void Crabs::update(Uint32 ticks){
   timeSinceLastFrame += ticks;
   std::list<CrabSprite*>::iterator it = crabList.begin();
   while(it != crabList.end()){
      (*it)->update(ticks);
      if ((*it)->ifOut()){
         freeList.push_back(*it);
         it = crabList.erase(it);
      }else
         ++it;
   }
}

void Crabs::draw() const {
   std::list<CrabSprite*>::const_iterator it = crabList.begin();
   while(it != crabList.end()){
      (*it)->draw();
      ++it;
   }
}


Crabs::~Crabs(){
   std::list<CrabSprite*>::iterator it;
   for(it = crabList.begin(); it != crabList.end(); ++it){
      delete *it;
   }
   crabList.clear();
   for(it = freeList.begin(); it != freeList.end(); ++it){
      delete *it;
   }
   freeList.clear();
}

void Crabs::deleteOne(){
   freeList.push_back(crabList.back());
   crabList.pop_back();
}
