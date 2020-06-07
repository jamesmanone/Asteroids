#include "renderer.h"
#include <emscripten/bind.h>
// #include <chrono>
// #include <thread>

EMSCRIPTEN_BINDINGS(renderer) {
  emscripten::class_<Renderer>("Renderer")
    .constructor<int, int>()
    .function("getFrame", &Renderer::getFrame)
    .function("randomFrame", &Renderer::randomFrame)
    .function("geometryTestFrame", &Renderer::geometryTestFrame);
};
// Renderer renderer(1280, 720);

// int main() {
//   // auto last = std::chrono::high_resolution_clock::now();
//   while(1) {
//     renderer.randomFrame();
//     // auto d = std::chrono::duration<std::milli>(last - std::chrono::high_resolution_clock::now()).count();
//     std::this_thread::sleep_for(std::chrono::milliseconds(15));
//   }
// }
