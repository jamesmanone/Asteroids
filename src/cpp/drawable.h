#ifndef DRAWABLE_H
#define DRAWABLE_H
#include <vector>

class Drawable {
public:
  Drawable();
  ~Drawable();

  struct Vertex {
    float x;
    float y;
    inline Vertex(float _x, float _y) { x = _x; y = _y; };
    Vertex scale(float m);
  };

  virtual std::vector<std::vector<Vertex>>getDrawPaths() = 0;
private:
  std::vector<std::vector<Vertex>> vert;
};

#endif