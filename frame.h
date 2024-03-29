#ifndef FRAME__H
#define FRAME__H

#include <iostream>
#include <string>
#include <SDL.h>

class Frame {
public:
  // The next constructor s/ only be used when the Frames's surface
  // starts at (0, 0) in the sprite sheet, and the frame uses the
  // entire sheet. For example, a Frame containing a background.
  // The surface is passed from FrameFactory and width & height
  // are obtained using the XML file.
  Frame( const std::string&, SDL_Surface*);

  // The next constructor is for a MultiSprite, a multi-frame sprite.
  // The sprite sheet surface is passed as a parameter, and this
  // constructor will extract a part of the surface for the MultiSprite.
  // Therefore, this constructor should be used when the Frame's surface
  // is found on only a part of sprite sheet, src_x and src_y are passed,
  // as parameters, but width and height is in XML:
  Frame( SDL_Surface*, const std::string& name );

  Frame(SDL_Surface*, Uint16 w, Uint16 h, Sint16 src_x, Sint16 src_y);

  Frame(const Frame&);
  Frame& operator=(const Frame&);

  //We're storing the surface in the FrameFactory for consistency.
  // Therefore, this class stores nothing on the heap, and object
  // deletion will be faster if the system does it.
  //~Frame() { ; }

  SDL_Surface* getSurface() const { return surface; }
  void draw(Sint16 x, Sint16 y) const;
  void draw(Sint16 x, Sint16 y, double angle) const;
  void draw(Sint16 sx, Sint16 sy, Sint16 dx, Sint16 dy) const;

  Uint16 getWidth()  const { return width; }
  Uint16 getHeight() const { return height; }

  Uint16 getSourceX() const {return sourceX;}
  Uint16 getSourceY() const {return sourceY;}
  void setSurface(SDL_Surface* s){surface = s;}

private:
  SDL_Surface * screen;
  Uint16 width;
  Uint16 height;
  SDL_Surface * surface;
  Sint16 sourceX;
  Sint16 sourceY;

  Frame();
};

#endif
