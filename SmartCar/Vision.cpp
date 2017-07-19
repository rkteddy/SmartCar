#include "Vision.h"
#include "opencv2\opencv.hpp"
#include "dataProcess.h"

#include <iostream>
#include <math.h>

using namespace cv;
using namespace std;

Vision::Vision(Mat& img)
{
	src = img;
	rows = src.rows;
	cols = src.cols;
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

	namedWindow("Raw midline", 1);
	imshow("Raw Midline", rawMidline);
	waitKey(0);

	namedWindow("Fitted line", 1);
	imshow("Fitted line", fittedLine);
	waitKey(0);
}


void Vision::bgrBinarization(int b, int g, int r, int allowence) {

	Mat dst(rows, cols, CV_8UC1, Scalar(0));

	for (int row = 0; row < rows; row++) {

		uchar *srcPtr = src.ptr<uchar>(row);
		uchar *dstPtr = dst.ptr<uchar>(row);

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
	}

	bin = dst;
}


void Vision::getRawMidline() {

	int leftPoint, rightPoint;

	Mat dst(rows, cols, CV_8UC1, Scalar(0));

	// 除去噪点
	//blur(bin, bin, Size(10, 10));

	for (int row = 0; row < rows; row++) {

		uchar *srcPtr = bin.ptr<uchar>(row);
		uchar *dstPtr = dst.ptr<uchar>(row);

		// 从左往右不断扫描直到检测到有色点或碰到边缘
		int col = 0;
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

void Vision::fitLine() {

	Mat X = LSE(A, B);

	Mat dst(rows, cols, CV_8UC1, Scalar(0));

	for (int row = 0; row < rows; row++) {
		uchar *dstPtr = dst.ptr(row);
		double col = 0;
		for (int i = 0; i < 2; i++) {
			uchar *XPtr = X.ptr(i);
			col += pow(row, (double)i) * (double)XPtr[i];
		}
		dstPtr[(int)floor(col)] = 255;
	}

	fittedLine = dst;
}
