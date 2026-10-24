// **************************************************************************
//  File       [sort_tool.cpp]
//  Author     [Yu-Hao Ho]
//  Synopsis   [The implementation of the SortTool Class]
//  Modify     [2021/02/26 Hsien-Chia Chen]
// **************************************************************************

#include "sort_tool.h"
#include<iostream>

// Constructor
SortTool::SortTool() {}

// Insertsion sort method
void SortTool::InsertionSort(vector<int>& data) {
    // Function : Insertion sort
    // TODO : Please complete insertion sort code here
    for (int i = 1; i < data.size(); i++){
        int key = data[i];
        int j = i-1;
        while(j >= 0 && data[j] > key){
            data[j+1] = data[j];
            j--;
        }
        data[j+1] = key;
    }
}

// Quick sort method
void SortTool::QuickSort(vector<int>& data){
    QuickSortSubVector(data, 0, data.size() - 1);
}
// Sort subvector (Quick sort)
void SortTool::QuickSortSubVector(vector<int>& data, int low, int high) {
    // Function : Quick sort subvector
    // TODO : Please complete QuickSortSubVector code here
    // Hint : recursively call itself
    //        Partition function is needed
    if (low >= high){
        return;
    }
    int q = Partition(data, low, high);
    QuickSortSubVector(data, low, q-1);
    QuickSortSubVector(data, q+1, high);
}

int SortTool::Partition(vector<int>& data, int low, int high) {
    // Function : Partition the vector 
    // TODO : Please complete the function
    // Hint : Textbook page 171
    int x = data[high];
    int i = low - 1;
    for (int j = low; j < high; j++){
        if (data[j] < x){
            i++;
            int temp = data[j];
            data[j] = data[i];
            data[i] = temp;
        }
    }
    data[high] = data[i + 1];
    data[i + 1] = x;

    return (i + 1);
}

// Merge sort method
void SortTool::MergeSort(vector<int>& data){
    MergeSortSubVector(data, 0, data.size() - 1);
}

// Sort subvector (Merge sort)
void SortTool::MergeSortSubVector(vector<int>& data, int low, int high) {
    // Function : Merge sort subvector
    // TODO : Please complete MergeSortSubVector code here
    // Hint : recursively call itself
    //        Merge function is needed
    if (low >= high){
        return;
    }
    int mid = (low + high) / 2;
    MergeSortSubVector(data, low, mid);
    MergeSortSubVector(data, mid + 1, high);
    Merge(data, low, mid, mid + 1, high);
}

// Merge
void SortTool::Merge(vector<int>& data, int low, int middle1, int middle2, int high) {
    // Function : Merge two sorted subvector
    // TODO : Please complete the function
    std::vector<int> left_subvector;
    std::vector<int> right_subvector;
    
    for (int i = low; i <= middle1; i++){
        left_subvector.push_back(data[i]);
    }
    for (int i = middle2; i <= high; i++){
        right_subvector.push_back(data[i]);
    }

    int l_n = middle1 - low + 1;
    int r_n = high - middle2 + 1;
    int i = 0;
    int j = 0;
    for (int k = low; k <= high; k++){
        if (i == l_n){
            data[k] = right_subvector[j];
            j++;
            continue;
        }
        else if (j == r_n){
            data[k] = left_subvector[i];
            i++;
            continue;
        }

        if (left_subvector[i] <= right_subvector[j]){
            data[k] = left_subvector[i];
            i++;
        }
        else{
            data[k] = right_subvector[j];
            j++;
        }
    }
}

// Heap sort method
void SortTool::HeapSort(vector<int>& data) {
    // Build Max-Heap
    BuildMaxHeap(data);
    // 1. Swap data[0] which is max value and data[i] so that the max value will be in correct location
    // 2. Do max-heapify for data[0]
	int tmp = 0;
    for (int i = data.size() - 1; i >= 1; i--) {
		tmp = data[i];
		data[i] = data[0];
		data[0] = tmp;
        heapSize--;
        MaxHeapify(data,0);
    }
}

//Max heapify
void SortTool::MaxHeapify(vector<int>& data, int root) {
    // Function : Make tree with given root be a max-heap if both right and left sub-tree are max-heap
    // TODO : Please complete max-heapify code here
    int l = 2 * (root + 1) - 1;
    int r = 2 * (root + 1);
    int largest = root;
    if ((l <= heapSize - 1) && (data[l] > data[largest])){
        largest = l;
    }
    if ((r <= heapSize - 1) && (data[r] > data[largest])){
        largest = r;
    }
    if (largest != root){
        int temp = data[root];
        data[root] = data[largest];
        data[largest] = temp;
        MaxHeapify(data, largest);
    }
}

//Build max heap
void SortTool::BuildMaxHeap(vector<int>& data) {
    heapSize = data.size(); // initialize heap size
    // Function : Make input data become a max-heap
    // TODO : Please complete BuildMaxHeap code here
    for (int i = (heapSize / 2) - 1; i >= 0; i--){
        MaxHeapify(data, i);
    }
}
