#include <iostream>
#include <emscripten/emscripten.h>

extern "C" EMSCRIPTEN_KEEPALIVE
int add(int a, int b) {
  return a + b;
}



int main() {
  std::cout << "Hello, World!" << std::endl;
  return 0;
}

