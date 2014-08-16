#include "frameFactory.h"
#include "extractSurface.h"
#include "ioManager.h"
#include "vector2f.h"
#include <SDL/SDL.h>
#include <SDL_ttf.h>
#include <iostream>
#include <sstream>
#include <SDL/SDL_rotozoom.h>

inline float randFloatBetween(float low, float high){
   float random = ((float) rand()) / (float) RAND_MAX;
   float diff = high - low;
   float inc = random * diff;
   return low + inc;
}


FrameFactory::~FrameFactory() {
  std::cout << "Deleting FrameFactory" << std::endl;
  std::map<std::string, SDL_Surface*>::iterator itSurf = surfaces.begin();
  while ( itSurf != surfaces.end() ) {
    SDL_FreeSurface( itSurf->second );
    ++itSurf;
  }
  std::map<std::string, std::vector<SDL_Surface*> >::iterator
    surfaces = multiSurfaces.begin();
  while ( surfaces != multiSurfaces.end() ) {
    for (unsigned int i = 0; i < surfaces->second.size(); ++i) {
      SDL_FreeSurface( surfaces->second[i] );
    }
    ++surfaces;
  }
  surfaces = twoWaySurfaces.begin();
  while ( surfaces != twoWaySurfaces.end() ) {
    for (unsigned int i = 0; i < surfaces->second.size(); ++i) {
      SDL_FreeSurface( surfaces->second[i] );
    }
    ++surfaces;
  }
  std::map<std::string, Frame*>::iterator frame = frames.begin();
  while ( frame != frames.end() ) {
    delete frame->second;
    ++frame;
  }
  std::map<std::string, std::vector<Frame*> >::iterator
    frames = multiFrames.begin();
  while ( frames != multiFrames.end() ) {
    for (unsigned int i = 0; i < frames->second.size(); ++i) {
      delete frames->second[i];
    }
    ++frames;
  }

  frames = twoWayFrames.begin();
  while ( frames != twoWayFrames.end() ) {
    for (unsigned int i = 0; i < frames->second.size(); ++i) {
      delete frames->second[i];
    }
    ++frames;
  }
}

FrameFactory& FrameFactory::getInstance() {
  static FrameFactory factory;
  return factory;
}

Frame* FrameFactory::getFrame(const std::string& name) {
    std::map<std::string, Frame*>::const_iterator pos = frames.find(name);
  if ( pos == frames.end() ) {
    SDL_Surface * const surface =
      IOManager::getInstance().loadAndSet(
          gdata.getXmlStr(name+"File"),
          gdata.getXmlBool(name+"Transparency"));
    surfaces[name] = surface;
    Frame * const frame =new Frame(name, surface);
    frames[name] = frame;
    return frame;
  }
  else {
    return pos->second;
  }
}


std::vector<Frame*> FrameFactory::getFrames(const std::string& name) {
  // First search map to see if we've already made it:
  std::map<std::string, std::vector<Frame*> >::const_iterator
    pos = multiFrames.find(name);
  if ( pos != multiFrames.end() ) {
    return pos->second;
  }

  // It wasn't in the map, so we have to make the vector of Frames:
  SDL_Surface* surface = IOManager::
     getInstance().loadAndSet(gdata.getXmlStr(name+"File"), true);
  unsigned numberOfFrames = gdata.getXmlInt(name+"Frames");
  std::vector<Frame*> frames;
  std::vector<SDL_Surface*> surfaces;
  frames.reserve(numberOfFrames);
  Uint16 srcX = gdata.getXmlInt(name+"SrcX");
  Uint16 srcY = gdata.getXmlInt(name+"SrcY");
  Uint16 width = gdata.getXmlInt(name+"Width");
  Uint16 height = gdata.getXmlInt(name+"Height");

  SDL_Surface* surf;
  for (unsigned i = 0; i < numberOfFrames; ++i) {
    unsigned frameX = i * width + srcX;
   surf = ExtractSurface::getInstance().
               get(surface, width, height, frameX, srcY);
    surfaces.push_back( surf );
    frames.push_back( new Frame(surf, name) );
  }
  SDL_FreeSurface(surface);
  multiSurfaces[name] = surfaces;
  multiFrames[name] = frames;
  return frames;
}


std::vector<Frame*> FrameFactory::getRandFrames(const std::string& name, const int speed) {
  SDL_Surface* surface = IOManager::
     getInstance().loadAndSet(gdata.getXmlStr(name+"File"), true);
  unsigned numberOfFrames = gdata.getXmlInt(name+"Frames");
  std::vector<Frame*> frames;
  std::vector<SDL_Surface*> surfaces;
  frames.reserve(numberOfFrames);
  Uint16 srcX = gdata.getXmlInt(name+"SrcX");
  Uint16 srcY = gdata.getXmlInt(name+"SrcY");
  Uint16 width = gdata.getXmlInt(name+"Width");
  Uint16 height = gdata.getXmlInt(name+"Height");

  float randZoom = -(float)(speed) / (float) 150;
  SDL_Surface* surf;
  for (unsigned i = 0; i < numberOfFrames; ++i) {
    unsigned frameX = i * width + srcX;
   surf = ExtractSurface::getInstance().
               get(surface, width, height, frameX, srcY);
   SDL_Surface* pic;
   pic = zoomSurface(surf, randZoom, randZoom, SMOOTHING_ON);
    surfaces.push_back(pic);
    frames.push_back( new Frame(pic, name) );
  }
  SDL_FreeSurface(surface);
  SDL_FreeSurface(surf);
  multiSurfaces[name] = surfaces;
  multiFrames[name] = frames;
  return frames;
}

std::vector<Frame*> FrameFactory::getTwoWayFrames(const std::string& name) {
  // First search map to see if we've already made it:
  std::map<std::string, std::vector<Frame*> >::const_iterator
    pos = twoWayFrames.find(name);
  if ( pos != twoWayFrames.end() ) {
    return pos->second;
  }

  // It wasn't in the map, so we have to make the two vector of Frames:
  SDL_Surface* surface = IOManager::
     getInstance().loadAndSet(gdata.getXmlStr(name+"File"), true);
  unsigned numberOfFrames = gdata.getXmlInt(name+"Frames");
  std::vector<Frame*> frames;
  std::vector<SDL_Surface*> surfaces;
  frames.reserve(numberOfFrames);
  Uint16 srcX = gdata.getXmlInt(name+"SrcX");
  Uint16 srcY = gdata.getXmlInt(name+"SrcY");
  Uint16 width = gdata.getXmlInt(name+"Width");
  Uint16 height = gdata.getXmlInt(name+"Height");

  SDL_Surface* surf;
  for (unsigned i = 0; i < numberOfFrames/2; ++i) {
    unsigned frameX = i * width + srcX;
   surf = ExtractSurface::getInstance().
               get(surface, width, height, frameX, srcY);
    surfaces.push_back( surf );
    frames.push_back( new Frame(surf, name) );
  }
  for (unsigned i = numberOfFrames/2; i < numberOfFrames; ++i){
   unsigned frameX = i * width + srcX;

   surf = ExtractSurface::getInstance().
               get(surface, width, height, frameX, height + srcY);
    surfaces.push_back( surf );
    frames.push_back( new Frame(surf, name) );
  }
  SDL_FreeSurface(surface);
  twoWaySurfaces[name] = surfaces;
  twoWayFrames[name] = frames;
  return frames;
}
