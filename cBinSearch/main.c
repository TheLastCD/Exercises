
#include <stdio.h>

int BinSearch(int* piSortedArray, int size, int iSearch) {
    int low = 0;
    int high = size - 1;

    while (low <= high) {
        int mid = low + (high - low) / 2;  // avoid overflow
        if (piSortedArray[mid] == iSearch) {
            return mid;  // found
        } else if (piSortedArray[mid] < iSearch) {
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }

    return -1;  // not found
}

int main() {

    int iSortedArray[8] = {0, 3, 5, 6, 30, 40, 100, 130};
    int iSearchValue = 5;

    int iIndex = BinSearch(iSortedArray, 8, iSearchValue);
    if (iIndex != -1) {
        printf("Found %d at index %d\n", iSearchValue, iIndex);
    } else {
        printf("%d not found\n", iSearchValue);
    }

    return 0;
}

