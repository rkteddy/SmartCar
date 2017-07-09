#pragma once

#include <stdlib.h>

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
	半径为n的中值滤波
*/
void medianFilter(int *a, int size, int n)
{
	int k = n / 2;
	int *tmp = (int*)malloc(sizeof(int) * n);

	// 上边缘补偿
	for (int i = 0; i < k; i++) {
		for (int j = 0; j < i + k; j++) {
			tmp[j] = a[j];
		}
		for (int j = i + k; j < n; j++) {
			tmp[j] = a[i];
		}
		quickSort(tmp, 0, n);
		a[i] = tmp[i];
	}

	// 中间数据
	for (int i = k; i < size - k; i++) {
		for (int j = 0; j <= n; j++) {
			tmp[j] = a[i - k + j];
		}
		quickSort(tmp, 0, n);
		a[i] = tmp[i];
	}

	// 下边缘补偿
	for (int i = size - k; i < size; i++) {
		for (int j = 0; j < size + k - i; j++) {
			tmp[j] = a[i - k + j];
		}
		for (int j = size + k - i; j < n; j++) {
			tmp[j] = a[i];
		}
		quickSort(tmp, 0, n);
		a[i] = tmp[i];
	}
}