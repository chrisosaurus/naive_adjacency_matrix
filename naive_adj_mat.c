
#include "naive_adj_mat.h"

/* FIXME pending implementation */
#pragma GCC diagnostic ignored "-Wunused-parameter"

/* allocate and initialise a new adj. matrix
 *
 * returns * on success
 * returns 0 on error
 */
struct naive_adj_mat * nam_new(void){
    /* FIXME unimplemented */
    return 0;
}

/* initialise an existing adj. matrix
 *
 * returns 1 on success
 * returns o on failure
 */
unsigned int nam_init(struct naive_adj_mat *nam){
    /* FIXME unimplemented */
    return 0;
}

/* destroy an existing adj. matrix
 * will call free on `nam` if `free_name` is truethy
 *
 * returns 1 on success
 * returns 0 on failure
 */
unsigned int nam_destroy(struct naive_adj_mat *nam, unsigned int free_nam){
    /* FIXME unimplemented */
    return 0;
}

/* resize an existing adj. matrix to include enough space for
 * the number of nodes specified by `num_node`
 *
 * returns 1 on success
 * returns 0 on failure
 */
unsigned int nam_resize(struct naive_adj_mat *nam, unsigned int num_nodes){
    /* FIXME unimplemented */
    return 0;
}

/* get current number of nodes
 *
 * returns number of nodes on success (which may be 0)
 * returns 0 on error
 */
unsigned int nam_size(struct naive_adj_mat *nam){
    /* FIXME unimplemented */
    return 0;
}

/* add a directed edge from node number `from` to node number `to`
 *
 * from and to must be less than current size, otherwise it is an error
 *
 * returns 1 on success
 * returns 0 on failure
 */
unsigned int nam_add_edge(struct naive_adj_mat *nam, unsigned int from, unsigned int to){
    /* FIXME unimplemented */
    return 0;
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
    /* FIXME unimplemented */
    return 0;
}

/* test if an edge exists from node number `from` to node number `to`.
 *
 * if `from` or `to` are not less than current size then `0` is returned
 *
 * returns 1 if edge exists
 * returns 0 if edge does not exist
 */
unsigned int nam_test_edge(struct naive_adj_mat *nam, unsigned int from, unsigned int to){
    /* FIXME unimplemented */
    return 0;
}


