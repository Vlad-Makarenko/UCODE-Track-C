
void mx_sort_arr_int (int *arr, int size){
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size - 1; ++j) {
            if (*(arr + j) > *(arr + j + 1)){
                int buf = *(arr + j);
                *(arr + j) = *(arr + j + 1);
                *(arr + j + 1) = buf;
            }
        }
    }
}
