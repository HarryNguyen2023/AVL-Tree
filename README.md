# AVL-Tree
## Author Harry Nguyen (Created 07/09/2023)

AVL tree is a type of balance binary search tree, that maintains the height property of the tree paths, in order to ensure the basic tree operations such as search, insertion or deletion only have O(logn) time complexity.

Instead of containing only the key value, each node in the AVL tree also have a variable to contain the height of it. The height property of the AVL tree states that, mximum difference between the height of the left child and right child of each node can not exceed 1. Therefore, during insertion and deletion, we must implement the rotation technique, to maintain the appropriate height of the tree, which makes it more suitable for databases that require more search than insertion and deletion operations.

### My updates
- Although most of the tutorials both in the books and online only use integer as the specific data type for the AVL tree node, I have tried to create a more general tree that can utilizas most of the common data types in Cpp, even structure and union.
- I also have practice a lot of BST tree algorithms in this project.

### References
[1]. AVL Tree, https://www.programiz.com/dsa/avl-tree.

