#include "dataprocess.h"
#include "Vision.h"

#include <stdio.h>
#include <tchar.h>
#include <opencv2\opencv.hpp>
#include <math.h>
#include <time.h>   
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>

using namespace std;
using namespace cv;

#define PI 3.141592653589792
#define ROW_MIN 600
#define ROW_MAX 1000
#define COL_MIN 0
#define COL_MAX 960
#define MIDLINE_LENGTH ROW_MAX - ROW_MIN

vector<int> midLine;    //中线
int startLine;			//起点或终点线
int nowRoad;			//当前所在跑道颜色： 
						//  0：黄色
						//  1：白色
						//  2：黑色

void showVideo();

int main() {

	Mat img = imread("road.jpg");
	if (img.empty()) {
		cout << "No files named \"road.jpg\"" << endl;
	}
	else {
		Vision test = Vision(img);
		test.bgrBinarization(70, 180, 220, 100);
		test.getRawMidline();
		test.showVision();
	}
	//showVideo();
	
    return 0;
}

/*
	调用摄像头
*/
void showVideo() {

	VideoCapture capture(1);
	namedWindow("video", 1);

	while (1) {
		Mat frame;
		capture >> frame;
		imshow("video", frame);
		waitKey(30);
	}

}
