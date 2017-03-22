#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>     
#include <stdio.h>
#include <sys/time.h>
using namespace cv;  
using namespace std;

#include <stdlib.h>  
#include <errno.h>  
#include <string.h>  
#include <sys/types.h>  
#include <netinet/in.h>  
#include <sys/socket.h>  
#include <sys/wait.h>  
#include <arpa/inet.h>  
#include <unistd.h>  
#define SERVPORT 3333  
#define MAXDATASIZE 100  
#define SERVER_IP "127.0.0.1"  

typedef struct MyMessage{  
    int ID;  
    char info[256];  
}MyMessage,*pMyMessage; 


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//\B3\B5\C5\C6\C2\D6\C0\AA\CD\E2\BDӾ\D8\D5\F3ɸѡ\BA\AF\CA\FD
bool imgVerifySizes(Rect mr,int d,int u)
  {
      float error = 0.5;//aspect\D4\CA\D0\ED\B5\C4ƫ\B2\EE\C2\CA(errorԽСҪ\C7\F3Խ\D1ϸ\F1)
      float aspect = 4;//\BE\D8\D0εĳ\A4\BF\ED\B1\C8
      float high=d-u;
	//\B8Ľ\F8\CB㷨\A3\AC\C3\E6\BB\FD\B2\C9\D3\C3\D0\C2\D4\F6\B5ļ\EC\B2\E2\D0\D0\C1\D0֮\BC\E4\B5Ĳ\EE\BE࣬\B3\CB\D2\D4\CBı\B6\B4\F3ԼΪ\B3\B5\C5\C6
     int min= 0.5*4*high*high; //\D4\CA\D0\ED\B5\C4\D7\EEС\BE\D8\D0\CE\C3\E6\BB\FD\A3\AC\B5\A5λ\CA\C7\CF\F1\CBأ\AC44*14*5=3080
     int max= 1.5*4*high*high; //\D4\CA\D0\ED\B5\C4\D7\EE\B4\F3\BE\D8\D0\CE\C3\E6\BB\FD\A3\AC44*14*30=18408
     float rmin= aspect-aspect*error;//\D4\CA\D0\ED\B5\C4\D7\EEС\B3\A4\BF\ED\B1ȣ\AC4*0.8=3.2
     float rmax= aspect+aspect*error;//\D4\CA\D0\ED\B5\C4\D7\EE\B4󳤿\ED\B1ȣ\AC4*1.2=4.8
 
     int area= mr.height * mr.width;//\C2\D6\C0\AA\BE\D8\D0ε\C4ʵ\BC\CA\C3\E6\BB\FD
     float r = (float)mr.width / (float)mr.height;//\C2\D6\C0\AA\BE\D8\D0ε\C4ʵ\BCʳ\A4\BF\ED\B1\C8

     if(r < 1)//\C8\E7\B9\FB\B3\A4\BF\ED\B1\C8С\D3\DA1\A3\AC\BD\AB\B3\A4\D3\EB\BF\ED\BB\A5\B5\F7һ\CF\C2
     {
         r= (float)mr.height / (float)mr.width;
     }
 
     if(( area < min || area > max ) || ( r < rmin || r > rmax ))//\C3\E6\BB\FD\BAͳ\A4\BF\ED\B1ȱ\D8\D0\EBͬʱ\C2\FA\D7\E3Ҫ\C7\F3
     {
         return false;
     }
     else
     {
         return true;
     }
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//\D7ַ\FB\C2\D6\C0\AA\CD\E2\BDӾ\D8\D5\F3ɸѡ\BA\AF\CA\FD
bool roiVerifySizes(Rect mr, Mat roi)
  {
      float error = 0.6;//aspect\D4\CA\D0\ED\B5\C4ƫ\B2\EE\C2\CA(errorԽСҪ\C7\F3Խ\D1ϸ\F1)
      float aspect = 1.8;//\BE\D8\D0εĳ\A4\BF\ED\B1\C8
     //int min= 100; //\D4\CA\D0\ED\B5\C4\D7\EEС\BE\D8\D0\CE\C3\E6\BB\FD\A3\AC\B5\A5λ\CA\C7\CF\F1\CBأ\AC35*20*0.8=560
     //int max= 1000; //\D4\CA\D0\ED\B5\C4\D7\EE\B4\F3\BE\D9\D0\D0\C3\E6\BB\FD\A3\AC35*20*1.2=840
     float rmin= aspect-aspect*error;//\D4\CA\D0\ED\B5\C4\D7\EEС\B3\A4\BF\ED\B1ȣ\AC4*0.7=2.8
     float rmax= aspect+aspect*error;//\D4\CA\D0\ED\B5\C4\D7\EE\B4󳤿\ED\B1ȣ\AC4*1.3=5.2
 
     int area= mr.height * mr.width;//\C2\D6\C0\AA\BE\D8\D0ε\C4ʵ\BC\CA\C3\E6\BB\FD
     float r = (float)mr.width / (float)mr.height;//\C2\D6\C0\AA\BE\D8\D0ε\C4ʵ\BCʳ\A4\BF\ED\B1\C8

     if(r < 1)//\C8\E7\B9\FB\B3\A4\BF\ED\B1\C8С\D3\DA1\A3\AC\BD\AB\B3\A4\D3\EB\BF\ED\BB\A5\B5\F7һ\CF\C2
     {
         r= (float)mr.height / (float)mr.width;
     }

     if( mr.height < (0.8*roi.rows ) || mr. width < 4 )//\C9\E1\C6\FAԭ\B7\BD\B7\A8\A3\AC\D2\F2Ϊԭ\B7\BD\B7\A8\B5ľ\D6\CF\DE\D0Էǳ\A3\B4󣬲\BB\C4\DCʶ\B1\F01\A3\A8\B3\A4\BF\ED\B1Ⱥ\CD\C3\E6\BB\FD\B6\BC\B2\BB\B4\EF\B1꣩\A3\AC\B6\F8\C7\D2\C8\DD\D2ױ\BB\B8\C9\C8ţ\AC\BC\F2\BB\AF\D4\CB\CB\E3\B9\FD\B3̣\AC\B4\F3\D3\DAroi\B5\C40.8\B1\B6\BC\B4\BF\C9
//\C3\E6\BB\FD\BAͳ\A4\BF\ED\B1ȱ\D8\D0\EBͬʱ\C2\FA\D7\E3Ҫ\C7\F3
     {
         return false;
     }
     else
     {
         return true;
     }
}

int main(int argc, char* argv[]){


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//\B3\B5\C5ƶ\A8λ\B2\BF\B7\D6
//\BC\C6ʱ\B3\F5ʼ\BB\AF
   char hello[6];
  //  hello[7]='\n';
  /*  unsigned int ts,te;
    unsigned int sdx,edx;
    unsigned long long int clock_cycles;
    unsigned int max=1<<31;
    unsigned long long int max0=(unsigned long long int )max*2;
		__asm__ __volatile__(
   			"rdtsc\n\t"
   			:"=a"(ts),"=d"(sdx));
	struct timeval tpstart,tpend; 
	float timeuse; 
	gettimeofday(&tpstart,NULL); */
//\BC\C6ʱ\B3\F5ʼ\BB\AF\BD\E1\CA\F8
	Mat img=imread("car.jpg");
	Mat img_gray;
	Mat img_resize=Mat::zeros(640,480,CV_8UC3);//\CFȶԴ\F3С\BD\F8\D0\D0\CF\DE\D6\C6,\CC\E1\B8\DF\D4\CB\D0\D0\CBٶ\C8
	resize(img, img_resize, img_resize.size());
	imshow("img_resize", img_resize);
	cvtColor(img_resize, img_gray, CV_BGR2GRAY);
	Mat img_blur;
	blur(img_gray, img_blur, Size(5,5));
	Mat img_sobel;
	Sobel(img_blur, img_sobel, CV_8U, 1, 0, 3, 1, 0, BORDER_DEFAULT);
	imshow("img_sobel",img_sobel);
	Mat img_threshold; 
	threshold(img_sobel, img_threshold, 0, 255, CV_THRESH_OTSU+CV_THRESH_BINARY);
	imshow("img_threshold",img_threshold);//\B6\D4\C6\E4\BD\F8\D0б\DF\D1ؼ\EC\B2⣬\B2\A2\C7Ҷ\FEֵ\BB\AF
	//\D7\D4\D4\F6\B8Ľ\F8\B2\BF\B7֣\ACĿ\B5\C4\D4\DA\D3ھ\DB\C0\E0\CB\E3\B3\F6\C1\AC\D0\F8\B5ı\DF\D1\D8\CC\F8\B1\E4\B4\CE\CA\FD\B7ḻ\B5\C4\C7\F8\D3\F2
	int height,width;
	height=img_threshold.rows;
	width=img_threshold.cols;
	int m,x,y;
	m=0;
	int a[height];
	int b[height];
	int tag;
	for(x=height;x>=1;x--)//\8F\C4\CF\C2\CD\F9\C9\CF
	{
 	tag=0;
 	for(y=1;y<width;y++)
   	  {
    	   if(img_threshold.at<uchar>(x,y)!=img_threshold.at<uchar>(x,y+1))// \B1\DF\D1ؼ\EC\B2\E2
     	   {
    		 tag=tag+1;
    	   }
   	  }
	if(tag>24)
	  {
	   a[m]=x;
	   m=m+1;
	  }
	}
	int n=1;	
	for(m=1;m<height-1;m++)
	 {
    	  if(a[m]-a[m+1]!=1 && a[m+1]-a[m+2]==1)//\CC\F8\B1\E4\B4\F3\D3\DA24\B5\C4\C9ϱ\DF\D1\D8
       		{
		b[n]=a[m+1];//\C6\E6\CA\FD\BC\C7¼\D7\F8\B1\EA
       		 b[n+1]=1;//ż\CA\FD\BC\C6\CA\FD
      		}
	  if(m!=1 && a[m]-a[m+1]==1 && a[m+1]-a[m+2]==1)//һֱ\CC\F8\B1䶼\B4\F3\D3\DA24\C7ҷǵ\DAһ\D7\E9
      		 {
		b[n+1]=b[n+1]+1;//\BC\C6\CA\FD
       		}
    	 if(m==1 && a[m]-a[m+1]==1 && a[m+1]-a[m+2]==1)//һֱ\B4\F3\D3\DA24\C7\D2Ϊ\B5\DAһ\D0\D0
       		{
		b[n]=a[m];
        	b[n+1]=2;
       		}
   	 if(a[m]-a[m+1]==1 && a[m+1]-a[m+2]!=1)//\CC\F8\B1\E4\B4\F3\D3\DA24\B5\C4\CF\C2\D1\D8
      		 {
		b[n+1]=b[1,n+1]+1;
        	n=n+2;//\C7л\BB\B5\BD\CF\C2һ\D7\E9
       		}
	}
	int i;
	int flag,temp,d,u;
	flag=0;
	temp=0;
	for(n=2;n<=height;n+=2)
  	{
  	  if(b[1,n]>20 && flag==0)//Ѱ\D5Ҵ\F3\D3\DA20\B4\CE\CC\F8\B1\E4\B5ą^\D3\F2\A3\AC\C8\E7\B9\FB\D3У\AC\84t\D5J\9E\E9\CA\C7܇\C5\C6
      		 {
		temp=n;flag=1;
      		 }
 	  }
	if(temp==0)
    	{
	u=b[1];
    	d=u-b[2];
     	u=u+10;
    	d=d-10;
    	}
	else
   	 {
   	 // u=b[temp-1];
   	//  d=u-b[temp];
  	 //   u=u+10;
   	//   d=d-10;
     	u=b[temp-1]+15;
	d=u-b[temp]-20;//\B7ſ\ED\C3\C5\CF\DE
   	 }
	cv::Mat roi_row;
	roi_row = img_threshold(cv::Range(d,u),cv::Range(1,width-1));
	cv::Mat roi_row_disp;
	roi_row_disp=img_resize(cv::Range(d,u),cv::Range(1,width-1));
	cv::imshow("roi_row",roi_row); 
	//\D7\D4\D4\F6\CD\EA\B1\CF
	Mat img_close;
	Mat element = getStructuringElement(MORPH_RECT, Size(17, 3) ); 
	morphologyEx(roi_row, img_close, CV_MOP_CLOSE, element);
	imshow("img_close",img_close);//\B6\D4ͼ\CF\F1\BD\F8\D0бղ\D9\D7\F7
	Mat img_close2 = img_close.clone();
	vector< vector< Point> > img_contours; //\B4\E6\B7\C5\C2\D6\C0\AA\B5\C4\CF\F2\C1\BF
	findContours(img_close2,  
           img_contours,           
           CV_RETR_EXTERNAL,    
           CV_CHAIN_APPROX_NONE);
	Mat img_showcontours;
	roi_row_disp.copyTo(img_showcontours);
	drawContours(img_showcontours,img_contours,-1,Scalar(0,255,0),2);
	//\D4\DAimg_showcontours\D6л\AD\B3\F6\CB\F9\D3е\C4\C2\D6\C0\AA\A3\ACScalar(0,255,0)\B4\FA\B1\ED\C2\CCɫ
	imshow("img_showcontours",img_showcontours);//\D3\C3\D3\DA\CF\D4ʾ\CB\F9\D3\D0\C2\D6\C0\AA

	Mat img_result; //\D3\C3\D3\DA\CF\D4ʾɸѡ\BA\F3\B5\C4\C2\D6\C0\AA\BE\D8\D0\CE
	roi_row_disp.copyTo(img_result);  
	vector<vector<Point> >::iterator img_itc= img_contours.begin();  //\B6\A8\D2\E5һ\B8\F6\B5\FC\B4\FA\C6\F7
	vector<Rect> img_rects;    
    while (img_itc!=img_contours.end()) 
	{   
         Rect img_mr= boundingRect(Mat(*img_itc));//\BB\AD\D7\EE\B4\F3\CD\E2\BD\D3\D5\FD\B7\BD\D0\CE
         if( !imgVerifySizes(img_mr,d,u))//\B2\E2\CA\D4\CAǷ\F1\C2\FA\D7㳤\BF\ED\B1\C8\C0\FD
	  {  
           img_itc= img_contours.erase(img_itc);  
          }
	else
	  {  
           ++img_itc;  
           img_rects.push_back(img_mr);
	   rectangle(img_result, img_mr, Scalar(0,255,0));//\D4\DAͼƬ\C9ϻ\AD\B3\F6ѡ\D6е\C4\C1\AAͨ\D3\F2
          }  
	}  
	imshow("img_result",img_result);
	Mat roi=roi_row_disp(Rect(img_rects[0].x,img_rects[0].y,img_rects[0].width,img_rects[0].height));
	imshow("roi",roi);
	//\B4˶\CE\D2\D4\C9\CF\CD\EAȫ\B5\F7ͨ

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//\D7ַ\FB\B7ָ\B7\D6

	Mat roi_gray;
	cvtColor(roi, roi_gray, CV_BGR2GRAY);//\CA\D7\CF\C8ת\BB\AFΪ\BBҶ\C8ͼ
	Mat roi_threshold;
	threshold(roi_gray, roi_threshold, 0, 255, CV_THRESH_OTSU+CV_THRESH_BINARY);//\D4\D9\D3ô\F3\BD\F2\E3\D0ֵ\CB㷨\B6\FEֵ\BB\AF
	Mat roi_threshold2;
	Mat roi_result;
//	roi_threshold.copyTo(roi_threshold2);
	roi_threshold.copyTo(roi_result);//\B8\B4\D6Ƹ\B1\B1\BE
	cvtColor(roi_result, roi_result, CV_GRAY2RGB); 
	imshow("roi_result",roi_result);
/*	// \CF\C2\C3\E6\D7\D4\D4\F6ȥȥ\D4\EB\CB㷨
	int m[roi_threshold.cols]={0};
	int i,j;
	for (i=0;i<roi.cols;i++) 
	{
    		for (j=1;j<roi_threshold.rows;j++) 
		{
        	if(roi_threshold.at<uchar>(i,j)==255) 
	 	 {         
        	    m[i]=m[i]+1;//\B4\B9ֱͶӰ 
         	 } 
    		} 
	} 

	int k=roi_threshold.rows;
	int u=roi_threshold.rows; 
	for (i=0;i<k;i++)
	{
	    if ( (m[i]> (roi_threshold.cols*0.15) ) && ( m[i]< (roi_threshold.cols*0.8) ) ) 
		{
        	u=u-1; 
		}    
	} 
	for (i=0;i<u;i++) 
	{
	    for (j=0;j<roi_threshold.cols;j++) 
	    {
	        if (roi_threshold.at<uchar>(i,j)=255) 
		{
	           roi_threshold.at<uchar>(i,j)=0;//ȥ\B3\FD\C9ϱ߿\F2\BA\CD\C9ϱߵ\C4í\B6\A4 
	        }
	    } 
	 }
	imshow("roi_threshold",roi_threshold);
	//\CD\EA\B1\CF			*/

	roi_threshold.copyTo(roi_threshold2);
	vector< vector< Point> > roi_contours; 
	findContours(roi_threshold2,  
            roi_contours,   
            CV_RETR_EXTERNAL,   
            CV_CHAIN_APPROX_NONE);//\D4ٴε\F7\D3ò\E9\D5\D2\C2\D6\C0\AA\B5ĺ\AF\CA\FD
	//\CF\C2\C3\E6\CA\C7\D7Լ\BA\D4\F6\BCӵ\C4
	Mat roi_showcontours;
	roi.copyTo(roi_showcontours);
	drawContours(roi_showcontours,roi_contours,-1,Scalar(0,255,0),2);
	//imshow("roi_showcontours",roi_showcontours);
	//\C4\DC\D5\FDȷ\BB\AD\B3\F6\C6\E4\C2\D6\C0\AA
	vector<vector<Point> >::iterator roi_itc= roi_contours.begin(); //\B9ʼ\BC\D6\D8ʩ 
	vector<Rect> roi_rects;    
    while (roi_itc!=roi_contours.end())
	{   
       Rect roi_mr= boundingRect(Mat(*roi_itc));
       if( !roiVerifySizes(roi_mr,roi))//\D5\E2\B4γ\A4\BF\ED\B1ȸ\FC\BB\BB\C1\CB
	 {  
           roi_itc= roi_contours.erase(roi_itc);//\B2\C1ȥ
         }
	else
	 {  
           ++roi_itc;  
           roi_rects.push_back(roi_mr);//\B9\B2\D3г\FD\C1\CB6\B8\F6\D7ַ\FB\A3\AC\D6\D0\CE\C4\D7ַ\FB\B2\BB\D4\DA\C6\E4\D6У\ACԪ\CB\D80-5\B5\C4˳\D0\F2\B5ĳ\B5\C5\C6\D7ַ\FB\B4\D3\D3\D2\CF\F2\D7\F3\B5\C4˳\D0\F2
	   rectangle(roi_result, roi_mr, Scalar(0,255,0));
	   imshow("roi_result",roi_result);
	 }  
	} 
//\D5\E2\C0\EF\D3\D0\CE\CA\CC\E2

	Mat roi1 = roi_threshold(Rect(roi_rects[5].x-3-roi_rects[5].width,roi_rects[5].y,roi_rects[5].width,roi_rects[5].height));
	//\D6\D0\CE\C4\D7ַ\FB\B5\C4λ\D6\C3\C5ж\A8\CA\C7ͨ\B9\FD\D6\D0\CE\C4ǰһ\B8\F6\D7ַ\FB\B5\B9\CD\C6λ\D6õõ\BD\B5\C4
	Mat roi2 = roi_threshold(Rect(roi_rects[5].x,roi_rects[5].y,roi_rects[5].width,roi_rects[5].height));
	Mat roi3 = roi_threshold(Rect(roi_rects[4].x,roi_rects[4].y,roi_rects[4].width,roi_rects[4].height));
	Mat roi4 = roi_threshold(Rect(roi_rects[3].x,roi_rects[3].y,roi_rects[3].width,roi_rects[3].height));
	Mat roi5 = roi_threshold(Rect(roi_rects[2].x,roi_rects[2].y,roi_rects[2].width,roi_rects[2].height));
	Mat roi6 = roi_threshold(Rect(roi_rects[1].x,roi_rects[1].y,roi_rects[1].width,roi_rects[1].height));
	Mat roi7 = roi_threshold(Rect(roi_rects[0].x,roi_rects[0].y,roi_rects[0].width,roi_rects[0].height));
	//imshow("\D7ַ\FB1",roi1);
	//imshow("\D7ַ\FB2",roi2);
	//imshow("\D7ַ\FB3",roi3);
	//imshow("\D7ַ\FB4",roi4);
	//imshow("\D7ַ\FB5",roi5);
	//imshow("\D7ַ\FB6",roi6);
	//imshow("\D7ַ\FB7",roi7);


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//\D7ַ\FBʶ\B1𲿷\D6	

	//\D7ַ\FBͳһ\B4\F3СΪ20\A1\C120
	Mat dst1=Mat::zeros(40,20,CV_8UC3);//\B7\B5\BB\D8һ\B8\F6\D6ƶ\A8\B4\F3С\BA\CD\C0\E0\D0͵\C4ȫ\C1\E3\BE\D8\D5\F3
	resize(roi1, dst1, dst1.size());//\BD\ABroiͳһ\B5\BDdst\B5Ĵ\F3С\A3\AC\D2\D4ʵ\CF\D6\CB\F9\D3\D0\D7ַ\FBͳһ\B4\F3С
	Mat dst2=Mat::zeros(40,20,CV_8UC3);
	resize(roi2, dst2, dst2.size());
	Mat dst3=Mat::zeros(40,20,CV_8UC3);
	resize(roi3, dst3, dst3.size());
	Mat dst4=Mat::zeros(40,20,CV_8UC3);
	resize(roi4, dst4, dst4.size());
	Mat dst5=Mat::zeros(40,20,CV_8UC3);
	resize(roi5, dst5, dst5.size());
	Mat dst6=Mat::zeros(40,20,CV_8UC3);
	resize(roi6, dst6, dst6.size());
	Mat dst7=Mat::zeros(40,20,CV_8UC3);
	resize(roi7, dst7, dst7.size());

	//\D7ַ\FB\B6\FEֵ\BB\AF
	threshold(dst1, dst1, 0, 255, CV_THRESH_OTSU+CV_THRESH_BINARY);
	threshold(dst2, dst2, 0, 255, CV_THRESH_OTSU+CV_THRESH_BINARY);
	threshold(dst3, dst3, 0, 255, CV_THRESH_OTSU+CV_THRESH_BINARY);
	threshold(dst4, dst4, 0, 255, CV_THRESH_OTSU+CV_THRESH_BINARY);
	threshold(dst5, dst5, 0, 255, CV_THRESH_OTSU+CV_THRESH_BINARY);
	threshold(dst6, dst6, 0, 255, CV_THRESH_OTSU+CV_THRESH_BINARY);
	threshold(dst7, dst7, 0, 255, CV_THRESH_OTSU+CV_THRESH_BINARY);
    
	//\BD\ABdst\B7\C5\C8\EB\CA\FD\D7\E9\D6У\AC\B7\BD\B1\E3\D2Ժ\F3\BD\F8\D0\D0ѭ\BB\B7\B2\D9\D7\F7
	vector<Mat> dst;
	dst.push_back(dst1);
	dst.push_back(dst2);
	dst.push_back(dst3);
	dst.push_back(dst4);
	dst.push_back(dst5);
	dst.push_back(dst6);
	dst.push_back(dst7);

	//\B6\C1\C8\EB\CA\FD\D7\D6ģ\B0\E5ͼƬ\A3\AC\B6\FEֵ\BB\AF\A3\AC\B2\A2\B7\C5\C8\EBnumbers\CA\FD\D7\E9\D6\D0
 	vector<Mat> numbers;
	Mat n0 = imread("0.jpg",0);
	numbers.push_back(n0);
	threshold(numbers[0], numbers[0], 0, 255, CV_THRESH_OTSU+CV_THRESH_BINARY);
	Mat n1 = imread("1.jpg",0);
	numbers.push_back(n1);
	threshold(numbers[1], numbers[1], 0, 255, CV_THRESH_OTSU+CV_THRESH_BINARY);
	Mat n2 = imread("2.jpg",0);
	numbers.push_back(n2);
	threshold(numbers[2], numbers[2], 0, 255, CV_THRESH_OTSU+CV_THRESH_BINARY);
	Mat n3 = imread("3.jpg",0);
	numbers.push_back(n3);
	threshold(numbers[3], numbers[3], 0, 255, CV_THRESH_OTSU+CV_THRESH_BINARY);
	Mat n4 = imread("4.jpg",0);
	numbers.push_back(n4);
	threshold(numbers[4], numbers[4], 0, 255, CV_THRESH_OTSU+CV_THRESH_BINARY);
	Mat n5 = imread("5.jpg",0);
	numbers.push_back(n5);
	threshold(numbers[5], numbers[5], 0, 255, CV_THRESH_OTSU+CV_THRESH_BINARY);
	Mat n6 = imread("6.jpg",0);
	numbers.push_back(n6);
	threshold(numbers[6], numbers[6], 0, 255, CV_THRESH_OTSU+CV_THRESH_BINARY);
	Mat n7 = imread("7.jpg",0);
	numbers.push_back(n7);
	threshold(numbers[7], numbers[7], 0, 255, CV_THRESH_OTSU+CV_THRESH_BINARY);
	Mat n8 = imread("8.jpg",0);
	numbers.push_back(n8);
	threshold(numbers[8], numbers[8], 0, 255, CV_THRESH_OTSU+CV_THRESH_BINARY);
	Mat n9 = imread("9.jpg",0);
	numbers.push_back(n9);
	threshold(numbers[9], numbers[9], 0, 255, CV_THRESH_OTSU+CV_THRESH_BINARY);
	
	//\B6\C1\C8\EB\D7\D6ĸģ\B0\E5ͼƬ\A3\AC\B6\FEֵ\BB\AF\A3\AC\B2\A2\B7\C5\C8\EBalphabet\CA\FD\D7\E9\D6\D0
	 vector<Mat> alphabet;
	 Mat A = imread("A.jpg",0);
	 threshold(A, A, 0, 255, CV_THRESH_OTSU+CV_THRESH_BINARY);
	 alphabet.push_back(A);
	 Mat B = imread("B.jpg",0);
	 threshold(B, B, 0, 255, CV_THRESH_OTSU+CV_THRESH_BINARY);
	 alphabet.push_back(B);
	 Mat C = imread("C.jpg",0);
	 threshold(C, C, 0, 255, CV_THRESH_OTSU+CV_THRESH_BINARY);
	 alphabet.push_back(C);
	 Mat D = imread("D.jpg",0);
	 threshold(D, D, 0, 255, CV_THRESH_OTSU+CV_THRESH_BINARY);
	 alphabet.push_back(D);
	 Mat E = imread("A.jpg",0);
	 threshold(E, E, 0, 255, CV_THRESH_OTSU+CV_THRESH_BINARY);
	 alphabet.push_back(E);
	 Mat F = imread("F.jpg",0);
	 threshold(F, F, 0, 255, CV_THRESH_OTSU+CV_THRESH_BINARY);
	 alphabet.push_back(F);
	 Mat G = imread("G.jpg",0);
	 threshold(G, G, 0, 255, CV_THRESH_OTSU+CV_THRESH_BINARY);
	 alphabet.push_back(G);
	 Mat H = imread("H.jpg",0);
	 threshold(H, H, 0, 255, CV_THRESH_OTSU+CV_THRESH_BINARY);
	 alphabet.push_back(H);
	 Mat J = imread("J.jpg",0);
	 threshold(J, J, 0, 255, CV_THRESH_OTSU+CV_THRESH_BINARY);
	 alphabet.push_back(J);
	 Mat R = imread("R.jpg",0);
	 threshold(R, R, 0, 255, CV_THRESH_OTSU+CV_THRESH_BINARY);
	 alphabet.push_back(R);
	 Mat T = imread("A.jpg",0);
	 threshold(T, T, 0, 255, CV_THRESH_OTSU+CV_THRESH_BINARY);
	 alphabet.push_back(T);
     

    //\B6\C1\C8\EB\D6\D0\CE\C4\D7ַ\FBģ\B0\E5ͼƬ\A3\AC\B6\FEֵ\BB\AF\A3\AC\B2\A2\B7\C5\C8\EBchinese\CA\FD\D7\E9\D6\D0
	vector<Mat> chinese;
	Mat c0 = imread("c0.jpg",0);
	threshold(c0,c0, 0, 255, CV_THRESH_OTSU+CV_THRESH_BINARY);
	chinese.push_back(c0);
	Mat c1 = imread("c1.jpg",0);
	threshold(c1,c1, 0, 255, CV_THRESH_OTSU+CV_THRESH_BINARY);
	chinese.push_back(c1);
	
	//\C6\E4\CB\FB\D6\D0\CE\C4\D7ַ\FB\C1\ED\D0в\E5\C8\EB

	//ijkg\B6\BC\CA\C7ѭ\BB\B7\B1\E4\C1\BF
	//int i=0;//i,j\B1\E9\C0\FAÿһ\D0\D0ÿһ\C1\D0
	i=0;
	int j=0;
	//j=0;
	int k=0;//k\B1\EDʾģ\B0\E5\D7ַ\FB\B5ĸ\F6\CA\FD\A3\AC\C8\E7\CA\FD\D7\D6k=10\A3\AC\D7\D6ĸk=11
	//k=0;
	int g=0;//g\B1\EDʾ\D5\E2\CAǵڼ\B8\B8\F6\D7ַ\FB\A3\AC\D3\EBseq\BA\CDcharcount\B6\D4Ӧ

	int count=0;//count\B4\E6\B7\C5ÿ\B4\CEѭ\BB\B7\B2\D9\D7\F7\D6\D0\C1\BD\D5\C5ͼ\CF\E0ͬ\B5\C4\CF\F1\CBص\E3\B8\F6\CA\FD
	int seq[]={0,0,0,0,0,0,0};//seq[]\B4\E6\B7\C5\D7ַ\FB\B5\C4\D0\F2\BAţ\AC\D3\EBchinesechar\A3\ACalphabetchar\A3\ACnumberchar\D6е\C4\D7ַ\FB\CF\E0\B6\D4Ӧ
	//string chinesechar[]={"\BE\A9","\BD\F2"};
	char alphabetchar[]={'A','B','C','D','E','F','G','H','J','R','T'};
	char numberchar[]={'0','1','2','3','4','5','6','7','8','9'};
	int charcount[]={0,0,0,0,0,0,0};//\D3\C3\D3ڴ\E6\B7\C5ѭ\BB\B7\B5\BDĿǰΪֹ\D7\EE\B4\F3\B5\C4\CF\E0ͬ\CF\F1\CBص\E3\B8\F6\CA\FD\A3\AC\C0\E0\CBƼ\F2\B5\A5ѡ\D4\F1\C5\C5\D0\F2\B9\FD\B3\CC

	//\B5\DA0\B8\F6\D6\D0\CE\C4\D7ַ\FB\B5\C4ʶ\B1\F0
	for(k=0;k<2;k++){
	count=0;
	for(i=0;i<dst[0].rows;i++)

        for(j=0;j<dst[0].cols;j++)
         {
			 if(dst[0].at<uchar>(i,j)==chinese[k].at<uchar>(i,j)){
			   count++;
			 }
            
        }
		if(count>charcount[0]){
		  charcount[0]=count;
		  seq[0]=k;
		}
  }
//printf("e");
	//\B5\DA1\B8\F6Ӣ\CE\C4\D7ַ\FB\B5\C4ʶ\B1\F0
	for(k=0;k<11;k++){
	count=0;
	for(i=0;i<dst[1].rows;i++)

        for(j=0;j<dst[1].cols;j++)
         {
			 if(dst[1].at<uchar>(i,j)==alphabet[k].at<uchar>(i,j)){
			   count++;
			 }
            
        }
		if(count>charcount[1]){
		  charcount[1]=count;
		  seq[1]=k;
		}
  }
		hello[0]=alphabetchar[seq[1]]; 
		
	//\B5\DA2-6\B8\F6\CA\FD\D7\D6\D7ַ\FB\B5\C4ʶ\B1\F0
	for(g=2;g<7;g++){
	for(k=0;k<10;k++){
	count=0;
	for(i=0;i<dst[g].rows;i++)

        for(j=0;j<dst[g].cols;j++)
         {
			 if(dst[g].at<uchar>(i,j)==numbers[k].at<uchar>(i,j)){
			   count++;
			 }
            
        }
		if(count>charcount[g]){
		  charcount[g]=count;
		 seq[g]=k;
		}
	//cout<<seq[g];
	}
	hello[g-1]= seq[g]+'0';
	}


	//這邊的代碼是從Client拷貝過來的
    char sockfd, recvbytes;  
    //char buf[MAXDATASIZE]='111';  
    MyMessage recvData; 
    
    struct sockaddr_in serv_addr;  
  
    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {  
        perror("socket error!");  
        exit(1);  
    }  
    bzero(&serv_addr, sizeof(serv_addr));  
    serv_addr.sin_family = AF_INET;  
    serv_addr.sin_port = htons(SERVPORT);  
    serv_addr.sin_addr.s_addr = inet_addr(SERVER_IP);  
  
    if (connect(sockfd, (struct sockaddr *) &serv_addr, sizeof(struct sockaddr))== -1) {  
        perror("connect error!");  
        exit(1);  
    }  
    //write(sockfd, buf, sizeof(DATA)); 
    write(sockfd, hello,strlen(hello));  
    memset((void *)&recvData,0,sizeof(MyMessage));  
    if ((recvbytes = recv(sockfd, (void *)&recvData,sizeof(MyMessage), 0)) == -1) {  
        perror("recv error!");  
        exit(1);  
    }  
    //buf[recvbytes] = '\0';  
    printf("Received:ID=%d,Info= %s",recvData.ID,recvData.info);  
    close(sockfd);  


	//\BD\E1\B9\FB\CA\E4\B3\F6
	//cout<<"a system of recongize number V1.0"<<endl;
	//cout<<"the number is"<<endl;
	//cout<<seq[6];//<<alphabetchar[seq[1]]<<numberchar[seq[2]]<<numberchar[seq[3]]<<numberchar[seq[4]]<<numberchar[seq[5]]<<numberchar[seq[6]];


/*
	//չʾ
	namedWindow("ԭͼ",WINDOW_NORMAL);
	imshow("ԭͼ",img);
	namedWindow("\BBҶȻ\AF",WINDOW_NORMAL);
	imshow("\BBҶȻ\AF",img_blur);
	namedWindow("sobel",WINDOW_NORMAL);
	imshow("sobel",img_sobel);
	namedWindow("\B6\FEֵ\BB\AF",WINDOW_NORMAL);
	imshow("\B6\FEֵ\BB\AF",img_threshold);
	namedWindow("\B1ղ\D9\D7\F7",WINDOW_NORMAL);
	imshow("\B1ղ\D9\D7\F7",img_close);
	namedWindow("\CB\F9\D3\D0\C2\D6\C0\AA",WINDOW_NORMAL);
	imshow("\CB\F9\D3\D0\C2\D6\C0\AA",img_showcontours);
	namedWindow("ɸѡ",WINDOW_NORMAL);
	imshow("ɸѡ",img_result);
	namedWindow("\B3\B5\C5\C6",WINDOW_NORMAL);
	imshow("\B3\B5\C5\C6",roi);
	namedWindow("\B3\B5\C5ƶ\FEֵ\BB\AF",WINDOW_NORMAL);
	imshow("\B3\B5\C5ƶ\FEֵ\BB\AF",roi_threshold);
	namedWindow("\D7ַ\FB\B7ָ\EE",WINDOW_NORMAL);
	imshow("\D7ַ\FB\B7ָ\EE",roi_result);
	namedWindow("\D7ַ\FB1",WINDOW_NORMAL);
	imshow("\D7ַ\FB1",dst[0]);
	namedWindow("\D7ַ\FB2",WINDOW_NORMAL);
	imshow("\D7ַ\FB2",dst[1]);
	namedWindow("\D7ַ\FB3",WINDOW_NORMAL);
	imshow("\D7ַ\FB3",dst[2]);
	namedWindow("\D7ַ\FB4",WINDOW_NORMAL);
	imshow("\D7ַ\FB4",dst[3]);
	namedWindow("\D7ַ\FB5",WINDOW_NORMAL);
	imshow("\D7ַ\FB5",dst[4]);
	namedWindow("\D7ַ\FB6",WINDOW_NORMAL);
	imshow("\D7ַ\FB6",dst[5]);
	namedWindow("\D7ַ\FB7",WINDOW_NORMAL);
	imshow("\D7ַ\FB7",dst[6]);
*/
	/*	 __asm__ __volatile__(
     		"rdtsc\n\t"
     		:"=a"(te),"=d"(edx));
		clock_cycles=(unsigned long long)(edx-sdx)*max0+te-ts;
		//printf("clock_cycles=%llu\n",clock_cycles);

gettimeofday(&tpend,NULL); 
timeuse=1000000*(tpend.tv_sec-tpstart.tv_sec)+ tpend.tv_usec-tpstart.tv_usec; 
timeuse/=1000000; 
//printf("Used Time:%f\n",timeuse); */
		 
	waitKey(0);
	cin.get();

 
return 0;
}
