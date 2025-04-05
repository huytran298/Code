#include <iostream>
using namespace std;

// Function to calculate the sum of an array
int sumArray(int arr[], int size) {
    int sum = 0;
    for (int i = 0; i < size; i++) {
        sum += arr[i];
    }
    return sum;
}

int main() {
    int size;

    // Ask the user for the size of the array
    cout << "Enter the size of the array: ";
    cin >> size;

    int arr[size];

    // Input array elements
    cout << "Enter " << size << " elements: ";
    for (int i = 0; i < size; i++) {
        cin >> arr[i];
    }

    // Calculate and display the sum
    cout << "The sum of the array is: " << sumArray(arr, size) << endl;

    return 0;
}