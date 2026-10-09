#include <cmath>
#include <random>
#include <vector>

template <typename datatype>
class KMeans {
  int init;  //    Number of time the k-means algorithm will be run with
             //    different centroid seeds. The final results will be the best
             //    output of n_init consecutive runs in terms of inertia/cost.
  int cluster;  // number of clusters to create
  int iter;  /// number iteration to run the training algo //i.e assigncluster
             /// and new centroid function
  std::mt19937 rng;  // random generator shared by all methods (like self.rng)

  float cost(const std::vector<std::vector<float>>& centroid,
             const std::vector<int>& labels,
             const std::vector<std::vector<datatype>>& points);
  std::vector<std::vector<float>> centroidInitialization(
      const std::vector<std::vector<datatype>>& points, int n_init,
      int no_of_cluster);
  void assignCluster(const std::vector<std::vector<float>>& centroid,
                     std::vector<int>& labels,
                     const std::vector<std::vector<datatype>>& points);
  float euclideanDistance(const std::vector<datatype>& xPoint,
                          const std::vector<float>& yPoint);
  void newCentroid(std::vector<std::vector<float>>& centroid,
                   const std::vector<int>& labels,
                   const std::vector<std::vector<datatype>>& points);

  // float

 public:
  KMeans(int n_Cluster = 8, int n_init = 10, int max_iter = 300) {
    cluster = n_Cluster;
    init = n_init;
    iter = max_iter;
    rng.seed(std::random_device{}());  // seed once from OS randomness
  };

  std::vector<int> labels_;  // Labels of each point [n_samples  * 1]
  std::vector<std::vector<float>>
      centroid_;  // Coordinates of cluster centers [n_Cluster * n_Feature]

  float inertia_;

  void fit(const std::vector<std::vector<datatype>>& train);
  void predict(const std::vector<std::vector<datatype>>& predict);
};

// Non Class Function :

// finds the index of minimum element in an array [Done]
int minIndex(float main_array[], int array_size) {
  float minimum = main_array[0];
  int index_min = 0;

  for (int i = 1; i < array_size; i++) {
    if (main_array[i] < minimum) {
      minimum = main_array[i];
      index_min = i;
    }
  }
  return index_min;
}

// adds two vector and  is assigned to vector passed in arg1; [Done]
template <typename datatype>
void add_vectors(std::vector<float>& xPoint,
                 const std::vector<datatype>& yPoint) {
  for (int i = 0; i < xPoint.size(); i++) {
    xPoint[i] = xPoint[i] + yPoint[i];
  }
}

// Class Function Declaration :
/// euclidean Distance of xpoint [1d vector] and centroid i.e yPoint [1d
/// vector];
template <typename datatype>
float KMeans<datatype>::euclideanDistance(const std::vector<datatype>& xPoint,
                                          const std::vector<float>& yPoint) {
  float Edistance = 0;
  int no_of_feature;  // n ...

  /* Trying to Implement : Pseudo Code
      Edistance += (xPoint[i] - yPoint[i]) ^ 2;
  */
  for (int i = 0; i < xPoint.size(); i++) {
    Edistance += pow((xPoint[i] - yPoint[i]), 2.0);
  }
  Edistance = sqrt(Edistance);

  return Edistance;
}

/// assigns cluster id to the given points; [Done]
template <typename datatype>
void KMeans<datatype>::assignCluster(
    const std::vector<std::vector<float>>& centroid, std::vector<int>& labels,
    const std::vector<std::vector<datatype>>& points) {
  /* To Implement  : Pseudo Code
  for i to m {

      for j to no_of_centroid{
          distance[k] = euclideanDistance(points[i],centroid[j])
      }
      labels[i] = indexof(min(distance)) // the index is the cluster ID

  }
  */
  int no_of_train = points.size();  // m
  int no_of_centroid = centroid.size();

  labels.clear();  // clearing the vector
  for (int i = 0; i < no_of_train; i++) {
    float* distance = new float[no_of_centroid];
    for (int j = 0; j < no_of_centroid; j++) {
      distance[j] = euclideanDistance(points[i], centroid[j]);
    }
    labels.push_back(
        minIndex(distance, no_of_centroid));  // indexof(min(distance))
    delete[] distance;
  }
}

// Uses centroid formula to calculate new centroid ; [....Done]
template <class datatype>
void KMeans<datatype>::newCentroid(
    std::vector<std::vector<float>>& centroid, const std::vector<int>& labels,
    const std::vector<std::vector<datatype>>& points) {
  /* trying to implement
  for i to k{
      // find all the labels with value i and their index // cluster_I_index //
      // sumOfPoints With i value = sum all the points of label i
      //newCentroid =  sumOfPoints / len(cluster_I_index)
      //centroid[i] = newCentroid
  }
  */
  int no_of_centroid = centroid.size();  // k
  int no_of_trains = labels.size();
  int no_of_feature = points[0].size();

  for (int k = 0; k < no_of_centroid; k++) {
    std::vector<float> sum_of_points_k;

    for (int i = 0; i < no_of_feature; i++) {
      sum_of_points_k.push_back(0.0);
    }

    int count_k = 0;

    for (int m = 0; m < no_of_trains; m++) {
      if (labels[m] == k) {
        add_vectors(sum_of_points_k,
                    points[m]);  // sum_of_points_k += points[m];
        count_k += 1;
      }
    }

    if (count_k == 0) {
      continue;  // Skip updating this centroid
    }

    for (int j = 0; j < centroid[k].size(); j++) {
      centroid[k][j] = sum_of_points_k[j] / count_k;
    }
    sum_of_points_k.clear();
  }
}

// private functions :
// Returns the cost [Done]
template <class datatype>
float KMeans<datatype>::cost(const std::vector<std::vector<float>>& centroid,
                             const std::vector<int>& labels,
                             const std::vector<std::vector<datatype>>& points) {
  float cost_value = 0;

  int no_of_feature = points[0].size();  // n
  int no_of_train = points.size();       // m

  for (int m = 0; m < no_of_train; m++) {
    cost_value += pow(euclideanDistance(points[m], centroid[labels[m]]), 2.0);
  }

  cost_value = cost_value / (no_of_train * 1.0);

  return cost_value;
}

template <class datatype>
std::vector<std::vector<float>> KMeans<datatype>::centroidInitialization(
    const std::vector<std::vector<datatype>>& points, int n_init,
    int no_of_cluster) {
  /*
  [Implement]
  for i to n_init{

      for index,c in randomCentroidIndex{
          centroid[index] = points[c];

      }

      labels = assignCluster(centriod,points);
      centroid = newCentroid(centriod,labels,points);

      J = cost(centriod,labels,points);

      arrayOfCentroid.push_back(centriod); ///3d vector
      arrayOfJ.push_back(J);

  }

  centroidIndex = minIndex(arrayOfJ,n_init)
  finalCentroid = arrayOfCentroid[centroidIndex]

  //
  https://riptutorial.com/cplusplus/example/11151/find-max-and-min-element-and-respective-index-in-a-vector

  */

  std::vector<std::vector<std::vector<float>>> vectorOfCentroid;

  float* arrayOfJ = new float[n_init];

  int no_of_feature = points[0].size();

  std::vector<std::vector<float>> randomCentroid;
  // random index in [0, number of points - 1], like rng.integers(0, n)
  std::uniform_int_distribution<size_t> pick(0, points.size() - 1);

  for (int i = 0; i < n_init; i++) {
    float cost_value = 0;
    randomCentroid.clear();

    // start each centroid on a random real pixel, so no cluster starts empty
    for (int k = 0; k < no_of_cluster; k++) {
      const std::vector<datatype>& p = points[pick(rng)];
      randomCentroid.push_back(std::vector<float>(p.begin(), p.end()));
    }

    assignCluster(randomCentroid, labels_, points);

    newCentroid(randomCentroid, labels_, points);
    cost_value = cost(randomCentroid, labels_, points);

    vectorOfCentroid.push_back(std::vector<std::vector<float>>());

    for (int p = 0; p < randomCentroid.size(); p++) {
      vectorOfCentroid[i].push_back(std::vector<float>());
      for (int q = 0; q < no_of_feature; q++) {
        vectorOfCentroid[i][p].push_back(randomCentroid[p][q]);
      }
    }

    arrayOfJ[i] = cost_value;

    labels_.clear();
  }

  int centroidIndex = minIndex(arrayOfJ, n_init);

  std::vector<std::vector<float>> finalCentroid =
      vectorOfCentroid[centroidIndex];

  delete[] arrayOfJ;

  return finalCentroid;
}

// Public Functions
// fits the train example ,,and sets the optimal final centroid
template <class datatype>
void KMeans<datatype>::fit(const std::vector<std::vector<datatype>>& train) {
  centroid_ = centroidInitialization(train, init, cluster);

  for (int i = 0; i < iter; i++) {
    assignCluster(centroid_, labels_, train);
    newCentroid(centroid_, labels_, train);
  }
  assignCluster(centroid_, labels_, train);
  inertia_ = cost(centroid_, labels_, train);  // once, after training
}

template <class datatype>
void KMeans<datatype>::predict(
    const std::vector<std::vector<datatype>>& predict) {
  assignCluster(centroid_, labels_, predict);
  inertia_ = cost(centroid_, labels_, predict);
}
