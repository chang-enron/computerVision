#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <cv.h>
#include <ctime> 
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

void showSavePicture(Mat picture,string windowName,string saveName)
{
    namedWindow( windowName, WINDOW_AUTOSIZE   );    
    imshow( windowName, picture );
    imwrite( saveName , picture );
    cout << windowName << ":";
}

double Normal( void  )
{
    int a, i;
    double b;
    for(i = 0; i < 12; i++)
    {
        b+=((double) rand() / RAND_MAX );
    }
    return b - 6;
}

Mat GaussianNoiseAmplitude(int row, int col, int amplitude, Mat input)
{
    int i,j;
    double ran = 0;
    Mat GNA(row,col,CV_8U);
    for(i=0; i<col; i++)
    {
        for(j=0; j<row; j++)
        {
            ran = Normal();
            if(amplitude * ran + input.at<unsigned char>(i,j) >= 255)
                GNA.at<unsigned char>(i,j) = 255;
            else if(amplitude * ran + input.at<unsigned char>(i,j) <= 0)
                GNA.at<unsigned char>(i,j) = 0;
            else
                GNA.at<unsigned char>(i,j) = input.at<unsigned char>(i,j) + amplitude * ran;
        }
    } 
    return GNA;
}

Mat saltAndPepperUniform(int row, int col, double uniform, Mat input)
{
    int i,j;
    Mat SAP(row, col, CV_8U);
    for(i=0; i<col; i++)
    {
        for(j=0; j<row; j++)
        {
            double ran = ((double) rand() / RAND_MAX );
            if(ran < uniform)
                SAP.at<unsigned char>(i,j) = 0;
            else if( ran > (1-uniform) )
                SAP.at<unsigned char>(i,j) = 255;
            else
                SAP.at<unsigned char>(i,j) = input.at<unsigned char>(i,j);
        }
    }
    return SAP;
}
int median(int arr[], int numOfelement)
{
    int i,j,k;
    for(i=0; i<numOfelement; i++)
    {
        for(j=i; j<numOfelement; j++)
        {
            if(arr[i] > arr[j])
            {
                k = arr[i];
                arr[i] = arr[j];
                arr[j] = k;     
            }
        }
    }
    return arr[(numOfelement+1)/2-1];
}

Mat medianFilter(int row, int col, int boxSize, Mat input)
{
    int i, j, k;
    int arr[boxSize];
    Mat medianFilter(row, col, CV_8U);
    if(boxSize == 9)
    {
        for(i=0; i<col; i++)
        {
            for(j=0; j<row; j++)
            {
                for(k=0; k<boxSize; k++)
                {
                    arr[k] = 0;
                }
                if(i>=1 && j>=1)
                    arr[0] = input.at<unsigned char>(i-1,j-1);
                if(j>=1)
                    arr[1] = input.at<unsigned char>(i,j-1);

                if(i<=950 && j>=1)
                    arr[2] = input.at<unsigned char>(i+1,j-1);
                if(i>=1)
                    arr[3] = input.at<unsigned char>(i-1,j);

                arr[4] = input.at<unsigned char>(i,j);
                if(i<=950)
                    arr[5] = input.at<unsigned char>(i+1,j);
                if(i>=1 && j<=1019)
                    arr[6] = input.at<unsigned char>(i-1,j+1);
                if(j<=1019)
                    arr[7] = input.at<unsigned char>(i,j+1);
                if(i<=950 && j<=1019)
                    arr[8] = input.at<unsigned char>(i+1,j+1);
                medianFilter.at<unsigned char>(i,j) = median(arr,boxSize);
            }
        }
    }
    else if(boxSize == 25)
    {
        for(i=0; i<col; i++)
        {
            for(j=0; j<row; j++)
            {
                for(k=0; k<boxSize; k++)
                {
                    arr[k] = 0;
                }
                if(i>=2 && j>=2)        arr[0] = input.at<unsigned char>(i-2, j-2);
                if(i>=1 && j>=2)        arr[1] = input.at<unsigned char>(i-1, j-2);
                if(j>=2)                arr[2] = input.at<unsigned char>(  i, j-2);
                if(i<=510 && j>=2)      arr[3] = input.at<unsigned char>(i+1, j-2);
                if(i<=509 && j>=2)      arr[4] = input.at<unsigned char>(i+2, j-2);

                if(i>=2 && j>=1)        arr[5] = input.at<unsigned char>(i-2, j-1);
                if(i>=1 && j>=1)        arr[6] = input.at<unsigned char>(i-1, j-1);
                if(j>=1)                arr[7] = input.at<unsigned char>(  i, j-1);
                if(i<=510 && j>=1)      arr[8] = input.at<unsigned char>(i+1, j-1);
                if(i<=509 && j>=1)      arr[9] = input.at<unsigned char>(i+2, j-1);

                if(i>=2)                arr[10] = input.at<unsigned char>(i-2,  j);
                if(i>=1)                arr[11] = input.at<unsigned char>(i-1,  j);
                arr[12] = input.at<unsigned char>(  i,  j);
                if(i<=510)              arr[13] = input.at<unsigned char>(i+1,  j);
                if(i<=509)              arr[14] = input.at<unsigned char>(i+2,  j);

                if(i>=2 && j<=510)      arr[15] = input.at<unsigned char>(i-2, j+1);
                if(i>=1 && j<=510)      arr[16] = input.at<unsigned char>(i-1, j+1);
                if(j<=510)              arr[17] = input.at<unsigned char>(  i, j+1);
                if(i<=510 && j<=510)    arr[18] = input.at<unsigned char>(i+1, j+1);
                if(i<=509 && j<=510)    arr[19] = input.at<unsigned char>(i+2, j+1);

                if(i>=2 && j<=509)      arr[20] = input.at<unsigned char>(i-2, j+2);
                if(i>=1 && j<=509)      arr[21] = input.at<unsigned char>(i-1, j+2);
                if(j<=509)              arr[22] = input.at<unsigned char>(  i, j+2);
                if(i<=510 && j<=509)    arr[23] = input.at<unsigned char>(i+1, j+2);
                if(i<=509 && j<=509)    arr[24] = input.at<unsigned char>(i+2, j+2);

                medianFilter.at<unsigned char>(i,j) = median(arr,boxSize);
            }
        }
    }//end else if    
    return medianFilter;
}

Mat boxFilter(int row, int col, int boxSize, Mat input)
{
    int i, j, k, z=0;
    int tempColor = 0;
    int arr[boxSize];
    int mask[25] = {0,3,4,3,0,3,6,7,6,3,4,7,8,7,4,3,6,7,6,3,0,3,4,3,0};
    Mat boxFilter(row, col, CV_8U);
    if(boxSize == 9)
    {
        for(i=0; i<col; i++)
        {
            for(j=0; j<row; j++)
            {
                for(k=0; k<boxSize; k++)
                {
                    arr[k] = 0;
                }
                if(i>=1 && j>=1)
                    arr[0] = input.at<unsigned char>(i-1,j-1);
                if(j>=1)
                    arr[1] = input.at<unsigned char>(i,j-1);

                if(i<=510 && j>=1)
                    arr[2] = input.at<unsigned char>(i+1,j-1);
                if(i>=1)
                    arr[3] = input.at<unsigned char>(i-1,j);

                arr[4] = input.at<unsigned char>(i,j);
                if(i<=510)
                    arr[5] = input.at<unsigned char>(i+1,j);
                if(i>=1 && j<=510)
                    arr[6] = input.at<unsigned char>(i-1,j+1);
                if(j<=510)
                    arr[7] = input.at<unsigned char>(i,j+1);
                if(i<=510 && j<=510)
                    arr[8] = input.at<unsigned char>(i+1,j+1);

                for(k=0; k<boxSize; k++)
                {
                    tempColor += arr[k]; 

                }
                boxFilter.at<unsigned char>(i,j) = (tempColor / 9);
                tempColor = 0;

            }

        }

    }//end if

    else if(boxSize == 25)
    {
        for(i=0; i<col; i++)
        {
            for(j=0; j<row; j++)
            {
                for(k=0; k<boxSize; k++)
                {
                    arr[k] = 0;
                }
                if(i>=2 && j>=2)        arr[0] = input.at<unsigned char>(i-2, j-2);
                if(i>=1 && j>=2)        arr[1] = input.at<unsigned char>(i-1, j-2);
                if(j>=2)                arr[2] = input.at<unsigned char>(  i, j-2 );
                if(i<=510 && j>=2)      arr[3] = input.at<unsigned char>(i+1, j-2);
                if(i<=509 && j>=2)      arr[4] = input.at<unsigned char>(i+2, j-2);

                if(i>=2 && j>=1)        arr[5] = input.at<unsigned char>(i-2, j-1);
                if(i>=1 && j>=1)        arr[6] = input.at<unsigned char>(i-1, j-1);
                if(j>=1)                arr[7] = input.at<unsigned char>(  i, j-1 );
                if(i<=510 && j>=1)      arr[8] = input.at<unsigned char>(i+1, j-1);
                if(i<=509 && j>=1)      arr[9] = input.at<unsigned char>(i+2, j-1);

                if(i>=2)                arr[10] = input.at<unsigned char>(i-2,  j);
                if(i>=1)                arr[11] = input.at<unsigned char>(i-1,  j);
                arr[12] = input.at<unsigned char>(  i,  j );
                if(i<=510)              arr[13] = input.at<unsigned char>(i+1,  j);
                if(i<=509)              arr[14] = input.at<unsigned char>(i+2,  j);

                if(i>=2 && j<=510)      arr[15] = input.at<unsigned char>(i-2, j+1);
                if(i>=1 && j<=510)      arr[16] = input.at<unsigned char>(i-1, j+1);
                if(j<=510)              arr[17] = input.at<unsigned char>(  i, j+1 );
                if(i<=510 && j<=510)    arr[18] = input.at<unsigned char>(i+1, j+1);
                if(i<=509 && j<=510)    arr[19] = input.at<unsigned char>(i+2, j+1);

                if(i>=2 && j<=509)      arr[20] = input.at<unsigned char>(i-2, j+2);
                if(i>=1 && j<=509)      arr[21] = input.at<unsigned char>(i-1, j+2);
                if(j<=509)              arr[22] = input.at<unsigned char>(  i, j+2 );
                if(i<=510 && j<=509)    arr[23] = input.at<unsigned char>(i+1, j+2);
                if(i<=509 && j<=509)    arr[24] = input.at<unsigned char>(i+2, j+2);


                for(k=0; k<boxSize; k++)
                {
                    tempColor += arr[k] * mask[k];   
                }
                for(k=0; k<25; k++)
                {
                    z += mask[k];
                }
                boxFilter.at<unsigned char>(i,j) = (tempColor / z);                                                                                   
                tempColor = 0;
                z = 0;
            }
        }
    }//end else if
    return boxFilter;
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
            if (src516[i  ][j-2] <  keyPoint[i][j])  keyPoint[i][j] = src516[i][j-2];  
            if (src516[i  ][j-1] <  keyPoint[i][j])  keyPoint[i][j] = src516[i][j-1];  

            if (src516[i  ][j+1] <  keyPoint[i][j])  keyPoint[i][j] = src516[i][j+1];  
            if (src516[i  ][j+2] <  keyPoint[i][j])  keyPoint[i][j] = src516[i][j+2];  
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

Mat opening(Mat src, int row, int col)
{
    Mat temp7(row, col, CV_8U);
    Mat temp8(row, col, CV_8U);

    temp7 = erosion(src, row, col);
    temp8 = dilation(temp7, row, col); 
    return temp8;
}

Mat closing(Mat src, int row, int col)
{
    Mat temp(row, col, CV_8U);
    Mat temp2(row, col, CV_8U);

    temp = dilation(src, row, col);
    temp2 = erosion(temp, row, col);

    return temp2;
}

Mat openThenClose(int row, int col, Mat src)
{
    Mat temp(row, col, CV_8U);
    Mat temp2(row, col, CV_8U);

    temp = opening(src, row, col);
    temp2 = closing(temp, row, col);

    return temp2;
}

Mat closeThenOpen(int row, int col, Mat src)
{
    Mat temp(row, col, CV_8U);
    Mat temp2(row, col, CV_8U);

    temp = closing(src, row, col);
    temp2 = opening(temp, row, col);

    return temp2;  
}

void SNR(Mat A, Mat B)
{
    int n=A.rows*A.cols;
    double uA=0;
    double uB=0;
    for (int i=0;i<A.rows;i++){
        for (int j=0;j<A.cols;j++){
            uA += A.at<unsigned char>(i,j);
            uB += B.at<unsigned char>(i,j)-A.at<unsigned char>(i,j);
        
        }   
    
    }   
    uA = uA / n;
    uB = uB / n;
    double tmpA=0;
    double tmpB=0;
    for (int i=0;i<A.rows;i++){
        for (int j=0;j<A.cols;j++){
            tmpA += (A.at<unsigned char>(i,j)-uA)*(A.at<unsigned char>(i,j)-uA);
            tmpB += (B.at<unsigned char>(i,j)-A.at<unsigned char>(i,j)-uB)*(B.at<unsigned char>(i,j)-A.at<unsigned char>(i,j)-uB);
        
        }   
    
    }   
    double VS = tmpA / n;
    double VN = tmpB / n;
    double SNR = 20 * log10(sqrt(VS)/sqrt(VN));
    cout << " SNR:" << SNR << endl; 

}


int main(int argc,char** argv )
{
    Mat src;
    src = imread("lena.bmp",CV_LOAD_IMAGE_GRAYSCALE);
    Mat src2 = imread("test_1_MOD_12_8.jpg",CV_LOAD_IMAGE_GRAYSCALE);
    srand(time(NULL));
    int i, j, k;
    double u = 0, vs = 0, un = 0, vn = 0;
    int row = src.rows;
    int col = src.cols;
    Mat GNA10(row, col, CV_8U);
    Mat GNA30(row, col, CV_8U);
    Mat SAP005(row, col,CV_8U);
    Mat SAP01(row,col,CV_8U);
    /*--medianFilter--noise--noiseNum(Amplitude....)--Size---*/
    Mat MF_GNA_10_9(row, col, CV_8U);
    Mat MF_GNA_30_9(row, col, CV_8U);
    Mat MF_GNA_10_25(row, col, CV_8U);
    Mat MF_GNA_30_25(row, col, CV_8U);
    Mat MF_SAP_005_9(row, col, CV_8U);
    Mat MF_SAP_01_9(row, col, CV_8U);
    Mat MF_SAP_005_25(row, col, CV_8U);
    Mat MF_SAP_01_25(row, col, CV_8U);
    /*--boxFilter--noise--noiseNum(Amplitude....)--Size---*/
    Mat BF_GNA_10_9(row, col, CV_8U);
    Mat BF_GNA_30_9(row, col, CV_8U);
    Mat BF_GNA_10_25(row, col, CV_8U);
    Mat BF_GNA_30_25(row, col, CV_8U);
    Mat BF_SAP_005_9(row, col, CV_8U);
    Mat BF_SAP_01_9(row, col, CV_8U);
    Mat BF_SAP_005_25(row, col, CV_8U);
    Mat BF_SAP_01_25(row, col, CV_8U);
    /*--openingThenClosing--noise--noiseNum(Amplitude....)--Size---*/
    Mat OC_GNA_10(row, col, CV_8U);
    Mat OC_GNA_30(row, col, CV_8U);
    Mat OC_SAP_01(row, col, CV_8U);
    Mat OC_SAP_005(row, col, CV_8U);
    /*--ClosingThenOpening--noise--noiseNum(Amplitude....)--Size---*/
    Mat CO_GNA_10(row, col, CV_8U);
    Mat CO_GNA_30(row, col, CV_8U);
    Mat CO_SAP_01(row, col, CV_8U);
    Mat CO_SAP_005(row, col, CV_8U);
    Mat apple(row, col, CV_8U); 
    //cout << "==================Gaussian noise 10 & 30 ===============" << endl;
    GNA10 = GaussianNoiseAmplitude(row, col, 10, src);
    GNA30 = GaussianNoiseAmplitude(row, col, 30, src);
    //cout << "==================salt-and-pepper noise 0.05 & 1 ===============" << endl;
    SAP005 = saltAndPepperUniform(row, col, 0.05, src);
    SAP01 = saltAndPepperUniform(row, col, 0.1, src);
    //cout << "===============Median Filter==================" << endl;
    MF_GNA_10_9 = medianFilter(row, col, 9, GNA10);
    MF_GNA_30_9 = medianFilter(row, col, 9, GNA30);
    MF_GNA_10_25 = medianFilter(row, col, 25, GNA10);
    MF_GNA_30_25 = medianFilter(row, col, 25, GNA30);
    MF_SAP_005_9 = medianFilter(row, col, 9, SAP005);
    MF_SAP_01_9 = medianFilter(row, col, 9, SAP01);
    MF_SAP_005_25 = medianFilter(row, col, 25, SAP005);
    MF_SAP_01_25 = medianFilter(row, col, 25, SAP01);
    apple = medianFilter(1019,950, 9, src2);
    //cout << "===============Box Filter==================" << endl;
    BF_GNA_10_9 = boxFilter(row, col, 9, GNA10);
    BF_GNA_30_9 = boxFilter(row, col, 9, GNA30);
    BF_GNA_10_25 = boxFilter(row, col, 25, GNA10);
    BF_GNA_30_25 = boxFilter(row, col, 25, GNA30);
    BF_SAP_01_9 = boxFilter(row, col, 9, SAP01);
    BF_SAP_005_9 = boxFilter(row, col, 9, SAP005);
    BF_SAP_01_25 = boxFilter(row, col, 25, SAP01);
    BF_SAP_005_25 = boxFilter(row, col, 25, SAP005); 
    //cout << "===============Opening then Closing==================" << endl;
    OC_GNA_10 = openThenClose(row, col, GNA10);
    OC_GNA_30 = openThenClose(row, col, GNA30); 
    OC_SAP_01 = openThenClose(row, col, SAP01);
    OC_SAP_005 = openThenClose(row, col, SAP005);
    //cout << "===============Closing then Opening==================" << endl;
    CO_GNA_10 = closeThenOpen(row, col, GNA10);
    CO_GNA_30 = closeThenOpen(row, col, GNA30);
    CO_SAP_01 = closeThenOpen(row, col, SAP01);
    CO_SAP_005 = closeThenOpen(row, col, SAP005);
    //cout << ==================show & save picture =============== << endl;
    
    showSavePicture(src,"src","src.bmp");
    showSavePicture(apple,"test_1_MOD_12_8","test_1_MOD_12_8_good.jpg");
    showSavePicture(GNA10,"GNA10","GNA10.bmp");
    SNR(src, GNA10);
    showSavePicture(GNA30,"GNA30","GNA30.bmp");
    SNR(src, GNA30);
    showSavePicture(SAP005,"SAP005","SAP005.bmp");
    SNR(src, SAP005);
    showSavePicture(SAP01,"SAP01","SAP01.bmp");
    SNR(src, SAP01);

    showSavePicture(MF_GNA_10_9,"MF_GNA_10_9","MF_GNA_10_9.bmp");
    SNR(src, MF_GNA_10_9);
    showSavePicture(MF_GNA_30_9,"MF_GNA_30_9","MF_GNA_30_9.bmp");
    SNR(src, MF_GNA_30_9);
    showSavePicture(MF_GNA_10_25,"MF_GNA_10_25","MF_GNA_10_25.bmp");
    SNR(src, MF_GNA_10_25);
    showSavePicture(MF_GNA_30_25,"MF_GNA_30_25","MF_GNA_30_25.bmp");
    SNR(src, MF_GNA_30_25);
    showSavePicture(MF_SAP_01_9,"MF_SAP_01_9","MF_SAP_01_9.bmp");
    SNR(src, MF_SAP_01_9);
    showSavePicture(MF_SAP_005_9,"MF_SAP_005_9","MF_SAP_005_9.bmp");
    SNR(src, MF_SAP_005_9);
    showSavePicture(MF_SAP_01_25,"MF_SAP_01_25","MF_SAP_01_25.bmp");
    SNR(src, MF_SAP_01_25);
    showSavePicture(MF_SAP_005_25,"MF_SAP_005_25","MF_SAP_005_25.bmp");
    SNR(src, MF_SAP_005_25);

    showSavePicture(BF_GNA_10_9,"BF_GNA_10_9","BF_GNA_10_9.bmp");
    SNR(src, BF_GNA_10_9);
    showSavePicture(BF_GNA_30_9,"BF_GNA_30_9","BF_GNA_30_9.bmp");
    SNR(src, BF_GNA_30_9);
    showSavePicture(BF_GNA_10_25,"BF_GNA_10_25","BF_GNA_10_25.bmp");
    SNR(src, BF_GNA_10_25);
    showSavePicture(BF_GNA_30_25,"BF_GNA_30_25","BF_GNA_30_25.bmp");
    SNR(src, BF_GNA_30_25);
    showSavePicture(BF_SAP_01_9,"BF_SAP_01_9","BF_SAP_01_9.bmp");
    SNR(src, BF_SAP_01_9);
    showSavePicture(BF_SAP_005_9,"BF_SAP_005_9","BF_SAP_005_9.bmp");
    SNR(src, BF_SAP_005_9);
    showSavePicture(BF_SAP_01_25,"BF_SAP_01_25","BF_SAP_01_25.bmp");
    SNR(src, BF_SAP_01_25);
    showSavePicture(BF_SAP_005_25,"BF_SAP_005_25","BF_SAP_005_25.bmp");
    SNR(src, BF_SAP_005_25);

    showSavePicture(OC_GNA_10,"OC_GNA_10","OC_GNA_10.bmp");
    SNR(src, OC_GNA_10);
    showSavePicture(OC_GNA_30,"OC_GNA_30","OC_GNA_30.bmp");
    SNR(src, OC_GNA_30);
    showSavePicture(OC_SAP_01,"OC_SAP_01","OC_SAP_01.bmp");
    SNR(src, OC_SAP_01);
    showSavePicture(OC_SAP_005,"OC_SAP_005","OC_SAP_005.bmp");
    SNR(src, OC_SAP_005);

    showSavePicture(CO_GNA_10,"CO_GNA_10","CO_GNA_10.bmp");
    SNR(src, CO_GNA_10);
    showSavePicture(CO_GNA_30,"CO_GNA_30","CO_GNA_30.bmp");
    SNR(src, CO_GNA_30);
    showSavePicture(CO_SAP_01,"CO_SAP_01","CO_SAP_01.bmp");
    SNR(src, CO_SAP_01);
    showSavePicture(CO_SAP_005,"CO_SAP_005","CO_SAP_005.bmp");
    SNR(src, CO_SAP_005);
    waitKey(0);
    return 0;
}
