#pragma once

#include <opencv2\opencv.hpp>

using namespace cv;
using namespace std;

void quickSort(int*, int, int);
void medianFilter(int*, int, int);
void meanFilter(int*, int, int);
Mat LSE(vector<Point>, vector<Point>);