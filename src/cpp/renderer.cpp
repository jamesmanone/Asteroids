#include "renderer.h"

Renderer::vertex const Renderer::vertex::operator+(Renderer::vertex const &b) {
  return Renderer::vertex(x+b.x, y+b.y);
}

uint32_t Renderer::getFrame() {
  return (uint32_t)screen.getFrame();
}

uint8_t Renderer::getRand() {
  if(rval == 0) rval = rand();
  uint8_t r = rval & 0xFF;
  rval >>= 8;
  return r;
}

void Renderer::randomFrame() {
  for(int x = 0; x < w; ++x) for(int y = 0; y < h; ++y) {
    Screen::pixel p(getRand(), getRand(), getRand());
    screen.setPixel(x, y, p);
  }
  screen.print();
}

void Renderer::geometryTestFrame() {
  Screen::pixel fill(0x10, 0x10, 0x10),
                blank(0, 0, 0),
                c1(0x80, 0x00, 0xFF),
                c2(0xFF, 0x00, 0x80),
                c3(0xFF, 0x6A, 0x00),
                c4(0x00, 0xCF, 0x15),
                c5(0x00, 0xCF, 0xC8),
                white(0xFF, 0xFF, 0xFF);

  screen.clearFrame(blank);



  fillRect((int)w*0.05, (int)h*0.05, (int)w*0.9, (int)h*0.9, fill);


  drawLine(0, 0, w, h, c1);
  drawLine(0, h, w, 0, c1);
  drawLine(w/2, 0, w/2, h, c1);

  drawRect((int)w*0.3, (int)h*0.3, (int)w*0.4, (int)h*0.4, 4, c2);

  int yl{static_cast<int>(h*0.7)}, yh{static_cast<int>(h*0.3)},
      xl{static_cast<int>(w*0.3)}, xr{static_cast<int>(w*0.7)},
      r{static_cast<int>(h*0.05)};

  fillCircle(xl, yl, r, c3);
  fillCircle(xr, yl, r, c3);
  drawCircle(xl, yh, r, c4);
  drawCircle(xr, yh, r, c4);

  drawCircle(0, h/2, h/2, c5);
  drawCircle(0, h/2, h/2 -1, c5);
  drawCircle(w, h/2, h/2, c5);
  drawCircle(w, h/2, h/2 -1, c5);

  std::vector<vertex> vert{
    vertex(0, -12),
    vertex(10, 10),
    vertex(10, 12),
    vertex(8, 12),
    vertex(8, 10),
    vertex(5, 5),
    vertex(-5, 5),
    vertex(-8, 10),
    vertex(-8, 12),
    vertex(-10, 12),
    vertex(-10, 10)
  };

  drawPath(w/2, h*0.75, vert, white);


  screen.print();
}

// Bresenham's line algorithm
void Renderer::drawLine(int x0, int y0, int x1, int y1, Screen::pixel &dot) {
  const bool steep = abs(y1-y0) > abs(x1-x0);
  if(steep) {
    std::swap(x0, y0);
    std::swap(x1, y1);
  }
  if(x0 > x1) {
    std::swap(x0, x1);
    std::swap(y0, y1);
  }

  const int dx{x1-x0}, dy{abs(y1-y0)}, ystep = y0 < y1 ? 1 : -1;
  float e{dx/2.0f};

  while(x0 <= x1) {
    if(steep) screen.setPixel(y0, x0, dot);
    else screen.setPixel(x0, y0, dot);

    e -= dy;
    if(e < 0) {
      y0 += ystep;
      e += dx;
    }
    ++x0;
  }

}

void Renderer::drawRect(int x, int y, int w, int h, Screen::pixel &dot) {
  const int xMax = x+w>this->w ? this->w : x+w,
            yMax = y+h>this->h ? this->h : y+h;

  // Top and bottom
  for(int i = x; i <= xMax; ++i){
    screen.setPixel(i, y, dot);
    screen.setPixel(i, yMax, dot);
  } 
  // Left and right
  for(int i = y; i <= yMax; ++i) {
    screen.setPixel(x, i, dot);
    screen.setPixel(xMax, i, dot);
  }
}

void Renderer::drawRect(int x, int y, int w, int h, int t, Screen::pixel &dot) {
  if(t == 0) return;
  while(t-- != 0) {
    drawRect(x++, y++, w, h, dot);
    w -= 2;
    h -= 2;
  }
}

void Renderer::fillRect(int x, int y, int w, int h, Screen::pixel &dot) {
  const int xMax = x+w>this->w ? this->w : x+w,
            yMax = y+h>this->h ? this->h : y+h;

  while(y <= yMax) {
    for(int i = x; i <= xMax; ++i) screen.setPixel(i, y, dot);
    ++y;
  }
}

void Renderer::drawCircle(int xc, int yc, int r, Screen::pixel &dot) {
  int d{3 - (2 * r)}, x{0}, y{r};

  while(x <= y) {
    if(d <= 0) d += (4 * x) + 6;
    else {
      d += (4 * x) - (4 * y) + 10;
      --y;
    }
    ++x;

    screen.setPixel(x+xc, y+yc, dot);
    screen.setPixel(x+xc, -y+yc, dot);
    screen.setPixel(-x+xc, -y+yc, dot);
    screen.setPixel(-x+xc, y+yc, dot);
    screen.setPixel(y+xc, x+yc, dot);
    screen.setPixel(y+xc, -x+yc, dot);
    screen.setPixel(-y+xc, -x+yc, dot);
    screen.setPixel(-y+xc, x+yc, dot);
  }
}

void Renderer::fillCircle(int x, int y, int r, Screen::pixel &dot) {
  for(float dy = 1; dy <= r; ++dy) {
    const float dx = floor(sqrt((2.0f * r * dy) - (dy * dy)));
    drawLine(x - dx, y + dy - r, x + dx, y + dy - r, dot);
    drawLine(x - dx, y - dy + r, x + dx, y - dy + r, dot);
  }
}

void Renderer::drawPath(int x, int y, std::vector<Renderer::vertex> &vert, Screen::pixel &dot) {
  Renderer::vertex offset(x, y);
  for(int i = 0; i < vert.size() - 1; ++i) {
    const Renderer::vertex  s = offset + vert[i],
                            e = offset + vert[i+1];
    drawLine(s.x, s.y, e.x, e.y, dot);
  }
  const Renderer::vertex  s = offset + vert[0],
                          e = offset + vert[vert.size() - 1];
  drawLine(s.x, s.y, e.x, e.y, dot);
}

