/*  gcc naive_adj_mat.c test_naive_adj_mat.c -Wall -Wextra -Werror -o test_nam
 * ./test_nam
 */
#include <assert.h> /* assert */
#include <stdio.h> /* puts */

#include "naive_adj_mat.h"

void simple(void){
    struct naive_adj_mat *nam = 0;
    int i = 0;
    int j = 0;

    puts("\ntesting basic usage");

    nam = nam_new();
    assert( nam );

    assert( nam_resize(nam, 5) );

    assert( nam->n_nodes == 5 );
    assert( nam_size(nam) == 5 );

    for( i=0; i<5; ++i ){
        for( j=0; j<5; ++j ){
            assert( 0 == nam_test_edge(nam, i, j) );
        }
    }

    assert( nam_add_edge(nam, 0, 2) );
    assert( nam_add_edge(nam, 1, 0) );
    assert( nam_add_edge(nam, 3, 1) );

    assert( nam_test_edge(nam, 0, 2) );
    assert( nam_test_edge(nam, 1, 0) );
    assert( nam_test_edge(nam, 3, 1) );

    assert( 0 == nam_test_edge(nam, 2, 0) );
    assert( 0 == nam_test_edge(nam, 0, 1) );
    assert( 0 == nam_test_edge(nam, 1, 3) );


    assert( nam_remove_edge(nam, 0, 2) );
    assert( 0 == nam_test_edge(nam, 0, 2) );
    assert( nam_test_edge(nam, 1, 0) );
    assert( nam_test_edge(nam, 3, 1) );

    assert( nam_remove_edge(nam, 1, 0) );
    assert( 0 == nam_test_edge(nam, 1, 0) );

    assert( nam_remove_edge(nam, 3, 1) );
    assert( 0 == nam_test_edge(nam, 3, 1) );


    for( i=0; i<5; ++i ){
        for( j=0; j<5; ++j ){
            assert( 0 == nam_test_edge(nam, i, j) );
        }
    }

    /* free nam as it was allocated via new */
    assert( nam_destroy(nam, 1) );

    puts("success!");
}

void init(void){
    struct naive_adj_mat nam;

    puts("\ntesting init");

    assert( nam_init(&nam) );

    assert( nam_resize(&nam, 4) );

    assert( nam.n_nodes == 4 );

    /* do not free nam as it was statically
     * allocated
     */
    assert( nam_destroy(&nam, 0) );

    puts("success!");
}

int main(void){
    simple();
    init();

    puts("\noverall testing success!");

    return 0;
}

