#ifndef NAIVE_ADJ_MAT_H
#define NAIVE_ADJ_MAT_H

/* this library is called `naive` because it uses a single char per edge
 * when really all we need is a single bit
 */
struct naive_adj_mat {
    unsigned int n_nodes;
    /* current size is n_nodes * n_nodes */
    unsigned char *matrix;
};

/* allocate and initialise a new adj. matrix containing `num_nodes` nodes
 * `num_nodes` may be 0
 *
 * returns * on success
 * returns 0 on error
 */
struct naive_adj_mat * nam_new(unsigned int num_nodes);

/* initialise an existing adj. matrix containing `num_nodes` nodes
 * `num_nodes` may be 0
 *
 * returns 1 on success
 * returns 0 on failure
 */
unsigned int nam_init(struct naive_adj_mat *nam, unsigned int num_nodes);

/* destroy an existing adj. matrix
 * will call free on `nam` if `free_name` is truethy
 *
 * returns 1 on success
 * returns 0 on failure
 */
unsigned int nam_destroy(struct naive_adj_mat *nam, unsigned int free_nam);

/* resize an existing adj. matrix to include enough space for
 * the number of nodes specified by `num_nodes`
 * `num_nodes` must be greater than 0
 *
 * returns 1 on success
 * returns 0 on failure
 */
unsigned int nam_resize(struct naive_adj_mat *nam, unsigned int num_nodes);

/* get current number of nodes
 *
 * returns number of nodes on success (which may be 0)
 * returns 0 on error
 */
unsigned int nam_size(struct naive_adj_mat *nam);

/* add a directed edge from node number `from` to node number `to`
 *
 * from and to must be less than current size, otherwise it is an error
 *
 * returns 1 on success
 * returns 0 on failure
 */
unsigned int nam_add_edge(struct naive_adj_mat *nam, unsigned int from, unsigned int to);

/* remove the directed edge from node number `from` to node number `to`.
 * such an edge doesn't have to already exist
 *
 * from and to must be less than current size, otherwise it is an error
 *
 * returns 1 on success
 * returns 0 on failure
 */
unsigned int nam_remove_edge(struct naive_adj_mat *nam, unsigned int from, unsigned int to);

/* test if an edge exists from node number `from` to node number `to`.
 *
 * if `from` or `to` are not less than current size then `0` is returned
 *
 * returns 1 if edge exists
 * returns 0 if edge does not exist
 */
unsigned int nam_test_edge(struct naive_adj_mat *nam, unsigned int from, unsigned int to);


#endif //NAIVE_ADJ_MAT_H

