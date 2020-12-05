# Color Quantization Using KMeans Clustering

Applied KMeans Clustering on the image pixels and obtaining 16 colors clusters which is used to replace the color value with the nearest cluster centroid.

Centroid Initialization is done using Random Initialization

[Sklearn Guide on Color Quantization using K-Means](https://scikit-learn.org/stable/auto_examples/cluster/plot_color_quantization.html)

Need To Comment Code ..

## Usage
- [Install OpenCV for C++](https://opencv.org/releases/)
- `mkdir build && cd build`
- `cmake ..`
- `make`
- `./main <image path>`

 Original Image             |   Quantized Image with 16 clusters
:------------------------: |:------------------------:
![Richard_Hendricks](Richard_Hendricks.jpg) |  ![Compressed_Richard_Hendricks](compressImage.jpg)
