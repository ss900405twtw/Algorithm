// **************************************************************************
//  File       [sort_tool.cpp]
//  Author     [Yu-Hao Ho]
//  Synopsis   [The implementation of the SortTool Class]
//  Modify     [2019/9/6 Cheng-Yun Hsieh]
// **************************************************************************

#include "sort_tool.h"
#include <iostream>
#include <math.h>
#include <climits>
#include <stdlib.h>

// Constructor
SortTool::SortTool() {}

// Insertsion sort method
void SortTool::InsertionSort(vector<int>& data) {
    // Function : Insertion sort
    // TODO : Please complete insertion sort code here
    for(int i = 1; i < data.size(); i++)
    {
        // cout << "i "<<i<<endl;
        int key = data[i];
        int j = i - 1;
        while((j >= 0) && (data[j] > key))
        {
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
    if(low < high)
    {
        int mid = randomPartition(data, low, high);
        QuickSortSubVector(data, low, mid );
        QuickSortSubVector(data, mid +1, high);
    }
}

int SortTool::Partition(vector<int>& data, int low, int high) {
    // Function : Partition the vector 
    // TODO : Please complete the function
    // Hint : Textbook page 171
    int x = data[low];
    // int x = data[rand()%(high - low + 1) + low];
    // swap(x,data[low]);

    
    int i = low - 1;
    int j = high + 1;
    while(true)
    {
        do{j = j - 1;} 
            while(data[j] > x );
        do{i = i + 1;} 
            while(data[i] < x);
        if(i < j) 
            swap(data[i], data[j]);
        else return j;
    }

}

int SortTool::randomPartition(vector<int>& data, int low, int high) {
    int x = rand()%(high - low + 1) + low;
    swap(data[low], data[x]);
    return Partition(data, low, high);




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
    if(low < high)
    {
        int mid = floor((low + high) / 2);
        MergeSortSubVector(data, low, mid);
        MergeSortSubVector(data, mid + 1, high);
        Merge(data,low, mid, high);
    }
}

// Merge
void SortTool::Merge(vector<int>& data, int low, int middle, int high) {
    // Function : Merge two sorted subvector
    // TODO : Please complete the function
    int n1 = middle - low + 1;
    int n2 = high - middle;
    int* L = new int[n1+1]; 
    int* R = new int[n2+1];
    for(int i =0; i < n1; i++)
    {
        L[i] = data[low + i];
    }  
    for(int j =0; j < n2; j++)
    {
        R[j] = data[middle + j + 1];
    }
    L[n1] = INT_MAX;
    R[n2] = INT_MAX;
    int i = 0;
    int j = 0;
    for(int k = low; k <= high; k++)
    {
        if(L[i] <= R[j])
        {
            data[k] = L[i];
            i++;
        }
        else
        {
            data[k] = R[j];
            j++;
        }
    }
    delete [] L;
    delete [] R;

}

// Heap sort method
void SortTool::HeapSort(vector<int>& data) {
    // Build Max-Heap
    BuildMaxHeap(data);
    // 1. Swap data[0] which is max value and data[i] so that the max value will be in correct location
    // 2. Do max-heapify for data[0]
    for (int i = data.size() - 1; i >= 0; i--) {
        swap(data[0],data[i]);
        MaxHeapify(data,0, i);
    }
}

//Max heapify
void SortTool::MaxHeapify(vector<int>& data, int root, int heap_size) {
    // Function : Make tree with given root be a max-heap if both right and left sub-tree are max-heap
    // TODO : Please complete max-heapify code here
    int lidx = root*2+1;
    int ridx = root*2+2;
    int largest = root;
    if(lidx < heap_size && data[lidx] > data[root])
    {
        largest = lidx;
    }
    else if(lidx < heap_size && data[lidx] <= data[root])
    {
        largest = root;
    }
    if(ridx < heap_size && data[ridx] > data[largest])
    {
        largest = ridx;
    }
    if(root != largest)
    {
        swap(data[largest], data[root]);
        MaxHeapify(data, largest, heap_size);
    }
}

//Build max heap
void SortTool::BuildMaxHeap(vector<int>& data) {
    heapSize = data.size(); // initialize heap size
    // Function : Make input data become a max-heap
    // TODO : Please complete BuildMaxHeap code here
    for(int i = heapSize/2-1; i>=0; i--)
    {
        MaxHeapify(data, i, heapSize);
    }

}
