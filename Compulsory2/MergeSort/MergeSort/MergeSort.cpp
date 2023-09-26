#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Merge two sorted subarrays leftArray[left..mid] and rightArray[mid+1..right]
void merge(vector<int>& array, int left, int mid, int right) 
{
    // Calculate the sizes of the two subarrays
    int subArray1 = mid - left + 1;
    int subArray2 = right - mid;

    // Create temporary arrays to hold the subarrays
    vector<int> leftArray(subArray1);
    vector<int> rightArray(subArray2);

    // Copy the data from the main array to the temporary arrays
    for (int i = 0; i < subArray1; i++) {
        leftArray[i] = array[left + i];
    }
    for (int i = 0; i < subArray2; i++) {
        rightArray[i] = array[mid + 1 + i];
    }

    int i = 0;
    int j = 0;
    int k = left;

    // Merge the two subarrays back into the main array
    while (i < subArray1 && j < subArray2) {
        if (leftArray[i] <= rightArray[j]) {
            array[k] = leftArray[i];
            i++;
        }
        else {
            array[k] = rightArray[j];
            j++;
        }
        k++;
    }

    // Copy any remaining elemnts from the left and right subarrays
    while (i < subArray1) {
        array[k] = leftArray[i];
        i++;
        k++;
    }

    while (j < subArray2) {
        array[k] = rightArray[j];
        j++;
        k++;
    }
}

// Iterative merge sort function
void mergeSort(vector<int>& array) 
{
    int n = array.size();

    // Iterate over different subarray sizes
    for (int currentSize = 1; currentSize <= n - 1; currentSize *= 2) {
        for (int leftStart = 0; leftStart < n - 1; leftStart += 2 * currentSize) {
            // Calculate mid and right end for each subarray
            int mid = min(leftStart + currentSize - 1, n - 1);
            int rightEnd = min(leftStart + 2 * currentSize - 1, n - 1);
            
            // Merge the subarrays
            merge(array, leftStart, mid, rightEnd);
        }
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

    // Print original array
    cout << "Original Array: ";
    for (int num : array) {
        cout << num << " ";
    }
    cout << endl;
    cout << endl;

    // Print sorted array
    mergeSort(array);

    cout << "Sorted Array: ";
    for (int num : array) {
        cout << num << " ";
    }
    cout << endl;

    return 0;
}
