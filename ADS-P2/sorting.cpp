// ADS Praktikum 2.1 Sortieren Musterl�sung
// Stand April 2025
#include "sorting.h"
#include <algorithm>



namespace sorting {

	//****************
	// insertionSort *
	//****************   
	void insertionSort(vector<int>& arr)
	{
		// shift each element left until it is in sorted position
		for (int i = 1; i < (int)arr.size(); i++) {
			int key = arr[i];
			int j = i - 1;
			while (j >= 0 && arr[j] > key) {
				arr[j + 1] = arr[j];
				j--;
			}
			arr[j + 1] = key;
		}
	}


	//************
	// QuickSort *
	//************      
	void quickSort(vector<int>& arr, int left, int right)
	{
		// 3-way partition (Dutch National Flag): groups equal elements in the
		// middle so they are never recursed into — avoids O(n²) on many duplicates
		if (left >= right) return;
		int pivot = arr[right];
		int lt = left;   // boundary: arr[left..lt-1] < pivot
		int gt = right;  // boundary: arr[gt+1..right] > pivot
		int i  = left;
		while (i <= gt) {
			if      (arr[i] < pivot) swap(arr[lt++], arr[i++]);
			else if (arr[i] > pivot) swap(arr[i],    arr[gt--]);
			else                     i++;
		}
		// arr[left..lt-1] < pivot, arr[lt..gt] == pivot, arr[gt+1..right] > pivot
		quickSort(arr, left,   lt - 1);
		quickSort(arr, gt + 1, right);
	}


	//************
	// MergeSort *
	//************
	void merge(vector<int>& a, vector<int>& b, int low, int pivot, int high)
	{
		// copy segment to temp buffer b, then merge back into a
		for (int k = low; k <= high; k++) b[k] = a[k];
		int i = low, j = pivot + 1;
		for (int k = low; k <= high; k++) {
			if      (i > pivot)       a[k] = b[j++];
			else if (j > high)        a[k] = b[i++];
			else if (b[i] <= b[j])    a[k] = b[i++];
			else                      a[k] = b[j++];
		}
	}


	void mergeSort(vector<int>& a, vector<int>& b, int low, int high)
	{
		// divide in half, sort each half, then merge
		if (low < high) {
			int pivot = (low + high) / 2;
			mergeSort(a, b, low, pivot);
			mergeSort(a, b, pivot + 1, high);
			merge(a, b, low, pivot, high);
		}
	}

	//************
	// Heapsort  *
	//************
	void Heapify(vector<int> &a, int n, int i)
	{
		// sift element i down to restore max-heap property
		int largest = i;
		int left    = 2 * i + 1;
		int right   = 2 * i + 2;
		if (left  < n && a[left]  > a[largest]) largest = left;
		if (right < n && a[right] > a[largest]) largest = right;
		if (largest != i) {
			swap(a[i], a[largest]);
			Heapify(a, n, largest);
		}
	}


	void heapSort(vector<int> &a, int n)
	{
		// build max-heap, then repeatedly extract max to end of array
		for (int i = n / 2 - 1; i >= 0; i--)
			Heapify(a, n, i);
		for (int i = n - 1; i > 0; i--) {
			swap(a[0], a[i]);
			Heapify(a, i, 0);
		}
	}

	//************
	// Shellsort *
	//************
	// Hier soll Hibbard implementiert werden
	void shellSort_2n(vector<int> &a, int n)
	{
		// build Hibbard gap sequence: 1, 3, 7, 15, ... (H_i = 2*H_{i-1}+1)
		vector<int> gaps;
		int h = 1;
		while (h < n) { gaps.push_back(h); h = 2 * h + 1; }

		// insertion sort with decreasing Hibbard gaps
		for (int g = (int)gaps.size() - 1; g >= 0; g--) {
			int gap = gaps[g];
			for (int i = gap; i < n; i++) {
				int tmp = a[i];
				int j   = i;
				while (j >= gap && a[j - gap] > tmp) {
					a[j] = a[j - gap];
					j -= gap;
				}
				a[j] = tmp;
			}
		}
	}


	//***************
	// CountingSort *
	//***************
	void countingSort(vector<int>& arr, int left, int right)
	{
		// detect actual value range, count occurrences, write back in order
		if (arr.empty()) return;
		int minVal = *min_element(arr.begin(), arr.end());
		int maxVal = *max_element(arr.begin(), arr.end());
		vector<int> count(maxVal - minVal + 1, 0);
		for (int x : arr) count[x - minVal]++;
		int idx = 0;
		for (int i = 0; i < (int)count.size(); i++)
			while (count[i]-- > 0)
				arr[idx++] = i + minVal;
	}


	//************
	// RadixSort *
	//************
	void radixSort(vector<int>& arr)
	{
		// LSD radix sort: one counting-sort pass per decimal digit
		if (arr.empty()) return;
		int maxVal = *max_element(arr.begin(), arr.end());
		for (int exp = 1; maxVal / exp > 0; exp *= 10) {
			vector<int> output(arr.size());
			int count[10] = {0};
			for (int x : arr)             count[(x / exp) % 10]++;
			for (int i = 1; i < 10; i++)  count[i] += count[i - 1];
			for (int i = (int)arr.size() - 1; i >= 0; i--)
				output[--count[(arr[i] / exp) % 10]] = arr[i];
			arr = output;
		}
	}

	void randomizeVector(vector<int> &array, int n) {
		array.resize(n);

		for (unsigned int i = 0; i < array.size(); i++)
			array[i] = rand() % 10;
			//array[i]=rand() % 1000000;
	}


}





