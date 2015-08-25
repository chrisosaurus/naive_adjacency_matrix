#include <stdio.h> /* puts */
#include <stdlib.h> /* calloc */

#include "naive_adj_mat.h"

/* return pointer to cell in matrix at [col][row]
 * returns 0 on error
 */
static unsigned char * nam_access(unsigned char *matrix, unsigned int n_nodes, unsigned int col, unsigned int row){
    unsigned int index = 0;

    if( ! matrix ){
        puts("nam_access: matrix was null");
        return 0;
    }

    if( col >= n_nodes ){
        puts("nam_access: provided column was greater than n_nodes");
        return 0;
    }

    if( row >= n_nodes ){
        puts("nam_access: provided row was greater than n_nodes");
        return 0;
    }

    /* index */
    index = col * n_nodes + row;

    if( index >= (n_nodes * n_nodes) ){
        puts("nam_access: illegal index");
        return 0;
    }

    return &(matrix[index]);
}

/* allocate and initialise a new adj. matrix containing `num_nodes` nodes
 * `num_nodes` may be 0
 *
 * returns * on success
 * returns 0 on error
 */
struct naive_adj_mat * nam_new(unsigned int num_nodes){
    struct naive_adj_mat *mat = 0;

    mat = calloc(1, sizeof(struct naive_adj_mat));
    if( ! mat ){
        puts("nam_new: call to calloc failed");
        return 0;
    }

    if( ! nam_init(mat, num_nodes) ){
        puts("nam_new: call to nam_init failed");
        return 0;
    }

    return mat;
}

/* initialise an existing adj. matrix containing `num_nodes` nodes
 * `num_nodes` may be 0
 *
 * returns 1 on success
 * returns 0 on failure
 */
unsigned int nam_init(struct naive_adj_mat *nam, unsigned int num_nodes){
    if( ! nam ){
        puts("nam_init: nam was null");
        return 0;
    }

    /* initialise to 0 */
    nam->n_nodes = 0;
    nam->matrix = 0;

    /* only call nam_resize if we have a `num_nodes` > 0 */
    if( num_nodes ){
        if( ! nam_resize(nam, num_nodes) ){
            puts("nam_init: call to nam_resize failed");
            return 0;
        }
    }

    return 1;
}

/* destroy an existing adj. matrix
 * will call free on `nam` if `free_name` is truethy
 *
 * returns 1 on success
 * returns 0 on failure
 */
unsigned int nam_destroy(struct naive_adj_mat *nam, unsigned int free_nam){
    if( ! nam ){
        puts("nam_destroy: nam was null");
        return 0;
    }

    /* always free matrix if defined */
    if( nam->matrix ){
        free(nam->matrix);
        nam->matrix = 0;
    }

    nam->n_nodes = 0;

    /* free nam if asked nicely */
    if( free_nam ){
        free(nam);
    }

    return 1;
}

/* resize an existing adj. matrix to include enough space for
 * the number of nodes specified by `num_nodes`
 * `num_nodes` must be greater than 0
 *
 * returns 1 on success
 * returns 0 on failure
 */
unsigned int nam_resize(struct naive_adj_mat *nam, unsigned int num_nodes){
    unsigned char *new_matrix = 0;
    unsigned int i = 0;
    unsigned int j = 0;
    unsigned char *from = 0;
    unsigned char *to = 0;

    if( ! nam ){
        puts("nam_resize: nam was null");
        return 0;
    }

    if( ! num_nodes ){
        puts("nam_resize: num_nodes must be greater than 0");
        return 0;
    }

    /* allocate new matrix */
    new_matrix = calloc(num_nodes * num_nodes, sizeof(unsigned char));
    if( ! new_matrix ){
        puts("nam_resize: call to calloc failed");
        return 0;
    }

    if( nam->matrix ){
        /* migrate over old elements */
        for( i=0; i < nam->n_nodes; ++i ){
            for( j=0; j < nam->n_nodes; ++j ){
                /* get pointer to `from` element */
                from = nam_access(nam->matrix, nam->n_nodes, i, j);
                if( ! from ){
                    puts("nam_resize: copying over failed, call to nam_access for from failed");
                    return 0;
                }

                /* get pointer to `to` slot */
                to = nam_access(new_matrix, num_nodes, i, j);
                if( ! to ){
                    puts("nam_resize: copying over failed, call to nam_access for to failed");
                    return 0;
                }

                /* perform copy */
                *to = *from;
            }
        }

        /* free old elements */
        free(nam->matrix);
    }

    /* swap */
    nam->matrix = new_matrix;
    nam->n_nodes = num_nodes;

    return 1;
}

/* get current number of nodes
 *
 * returns number of nodes on success (which may be 0)
 * returns 0 on error
 */
unsigned int nam_size(struct naive_adj_mat *nam){
    if( ! nam ){
        puts("nam_size: nam was null");
        return 0;
    }

    return nam->n_nodes;
}

/* add a directed edge from node number `from` to node number `to`
 *
 * from and to must be less than current size, otherwise it is an error
 *
 * returns 1 on success
 * returns 0 on failure
 */
unsigned int nam_add_edge(struct naive_adj_mat *nam, unsigned int from, unsigned int to){
    unsigned char *edge = 0;

    /* FIXME consider refactoring add_edge and remove_edge into single function */
    /* FIXME consider how much work we need to do here since we do work in nam_access */

    if( ! nam ){
        puts("nam_add_edge: nam was null");
        return 0;
    }

    if( from >= nam->n_nodes ){
        puts("nam_add_edge: from node is out of range");
        return 0;
    }

    if( to >= nam->n_nodes ){
        puts("nam_add_edge: to node is out of range");
        return 0;
    }

    edge = nam_access(nam->matrix, nam->n_nodes, from, to);
    if( ! edge ){
        puts("nam_add_edge: call to nam_access failed");
        return 0;
    }

    /* mark edge as existing */
    *edge = 1;

    return 1;
}

/* remove the directed edge from node number `from` to node number `to`.
 * such an edge doesn't have to already exist
 *
 * from and to must be less than current size, otherwise it is an error
 *
 * returns 1 on success
 * returns 0 on failure
 */
unsigned int nam_remove_edge(struct naive_adj_mat *nam, unsigned int from, unsigned int to){
    unsigned char *edge = 0;

    /* FIXME consider refactoring add_edge and remove_edge into single function */
    /* FIXME consider how much work we need to do here since we do work in nam_access */

    if( ! nam ){
        puts("nam_remove_edge: nam was null");
        return 0;
    }

    if( from >= nam->n_nodes ){
        puts("nam_remove_edge: from node is out of range");
        return 0;
    }

    if( to >= nam->n_nodes ){
        puts("nam_remove_edge: to node is out of range");
        return 0;
    }

    edge = nam_access(nam->matrix, nam->n_nodes, from, to);
    if( ! edge ){
        puts("nam_remove_edge: call to nam_access failed");
        return 0;
    }

    /* mark edge as not-existing */
    *edge = 0;

    return 1;
}

/* test if an edge exists from node number `from` to node number `to`.
 *
 * if `from` or `to` are not less than current size then `0` is returned
 *
 * returns 1 if edge exists
 * returns 0 if edge does not exist
 */
unsigned int nam_test_edge(struct naive_adj_mat *nam, unsigned int from, unsigned int to){
    unsigned char *edge = 0;

    /* FIXME consider refactoring add_edge and remove_edge into single function */
    /* FIXME consider how much work we need to do here since we do work in nam_access */

    if( ! nam ){
        puts("nam_test_edge: nam was null");
        return 0;
    }

    if( from >= nam->n_nodes ){
        puts("nam_test_edge: from node is out of range");
        return 0;
    }

    if( to >= nam->n_nodes ){
        puts("nam_test_edge: to node is out of range");
        return 0;
    }

    edge = nam_access(nam->matrix, nam->n_nodes, from, to);
    if( ! edge ){
        puts("nam_test_edge: call to nam_access failed");
        return 0;
    }

    /* return if edge exists */
    return 1 == *edge;
}


