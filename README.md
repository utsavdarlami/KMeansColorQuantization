# Color Quantization Using KMeans Clustering

**[Live demo](https://utsavdarlami.github.io/KMeansColorQuantization/web/)**: the same C++ k-means compiled to WebAssembly and running in your browser. Upload an image and drag *k* to change the number of colors. Images never leave your machine.

Applied KMeans Clustering on the image pixels and obtaining *k* color clusters, which are used to replace each pixel's color with the nearest cluster centroid.

- `KMeans.h`: header-only k-means written from scratch, standard library only (`fit`, `predict`, `n_init` restarts keeping the lowest-cost run).
- Centroid initialization picks *k* random pixels from the image. k-means++ was tested too: about 5% lower cost on the sample image, not worth the extra code.

[Sklearn Guide on Color Quantization using K-Means](https://scikit-learn.org/stable/auto_examples/cluster/plot_color_quantization.html)

## Usage (native, OpenCV)
- [Install OpenCV for C++](https://opencv.org/releases/)
- `mkdir build && cd build`
- `cmake ..`
- `make`
- `./main <image path>`

## Web demo (WebAssembly)
- [Install Emscripten](https://emscripten.org/docs/getting_started/downloads.html), then `source ~/emsdk/emsdk_env.sh`
- Build (from the repo root):
  ```
  em++ -O3 web/quantize.cpp -o web/quantize.js -lembind -sMODULARIZE -sEXPORT_NAME=createQuantizeModule -sALLOW_MEMORY_GROWTH
  em++ -O3 web/invert.cpp -o web/invert.js -lembind -sMODULARIZE -sEXPORT_NAME=createInvertModule
  ```

How it works: the canvas gives the image as RGBA bytes, [embind](https://emscripten.org/docs/porting/connecting_cpp_and_javascript/embind.html) passes them to C++, `quantize` fits k-means on a ~10,000-pixel sample, labels every pixel, and returns the recolored bytes.

 Original Image             |   Quantized Image with 16 clusters
:------------------------: |:------------------------:
![Richard_Hendricks](Richard_Hendricks.jpg) |  ![Compressed_Richard_Hendricks](compressImage.jpg)
