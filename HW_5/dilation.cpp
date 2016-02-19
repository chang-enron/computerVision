#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <cv.h>
using namespace std;
using namespace cv;
Mat picInitialSrc(Mat pic, Mat src, int row, int col)
{
    int i,j;
    for(i=0; i<col; i++)
    {
        for(j=0; j<row; j++)
        {
            pic.at<unsigned char>(i,j) = src.at<unsigned char>(i,j);
        }
    }
    return pic;
}

Mat dilation(Mat dila, Mat src, int row, int col)
{
    int i,j;
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

            }
        }

    }
    return dila;
}

Mat erosion(Mat eros, Mat src, int row, int col)
{
    int i,j;
    for(i=0; i<col; i++)
    {
        for(j=0; j<row; j++)
        {
            if(     ( src.at<unsigned char>(i-2,j-1) == 0  && i>=2   && j>=1   )   ||
                    ( src.at<unsigned char>(i-2,j) == 0    && i>=2             )   ||              
                    ( src.at<unsigned char>(i-2,j+1) == 0  && i>=2   && j<=511 )   ||
                    ( src.at<unsigned char>(i-1,j-2) == 0  && i>=1   && j>=2   )   ||
                    ( src.at<unsigned char>(i-1,j-1) == 0  && i>=1   && j>=1   )   ||
                    ( src.at<unsigned char>(i-1,j) == 0    && i>=1             )   ||
                    ( src.at<unsigned char>(i-1,j+1) == 0  && i>=1   && j<=511 )   ||
                    ( src.at<unsigned char>(i-1,j+2) == 0  && i>=1   && j<=510 )   ||
                    ( src.at<unsigned char>(i,j-2) == 0              && j>=2   )   ||
                    ( src.at<unsigned char>(i,j-1) == 0              && j>=1   )   ||
                    ( src.at<unsigned char>(i,j) == 0                          )   ||
                    ( src.at<unsigned char>(i,j+1) == 0              && j<=511 )   ||
                    ( src.at<unsigned char>(i,j+2) == 0              && j<=510 )   ||
                    ( src.at<unsigned char>(i+1,j-2) == 0  && i<=511 && j>=2   )   ||
                    ( src.at<unsigned char>(i+1,j-1) == 0  && i<=511 && j>=1   )   ||
                    ( src.at<unsigned char>(i+1,j) == 0    && i<=511           )   ||
                    ( src.at<unsigned char>(i+1,j+1) == 0  && i<=511 && j<=511 )   ||
                    ( src.at<unsigned char>(i+1,j+2) == 0  && i<=511 && j<=510 )   ||
                    ( src.at<unsigned char>(i+2,j-1) == 0  && i<=510 && j>=1   )   ||
                    ( src.at<unsigned char>(i+2,j) == 0    && i<=510           )   ||
                    ( src.at<unsigned char>(i+2,j+1) == 0  && i<=510 && j<=511 )   ){
                eros.at<unsigned char>(i,j) = 0;                
            }
            else
            {
                eros.at<unsigned char>(i,j) = 255;
            }
        }
    }
    return eros;
}


Mat erosionA(Mat eros, Mat src, int row, int col)
{
    int i,j;
    for(i=0; i<col; i++)
    {
        for(j=0; j<row; j++)
        {
            if( ( src.at<unsigned char>(i,j-1) == 0  && j >= 1   )      ||
                ( src.at<unsigned char>(i+1,j) == 0  && i <= 511 )      ||
                ( src.at<unsigned char>(i,j) == 0                )      ){
                eros.at<unsigned char>(i,j) = 0;                
            }
            else
            {
                eros.at<unsigned char>(i,j) = 255;
            }
        }
    }
    return eros;
}


Mat erosionB(Mat eros, Mat src, int row, int col)
{
    int i,j;
    for(i=0; i<col; i++)
    {
        for(j=0; j<row; j++)
        {
            if( ( src.at<unsigned char>(i-1,j) == 0    && i >= 1            )      ||
                    ( src.at<unsigned char>(i-1,j+1) == 0  && i >= 1 &&  j <= 511 )      ||
                    ( src.at<unsigned char>(i,j+1) == 0    && j <= 511          )      ){
                eros.at<unsigned char>(i,j) = 0;                
            }
            else
            {
                eros.at<unsigned char>(i,j) = 255;
            }
        }
    }
    return eros;
}

Mat opening(Mat src, int row, int col)
{
    Mat temp(row, col, CV_8U);
    Mat temp2(row, col, CV_8U);
    Mat temp3(row, col, CV_8U);

    temp = picInitialSrc(temp, src, row, col);
    temp2 = picInitialSrc(temp2, src, row, col);
    temp3 = picInitialSrc(temp3, src, row, col);

    temp = dilation(temp, src, row, col);
    temp2 = picInitialSrc(temp2, temp, row, col);
    temp3 = erosion(temp3, temp2, row, col);

    return temp3;
}


Mat closing(Mat src, int row, int col)
{
    Mat temp(row, col, CV_8U);
    Mat temp2(row, col, CV_8U);
    Mat temp3(row, col, CV_8U);

    temp = picInitialSrc(temp, src, row, col);
    temp2 = picInitialSrc(temp2, src, row, col);
    temp3 = picInitialSrc(temp3, src, row, col);

    temp = erosion(temp, src, row, col);
    temp2 = picInitialSrc(temp2, temp, row, col);
    temp3 = dilation(temp2, temp, row, col);

    return temp3;
}

void showSavePicture(Mat picture,string windowName,string saveName)
{
    namedWindow( windowName, WINDOW_AUTOSIZE   );    
    imshow( windowName, picture );
    imwrite( saveName , picture );
}

Mat hit_and_miss(Mat src,int row,int col)
{
    Mat src_inverse(row, col, CV_8U);
    Mat A(row, col, CV_8U);
    Mat B(row, col, CV_8U);
    Mat HAM(row, col, CV_8U);
    int i,j;

    for(int i=0; i<col; i++)
    {
        for(int j=0; j<row; j++)
        {
            if(src.at<unsigned char>(i,j) == 0)
                src_inverse.at<unsigned char>(i,j) = 255; 
            else 
                src_inverse.at<unsigned char>(i,j) = 0;

        }
    }

    A = erosionA(A,src,row,col);
    B = erosionB(B,src_inverse,row,col);    

    showSavePicture(A,"A","A.bmp");
    showSavePicture(B,"B","B.bmp");


    for(int i=0; i<col; i++)
    {
        for(int j=0; j<row; j++)
        {
            if(A.at<unsigned char>(i,j) == 255 && B.at<unsigned char>(i,j) == 255)
                HAM.at<unsigned char>(i,j) = 255;
            else 
                HAM.at<unsigned char>(i,j) = 0;
        }
    }


    return HAM;
}

int main(int argc,char** argv )
{
    Mat src;
    src = imread("lena_binary.bmp",CV_LOAD_IMAGE_GRAYSCALE);

    int i,j;
    int row = src.rows;
    int col = src.cols;

    Mat dila(row, col, CV_8U);
    Mat eros(row, col, CV_8U);
    Mat opic(row, col, CV_8U);    
    Mat clos(row, col, CV_8U);
    Mat HAM (row, col, CV_8U);

    dila = picInitialSrc(dila,src,row,col);
    eros = picInitialSrc(eros,src,row,col);
    opic = picInitialSrc(opic,src,row,col);
    clos = picInitialSrc(clos,src,row,col);



    dila = dilation(dila, src, row, col);
    eros = erosion(eros, src, row, col);   
    opic = opening(src, row, col);   
    clos = closing(src, row, col);
    HAM  = hit_and_miss(src, row, col);

    showSavePicture(dila,"dilation","dilation.bmp");
    showSavePicture(eros,"erosion","erosion.bmp");
    showSavePicture(opic,"opening","opening.bmp");
    showSavePicture(clos,"closing","closing.bmp");
    showSavePicture(HAM,"hit-and-miss","hit_and_miss.bmp");


   // waitKey(0);
    return 0;
}
