#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <cv.h>
#include <stdlib.h>

using namespace std;
using namespace cv;


bool compareTest(int now[][512], int last[][512])
{
    int i=0,j=0;
    for(i=0; i<512; i++)
    {
        for(j=0; j<512; j++)
        {
            if(now[i][j] != last[i][j])
                return false;
        }
    }
    return true;
}

int main(int argc,char** argv )
{
    Mat src;
    int i=0, j=0, k=0;


    src = imread("lena_binary.bmp",CV_LOAD_IMAGE_GRAYSCALE);
    // dst.create( src.size(),  src.type());



    int row = src.rows;
    int col = src.cols;
    //Mat tmp(row,col,CV_8U);//store tmp group
    Mat test(row,col,CV_8U);    



    int numOfGroup = 0;//group's number
    int countOfGroup = 0;//total count of group
    int groupArr[100000]={-1};
    int tmp[512][512] = {0};//point pixel's group
    int lastmp[512][512] = {0};//use to compare
   
    
    for(i=0; i<row; i++)
    {
        for(j=0; j<col; j++)
        {
            if(src.at<unsigned char>(i,j)==255)//white
            {
                numOfGroup++;
                tmp[i][j] = numOfGroup;
                //cout << i << "," << j << ":" << tmp[i][j] << endl ;
            }
        }
    }

    while(true)
    {
        for(i=0; i<row; i++)
        {
            for(j=0; j<col; j++)
            {
                if(tmp[i][j]>tmp[i-1][j] && tmp[i-1][j]!=0 && i!=0)
                    tmp[i][j] = tmp[i-1][j];
                if(tmp[i][j]>tmp[i][j-1] && tmp[i][j-1]!=0 && j!=0)
                    tmp[i][j] = tmp[i][j-1];
                if(tmp[i][j]>tmp[i+1][j] && tmp[i+1][j]!=0 && i!=511)
                    tmp[i][j] = tmp[i+1][j];
                if(tmp[i][j]>tmp[i][j+1] && tmp[i][j+1]!=0 && j!=511)
                    tmp[i][j] = tmp[i][j+1];
            
            }
        
        }
        
        if(compareTest(tmp,lastmp))
             break;
        
        for(i=0; i<row; i++)//backup
        {
             for(j=0; j<col; j++)
             {
                 lastmp[i][j] = tmp[i][j];
             }
        }
    }

    /*for(i=0; i<row; i++)
    {
        for(j=0; j<col; j++)
        {
             test.at<unsigned char>(i,j) = 0;
             if(tmp[i][j] != 0)
                 cout << "["<< i<< "] [" << j << "]:" << tmp[i][j] << endl;
             if(tmp[i][j] == 1)
             {
                 test.at<unsigned char>(i,j) = 255;
             }
        }
    }*/

    for(i=0; i<512; i++)
    {
         for(j=0; j<512; j++)
         {
             if(tmp[i][j] != 0)
             {
                 for(k=0; k<countOfGroup; k++)
                 {
                     if(tmp[i][j] == groupArr[k]) 
                     {
                         //cout << "break" << endl;
                         break;
                     }
                 }
                 if(k == countOfGroup)
                 {
                     groupArr[countOfGroup] = tmp[i][j];
                     countOfGroup++;
                 }
             }
         }
    }
  

    /*for(k=0; k<countOfGroup; k++)
    {
        cout << groupArr[k] <<","<< countOfGroup<< endl;
    }*/
    int coordinate[983][7] = {0}; //minX,maxX,minY,maxY,centerX,centerY,totalPixel   
    bool first = true;
    for(k=0;k<countOfGroup;k++)
    {
        for(i=0; i<512; i++)
        {
            for(j=0; j<512; j++)
            {
                
                if(groupArr[k] == tmp[i][j])
                {
                    if(first)
                    {
                        coordinate[k][0] = i;
                        coordinate[k][1] = i;
                        coordinate[k][2] = j;
                        coordinate[k][3] = j;
                        coordinate[k][4] = i;
                        coordinate[k][5] = j;
                        first = false;
                        coordinate[k][6] = 1;
                    }
                    else
                    {
                        if(coordinate[k][0] > i)
                            coordinate[k][0] = i;
                        if(coordinate[k][1] < i)
                            coordinate[k][1] = i;
                        if(coordinate[k][2] > j)
                            coordinate[k][2] = j;
                        if(coordinate[k][3] < j)
                            coordinate[k][3] = j;
                        
                       // coordinate[k][4] = (coordinate[k][4]*coordinate[k][6]+i)/(coordinate[k][6]+1);
                       // coordinate[k][5] = (coordinate[k][5]*coordinate[k][6]+j)/(coordinate[k][6]+1);
                        coordinate[k][4] += i;
                        coordinate[k][5] += j;
                        coordinate[k][6]++;
                    }
                }
            }
        }
        first = true;
        coordinate[k][4] = coordinate[k][4] / coordinate[k][6];
        coordinate[k][5] = coordinate[k][5] / coordinate[k][6];
    }
    

   /* for(i=0; i<983; i++)
    {
             cout<<coordinate[i][0]<<","<<coordinate[i][1]<<","<<coordinate[i][2]<<","<<coordinate[i][3]<<","<<coordinate[i][4]<<","<<coordinate[i][5]<<","<<coordinate[i][6]<<","<<endl;
    }*/
    
    for(i=0; i<col; i++)
    {
        for(j=0; j<row; j++)
        {
            test.at<unsigned char>(i,j) = src.at<unsigned char>(i,j);
        }

    }


    int hh =0;
    for(k=0;k<countOfGroup;k++)
    {
        if(coordinate[k][6] > 500)
        {
            for(i=coordinate[k][0]; i< coordinate[k][1]; i++)
                test.at<unsigned char>(i,coordinate[k][2]) = 128;

            for(i=coordinate[k][0]; i< coordinate[k][1]; i++)
                test.at<unsigned char>(i,coordinate[k][3]) = 128;
        
            for(i=coordinate[k][2]; i< coordinate[k][3]; i++)
                test.at<unsigned char>(coordinate[k][1],i) = 128;
      
            for(i=coordinate[k][2]; i< coordinate[k][3]; i++)
                test.at<unsigned char>(coordinate[k][0],i) = 128;

            //int centerX = (coordinate[k][2]+coordinate[k][3])/2;
            //int centerY = (coordinate[k][0]+coordinate[k][1])/2; 
            putText(test,"+",Point(coordinate[k][5],coordinate[k][4]),FONT_HERSHEY_PLAIN,0.5,128);
            hh++;
            cout << "Hh" << hh << endl;
        }

    }

    /*for(k=0;k<countOfGroup;k++)
    {
        if(coordinate[k][6] > 250) 
        putText(test,"X",Point(coordinate[k][4],coordinate[k][5]),FONT_HERSHEY_PLAIN,1,128);

    }*/
    //cout << countOfGroup << endl;
    //cout << i << "," << j << ":" << tmp[511][476] << endl ;    
    namedWindow( "connected", WINDOW_AUTOSIZE );
    imshow( "connected", test );
    imwrite("connected.bmp", test );
    //namedWindow( "connected", WINDOW_AUTOSIZE );
    //imshow( "connected", dst );

    //imwrite("connected.bmp", dst );

    waitKey(0);
    return 0;

}

