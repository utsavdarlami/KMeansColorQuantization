#include <emscripten/bind.h>
#include <emscripten/val.h>
#include <cstdint>
#include <vector>

using namespace emscripten;

val invert(val input){
  std::vector<uint8_t> data = convertJSArrayToNumberVector<uint8_t>(input);
  for (size_t i = 0; i < data.size(); i++){
    if (i % 4 == 3) continue; // Skip alpha channel
    data[i] = 255 - data[i];
  }
  return val::array(data);
}


EMSCRIPTEN_BINDINGS(invert_module) {
  function("invert", &invert);
}
