#pragma once

#include <opencv2\opencv.hpp>

using namespace cv;

class Vision
{
public:
	Mat src;
	Mat bin;
	Mat rawMidline;
	Vision(cv::Mat&);
	~Vision();
	void showVision();
	void bgrBinarization(int, int, int, int);
	void getRawMidline();
};
