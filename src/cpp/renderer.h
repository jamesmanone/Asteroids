#ifndef RENDERER_H
#define RENDERER_H
#include "screen.h"
#include <random>
#include <vector>

class Renderer {
public:
  Renderer(int w, int h) : h(h), w(w), screen(w, h), rand(std::mt19937(std::time(0))) { }
  ~Renderer();

  struct vertex {
    int x;
    int y;
    vertex(int _x, int _y) { x = _x; y = _y; };
    vertex const operator+(vertex const &b);
  };
  

  uint32_t getFrame();
  void randomFrame();
  void drawLine(int x0, int y0, int x1, int y1, Screen::pixel &dot);
  void geometryTestFrame();
  void drawRect(int x, int y, int w, int h, Screen::pixel &dot);
  void fillRect(int x, int y, int w, int h, Screen::pixel &dot);
  void drawRect(int x, int y, int w, int h, int t, Screen::pixel &dot);
  void drawCircle(int xc, int yc, int r, Screen::pixel &dot);
  void fillCircle(int x, int y, int r, Screen::pixel &dot);
  void drawPath(int x, int y, std::vector<Renderer::vertex> &vert, Screen::pixel &dot);
private:
  uint8_t getRand();
  Screen screen;
  int w;
  int h;
  std::mt19937 rand;
  uint32_t rval{0};
};

#endif