#include <stdio.h>
#include <opencv2/opencv.hpp>
#include "KMeans.h"

int main(int argc, char** argv )
{
    if ( argc != 2 ) //if image path is not given [ ./main <image path> ]
    {
        printf("usage: DisplayImage.out <Image_Path>\n");
        return -1;
    }

    cv::Mat image;
    image = cv::imread( argv[1], 1 );

    if ( !image.data )
    {
        printf("No image data \n");
        return -1;
    }
    
    //for 32 * 32 * 3 image 
    int rows = image.rows; //32 ;
    int cols = image.cols;  //32  ;
    int channels =  image.channels();//3;

    std::cout<<"Rows in Image "<<rows<<std::endl;

    std::cout<<"Columns in Image "<<cols<<std::endl;

    std::cout<<"Channels in Image "<<channels<<std::endl;


    // unsigned char *pixel = image.ptr(0,0); /// x ,y .. [0,0] pixel value

    // std::cout<<"Blue "<<static_cast<int>(pixel[0])<<std::endl;
    // std::cout<<"Green "<<static_cast<int>(pixel[1])<<std::endl;
    // std::cout<<"Red "<<static_cast<int>(pixel[2])<<std::endl;
  
    
    int no_of_points  = rows * cols; // no of pixels in the image

    std::vector<std::vector<int>> resizeImage;//  creating a vector of  pixel value of each point for ;32 * 32 their will be 1024 * 3 ; [no of point * 3]



    int pointPosition = 0; //index for each pixel
    for(int i=0;i<rows;i++){
      for(int j=0;j<cols;j++){

        unsigned char *pixel = image.ptr(i,j); /// x ,y .. [0,0] pixel value
        resizeImage.push_back(std::vector<int>());
        
        for(int k=0;k<channels;k++){
          
          resizeImage[pointPosition].push_back(static_cast<int>(pixel[k]));//appending pixel value
          // A  Cast operator is an unary operator which forces one data type to be converted into another data type.
        }
        
        pointPosition +=1; /// index for each pixel //for 32 * 32 image = count is from 0 to 1024
 
      }
    }

    std::cout<<"No of Points :  "<<pointPosition<<std::endl;

    // testing pixel value at a point;
    // int atPoint = 69;
    // std::cout<<"Pixel from Vector"<<std::endl;
    // std::cout<<"B "<<resizeImage[atPoint][0]<<std::endl;
    // std::cout<<"G "<<resizeImage[atPoint][1]<<std::endl;
    // std::cout<<"R "<<resizeImage[atPoint][2]<<std::endl;

    // */
    
    cv::namedWindow("Display Image", cv::WINDOW_NORMAL);
    cv::resizeWindow("Display Image", 680,480);
    cv::imshow("Display Image", image);
    
    cv::waitKey(0);
    
    // */

    
    // std::cout<<"Vector resize image size : "<<resizeImage.size()<<std::endl;

    printf("--- Now Clustering ---");
    std::cout<<" --------------------------------------------------------------------"<<std::endl;


    //KMeans<datatype>KMeans(int no of cluster = 8,int no of centroid initialization =10,int no of iteration=300){

    KMeans<int> imageCluster(16,10,100);
    
    imageCluster.fit(resizeImage); // pass the training samples; 
    /*
      This sets new centroid with least cost
      imageCluster.centroid_ vector contains the centroid 
    */
    
    // for (int p = 0; p < imageCluster.centroid_.size(); p++) { 
    //         std::cout<<p<<" Image Cluster Centroid FInal  : ";
    //         for (int q = 0; q < imageCluster.centroid_[0].size();q++) { 
    //             std::cout<<imageCluster.centroid_[p][q]<<" ";
    //         }
    //         std::cout<<" "<<std::endl;
    // }

    imageCluster.predict(resizeImage); // pass the predict samples;
     /*
      This sets cluster id for the given predict samples 
      imageCluster.labels_ vector contains the label for given predict samples; 
    */

  /*
    for(int u=0;u<=10;u++){
    
      std::cout<<"Point "<<u<<" has label "<<imageCluster.labels_[u]<<" and Centroid  ";

      for (int q = 0; q < imageCluster.centroid_[0].size();q++) { 
          // std::cout<< imageCluster.centroid_[imageCluster.labels_[u]][q]<<" ,";
          std::cout<< static_cast<char>(int(imageCluster.centroid_[imageCluster.labels_[u]][q]))<<" ";

        }
      std::cout<<" "<<std::endl;
    }

    */



    pointPosition = 0; //index for each pixel

    for(int i=0;i<rows;i++){
      for(int j=0;j<cols;j++){

        unsigned char *pixel = image.ptr(i,j); /// x ,y .. [0,0] pixel value

        for(int k=0;k<channels;k++){
          
          pixel[k] = static_cast<char>(int(imageCluster.centroid_[imageCluster.labels_[pointPosition]][k]));  
          //changing the color value in the image at i,j and channel k
        }
        pointPosition +=1; /// index for each pixel //for 32 * 32 image = count is from 0 to 1024
 
      }
    }

    std::cout<<" Done Compression"<<std::endl;
    
    std::cout<<" --------------------------------------------------------------------"<<std::endl;

    cv::namedWindow("Compress Image", cv::WINDOW_NORMAL);
    cv::resizeWindow("Compress Image", 680,480);
    cv::imshow("Compress Image", image);

    cv::imwrite("../compressImage.jpg",image);//writing the compressed image
    
    cv::waitKey(0);

    std::cout<<" --------------------------------------------------------------------"<<std::endl;

    cv::destroyAllWindows();

    return 0;
}



