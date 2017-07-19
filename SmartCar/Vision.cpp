#include "Vision.h"
#include "opencv2\opencv.hpp"
#include <iostream>

using namespace cv;
using namespace std;

Vision::Vision(Mat& img)
{
	src = img;
}


Vision::~Vision()
{
}


void Vision::showVision() {

	namedWindow("Source image", 1);
	imshow("Source image", src);
	waitKey(0);

	namedWindow("Binary image", 1);
	imshow("Binary image", bin);
	waitKey(0);

	namedWindow("Raw Midline", 1);
	imshow("Raw Midline", rawMidline);
	waitKey(0);
}


void Vision::bgrBinarization(int b, int g, int r, int allowence) {

	Mat dst(src.rows, src.cols, CV_8UC1, Scalar(0));

	int rows = src.rows;
	for (int row = 0; row < rows; row++) {

		uchar *srcPtr = src.ptr<uchar>(row);
		uchar *dstPtr = dst.ptr<uchar>(row);

		int cols = src.cols;
		for (int col = 0; col < cols; col++) {

			int error = abs(srcPtr[col * 3] - 0 - b)
				+ abs(srcPtr[col * 3 + 1] - 0 - g)
				+ abs(srcPtr[col * 3 + 2] - 0 - r);

			if (error <= allowence) {
				dstPtr[col] = 255;
			}
			else {
				dstPtr[col] = 0;
			}
		}

		bin = dst;
	}
}


void Vision::getRawMidline() {

	int leftPoint, rightPoint;

	Mat dst(bin.rows, bin.cols, CV_8UC1, Scalar(0));
	vector<Point> A;
	vector<Point> B;

	// 除去噪点
	blur(bin, bin, Size(10, 10));

	int rows = bin.rows;
	for (int row = 0; row < rows; row++) {

		uchar *srcPtr = bin.ptr<uchar>(row);
		uchar *dstPtr = dst.ptr<uchar>(row);

		// 从左往右不断扫描直到检测到有色点或碰到边缘
		int col = 0;
		int cols = bin.cols;
		while (srcPtr[col] == 0 && col < cols - 1)
			col++;

		// 如果上述检测没碰到边缘
		if (col != cols - 1) {

			// 将此点设为左点
			leftPoint = col;

			// 则从右往左检测右点
			col = cols - 1;
			while (srcPtr[col] == 0 && col > leftPoint)
				col--;

			// 如果左右两点不会重合
			if (leftPoint != col) {
				// 得到右点
				rightPoint = col;
				// 输出到新图像矩阵
				dstPtr[(leftPoint+rightPoint)/2] = 255;
				// 输入数据集
				A.push_back(Point(row));
				B.push_back(Point(col));
			} else {
				continue;
			}
		}
	}

	rawMidline = dst;
}

