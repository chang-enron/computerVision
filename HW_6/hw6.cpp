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

int cal(int a[4]) // q=1, r=2, s=3
{
    if(a[0] != a[1])
        return 3;
    else if(a[2] == a[0] && a[3] == a[0])
        return 2;
    else
        return 1;
}

int* hFunction(Mat yokoi64, int i, int j)
{
    int *f4 = new int[4];//return 4 neborhood
    int a[4] = {0};//temp 
    for(int k=0; k<4; k++)     
    {
        a[k] = 0;
    }
    a[0] = yokoi64.at<unsigned char>(i,j);
    if(j<=62)
        a[1] = yokoi64.at<unsigned char>(i,j+1);
    if(i>=1 && j<=62)
        a[2] = yokoi64.at<unsigned char>(i-1,j+1);
    if(i>=1)
        a[3] = yokoi64.at<unsigned char>(i-1,j); 

    //cout << "0:" << a[0] << "1:" << a[1] << "2:" << a[2] << "3:" << a[3] << endl;
    f4[0] = cal(a);

    for(int k=1; k<4; k++)
    {
        a[k] = 0;
    }

    if(i>=1)
        a[1] = yokoi64.at<unsigned char>(i-1,j);
    if(i>=1 && j>=1)
        a[2] = yokoi64.at<unsigned char>(i-1,j-1);
    if(j>=1)
        a[3] = yokoi64.at<unsigned char>(i,j-1); 

    //cout << "0:" << a[0] << "1:" << a[1] << "2:" << a[2] << "3:" << a[3] << endl; 

    f4[1] = cal(a);

    for(int k=1; k<4; k++)
    {
        a[k] = 0;
    }

    if(j>=1)
        a[1] = yokoi64.at<unsigned char>(i,j-1);
    if(i<=62 && j>=1)
        a[2] = yokoi64.at<unsigned char>(i+1,j-1);
    if(i<=62)
        a[3] = yokoi64.at<unsigned char>(i+1,j); 

    //cout << "0:" << a[0] << "1:" << a[1] << "2:" << a[2] << "3:" << a[3] << endl; 

    f4[2] = cal(a);


    for(int k=1; k<4; k++)
    {
        a[k] = 0;
    }

    if(i<=62)
        a[1] = yokoi64.at<unsigned char>(i+1,j);
    if(i<=62 && j<=62)
        a[2] = yokoi64.at<unsigned char>(i+1,j+1);
    if(j<=62)
        a[3] = yokoi64.at<unsigned char>(i,j+1); 

    //cout << "0:" << a[0] << "1:" << a[1] << "2:" << a[2] << "3:" << a[3] << endl; 

    f4[3] = cal(a);

    return f4;
}

void showSavePicture(Mat picture,string windowName,string saveName)
{
    namedWindow( windowName, WINDOW_AUTOSIZE   );    
    imshow( windowName, picture );
    imwrite( saveName , picture );
}


int main(int argc,char** argv )
{
    Mat src;
    src = imread("lena.bmp",CV_LOAD_IMAGE_GRAYSCALE);

    int i,j,k;
    int row = src.rows;
    int col = src.cols;

    int* h4num;
    int ans[64][64] = {0};    

    Mat yokoi64(64, 64, CV_8U);
    for(i=0; i<512; i++)
    {
        for(j=0; j<512; j++)
        {
            if(i%8==0 && j%8==0)
            {
                if(src.at<unsigned char>(i,j) >= 128)
                    yokoi64.at<unsigned char>(i/8,j/8) = 255;
                else
                    yokoi64.at<unsigned char>(i/8,j/8) = 0;
                cout << "(" << i << "," << j << ")" << endl;
            }
        }
    }

    for(i=0; i<64; i++)// q=1, r=2, s=3
    {
        for(j=0; j<64; j++)
        {

            int timeForQ = 0;
            int timeForR = 0;
            if(yokoi64.at<unsigned char>(i,j) == 255)
            {
                h4num = hFunction(yokoi64,i,j);
                //time ++;
                //cout << "time:" << time << endl;
                //for(int i = 0 ; i< 4; i++)
                //cout << "h4num:" << h4num[i] << endl;
                for(k=0; k<4; k++)
                {
                    if(i==0 && j==63)
                        cout << "ans:" << h4num[k] << endl;
                    if(h4num[k] == 1)
                    {
                        timeForQ++;
                    }
                    else if(h4num[k] == 2)
                        timeForR++;
                }
                if(timeForR == 4)
                    ans[i][j] = 5;
                else
                    ans[i][j] = timeForQ;

            }
        }}

    //h4num = hFunction(yokoi64,0,0);

    //for(int i = 0 ; i< 4; i++)
    // cout << "h4num:" << h4num[i] << endl;

    for(i=0; i<64; i++)
    {
        for(j=0; j<64; j++)
        {
            if(yokoi64.at<unsigned char>(i,j) == 0)
                cout << " ";
            else
                cout<< ans[i][j];   

        }
        cout << endl;
    }


    //dila = picInitialSrc(dila,src,row,col);

    //showSavePicture(yokoi64,"yokoi64","yokoi64.bmp");

    waitKey(0);
    return 0;
}
