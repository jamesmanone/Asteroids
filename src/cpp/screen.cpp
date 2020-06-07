#include "screen.h"
#include <stdio.h>


void Screen::rotate(uint32_t &n) {
  n = (n >> 8) | ((n & 0xFF) << 24);
}


Screen::Screen(int w, int h) : 
    w(w), h(h), working(std::make_unique<uint8_t[]>(w*h*4)),
    ready(std::make_unique<uint8_t[]>(w*h*4)), l(w*h*4) { }

Screen::~Screen() {
  printf("Destructed");
}

uint32_t const Screen::pixel::toBytes() {
  return ((uint32_t)r << 24) | ((uint32_t)g << 16) | ((uint32_t)b << 8) | (uint32_t)a;
}

uint8_t* Screen::getFrame() {
  return ready.get();
}

void Screen::setPixel(int x, int y, Screen::pixel &val) {
  if(x >= w || y >= h || x < 0 || y < 0) return; // bounds check
  int start = (y*w*4) + (x*4);
  working[start] = val.r;
  working[start+1] = val.g;
  working[start+2] = val.b;
  working[start+3] = val.a;
}

Screen::pixel Screen::getPixel(int x, int y) {
  int start = ((y*4) * (w*4)) + (x*4);
  return Screen::pixel(working[start], working[start+1], working[start+2], working[start+3]);
}

void Screen::clearFrame(Screen::pixel &val) {
  int l = w*h*4;
  uint32_t c = val.toBytes();
  for(int i = 0; i < l; ++i) {
    working[i] = (uint8_t)(c & 0xFF);
    rotate(c);
  }
}

void Screen::print() {
  ready.swap(working);
}
