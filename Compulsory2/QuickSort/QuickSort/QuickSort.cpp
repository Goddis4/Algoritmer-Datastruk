#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Function to partition the array into two subarrays
// and return the index of the pivot element
int partition(vector<int>& array, int low, int high) 
{
    int pivot = array[high];  // Choose the pivot as the last element
    int i = low - 1;  // Index of the smaller element

    for (int j = low; j < high; j++) {
        // If the current element is smaller than or equal to the pivot
        if (array[j] <= pivot) {
            i++;
            // Swap array[i] and array[j]
            swap(array[i], array[j]);
        }
    }

    // Swap array[i + 1] and array[high] (pivot)
    swap(array[i + 1], array[high]);
    return i + 1;
}

// Recursive function to perform quick sort
void quickSort(vector<int>& array, int low, int high) 
{
    if (low < high) {
        // Find the pivot element such that
        // element smaller than pivot are on the left
        // and elements greater than pivot are on the right
        int pivotIndex = partition(array, low, high);

        // Recursively sort elements before and after pivot
        quickSort(array, low, pivotIndex - 1);
        quickSort(array, pivotIndex + 1, high);
    }
}

int main() 
{
    vector<int> array = {};
    // Create array with 10 elements
    //for (int i = 0; i < 10; i++)
    //{
    //    array.insert(array.end(), i + 1);
    //}

    // Create array with 100 elements
    //for (int i = 0; i < 100; i++)
    //{
    //    array.insert(array.end(), i + 1);
    //}

    // Create array with 1000 elements
    //for (int i = 0; i < 1000; i++)
    //{
    //    array.insert(array.end(), i + 1);
    //}

    // Create array with 10000 elements
    //for (int i = 0; i < 10000; i++)
    //{
    //    array.insert(array.end(), i + 1);
    //}

    // Randomizing the position of each element within the array
    random_shuffle(array.begin(), array.end());

    // Printing original array
    cout << "Original Array: ";
    for (int num : array) {
        cout << num << " ";
    }
    cout << endl;
    cout << endl;

    // Printing sorted array
    int n = array.size();
    quickSort(array, 0, n - 1);

    cout << "Sorted Array: ";
    for (int num : array) {
        cout << num << " ";
    }
    cout << endl;

    return 0;
}
