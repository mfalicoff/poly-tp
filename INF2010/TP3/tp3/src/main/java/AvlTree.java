import java.util.ArrayDeque;
import java.util.LinkedList;
import java.util.List;

public class AvlTree<ValueType extends Comparable<? super ValueType> > {

    // Only node which has its parent to null
    private BinaryNode<ValueType> root;

    public AvlTree() { }

    /** TODO Worst case : O ( log n ) HAS TO BE ITERATIVE, NOT RECURSIVE
     *
     * Adds value to the tree and keeps it as a balanced AVL Tree
     * Should call balance only if insertion succeeds
     * AVL Trees do not contain duplicates
     *
     * @param value value to add to the tree
     */
    public void add(ValueType value) {
        if(root == null){
            root = new BinaryNode<ValueType>(value, null);
        }else{
            BinaryNode<ValueType> currentNode = root;

            //parcours de l'arbre
            while(currentNode.left != null && currentNode.right != null) {
                int compareToCurrentNode = value.compareTo(currentNode.value);
                if (compareToCurrentNode < 0) {
                    currentNode = currentNode.left;
                } else if (compareToCurrentNode > 0){
                    currentNode = currentNode.right;
                }else if(compareToCurrentNode == 0)
                    return;
            }

            //ajout du node
            int compareToCurrentNode = value.compareTo(currentNode.value);
            if(compareToCurrentNode < 0){
                if(currentNode.left != null){
                    currentNode = currentNode.left;
                }
                currentNode.left = new BinaryNode<ValueType>(value, currentNode);
                currentNode = currentNode.left;
            }else if(compareToCurrentNode > 0){
                if(currentNode.right != null){
                    currentNode = currentNode.right;
                }
                currentNode.right = new BinaryNode<ValueType>(value, currentNode);
                currentNode = currentNode.right;
            }else{
                //duplicate
                return;
            }

            //updating parents height, backtracking
            BinaryNode<ValueType> currentNodeCopy = currentNode;
            while(currentNodeCopy.parent != null){
                currentNodeCopy = currentNodeCopy.parent;
                currentNodeCopy.height = Math.max(height(currentNodeCopy.left), height(currentNodeCopy.right)) + 1;
            }
            balance(currentNode);
        }
    }

    /** TODO Worst case : O ( log n ) HAS TO BE ITERATIVE, NOT RECURSIVE
     *
     * Removes value from the tree and keeps it as a balanced AVL Tree
     * Should call balance only if removal succeeds
     *
     * @param value value to remove from the tree
     */
    public void remove(ValueType value){

            BinaryNode<ValueType> currentNode = root;

            //if root is all that is left
            if(value.compareTo(root.value) == 0){
                if(root.left == null && root.right == null){
                    root = null;
                    return;
                }
                // removes root and sets new root
                BinaryNode<ValueType> temp = root.right;
                BinaryNode<ValueType> tempL = root.left;
                BinaryNode<ValueType> tempR = root.left;
                while(temp.right != null){
                    temp = temp.right;
                }
                temp.parent.right = null;
                root = temp;
                tempR.parent = root;
                tempL.parent = root;
                root.right = tempR;
                root.left = tempL;
                root.parent = null;
                root.height = Math.max(root.right.height, root.left.height) + 1;
                balance(temp);
                return;
            }

            //traversing the tree
            while(currentNode.left != null && currentNode.right != null){
                int compareToCurrentNode = value.compareTo(currentNode.value);
                if(compareToCurrentNode < 0){
                    currentNode = currentNode.left;;
                }else if(compareToCurrentNode > 0){
                    currentNode = currentNode.right;
                }else if(compareToCurrentNode == 0){
                    BinaryNode<ValueType> currentCopy = currentNode;
                    currentNode = currentCopy.right;
                    int count = 0;
                    while(currentNode.left != null){
                        currentNode = currentNode.left;
                        count++;
                    }if(count != 0){
                        currentNode.parent.left = null;
                    }else
                        currentNode.parent.right = null;
                        currentNode.parent = currentCopy.parent;
                        currentNode.right = currentCopy.right;
                        currentNode.left = currentCopy.left;
                        if (currentNode.right != null)
                            currentNode.right.parent = currentNode;
                        if (currentNode.left != null)
                            currentNode.left.parent = currentNode;

                        if (currentNode.parent != null && currentCopy.value.compareTo(currentNode.parent.value) < 0)
                            currentNode.parent.left = currentNode;
                        else if (currentNode.parent != null)
                            currentNode.parent.right = currentNode;
                        //currentNode = currentNode.right;
                        while (currentNode.parent != null) {
                            currentNode.height = Math.max(height(currentNode.left), height(currentNode.right)) + 1;
                            currentNode = currentNode.parent;
                        }
                        balance(currentNode);
                        return;

                }

            }
            if(currentNode.value == value) {
                currentNode = currentNode.parent;
            }
            int compareToCurrentNode = value.compareTo(currentNode.value);
            if(compareToCurrentNode < 0){
                currentNode.left = null;
            }else{
                currentNode.right = null;
            }
        BinaryNode<ValueType> currentNodeCopy = currentNode;
        while(currentNodeCopy.parent != null){
            currentNodeCopy.height = Math.max(height(currentNodeCopy.left), height(currentNodeCopy.right)) + 1;
            currentNodeCopy = currentNodeCopy.parent;
        }
        balance(currentNode);
    }

    /** TODO Worst case : O ( log n ) HAS TO BE ITERATIVE, NOT RECURSIVE
     *
     * Verifies if the tree contains value
     * @param value value to verify
     * @return if value already exists in the tree
     */
    public boolean contains(ValueType value) {
        BinaryNode<ValueType> currentNode = root;
        while(currentNode != null){
            if(value.compareTo(currentNode.value) < 0){
                currentNode = currentNode.left;
            }else if(value.compareTo(currentNode.value) > 0){
                currentNode = currentNode.right;
            }else{
                return true;
            }
        }
        return false;
    }

    /** TODO Worst case : O( 1 )
     * Returns the max level contained in our root tree
     * @return Max level contained in our root tree
     */
    public int getHeight() {
        if(root == null)
            return -1;
        return root.height;
    }

    /** TODO Worst case : O( log n ) HAS TO BE ITERATIVE, NOT RECURSIVE
     *
     * Returns the node which has the minimal value contained in our root tree
     * @return Node which has the minimal value contained in our root tree
     */
    public ValueType findMin() {
        if(root == null)
            return null;
        BinaryNode<ValueType> currentNode = root;
        while(currentNode.left != null){
            currentNode = currentNode.left;
        }
        return currentNode.value;
    }


    /** TODO Worst case : O( n ) HAS TO BE ITERATIVE, NOT RECURSIVE
     * Returns all values contained in the root tree in ascending order
     * @return Values contained in the root tree in ascending order
     */
    public List<ValueType> infixOrder() {
        if(root == null)
            return null;
        LinkedList<BinaryNode<ValueType>> list = new LinkedList<BinaryNode<ValueType>>();
        BinaryNode<ValueType> currentNode = root;
        LinkedList<ValueType> retList = new LinkedList<ValueType>();
        while (currentNode != null || list.size() > 0){
            while(currentNode != null){
                list.addFirst(currentNode);
                currentNode = currentNode.left;
            }
                currentNode = list.pop();
                retList.add(currentNode.value);
                currentNode = currentNode.right;
        }
        return retList;
    }

    /** TODO Worst case : O( n ) HAS TO BE ITERATIVE, NOT RECURSIVE
     *
     * Returns all values contained in the root tree in level order from top to bottom
     * @return Values contained in the root tree in level order from top to bottom
     */
    public List<ValueType> levelOrder(){

        LinkedList<ValueType> list = new LinkedList<>();
        BinaryNode<ValueType> currentNode = root;
        LinkedList<BinaryNode<ValueType>> stack = new LinkedList<>();
        stack.add(root);

        while(!stack.isEmpty()){
            BinaryNode<ValueType> node = stack.pop();
            list.add(node.value);

            if(node.left != null)
                stack.add(node.left);
            if(node.right != null)
                stack.add(node.right);
        }
        return list;
    }

    private int height(BinaryNode<ValueType> node){
        if(node == null)
            return -1;
        else
            return node.height;
    }

    /** TODO Worst case : O( log n ) HAS TO BE ITERATIVE, NOT RECURSIVE
     *
     * Balances the whole tree
     * @param node Node to balance all the way to root
     */
    private void balance(BinaryNode<ValueType> node) {
        if(node == null)
            return;
        while(node != null){
            if(height(node.left) - height(node.right) > 1){
                if(height(node.left.left) >= height(node.left.right))
                    rotateLeft(node);
                else
                    doubleRotateLeft(node);
            }else if(height(node.right) - height(node.left) > 1){
                if(height(node.right.right) >= height(node.right.left))
                    rotateRight(node);
                else
                    doubleRotateRight(node);
            }
            node = node.parent;
        }
    }

    private void doubleRotateRight(BinaryNode<ValueType> node1){
        rotateLeft(node1.right);
        rotateRight(node1);
    }

    private void doubleRotateLeft(BinaryNode<ValueType> node1){
        rotateRight(node1.left);
        rotateLeft(node1);
    }


    /** TODO Worst case : O ( 1 )
     *
     * Single rotation to the left child, AVR Algorithm
     * @param node1 Node to become child of its left child
     */
    private void rotateLeft(BinaryNode<ValueType> node1){
        BinaryNode<ValueType> k1 = node1.left;
        node1.left = k1.right;
        if(node1.left != null)
            node1.left.parent = node1;
        k1.right = node1;
        k1.parent = node1.parent;
        if(height(k1.parent) == -1){
            this.root = k1;
        }
        node1.height = Math.max(height(node1.left), height(node1.right)) + 1;
        k1.height = Math.max(height(k1.left), node1.height) + 1;
        if(node1.parent != null)
            if(k1.value.compareTo(node1.parent.value) < 0){
                node1.parent.left = k1;
            }else
                node1.parent.right = k1;
        node1.parent = k1;
    }

    /** TODO Worst case : O ( 1 )
     *
     * Single rotation to the right, AVR Algorithm
     * @param node1 Node to become child of its right child
     */
    private void rotateRight(BinaryNode<ValueType> node1){
        BinaryNode<ValueType> k1 = node1.right;
        node1.right = k1.left;
        if(node1.right != null)
            node1.right.parent = node1;
        k1.left = node1;
        k1.parent = node1.parent;
        if(height(k1.parent) == -1){
            this.root = k1;
        }
        if(node1.parent != null)
            if(k1.value.compareTo(node1.parent.value) < 0){
                node1.parent.left = k1;
            }else
                node1.parent.right = k1;
        node1.height = Math.max(height(node1.left), height(node1.right)) + 1;
        k1.height = Math.max(height(k1.right), node1.height) + 1;
        node1.parent = k1;
    }

    static private class BinaryNode<ValueType> {
        ValueType value;

        BinaryNode<ValueType> parent; // Pointer to the node containing this node

        BinaryNode<ValueType> left = null; // Pointer to the node on the left which should contain a value below this.value
        BinaryNode<ValueType> right = null; // Pointer to the node on the right which should contain a value above this.value

        int height = 0;

        BinaryNode(ValueType value, BinaryNode<ValueType> parent)
        {
            this.value = value;
            this.parent = parent;
        }
    }
}
