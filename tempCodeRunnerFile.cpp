#include <iostream>
using namespace std;

int sumArray(int arr[], int size) {
    int sum = 0;
    for (int i = 0; i < size; i++) {
        sum += arr[i];
    }
    return sum;
}
double averageArray(int arr[], int size) {
    return static_cast<double>(sumArray(arr, size)) / size;
}
int main() {
    int size;
    cout << "Enter the number of elements in the array: ";
    cin >> size;

    int arr[size];
    cout << "Enter the elements of the array: ";
    for (int i = 0; i < size; i++) {
        cin >> arr[i];
    }

    cout << "Sum of array elements: " << sumArray(arr, size) << endl;
    cout << "Average of array elements: " << averageArray(arr, size) << endl;
    return 0;
}