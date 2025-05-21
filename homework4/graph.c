#include "graph.h"


/* This function initializes an adjacency list for a graph.
   input parameters:
       The following are 'consumed' by this function
       int           rows	# of rows (or vertices)

       The following are 'produced' by this function
       adj_node_t*** list 	initialized linked list of adjacencies for each 
				vertex
   return parameters:
       none
 */
void init_adj_list(adj_node_t*** list, int rows)
{
    // Allocate memory
    adj_node_t** tmpList = (adj_node_t**) malloc(sizeof(adj_node_t*) * rows);
    assert(tmpList);

    // Initialize each list to point to NULL
    for(int i = 0; i < rows; i++) {
        tmpList[i] = NULL;
    }

    // Return list
    *list = tmpList;
}


/* This function creates a new adj_node_t node for a vertex and initializes 
    it with node->vid = vid and node->next = NULL (i.e., no neighbor)
   The function then returns this node
   input parameters:
       int        vid		the ID of the vertex
   return parameters:
       adj_node_t newNode	the new node for the vertex 
 */
adj_node_t* create_node(int vid)
{
    adj_node_t* newNode = (adj_node_t*) malloc(sizeof(adj_node_t));
    assert(newNode);
    newNode->vid = vid;
    newNode->next = NULL;
    return newNode;

}


/* Pass in a linked list that represents an adjacnecy list and the row (or 
   vertex) to which you need to add a new node.
   First check that the adjacency list for the current row is not
   empty (i.e., NULL). If it is NULL, this is the first adjacent node.
   Otherwise, traverse the list until you reach the end, and then add
   the new node.
   input parameters:
       adj_node_t** list	adjacency list for the current graph
       int          row		vertex that has this node as adjacent
       adj_node_t*  node	the node that needs to be added
   return parameters:
       none
 */
void add_node(adj_node_t** list, int row, adj_node_t* node)
{
    if(list[row] == NULL) {
        // empty list - the head points to this node
        list[row] = node;
    } else {
        // otherwise, find the end, and add it to the end
        adj_node_t* next = list[row];
        while(next->next != NULL) {
            next = next->next;
        }
        next->next = node;
    }

}

/* Deqeueu a node from linked list and return the vertex id of the 
   removed node.

   Note that the input parameters is of type adj_node_t**, but in the
   beginning, it dereferences it to adj_node_t* head. So you are
   essentially passing in a pointer to adj_node_t*. 

   input parameters:
       adj_node_t**     pointer to an adj_node_t* , whic is essentially
                        the adjacency list of a PARTICULAR vertex, but
                        passed in by refrence.
   return parameters:
       int vid		the vertex ID (vid) of the removed node
 */
int remove_node(adj_node_t** list)
{
    int vid = -1;

    // if list valid - this should really never happen
    if(list != NULL) {
        adj_node_t* head = *list;
        // if list is not empty - this can happen if this
        // vertex has no neighbors left
        if(head != NULL) {
            adj_node_t* tmp = head;
            vid = head->vid;
            head = head->next;
            // don't foget to free the removed node
            free(tmp);
        }
        *list = head;
    } else {
        fprintf(stderr, "Adjacency list is NULL\n");
        exit(EXIT_FAILURE);
    }

    return vid;

}


/* This function constructs an adjacency list for a graph from an adjacency
   matrix
   input parameters: 
       The following are 'consumed' by this function
       int**         adj_mat 	2D array that stores the adjacency matrix
       int           rows	# of rows in the matrix
       int           cols	# of columns in the matrix

       The following are 'produced' by this function
       adj_node_t*** list	a linked list of adjacencies

   return parameters:
       none   

   adj_node_t*** list is passed in by reference from the main function so that
   it can be malloc'd via the init_adj_list function.
   After initializing it go through each row and add its adjacent nodes
 */
void construct_adj_list(int** adj_mat, int rows, int cols, adj_node_t*** list)
{
    if (rows != cols) {
        fprintf(stderr, "Adjacency matrix is not square\n");
        exit(EXIT_FAILURE);
    }
    fprintf(stdout, "Constructing the adjacency list for this graph ... ");

    init_adj_list(list, rows);
    adj_node_t** myList = *list;

    //Add edges properly
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (adj_mat[i][j] != 0) {  // There is an edge from i → j
                adj_node_t* node = create_node(j);
                add_node(myList, i, node);

                //if the graph is undirected, add the reverse edge
                adj_node_t* reverseNode = create_node(i);
                add_node(myList, j, reverseNode);
            }
        }
    }

    fprintf(stdout, "done\n");
}


/* This function takes in an adjacency ilst and prints out the list,
   one row/vertext at a time
   input parameters:
       adj_node_t** list	adjacency list for the graph
       int          rows	# of rows/vertices in the graph
   return parameters:
       none
 */
void print_adj_list(adj_node_t** list, int rows)
{
    assert(list);

    fprintf(stdout, "---- Print Adj. List ----\n");
    for(int i = 0; i < rows; i++) {
        fprintf(stdout, "|%d| -> ", i);
        adj_node_t* next = list[i];
        while(next != NULL) {
            fprintf(stdout, "%d -> ", next->vid);
            next = next->next;
        }
        fprintf(stdout, "END\n");
    }
    fprintf(stdout, "--------\n\n");
}

void free_adj_list(adj_node_t** list, int rows)
{
    if(list != NULL) {
        for(int i = 0; i < rows; i++) {
            if(list[i] != NULL) {
                adj_node_t* head = list[i];
                do {
                    adj_node_t* tmp = head;
                    head = head->next;
                    free(tmp);
                } while(head != NULL);
            }
        }
        free(list);
    }

    
}

void print_bfs_result(int rows, int* color, int* distance, int* parent)
{
    assert(color);
    assert(distance);
    assert(parent);

    printf("---- Print BFS Result ----\n");
    printf("Vert\tCol\tDis\tParent\n");
    for(int i = 0; i < rows; i++) {
        printf("%d\t%d\t%d\t%d\n", i, color[i], distance[i], parent[i]);
    }
    printf("--------\n\n");
}


/* Do the list-based BFS, given the source node and the graph's adjacency 
   list.
   Go through each vertices in a BFS manner, and then calculate the dsitance
   from the source vertex. 
       input parameters:
       The following are 'consumed' by this function
       adj_node_t** list		adjacency list for the graph
       int          rows		number of rows/vertices in the graph
       int          source		BFS source

       The following are 'produced' by this function
       int*         color		keeps track of color during BFS 
       int*         distance		distance from the source
       int*         parent		parent of each vertex
   return parameters:
       none
 */

void bfs(adj_node_t** list, int rows, int source, int* color, int* distance, int* parent)
{
    if (source >= rows) {
        fprintf(stderr, "Invalid source vertex\n");
        exit(EXIT_FAILURE);
    }
    assert(list && color && distance && parent);

    fprintf(stdout, "Breadth first search on the graph using linked list ... ");

    //Initialize BFS structures
    for (int i = 0; i < rows; i++) {
        color[i] = 0;      // White (unvisited)
        distance[i] = -1;  // -1 represents infinity/unreachable
        parent[i] = -1;    // No parent
    }

    //source vertex
    color[source] = 1;  // Gray (discovered)
    distance[source] = 0;
    parent[source] = -1;

    // dynamic array as a queue
    int* queue = (int*) malloc(rows * sizeof(int));
    int front = 0, back = 0;
    queue[back++] = source;  // Enqueue source

    //BFS loop
    while (front < back) {
        int u = queue[front++];  // Dequeue

        adj_node_t* curr = list[u];
        while (curr != NULL) {
            int v = curr->vid;
            if (color[v] == 0) {  // Not visited yet
                color[v] = 1;  // Mark as discovered
                distance[v] = distance[u] + 1;
                parent[v] = u;
                queue[back++] = v;  // Enqueue v
            }
            curr = curr->next;
        }
        color[u] = 2; // Mark as processed
    }

    free(queue);

    fprintf(stdout, "done\n");

    #if DEBUG
        print_bfs_result(rows, color, distance, parent);
    #endif
}


