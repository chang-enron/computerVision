#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <cv.h>

using namespace std;
using namespace cv;

int main(int argc,char** argv)
{
    Mat src;
    int i=0, j=0;
    src = imread("lena.bmp",CV_LOAD_IMAGE_GRAYSCALE);
    int row = src.rows;
    int col = src.cols;
    Mat dst(row,col,CV_8U);


    for(i=0;i<col;i++)
    {
        for(j=0;j<row;j++)
        {
            if(src.at<unsigned char>(i,j)>127)
                dst.at<unsigned char>(i,j) = 255;
            else
                dst.at<unsigned char>(i,j) = 0;

        }
    }

    namedWindow( "threshold", WINDOW_AUTOSIZE );
    imshow( "threshold", dst ); 
    imwrite("threshold.bmp", dst );
    waitKey(0);
    return 0;
}
