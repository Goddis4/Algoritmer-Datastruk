#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Function to reverse a portion of the array from index 0 to k
void flip(vector<int>& array, int k) 
{
    int start = 0;
    while (start < k) {
        swap(array[start], array[k]);
        start++;
        k--;
    }
}

// Function to find the index of the maximum element in the array
int findMaxIndex(vector<int>& array, int n) 
{
    int maxIndex = 0;
    for (int i = 1; i < n; i++) {
        if (array[i] > array[maxIndex]) {
            maxIndex = i;
        }
    }
    return maxIndex;
}

// Recursive pancake sort function
void pancakeSortRecursive(vector<int>& array, int n) 
{
    // Base case: If the array has only one element, it is already sorted
    if (n == 1) {
        return;
    }

    // Find the index of the maximum element in the current unsorted portion
    int maxIndex = findMaxIndex(array, n);

    // If the maximum element is not at the last position, perform a flip
    if (maxIndex != n - 1) {
        // Flip the portion of the array to move the maximum element to the first position
        flip(array, maxIndex);
        // Flip the entire array to move the maximum element to the last position
        flip(array, n - 1);
    }

    // Recursively sort the remaining portion of the array (excluding the last element)
    pancakeSortRecursive(array, n - 1);
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
    int n = array.size();
    pancakeSortRecursive(array, n);

    cout << "Sorted Array: ";
    for (int num : array) {
        cout << num << " ";
    }
    cout << endl;

    return 0;
}
