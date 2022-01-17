#include "pathfinder.h"

void mx_Dijkstra_algorithm( int **adjacency_matrix, int **distance, int size, int begin_index) {

    int *_distance = *distance;
    int checked_vertices[size];

    for (int i = 0; i < size; ++i) {
        _distance[i] = INF;
        checked_vertices[i] = 1;
    }
    _distance[begin_index] = 0;
    int min_index = INF;
    int min_dist = INF;
    do{
        min_index = INF;
        min_dist = INF;
        for (int i = 0; i < size; ++i) {
            if( (checked_vertices[i] == 1) && (_distance[i] < min_dist) ){
                min_dist = _distance[i];
                min_index = i;
            }
        }
        if (min_index != INF){
            for (int i = 0; i < size; ++i) {
                if (adjacency_matrix[min_index][i] > 0){
                    int temp = min_dist + adjacency_matrix[min_index][i];
                    if (temp < _distance[i]) {
                        _distance[i] = temp;
                    }
                }
            }
            checked_vertices[min_index] = 0;
        }
    } while (min_index < INF);
}

