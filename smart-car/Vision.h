#pragma once

using namespace cv;

class Vision
{
public:
	Mat src;
	Vision(Mat&);
	~Vision();
	Mat bgrBinarization(int, int, int, int);
};
