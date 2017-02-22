# Algorithm


Algorithm and DataStructures exercises.

Build with CPP.


## DataStructures

1. ListNode: node for single linked list.  
2. LinkedList: single linked list based on pointer.  
3. Polynomial: polynomial class based on linked list, which supports operators +, - and *.  
4. Stack: stack based on linked list.  
5. StackBasedOnArray: stack based on array.
6. Queue: queue based on linked list.  
7. QueueBasedOnArray: queue based on array.
8. PriorityQueue: priority queue based on linked list.  
9. BinaryHeap: Binary heap based on array.  
10. SymbolTable: Symbol table based on linked list.  
11. OrderlySymbolTable: Orderly symbol table based on priority queue.  
12. BinarySearchTree: Binary search tree based on pointer.  
13. TwoThreeTree: 2-3-tree based on pointer, waiting for testing.
14. RBTree: Red-black tree based on pointer.
15. AVLTree: AVL tree based on pointer.
16. HashTable: Separate chaining hash table based on array and symbol table.
17. Graph: Undirected graph based on red black tree(vertex) and symbol table(adjacent vertex set).
18. Digraph: Directed graph based on red black tree(vertex) and symbol table(adjacent vertex set).

## Algorithm

1. BucketSort: bucket sort, time-O(num_max + num_size), space-O(num_max).  
2. RadixSort: radix sort, time-O(num_msd(num_size)), space-O(num_size * num_radix).  
3. SymbolPairChecker: check the symbol pairs in string, time-online-O(n), space-O(n).  
4. PostfixExpressionManager: evaluate a postfix expression(time-O(n), space-O(1)) or convert an infix expression to postfix expression(time-O(n), space-O(N)).  
5. SelectionSort: selection sort, time-O(n^2), space-O(1).  
6. insertionSort: insertion sort, time-O(n)~O(n^2), space-O(1). 
7. shellSort: shell sort, time-O(n)~O(n^(3/2))(faster than insertion sort), space-O(1). 
8. mergeSort: merge sort, time-O(n * log(n)), space-O(Pn). 
9. quickSort: quick sort, optimized by insertion sort, median3 and 3way, time-O(n * log(n)), space-O(n).
10. heapSort: heap sort, time-O(n * log(n)), space-O(n).
11. binarySearch: binary search, time-O(log(n)), space-O(1).
12. GraphDFS, GraphPathsDFS, GraphPathsBFS: algorithms for searching in graphs.
13. DigraphDFS, DigraphPathsDFS, DigraphPathsBFS: algorithms for searching in graphs.
14. DigraphFindCycle: finding the cycle in an digraph.  
15. DigraphDFO: depth-first-order algorithm for digraph.   
16. DigraphTopological: topological sorting for an non-cycle digraph.
17. DigraphSCCKosaraju: finding all strongly connected components in a digraph.
