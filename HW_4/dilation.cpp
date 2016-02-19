#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <cv.h>
using namespace std;
using namespace cv;

Mat dilation(Mat dila, Mat src)
{




}

int main(int argc,char** argv )
{
    Mat src;
    src = imread("lena_binary.bmp",CV_LOAD_IMAGE_GRAYSCALE);

    int i,j;
    int row = src.rows;
    int col = src.cols;
    cout << "row:" << row <<"col" << col ; 
    Mat dila(row, col, CV_8U);
    Mat eros(row, col, CV_8U);
    for(i=0; i<col; i++)
    {
        for(j=0; j<row; j++)
        {
            dila.at<unsigned char>(i,j) = src.at<unsigned char>(i,j);
            eros.at<unsigned char>(i,j) = src.at<unsigned char>(i,j);
        }
    }

    namedWindow( "srcOrigin", WINDOW_AUTOSIZE    );
    imshow( "srcOrigin", src  );

    namedWindow( "dilationOrigin", WINDOW_AUTOSIZE    );
    imshow( "dilationOrigin", dila  );

    int count =0;
    for(i=0; i<col; i++)
    {
        for(j=0; j<row; j++)
        {
            if(src.at<unsigned char>(i,j) == 255 )
            {
                if(i>=2 && j>=1)       dila.at<unsigned char>(i-2,j-1) = 255;
                if(i>=2)               dila.at<unsigned char>(i-2,j) = 255;
                if(i>=2 && j<=511)     dila.at<unsigned char>(i-2,j+1) = 255;
                if(i>=1 && j>=2)       dila.at<unsigned char>(i-1,j-2) = 255;
                if(i>=1 && j>=1)       dila.at<unsigned char>(i-1,j-1) = 255;
                if(i>=1)               dila.at<unsigned char>(i-1,j) = 255;
                if(i>=1 && j<=511)     dila.at<unsigned char>(i-1,j+1) = 255;
                if(i>=1 && j<=510)     dila.at<unsigned char>(i-1,j+2) = 255;
                if(j>=2)               dila.at<unsigned char>(i,j-2) = 255;
                if(j>=1)               dila.at<unsigned char>(i,j-1) = 255;
                                       dila.at<unsigned char>(i,j) = 255;
                if(j<=511)             dila.at<unsigned char>(i,j+1) = 255;
                if(j<=510)             dila.at<unsigned char>(i,j+2) = 255;
                if(i<=511 && j>=2)     dila.at<unsigned char>(i+1,j-2) = 255;
                if(i<=511 && j>=1)     dila.at<unsigned char>(i+1,j-1) = 255;
                if(i<=511)             dila.at<unsigned char>(i+1,j) = 255;
                if(i<=511 && j<=511)   dila.at<unsigned char>(i+1,j+1) = 255;
                if(i<=511 && j<=510)   dila.at<unsigned char>(i+1,j+2) = 255;
                if(i<=510 && j>=1)     dila.at<unsigned char>(i+2,j-1) = 255;
                if(i<=510 )            dila.at<unsigned char>(i+2,j) = 255;
                if(i<=510 && j<=511)   dila.at<unsigned char>(i+2,j+1) = 255;

                count++;
            }
        }

    }
    cout << "count" << count <<endl;
    namedWindow( "dilation", WINDOW_AUTOSIZE   );    
    imshow( "dilation", dila );
    imwrite("dilation.bmp", dila );
   
 
    for(i=0; i<col; i++)
    {
        for(j=0; j<row; j++)
        {
            if(src.at<unsigned char>(i-2,j-1) == 0 ||
               src.at<unsigned char>(i-2,j) == 0 ||              
               src.at<unsigned char>(i-2,j+1) == 0 ||
               src.at<unsigned char>(i-1,j-2) == 0 ||
               src.at<unsigned char>(i-1,j-1) == 0 ||
               src.at<unsigned char>(i-1,j) == 0 ||
               src.at<unsigned char>(i-1,j+1) == 0 ||
               src.at<unsigned char>(i-1,j+2) == 0 ||
               src.at<unsigned char>(i,j-2) == 0 ||
               src.at<unsigned char>(i,j-1) == 0 ||
               src.at<unsigned char>(i,j) == 0 ||
               src.at<unsigned char>(i,j+1) == 0 ||
               src.at<unsigned char>(i,j+2) == 0 ||
               src.at<unsigned char>(i+1,j-2) == 0 ||
               src.at<unsigned char>(i+1,j-1) == 0 ||
               src.at<unsigned char>(i+1,j) == 0 ||
               src.at<unsigned char>(i+1,j+1) == 0 ||
               src.at<unsigned char>(i+1,j+2) == 0 ||
               src.at<unsigned char>(i+2,j-1) == 0 ||
               src.at<unsigned char>(i+2,j) == 0 ||
               src.at<unsigned char>(i+2,j+1) == 0  ){
                eros.at<unsigned char>(i,j) = 0;                
            }
            else
            {
                eros.at<unsigned char>(i,j) = 255;
            }
                
        }
    }


    namedWindow( "dilation", WINDOW_AUTOSIZE   );    
    imshow( "erosion", eros );
    imwrite("erosion.bmp", eros );   
    waitKey(0);



    return 0;
}
