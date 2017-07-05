#include "stdafx.h"
#include "Vision.h"


Vision::Vision(Mat&)
{
}


Vision::~Vision()
{
}


Mat Vision::bgrBinarization(int b, int g, int r, int allowence)
{
	int error, row, col;
	Mat dst;

	for (row = 0; row < src.rows; row++) {
		uchar *srcPtr = src.ptr<uchar>(row);
		uchar *dstPtr = dst.ptr<uchar>(row);
		for (col = 0; col < src.cols; col++) {
			error = abs(srcPtr[col * 3] - 0 - b)
				+ abs(srcPtr[col * 3 + 1] - 0 - g)
				+ abs(srcPtr[col * 3 + 2] - 0 - r);
			if (error <= allowence) {
				dstPtr[col] = 255;
			}
			else {
				dstPtr[col] = 0;
			}
		}

		return dst;
	}
}
