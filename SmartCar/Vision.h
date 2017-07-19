#pragma once

#include <opencv2\opencv.hpp>

using namespace cv;
using namespace std;

class Vision
{
public:
	Mat src;
	Mat bin;
	Mat rawMidline;
	Mat fittedLine;
	int rows;
	int cols;
	vector<Point> A;
	vector<Point> B;
	Vision(cv::Mat&);
	~Vision();
	void showVision();
	void bgrBinarization(int, int, int, int);
	void getRawMidline();
	void fitLine();
};
