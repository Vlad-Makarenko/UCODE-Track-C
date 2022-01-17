#include "libmx.h"

int mx_quicksort(char ** arr, int left, int right){
    if(arr == NULL){
        return -1;
    }

    int tmp_left = left;
    int tmp_right = right; 
    int swaps = 0;
    char *temp;
    char *pivot = arr[ (left + right) /2 ];

    while (tmp_left <= tmp_right) {
        while (mx_strlen(arr[tmp_left]) < mx_strlen(pivot)) {
            tmp_left++;
        }
        while (mx_strlen(arr[tmp_right]) > mx_strlen(pivot)) { 
            tmp_right--;
        }
        if (tmp_left <= tmp_right) {
            if (mx_strlen(arr[tmp_left]) > mx_strlen(arr[tmp_right])) {
                temp = arr[tmp_left]; 
                arr[tmp_left] = arr[tmp_right]; 
                arr[tmp_right] = temp;
                swaps++;
            }
            tmp_left++; tmp_right--;
        }
    }
    if (left < tmp_right) {
        swaps += mx_quicksort (arr, left, tmp_right);
    }
    if (tmp_left < right) {
        swaps += mx_quicksort (arr, tmp_left, right);
    }

    return swaps;
}
