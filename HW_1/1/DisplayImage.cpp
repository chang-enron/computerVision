#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <cv.h>

using namespace std;
using namespace cv;

int main(int argc,char** argv )
{

    Mat src;
    int i=0, j=0;


    src = imread("lena.bmp",CV_LOAD_IMAGE_GRAYSCALE);
   // dst.create( src.size(),  src.type());


    namedWindow( "original", WINDOW_AUTOSIZE );
    imshow( "original", src );




    int row = src.rows;
    int col = src.cols;
   Mat dst(row,col,CV_8U);

    for(i=0; i<col; i++)
    {
        for(j=0; j<row; j++)
        {
            dst.at<unsigned char>(i,j) = src.at<unsigned char>(row-i-1,j);   
        }

    }
    
    namedWindow( "upside-down", WINDOW_AUTOSIZE );
    imshow( "upside-down", dst );
    imwrite("upside-down.bmp", dst ); 


    for(i=0; i<col; i++)
    {
        for(j=0; j<row; j++)
        {
            dst.at<unsigned char>(i,j) = src.at<unsigned char>(i,col-j-1);
    
        }

    }

    namedWindow( "left right", WINDOW_AUTOSIZE );
    imshow( "left right", dst );
    imwrite("left-right.bmp", dst ); 

    
    

    for(i=0; i<col; i++)
    {
        for(j=0; j<row; j++)
        {
            dst.at<unsigned char>(i,j) = src.at<unsigned char>(row-i-1,col-j-1);
        }

    }

    namedWindow( "mirr", WINDOW_AUTOSIZE );
    imshow( "mirr", dst );
    imwrite("mirr.bmp", dst ); 

    
     
        

    waitKey(0);
    return 0;
}

