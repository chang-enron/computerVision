#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <cv.h>
using namespace std;
using namespace cv;

int main(int argc,char** argv )
{
    Mat src;
    src = imread("lena.bmp",CV_LOAD_IMAGE_GRAYSCALE);

    int i,j;
    int row = src.rows;
    int col = src.cols;

    Mat divi(row, col, CV_8U);
    int pixel[256] = {0};


    for(i=0; i<col; i++)
    {
        for(j=0; j<row; j++)
        {
            divi.at<unsigned char>(i,j) = (src.at<unsigned char>(i,j))/3;
            pixel[divi.at<unsigned char>(i,j)]++;
            //cout << pixel[divi.at<unsigned char>(i,j)] << endl;
        
        }
    }


    namedWindow( "divi3", WINDOW_AUTOSIZE  );
    imshow( "divi3", divi  );
    imwrite("divi3.bmp", divi );  

    



    double nj = 0;
    int sk[256] = {0};
    for(i=0; i<256; i++)
    {
        nj += pixel[i]; 
        sk[i] = 255*(nj/262144);
    }




    for(i=0; i<col; i++)
    {
        for(j=0; j<row; j++)
        {
            divi.at<unsigned char>(i,j) = sk[divi.at<unsigned char>(i,j)]; 
        }
    }


    namedWindow( "answer", WINDOW_AUTOSIZE   );
    imshow( "answer", divi   );
    imwrite("answer.bmp", divi );  


    int count[256] = {0};
    for(i = 0; i<512; i++)
    {
        for(j=0; j<512; j++)
        {
            count[divi.at<unsigned char>(i,j)]++;
        }
    }


    int maxCount = 0;
    for(i=0; i<256; i++)
    {
        if(count[i]>maxCount)
        {
            maxCount = count[i];
        }
    }
    cout <<"maxC:"<< maxCount;
    
    Mat app(803, 256, CV_8U);

    for(i=0; i<256; i++)
    {
        for(j=0; j<803; j++)
        {
            app.at<unsigned char>(j,i) = 0;
        }
    }
    
    //namedWindow( "temp", WINDOW_AUTOSIZE);
    //imshow( "temp", app);
    //imwrite("temp.bmp", dst );  


    for(i=0; i<256; i++)
    {
        for(j=0; j<(count[i]/10); j++)
        {
            app.at<unsigned char>(803-j,i) = 255;
        }

    }

    namedWindow( "finalHistogram", WINDOW_AUTOSIZE    );
    imshow( "finalHistogram", app);
    imwrite("finalHistogram.bmp", app );
    waitKey(0);

    return 0;


}
