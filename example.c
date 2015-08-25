#include <stdio.h>

#include "naive_adj_mat.h"

int main(void){
    /* create a new adjacency matrix with 3 nodes */
    struct naive_adj_mat *nam = nam_new(4);

    /* temporary integers used later */
    int i = 0;
    int j = 0;
    int n = 0;

    /* add some edges */
    /* 0 -> 1 */
    nam_add_edge(nam, 0, 1);
    /* 0 -> 2 */
    nam_add_edge(nam, 0, 2);
    /* 2 -> 3 */
    nam_add_edge(nam, 2, 3);

    /* test existing connections */
    if( nam_test_edge(nam, 0, 1) ){
        puts("edge exists from 0 to 1");
    }

    /* test non-existing connections */
    if( ! nam_test_edge(nam, 1, 0) ){
        puts("no edge exists from 1 to 0");
    }

    /* delete edge 0 -> 1 */
    nam_remove_edge(nam, 0, 1);

    /* get number of nodes */
    n = nam_size(nam);

    puts("\nlist of all edges");

    /* iterate through nodes */
    for( i = 0; i<n; ++i ){
        for( j=0; j<n; ++j ){
            if( nam_test_edge(nam, i, j) ){
                printf("%d -> %d\n", i, j);
            }
        }
    }

    /* cleanup
     *  destroy(nam, free_nam) */
    nam_destroy(nam, 1);

    return 0;
}

