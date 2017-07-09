#pragma once
/*
	¿ìËÙÅÅÐò
*/
void Quicksort(int a[], int low, int high)
{
	if (low >= high)
		return;

	int left = low;
	int right = high;
	int key = a[left];

	while (left < right)
	{
		while (left < right && a[right] >= key)
			right--;
		a[left] = a[right];
		while (left < right && a[left] <= key)
			left++;
		a[right] = a[left];
	}

	a[left] = key;

	Quicksort(a, low, left - 1);
	Quicksort(a, left + 1, high);
}
