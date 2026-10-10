#include <emscripten/bind.h>
#include <emscripten/val.h>

#include <algorithm>
#include <cstdint>
#include <vector>

#include "../KMeans.h"  // quotes + path: your own file, relative to this one

using namespace emscripten;

val quantize(val input, int k) {
  std::vector<uint8_t> rgba = convertJSArrayToNumberVector<uint8_t>(input);
  size_t n_pixels = rgba.size() / 4;

  // 1. TODO: all pixels as {R, G, B}
  std::vector<std::vector<int>> pixels;
  for (size_t i = 0; i < n_pixels; i++) {
    size_t idx = i * 4;
    pixels.push_back({rgba[idx], rgba[idx + 1], rgba[idx + 2]});
  }

  // 2. TODO: a sample of about 10,000 pixels
  std::vector<std::vector<int>> sample;
  // sample about 10,000 pixels evenly spaced across the image
  size_t step = std::max(size_t(1), n_pixels / 10000);
  for (size_t i = 0; i < n_pixels; i += step) {
    sample.push_back(pixels[i]);
  }

  // 3. TODO: fit on the sample, label all pixels
  KMeans<int> km(k, 3, 50);

  km.fit(sample);

  // 4. TODO: write each pixel's centroid color back into rgba
  km.predict(pixels);
  for (size_t p = 0; p < n_pixels; p++) {
    const std::vector<float>& color = km.centroid_[km.labels_[p]];
    size_t pidx = p * 4;
    rgba[pidx] = color[0];
    rgba[pidx + 1] = color[1];
    rgba[pidx + 2] = color[2];
    // rgba[p * 4 + 3] is alpha: untouched
  }

  return val::global("Uint8Array")
      .new_(typed_memory_view(rgba.size(), rgba.data()));
}

EMSCRIPTEN_BINDINGS(quantize_module) { function("quantize", &quantize); }
