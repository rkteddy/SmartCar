#pragma once

using namespace cv;

class Vision
{
public:
	Mat src;
	Vision(Mat&);
	~Vision();
	Mat bgrGetColor(int, int, int, int);
};

