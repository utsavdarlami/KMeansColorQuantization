#include <iostream>
#include <ctime>
#include <unistd.h>
#include<vector>
template<typename datatype>
class KMeans
{
    int init; //    Number of time the k-means algorithm will be run with different centroid seeds. The final results will be the best output of n_init consecutive runs in terms of inertia/cost.
    int cluster; // number of clusters to create
    int iter; /// number iteration to run the training algo //i.e assigncluster and new centroid function

    float cost(std::vector<std::vector<float>> &centroid,std::vector<int> &labels,std::vector<std::vector<datatype>> &points);
    std::vector<std::vector<float>> centroidInitialization(std::vector<std::vector<datatype>> points,int n_init,int no_of_cluster);
    void assignCluster(std::vector<std::vector<float>> centroid,std::vector<int>&labels,std::vector<std::vector<datatype>> points);
    float euclideanDistance(std::vector<datatype> xPoint,std::vector<float> yPoint);
    void newCentroid(std::vector<std::vector<float>> &centroid,std::vector<int>labels,std::vector<std::vector<datatype>> points);

    // float 

  public:

    KMeans(int n_Cluster = 8,int n_init=10,int max_iter=300){
      cluster =n_Cluster;
      init  = n_init;
      iter = max_iter;
    };

    
    std::vector<int> labels_; //Labels of each point [n_samples  * 1]
    std::vector<std::vector<float>> centroid_; // Coordinates of cluster centers [n_Cluster * n_Feature]

    float inertia_;

    void fit(std::vector<std::vector<datatype>> train);
    void predict(std::vector<std::vector<datatype>> predict);

};


// Non Class Function :

// Creates 2D vector [ rows * cols ] with random float value containing at maximum a value of max_value.  [Done]
std::vector<std::vector<float>> randomVector(int rows,int cols,float max_value){
 
    sleep(1.0);
    std::vector<std::vector<float>> random_vec;
    
    srand((unsigned)time(0)); 
     
    for(int i=0; i<rows; i++){ 
        random_vec.push_back(std::vector<float>());
        for(int j=0; j<cols; j++){ 
            random_vec[i].push_back(rand()%int(max_value+1)); 
        }
        // std::cout << arr[i] << std::endl;
    } 
    return random_vec;
}

// finds the index of minimum element in an array [Done]
int minIndex(float main_array[],int array_size){
    float minimum = main_array[0];
    int index_min=0;

    for (int i=1; i<array_size; i++)
    {
        if (main_array[i] < minimum)
        {
            minimum = main_array[i];
            index_min = i;
        }
    }
    // std::cout<<"Min Index : "<<index_min<<std::endl;
    return index_min;

}

// adds two vector and  is assigned to vector passed in arg1; [Done]
template<typename datatype>
void add_vectors(std::vector<float> &xPoint,std::vector<datatype> yPoint){

    for(int i=0;i<xPoint.size();i++)
    {        
        // std::cout<<" "<<xPoint[i]<<"    "<<yPoint[i]<<std::endl;
        xPoint[i] = xPoint[i]+yPoint[i];
    }
    /*
    for(int i=0;i<xPoint.size();i++){
        std::cout<<xPoint[i]<<" ";
    }
    std::cout<<"  "<<std::endl;
    */

}
//returns the maximum value in the vector
template<class datatype>
float max_in_vector(std::vector<std::vector<datatype>> vec){
    float temp = 0;

    for(int i = 0; i < vec.size(); i++)
        for(int j = 0; j< vec[i].size(); j++)
            if(temp < vec[i][j])
            {
                temp = vec[i][j];
            }

    // std::cout<<"Maximum Value is "<<temp<<std::endl;
    return temp;
}

// Class Function Declaration :

/// euclidean Distance of xpoint [1d vector] and centroid i.e yPoint [1d vector]; [Done ..]
template<typename datatype>
float KMeans<datatype>::euclideanDistance(std::vector<datatype> xPoint,std::vector<float> yPoint){
    float Edistance  = 0;
    int no_of_feature ; //n ... 

    /* Trying to Implement : Pseudo Code
    for i to n{
        Edistance += (xPoint[i] - yPoint[i]) ^ 2;
    }
    */
    for (int i = 0; i < xPoint.size(); i++) { 
        // std::cout<<xPoint[i]<<" "<<yPoint[i]<<std::endl;
        Edistance += pow((xPoint[i] - yPoint[i]),2.0);
    }
    Edistance= sqrt(Edistance);
    // std::cout<<"Euclidean Distance :" <<Edistance<<std::endl;

    return Edistance;
}

/// assigns cluster id to the given points; [Done]
template<typename datatype>
void KMeans<datatype>::assignCluster(std::vector<std::vector<float>> centroid,std::vector<int> &labels,std::vector<std::vector<datatype>> points){

    int no_of_train = points.size(); //m
    int no_of_centroid= centroid.size();

    /* To Implement  : Pseudo Code
    for i to m {
        
        for j to no_of_centroid{
            distance[k] = euclideanDistance(points[i],centroid[j])
        }
        labels[i] = indexof(min(distance)) // the index is the cluster ID 

    }
    */
    labels.clear(); // clearing the vector
    for(int i=0;i<no_of_train;i++)
    {
        float* distance= new float[no_of_centroid];
        for(int j=0;j<no_of_centroid;j++)
        {
            
            distance[j] = euclideanDistance(points[i],centroid[j]);

        }
        // minimum distance index = minIndex(distance,no_of_centroid); //indexof(min(distance))
        // labels[i]= minIndex(distance,no_of_centroid); //indexof(min(distance)) 
        labels.push_back(minIndex(distance,no_of_centroid)); //indexof(min(distance))
        delete[] distance;  
    }

    // return cluster_labels;
}

// Uses centroid formula to calculate new centroid ; [....Done]
template<class datatype>
void KMeans<datatype>::newCentroid(std::vector<std::vector<float>> &centroid,std::vector<int>labels,std::vector<std::vector<datatype>> points){
    int no_of_centroid = centroid.size();//k
    int no_of_trains = labels.size();
    int no_of_feature = points[0].size();
    
    /* trying to implement
    for i to k{
        // find all the labels with value i and their index // cluster_I_index //
        // sumOfPoints With i value = sum all the points of label i
        //newCentroid =  sumOfPoints / len(cluster_I_index)
        //centroid[i] = newCentroid
    }
    */

    for(int k=0;k<no_of_centroid;k++){
        std::vector<float> sum_of_points_k;
        
        for(int i=0;i<no_of_feature;i++){
            sum_of_points_k.push_back(0.0);
        }

        int count_k  = 0;

        for(int m=0;m<no_of_trains;m++){
            if(labels[m]==k){
                add_vectors(sum_of_points_k,points[m]);// sum_of_points_k += points[m];
                count_k+=1;
            }
            
        }
        // std::cout<<" sum : ";
        // for(int i=0;i<sum_of_points_k.size();i++)
        // {
        //     std::cout<<sum_of_points_k[i]<<" ";
        // }
        // std::cout<<"  "<<std::endl;
        
        // sum_of_points_k.clear();

        for(int j=0;j<centroid[k].size();j++){

            centroid[k][j] =  sum_of_points_k[j]/(count_k*1.0+1.0);
        
        }
        sum_of_points_k.clear();

    }
    // return centroid;
}


// private functions :
// Returns the cost [Done]
template<class datatype>
float KMeans<datatype>::cost(std::vector<std::vector<float>> &centroid,std::vector<int> &labels,std::vector<std::vector<datatype>> &points){

    // std::cout<<"Private : This Is Cost Function"<<std::endl;

    float cost_value=0;

    int no_of_feature = points[0].size(); //n
    int no_of_train= points.size(); //m

    for(int m=0;m<no_of_train;m++){
        cost_value += pow(euclideanDistance(points[m],centroid[labels[m]]),2.0);
    }
    
    cost_value = cost_value/(no_of_train*1.0);
    std::cout<<"- Cost : "<<cost_value<<std::endl;

    return cost_value;
}


template<class datatype>
std::vector<std::vector<float>> KMeans<datatype>::centroidInitialization(std::vector<std::vector<datatype>> points,int n_init,int no_of_cluster){
    
    std::vector<std::vector<std::vector<float>>> vectorOfCentroid;
   
    float* arrayOfJ= new float[n_init];
    
    int no_of_feature = points[0].size();
    
    std::cout<<"Private : Centroid Initialization "<<std::endl;
    
    float max_value = max_in_vector(points); // return 255 for image vector of 0 - 255
    std::vector<std::vector<float>> randomCentroid;

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

    // https://riptutorial.com/cplusplus/example/11151/find-max-and-min-element-and-respective-index-in-a-vector
    
    */


    for(int i=0;i<n_init;i++){
        float cost_value = 0;
        randomCentroid.clear();

        randomCentroid = randomVector(no_of_cluster,no_of_feature,max_value);
        
        /*
        std::cout<<"1 .  Random "<<std::endl;
        for (int p = 0; p < randomCentroid.size(); p++) { 
            std::cout<<p+1<<" Rc : ";
            for (int q = 0; q < no_of_feature;q++) { 

                std::cout<<randomCentroid[p][q]<<" ";
            }
            std::cout<<" "<<std::endl;
        }
        */

        assignCluster(randomCentroid,labels_,points);


        newCentroid(randomCentroid,labels_,points);

    /*
        std::cout<<".  New Centroid "<<std::endl;
 
        for (int p = 0; p < randomCentroid.size(); p++) { 
            std::cout<<p+1<<" Rc : ";
            for (int q = 0; q < no_of_feature;q++) { 
                std::cout<<randomCentroid[p][q]<<" ";
            }
            std::cout<<" "<<std::endl;
        }
        
    */
        cost_value = cost(randomCentroid,labels_,points);


        // std::cout<<"Cost : "<<costd_value<<std::endl;

        // std::cout<<i<<" --------------------------------------------------------------------"<<std::endl;
        std::cout<<" --------------------------------------------------------------------"<<std::endl;

        vectorOfCentroid.push_back(std::vector<std::vector<float>>());

        for (int p = 0; p < randomCentroid.size(); p++) { 
            // std::cout<<p+1<<" Rc : ";
            vectorOfCentroid[i].push_back(std::vector<float>());
            for (int q = 0; q < no_of_feature;q++) { 
                
                vectorOfCentroid[i][p].push_back(randomCentroid[p][q]);
                // std::cout<<randomCentroid[p][q]<<" ";
            }
            // std::cout<<" "<<std::endl;
        }


        arrayOfJ[i] = cost_value;

        labels_.clear();
    }


    int centroidIndex = minIndex(arrayOfJ,n_init) ;
    
    std::cout<<" --------------------------------------------------------------------"<<std::endl;

    std::cout<<"The Minimun Cost is At Centroid with Index : " <<centroidIndex<<std::endl;

    // std::cout<<"Vec of centroid Size : "<<vectorOfCentroid.size()<<std::endl;
    // std::cout<<"Vec of vec centroid Size : "<<vectorOfCentroid[0].size()<<std::endl;
    // std::cout<<"Vec of no of features : "<<vectorOfCentroid[0][0].size()<<std::endl;

    std::vector<std::vector<float>> finalCentroid = vectorOfCentroid[centroidIndex];

    // for (int p = 0; p < finalCentroid.size(); p++) { 
    //     std::cout<<p+1<<"----  Final Random centroid : ";
    //     for (int q = 0; q < no_of_feature;q++) { 
            
    //         std::cout<<finalCentroid[p][q]<<" ";
    //     }
    //     std::cout<<" "<<std::endl;
    // }

    delete[] arrayOfJ;  

    return finalCentroid;
    
}

// Public Functions
// fits the train example ,,and sets the optimal final centroid 
template<class datatype>
void KMeans<datatype>::fit(std::vector<std::vector<datatype>> train){

    std::cout<<"Public : Fit Function Called"<<std::endl;

    std::cout<<"Numberof Cluster : "<<cluster<<"  Number of Initialization : "<<init<<std::endl;
    std::cout<<"  Max iteration : "<<iter<<std::endl;

    

    /*
    //
    
    centroid  = centroidInitialization(train,init)
    
    for i to iter{

        labels = assignCluster(centriod,train);
        centriod = newCentroid(centriod,labels,train);

    }
    */

    // noOfPoints = train.size();

    // cost_val = cost(centroid,labels,train);

    centroid_ = centroidInitialization(train,init,cluster);

    /*
        for (int p = 0; p < centroid_.size(); p++) { 
                std::cout<<p+1<<"From Centroid  Initial  : ";
                for (int q = 0; q < centroid_[0].size();q++) { 
                    std::cout<<centroid_[p][q]<<" ";
                }
                std::cout<<" "<<std::endl;
        }
    */


    float c_v = 0.0;
    std::cout<<"# Training "<<std::endl;
    for(int i=0;i<iter;i++){


        assignCluster(centroid_,labels_,train);


        newCentroid(centroid_,labels_,train);
        

        c_v = cost(centroid_,labels_,train);



    }

    std::cout<<" Final Cost "<<std::endl;

    float cost_after_value = cost(centroid_,labels_,train);

}

template<class datatype>
void KMeans<datatype>::predict(std::vector<std::vector<datatype>> predict){
   
    std::cout<<"Predict Function Called"<<std::endl;
    inertia_ = cost(centroid_,labels_,predict);
    assignCluster(centroid_,labels_,predict);

    // return labels_ ; 
}
