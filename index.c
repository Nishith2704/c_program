#include <stdio.h>

// Structure to represent an edge in the graph
typedef struct {
    int src, dest, weight;
} Edge;

// Constants
#define NUM_VERTICES 7
#define NUM_EDGES 9

// Given edge list
Edge edges[] = {
    {0, 0, 0},
    {6, 1, 10}, {2, 1, 28}, {3, 2, 16},
    {7, 2, 14}, {4, 3, 12}, {5, 4, 22},
    {6, 5, 25}, {7, 5, 24}, {7, 4, 18}
};

// Function prototypes
void adjust(Edge a[], int i, int n);
void buildMinHeap(Edge a[], int n);
Edge deleteMin(Edge a[], int* n);

// Disjoint set operations
int parent[NUM_VERTICES + 1]; // Parent array for disjoint set
void simpleUnion(int i, int j);
int simpleFind(int i);

// Kruskal's algorithm
void kruskalMST(Edge edges[], int numEdges) {
    // Initialize parent array for disjoint set
    for (int i = 1; i <= NUM_VERTICES; i++) {
        parent[i] = -1;
    }

    Edge t[NUM_VERTICES + 1];
    int minCost = 0;
    int i = 0;

    // Construct a heap out of the edge costs
    buildMinHeap(edges, numEdges);

    // Process edges in sorted order
    while (i < NUM_VERTICES - 1 && numEdges > 0) {
        Edge minEdge = deleteMin(edges, &numEdges);
        int j = simpleFind(minEdge.src);
        int k = simpleFind(minEdge.dest);
        if (j != k) {
            i++;
            t[i] = minEdge;
            minCost += minEdge.weight;
            simpleUnion(j, k);
        }
    }

    // If there are less than n - 1 edges, no spanning tree exists
    if (i != NUM_VERTICES - 1) {
        printf("No spanning tree exists.\n");
        return;
    }

    // Output the edges of the minimum spanning tree
    printf("Edges in the minimum spanning tree:\n");
    for (int j = 1; j <= NUM_VERTICES - 1; j++) {
        printf("(%d, %d) : %d\n", t[j].src, t[j].dest, t[j].weight);
    }
    printf("Minimum cost: %d\n", minCost);
}

int main() {
    printf("Edges before sorting:\n");
    for (int i = 1; i <= NUM_EDGES; i++) {
        printf("(%d, %d) : %d\n", edges[i].src, edges[i].dest, edges[i].weight);
    }

    // Find the minimum spanning tree using Kruskal's algorithm
    kruskalMST(edges, NUM_EDGES);

    return 0;
}

// Function to build a min heap from an array of edges
void buildMinHeap(Edge a[], int n) {
    for (int i = n / 2; i >= 1; i--) {
        adjust(a, i, n);
    }
}

// Function to perform min-heapify operation
void adjust(Edge a[], int i, int n) {
    int j = 2 * i;
    Edge item = a[i];
    
    while (j <= n) {
        if (j < n && a[j].weight > a[j + 1].weight) {
            j++;
        }
        if (item.weight <= a[j].weight) {
            break;
        }
        a[j / 2] = a[j];
        j *= 2;
    }
    a[j / 2] = item;
}

// Function to delete the minimum element from a min heap
Edge deleteMin(Edge a[], int* n) {
    Edge min = a[1];
    a[1] = a[*n];
    (*n)--;
    adjust(a, 1, *n);
    return min;
}

// Performs the Union operation
void simpleUnion(int i, int j) {
    parent[i] = j; // Setting the parent of i as j.
}

// Performs the Find operation
int simpleFind(int i) {
    while (parent[i] >= 0) {
        i = parent[i]; // Traverse up the tree until finding the root
    }
    return i; // Return the root element of the set
}


