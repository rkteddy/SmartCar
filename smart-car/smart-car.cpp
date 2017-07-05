// smart-car.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

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
	//showVideo();
    return 0;
}

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
