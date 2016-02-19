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



    int row = src.rows;
    int col = src.cols;
    int count[256]= {0};
    int maxCount = 0;
    Mat dst(275,256,CV_8U);


    for(i=0; i<col; i++)
    {
        for(j=0; j<row; j++)
        {
           count[src.at<unsigned char>(i,j)]++;
        }

    }
    //cout << count[100] <<","<< count[107]<<endl;
    for(i=0; i<256; i++)
    {
        //cout << count[i] << endl;
        if(count[i]>maxCount)
        {
            maxCount = count[i];
        }
    }
    //cout << "maxCount" << maxCount << endl;

    for(i=0; i<256; i++)
    {
        for(j=0; j<275; j++)
        {
                dst.at<unsigned char>(j,i) = 0; 
        }

    }



    for(i=0; i<256; i++)
    {
	//cout << "i:" << i << endl;
        for(j=0; j<(count[i]/10); j++)
        {
                dst.at<unsigned char>(274-j,i) = 255;
               // cout << 2742-j << endl;
        }
        //cout << "j:" << j << endl;
        //cout << "count:" << count[i] << endl;
    }

    namedWindow( "histogram", WINDOW_AUTOSIZE );
    imshow( "histogram", dst );

    imwrite("histogram.bmp", dst );
  
    waitKey(0);
    return 0;
}


