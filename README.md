# B-TREE
![PyPI - Status](https://img.shields.io/pypi/status/Django.svg)

B-Tree exercise proposed by Data Structures and Algorithms professor, at [CESAR School](https://www.cesar.school).

## Context
`B-Tree` is a self-balancing search tree. In most of the other self-balancing search trees (like AVL and Red-Black Trees), it is assumed that everything is in main memory. To understand the use of B-Trees, we must think of the huge amount of data that cannot fit in main memory. When the number of keys is high, the data is read from disk in the form of blocks. Disk access time is very high compared to main memory access time. The main idea of using B-Trees is to reduce the number of disk accesses. Most of the tree operations (search, insert, delete, max, min, ..etc ) require `O(h)` disk accesses where `h` is the height of the tree. B-tree is a fat tree. The height of B-Trees is kept low by putting maximum possible keys in a B-Tree node. Generally, a B-Tree node size is kept equal to the disk block size. Since `h` is low for B-Tree, total disk accesses for most of the operations are reduced significantly compared to balanced Binary Search Trees like AVL Tree, Red-Black Tree, ..etc.

## Properties of B-Tree
1. All leaves are at same level.
2. A B-Tree is defined by the term minimum degree `t`. The value of `t` depends upon disk block size.
3. Every node except root must contain at least `t-1` keys. Root may contain minimum 1 key.
4. All nodes (including root) may contain at most `2t – 1` keys.
5. Number of children of a node is equal to the number of keys in it `plus 1`.
6. All keys of a node are sorted in increasing order. The child between two keys `k1` and `k2` contains all keys in the range from `k1` and `k2`.
7. B-Tree grows and shrinks from the root which is unlike Binary Search Tree. Binary Search Trees grow `downward` and also shrink from `downward`.
8. Like other balanced Binary Search Trees, time complexity to search, insert and delete is `O(Logn)`.

### Example
Following is an example B-Tree of minimum degree `3`. Note that in practical B-Trees, the value of minimum degree is much more than `3`.

                                           3  30  60   
                                       /      / \      \
                                    1 2  4 5 6  40 50  70 80 82 84 86
