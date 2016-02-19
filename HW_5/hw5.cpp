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

Mat dilation(Mat src, int row, int col)
{
    int i, j;
    Mat dila(row, col, CV_8U);
    int dila516[516][516] = {0};
    int src2[516][516] = {0};
    for(i=0; i<516; i++)
    {
        for(j=0; j<516; j++)
        {
            src2[i][j] = 0;
            dila516[i][j] = 0;            
        }
    }

    for(i=2; i<col+2; i++)
    {   
        for(j=2; j<row+2; j++)
        {   
            src2[i][j] = src.at<unsigned char>(i-2, j-2);
            dila516[i][j] = src.at<unsigned char>(i-2, j-2);
        }   
    }

    for(i=2; i<row+2; i++)
    {
        for(j=2; j<col+2; j++)
        {
                if(src2[i][j] < src2[i-2][j-1]) dila516[i][j] = src2[i-2][j-1];
                if(dila516[i][j] < src2[i-2][j]  ) dila516[i][j] = src2[i-2][j];
                if(dila516[i][j] < src2[i-2][j+1]) dila516[i][j] = src2[i-2][j+1];

                if(dila516[i][j] < src2[i-1][j-2]) dila516[i][j] = src2[i-1][j-2];
                if(dila516[i][j] < src2[i-1][j-1]) dila516[i][j] = src2[i-1][j-1];
                if(dila516[i][j] < src2[i-1][j]  ) dila516[i][j] = src2[i-1][j];
                if(dila516[i][j] < src2[i-1][j+1]) dila516[i][j] = src2[i-1][j+1];
                if(dila516[i][j] < src2[i-1][j+2]) dila516[i][j] = src2[i-1][j+2];

                if(dila516[i][j] < src2[i][j-2]  ) dila516[i][j] = src2[i][j-2];
                if(dila516[i][j] < src2[i][j-1]  ) dila516[i][j] = src2[i][j-1];

                if(dila516[i][j] < src2[i][j+1]  ) dila516[i][j] = src2[i][j+1];
                if(dila516[i][j] < src2[i][j+2]  ) dila516[i][j] = src2[i][j+2];

                if(dila516[i][j] < src2[i+1][j-2]) dila516[i][j] = src2[i+1][j-2];
                if(dila516[i][j] < src2[i+1][j-1]) dila516[i][j] = src2[i+1][j-1];
                if(dila516[i][j] < src2[i+1][j]  ) dila516[i][j] = src2[i+1][j];
                if(dila516[i][j] < src2[i+1][j+1]) dila516[i][j] = src2[i+1][j+1];
                if(dila516[i][j] < src2[i+1][j+2]) dila516[i][j] = src2[i+1][j+2];

                if(dila516[i][j] < src2[i+2][j-1]) dila516[i][j] = src2[i+2][j-1];
                if(dila516[i][j] < src2[i+2][j]  ) dila516[i][j] = src2[i+2][j];
                if(dila516[i][j] < src2[i+2][j+1]) dila516[i][j] = src2[i+2][j+1]; 
        }
    }//end for

    for(i=2; i<row+2; i++)
    {
        for(j=2; j<col+2; j++)
        {
            dila.at<unsigned char>(i-2,j-2) = dila516[i][j];
        }      
    }


    return dila;
}

Mat erosion(Mat src, int row, int col)
{
    Mat eros(row, col, CV_8U);
    eros = picInitialSrc(eros, src, row, col);
    int i,j;
    int keyPoint[516][516] = {0};
    int src516[516][516] = {0};

    for(i=0; i<515; i++)
    {
        for(j=0; j<515; j++)
        {
            src516[i][j] = 255;
            keyPoint[i][j] = 255;
        }
    }

    for(i=2; i<col+2; i++)
    {   
        for(j=2; j<row+2; j++)
        {   
            src516[i][j] = src.at<unsigned char>(i-2, j-2);
            keyPoint[i][j] = src516[i][j];
        }   
    }



    for(i=2; i<col+2; i++)
    {
        for(j=2; j<row+2; j++)
        {
                   keyPoint[i][j] = src516[i][j]; 
                   if (src516[i-2][j-1] <  keyPoint[i][j])  keyPoint[i][j] = src516[i-2][j-1];
                   if (src516[i-2][j  ] <  keyPoint[i][j])  keyPoint[i][j] = src516[i-2][j];                
                   if (src516[i-2][j+1] <  keyPoint[i][j])  keyPoint[i][j] = src516[i-2][j+1];  
                   if (src516[i-1][j-2] <  keyPoint[i][j])  keyPoint[i][j] = src516[i-1][j-2];  
                   if (src516[i-1][j-1] <  keyPoint[i][j])  keyPoint[i][j] = src516[i-1][j-1];  
                   if (src516[i-1][j  ] <  keyPoint[i][j])  keyPoint[i][j] = src516[i-1][j];  
                   if (src516[i-1][j+1] <  keyPoint[i][j])  keyPoint[i][j] = src516[i-1][j+1];  
                   if (src516[i-1][j+2] <  keyPoint[i][j])  keyPoint[i][j] = src516[i-1][j+2];  
                   if (src516[i][j-2  ] <  keyPoint[i][j])  keyPoint[i][j] = src516[i][j-2];  
                   if (src516[i][j-1  ] <  keyPoint[i][j])  keyPoint[i][j] = src516[i][j-1];  
                  
                   if (src516[i][j+1  ] <  keyPoint[i][j])  keyPoint[i][j] = src516[i][j+1];  
                   if (src516[i][j+2  ] <  keyPoint[i][j])  keyPoint[i][j] = src516[i][j+2];  
                   if (src516[i+1][j-2] <  keyPoint[i][j])  keyPoint[i][j] = src516[i+1][j-2];  
                   if (src516[i+1][j-1] <  keyPoint[i][j])  keyPoint[i][j] = src516[i+1][j-1];  
                   if (src516[i+1][j  ] <  keyPoint[i][j])  keyPoint[i][j] = src516[i+1][j];  
                   if (src516[i+1][j+1] <  keyPoint[i][j])  keyPoint[i][j] = src516[i+1][j+1];  
                   if (src516[i+1][j+2] <  keyPoint[i][j])  keyPoint[i][j] = src516[i+1][j+2];  
                   if (src516[i+2][j-1] <  keyPoint[i][j])  keyPoint[i][j] = src516[i+2][j-1];  
                   if (src516[i+2][j  ] <  keyPoint[i][j])  keyPoint[i][j] = src516[i+2][j];  
                   if (src516[i+2][j+1] <  keyPoint[i][j])  keyPoint[i][j] = src516[i+2][j+1]; 
        }
    }//end for
    

    for(i=2; i<row+2; i++)
    {
          for(j=2; j<col+2; j++)
          {
              eros.at<unsigned char>(i-2,j-2) = keyPoint[i][j];
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
    Mat temp7(row, col, CV_8U);
    Mat temp8(row, col, CV_8U);
    Mat temp9(row, col, CV_8U);

    //temp = picInitialSrc(temp, src, row, col);
    //temp2 = picInitialSrc(temp2, src, row, col);
    //temp3 = picInitialSrc(temp3, src, row, col);

    temp7 = erosion(src, row, col);
    temp8 = dilation(temp7, row, col); 
    return temp8;
}


Mat closing(Mat src, int row, int col)
{
    Mat temp(row, col, CV_8U);
    Mat temp2(row, col, CV_8U);
    Mat temp3(row, col, CV_8U);

    //temp = picInitialSrc(temp, src, row, col);
    //temp2 = picInitialSrc(temp2, src, row, col);
    //temp3 = picInitialSrc(temp3, src, row, col);

    //temp = erosion(src, row, col);
    //temp2 = picInitialSrc(temp2, temp, row, col);
    temp = dilation(src, row, col);
    temp2 = erosion(temp, row, col);

    return temp2;
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
    src = imread("lena.bmp",CV_8U);

    int i,j;
    int row = src.rows;
    int col = src.cols;

    //Mat dila(row, col, CV_8U);
    Mat eros(row, col, CV_8U);
    //Mat opic(row, col, CV_8U);    
    //Mat clos(row, col, CV_8U);
    //Mat HAM (row, col, CV_8U);

    //dila = picInitialSrc(dila,src,row,col);
    eros = picInitialSrc(eros,src,row,col);
    //opic = picInitialSrc(opic,src,row,col);
    //clos = picInitialSrc(clos,src,row,col);



    //dila = dilation(src, row, col);
    eros = erosion(src, row, col);   
    //opic = opening(src, row, col);   
    //clos = closing(src, row, col);
    //HAM  = hit_and_miss(src, row, col);
    //showSavePicture(src,"src","src.bmp");
    //showSavePicture(dila,"dilation","dilation.bmp");
    showSavePicture(eros,"erosion","erosion.bmp");
    //showSavePicture(opic,"opening","opening.bmp");
    //showSavePicture(clos,"closing","closing.bmp");
    //showSavePicture(HAM,"hit-and-miss","hit_and_miss.bmp");

    //opic = dilation(eros, eros,row,col);
    //showSavePicture(eros,"opening","opening.bmp");
    //clos = erosion(dila, dila,row, col);
    //showSavePicture(clos,"closing","closing.bmp");

    waitKey(0);
    return 0;
}
