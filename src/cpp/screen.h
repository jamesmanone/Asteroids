#ifndef SCREEN_H
#define SCREEN_H
#include <cstdint>
#include <memory>

class Screen {
public:
  Screen(int w, int h);
  ~Screen();

  struct pixel {
    uint8_t r;
    uint8_t g;
    uint8_t b;
    uint8_t a;
    pixel(uint8_t r, uint8_t g, uint8_t b) : pixel(r, g, b, 0xFF) { }
    pixel(uint8_t r, uint8_t g, uint8_t b, uint8_t a) : r(r), g(g), b(b), a(a) { }
    uint32_t const toBytes();
  };

  uint8_t* getFrame();
  void setPixel(int x, int y, Screen::pixel &val);
  Screen::pixel getPixel(int x, int y);
  void clearFrame(Screen::pixel &val);
  void print();

private:
  static void rotate(uint32_t &n);
  int w;
  int h;
  int l;
  std::unique_ptr<uint8_t[]> working;
  std::unique_ptr<uint8_t[]> ready;
};

#endif