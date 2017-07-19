#pragma once

#include <stdlib.h>
#include <opencv2\opencv.hpp>

using namespace cv;
using namespace std;

/*
	快速排序
*/
void quickSort(int *a, int low, int high)
{
	if (low >= high) {
		return;
	}

	int left = low;
	int right = high;
	int key = a[left];

	while (left < right) {
		while (left < right && a[right] >= key)
			right--;
		a[left] = a[right];
		while (left < right && a[left] <= key)
			left++;
		a[right] = a[left];
	}

	a[left] = key;

	quickSort(a, low, left - 1);
	quickSort(a, left + 1, high);
}

/*
	半径为n的向量中值滤波
*/
void medianFilter(int *a, int size, int n)
{
	int k = n / 2;
	int *tmp = (int*)malloc(sizeof(int) * n);

	// 上边缘补偿
	for (int i = 0; i < k; i++) {
		int t = 0;
		for (int j = 0; j < i + k; j++) {
			tmp[t++] = a[j];
		}
		for (int j = i + k; j < n; j++) {
			tmp[t++] = a[i];
		}
		quickSort(tmp, 0, n);
		a[i] = tmp[i];
	}

	// 中间数据
	for (int i = k; i < size - k; i++) {
		int t = 0;
		for (int j = i - k; j < i + k; j++) {
			tmp[t++] = a[j];
		}
		quickSort(tmp, 0, n);
		a[i] = tmp[i];
	}

	// 下边缘补偿
	for (int i = size - k; i < size; i++) {
		int t = 0;
		for (int j = i - k; j < size; j++) {
			tmp[t++] = a[j];
		}
		for (int j = size; j < i + k; j++) {
			tmp[t++] = a[i];
		}
		quickSort(tmp, 0, n);
		a[i] = tmp[i];
	}
}

/*
    半径为n的向量均值滤波
*/
void meanFilter(int *a, int size, int n)
{
	int k = n / 2;

	// 上边缘补偿
	for (int i = 0; i < k; i++) {
		int sum = 0;
		int t = 0;
		for (int j = 0; j < i + k; j++) {
			sum += a[j];
		}
		for (int j = i + k; j < n; j++) {
			sum += a[i];
		}
		a[i] = sum / n;
	}

	// 中间数据
	for (int i = k; i < size - k; i++) {
		int sum = 0;
		for (int j = i - k; j < i + k; j++) {
			sum += a[j];
		}
		a[i] = sum / n;
	}

	// 下边缘补偿
	for (int i = size - k; i < size; i++) {
		int sum = 0;
		int t = 0;
		for (int j = i - k; j < size; j++) {
			sum += a[j];
		}
		for (int j = size; j < i + k; j++) {
			sum += a[i];
		}
		a[i] = sum / n;
	}
}

// 最小二乘法拟合曲线
Mat LSE(vector<Point> srcA, vector<Point> srcB) {
	
	int n = srcA.size();
	Mat A(n, 4, CV_8UC1, Scalar(0));
	Mat B(n, 1, CV_8UC1, Scalar(0));

	for (int row = 0; row < n; row++) {
		uchar *APtr = A.ptr<uchar>(row);
		for (int col = 0; col < 4; col++) {
			APtr[col] = pow(srcA[row].x, col);
		}
	}

	for (int row = 0; row < n; row++) {
		B.at<uchar>(row, 0) = srcB[row].x;
	}
	
	Mat X(4, 1, CV_8UC1, Scalar(0));
	solve(A, B, X, DECOMP_LU);

	return X;
}