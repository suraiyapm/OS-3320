#include <stdio.h>

int binarySearch(int arr[], int key) { // Issue to remember: Kept trying to type it as
// variations of int[] arr, kept having a problem come up on bottom panel.

    int lhs = 0;
    int mid;
    int rhs = sizeof(arr)-1;
    // In the bottom panel for VS Code (within the VB Ubuntu) is pointing out:
    // sizeof here is returning basically the pointer to that, but that's the point, no?

    while (lhs <= rhs) {
        // middle loc in arr
        mid = lhs + ((rhs - lhs) / 2);

        if (arr[mid] == key) {
            return mid;
        } else if (arr[mid] < key) {
            lhs = ++mid;
        } else {
            rhs = --mid;
        }
    }
    return -1;
    // If it's never found throughout that. Should be found as mid in the first part of the if statement.
}

// Had issue: implicit function declaration. Forgot to move it above main! Java habits.
// Moving it to earlier than it's call appearance solved the issue.

int main() { // doesn't need command-line parameters, so going with no parameters (although void may be good).
    int arr[] = {0,1,2,3,4,5,6,7,8,9};
    int x = 4;
    int y = 10;
    int result;
    // printf("Type a number between zero and nine, inclusive: ");
    // I'll figure out regular I/O later on.
    printf("Array is from zero to nine, inclusive. My test number will be: %d.\n", x);

    result = binarySearch(arr, x);

    if (result == -1) {
        printf("%d was not found in this array.\n", x);
    } else {
        printf("%d was found at (from indices): %d\n", x, result);
    }

    printf("Now testing an expected fail, number: %d\n", y);

    result = binarySearch(arr, y);

    if (result == -1) {
        printf("%d was not found in the array, cool!\n", y);
    } else {
        printf("Uh oh, I seem to have an issue, as %d was found at %d.\n", y, result);
    }
    return 0;
}
// Did zero error handling, but functional!