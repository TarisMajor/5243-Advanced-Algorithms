# Adding the Delete Feature in a Binary Search Tree (BST)

In order to delete a node from a BST, there are 3 conditions that can take place: deleting a leaf node, deleting a node with one child, and deleting a node with two children. Each case requires careful handling to ensure that the tree remains balanced and correctly ordered. For nodes with two children, we have to replace the node with its inorder successor or predecessor, ensuring minimal disruption to the tree structure.

I had the most trouble implementing this scenario. It was easy to implement the base case when the tree either is empty, or doesn't have the number to delete. If the number to delete was less or greater than the node->data, then go to the left or right child respectively. If the node to delete has only a left child, replace the data with the left child's data. Then delete the left child. Do the same if the node to delete only has a right child.

If the node to delete has both children, then we need the next biggest number that is closest to the deleted node's value. The way to find the next biggest number is to go the the right child, then go all the way left. Then replace the value of that child with the node to be deleted, and delete the child node.
