/**
* Binary Search Tree Class
* Stub written by Sorrachai Yingchareonthawornchai, 26 Sep 2014
* Completed by [Your Name]
*/

#ifndef BinarySearchTree_H
#define BinarySearchTree_H


//  Project description said no IO
#include <iostream>

#include <functional>


using namespace std;


template<class T> class BinarySearchTree
{
public:
    // Constructor
    BinarySearchTree() {root = nullptr;}

    // Destructor
    ~BinarySearchTree() { deleteTree(root); } // Complete

    // Insert
    void insert(const T &t); // Complete

    // Display (Commented out because of the "No I/O" specification
    void display() const { int level=0; _display(root,level); }

    // InOrder Traversal (vector parameter)
    void inOrderTraverse(vector<T>& vec) const; // Complete

    // Deletion
    void deleteNode(const T &t); // Complete

    // Foreach node in interval, do..
    void forEachInterval(const T &a, const T&b, function<void (const T)> func) const; // Complete

    // Filter results
    void filter(function<bool (const T)> isIn); // Complete

    // Verify tree
    bool verifyBinarySearchTree() const; // Complete


private:
    // class Node (you can modify,but it is not necessary)
    // The nested node class for objects in our tree.
    struct Node
    {
        // Friend classing
        friend class BinarySearchTree;

        // Constructor
        Node() {m_ll = nullptr;  m_rl = nullptr;}

        // Constructor with one param - data
        Node(const T &t) {m_num = t;  m_ll = nullptr;  m_rl = nullptr;}

        // Constructor with three params - data, left child, right child
        Node(const T &t, Node * l, Node *r) : m_num{t}, m_ll{l}, m_rl{r} {}

        // Function to return data
        T &data() {return m_num;}
        const T &data() const {return m_num;}

        // Lower left, lower right, and data
        Node    *m_ll;
        Node    *m_rl;
        T       m_num;
    };

    // Member
    Node *root;

    // Internal Display Method
    // Rotate the whole "graph" to the right once to see the tree (mentally..)

    // Commented Out - Project description says no IO

    void _display(Node *p,int level) const
    {
        // If node doesn't exist, return?? (void?)
        if (p ==nullptr) return;

        // Go down a level
        level++;

        // If the right child exists
        if (p->m_rl != nullptr)
        {
            // Display
            _display(p->m_rl,level);
        }

        // Add level 'spaces'
        for (int i = 0; i <= level; i++)
        {
            cout<<"    ";
        }

        // Add markers
        cout << "__" << p->data()<<endl;

        // If left child exists
        if (p->m_ll != nullptr)
        {
            // Display
            _display(p->m_ll, level);
        }
    }

    // Helpers
    void InsertHelper(Node *node, const T &t);
    void InOrderTraverseHelper(Node *node, vector<T> &vec) const;
    void DeleteHelper(Node *node, const T &t);
    void ForEachHelper(Node *node, const T &a, const T &b, function<void(const T)> func) const;
    bool VerifyHelper(Node *node) const;
    void FilterHelper(function<bool (const T)> isIn, Node* node);
    void RemoveRoot();
    void ReplaceWithLeftChildMaximum(Node *parent, Node *leftChild);
    void deleteTree(Node* node);
    T FindMaximum(Node *subRoot); // Returns the value

};

/**
* \brief Inserts a Node into the tree
* \param t - The data to insert as a Node into the tree
*/
template <class T> void BinarySearchTree<T>::insert(const T &t)
{
    // If there isn't a root
    if (root == nullptr)
    {
        // Create root with data
        root = new Node(t);
    }
    else // If there is a root
    {
        // Insert as leaf - beginning at root (helper call)
        InsertHelper(root, t);
    }
}

template<class T> void BinarySearchTree<T>::InsertHelper(Node *node, const T &t)
{
    // If node passed isn't null
    if (node != nullptr)
    {
        // If data is greater than the current node's data
        if (t > node->data())
        {
            // If the current node's right child doesn't exist
            if (node->m_rl == nullptr)
            {
                // Create right child as new node with the passed data
                node->m_rl = new Node(t);
            }
            else // The node's right child does exist
            {
                // Recursive call to insert on the right child side
                InsertHelper(node->m_rl, t);
            }
        }
        else if (t < node->data()) // If the data is less than the current node's data
        {
            // If the left child node doesn't exist
            if (node->m_ll == nullptr)
            {
                // Create node
                node->m_ll = new Node(t);
            }
            else // If the left child node exists
            {
                // Recursive call on the left child node to insert
                InsertHelper(node->m_ll, t);
            }
        }
    }

}

/**
* \brief Traverses the binary tree using the InOrder method and adds to a vector
* \param vec - The vector that will match our traversal of the tree (create)
*/
template <class T> void BinarySearchTree<T>::inOrderTraverse(vector<T> &vec) const
{
    if (root != nullptr)
    {
        InOrderTraverseHelper(root, vec);
    }
}

/**
* \brief Traverses the binary tree using the InOrder method
* \param node - The node we are displaying and traversing
* \param vec - The vector (passed by reference) to add the numbers to
* */
template <class T> void BinarySearchTree<T>::InOrderTraverseHelper(Node *node, vector<T> &vec) const
{
    // If the node exists
    if (node != nullptr)
    {
        // If left node exists
        if (node->m_ll != nullptr)
        {
            // Recursive call on left side
            InOrderTraverseHelper(node->m_ll, vec);
        }

        // Add to the vector
        vec.push_back(node->data());

        // If right child exists
        if (node->m_rl != nullptr)
        {
            // Recursive call on the right side
            InOrderTraverseHelper(node->m_rl, vec);
        }
    }
}

/*
 Deletes a node in the tree via passed value
 */
template <class T> void BinarySearchTree<T>::deleteNode(const T &t)
{
    // If the root exists
    if (root != nullptr)
    {
        // If we want to delete root
        if (root->data() == t)
        {
            // Remove the root
            RemoveRoot();
        }
        else
        {
            // Otherwise, delete member of the tree
            DeleteHelper(root, t);
        }
    }
}

/*
The helper function (recursive) for the deleteNode function
 */
template <class T> void BinarySearchTree<T>::DeleteHelper(Node *node, const T &t)
{
    // If the node exists
    if (node != nullptr)
    {
        // If t is less than the nodes data
        if (t < node->data())
        {
            // And the left child exists
            if (node->m_ll != nullptr)
            {
                // Check if left child is desired node to delete
                if (node->m_ll->data() == t)
                {
                    // Remove left node appropriately

                    // If left child node has no children
                    if (node->m_ll->m_ll == nullptr && node->m_ll->m_rl == nullptr)
                    {
                        node->m_ll = nullptr;

                        delete node->m_ll;
                    }

                    // If left child node has only right child
                    else if (node->m_ll->m_rl != nullptr && node->m_ll->m_ll == nullptr)
                    {
                        // Replace with right child subtree
                        node->m_ll = node->m_ll->m_rl;
                    }

                    // If left child node has left child (and maybe also right)
                    else if (node->m_ll->m_ll != nullptr)
                    {
                        // Replace with left child subtree maximum
                        ReplaceWithLeftChildMaximum(node->m_ll, node->m_ll->m_ll);
                    }
                }
                else // Otherwise - not desired node
                {
                    // Move down a level
                    DeleteHelper(node->m_ll, t);
                }
            }
        }

        // Otherwise, if t(data) is greater than current node's data
        else if (t > node->data())
        {
            // And the current node's right child exists
            if (node->m_rl != nullptr)
            {
                // If the right child's data is what we want to delete
                if (node->m_rl->data() == t)
                {
                    // Delete Right child

                    // If right child node has no children
                    if (node->m_rl->m_ll == nullptr && node->m_rl->m_rl == nullptr)
                    {
                        node->m_rl = nullptr;

                        delete node->m_rl;
                    }

                    // If right child node has only right child
                    else if (node->m_rl->m_rl != nullptr && node->m_rl->m_ll == nullptr)
                    {
                        // Replace with right child subtree
                        node->m_rl = node->m_rl->m_rl;
                    }

                    // If right child node has left child (and maybe also right)
                    else if (node->m_rl->m_ll != nullptr)
                    {
                        // Replace with left child subtree maximum
                        ReplaceWithLeftChildMaximum(node->m_rl, node->m_rl->m_ll);
                    }
                }
                else
                {
                    // Move down level
                    DeleteHelper(node->m_rl, t);
                }
            }
        }
    }
}

/*
Runs a function over each value in the search tree that falls within the specified interval (a -> b)
 */
template <class T> void BinarySearchTree<T>::forEachInterval(const T &a, const T &b, function<void(const T)> func) const
{
    // Make sure interval is valid
    if (b > a)
    {
        // Create temporary root node pointer
        Node *temp = root;

        // Run helper with pointer, interval, and function
        ForEachHelper(temp, a, b, func);
    }
}

/*
Helper (recursive) function for the foreach function
 */
template <class T> void BinarySearchTree<T>::ForEachHelper(Node *node, const T &a, const T &b, function<void(const T)> func) const
{
    // If passed node exists
    if (node != nullptr)
    {
        // If the data is within interval (equal to as well)
        if (node->data() >= a && node->data() <= b)
        {
            // Do operation
            func(node->data());

            // Repeat down both subtrees (left)
            if (node->m_ll != nullptr)
            {
                ForEachHelper(node->m_ll, a, b, func);
            }
            // Right
            if (node->m_rl != nullptr)
            {
                ForEachHelper(node->m_rl, a, b, func);
            }
        }
        else if (node->data() < a)
        {
            // Just go down right (don't want to get any smaller!)
            if (node->m_rl != nullptr)
            {
                ForEachHelper(node->m_rl, a, b, func);
            }
        }
        else if (node->data() > b)
        {
            // Just go down left (don't want to get any bigger!)
            if (node->m_ll != nullptr)
            {
                ForEachHelper(node->m_ll, a, b, func);
            }
        }
    }
}

/*
Verifies that the binary search tree is accurate
 */
template <class T> bool BinarySearchTree<T>::verifyBinarySearchTree() const
{
    // If there is a root node
    if (root != nullptr)
    {
        // Call helper (recursive function)
        bool result = VerifyHelper(root);

        // Return findings from helper
        return result;
    }
    else
    {
        // Empty tree is a legal B.S.T.
        return true;
    }
}

/*
Verify helper (recursive)
 */
template <class T> bool BinarySearchTree<T>::VerifyHelper(Node *node) const
{
    // If the node exists
    if (node != nullptr)
    {
        // Left and right subtree booleans (assume valid)
        bool leftSide = true;
        bool rightSide = true;

        // If left child node exists and is greater/equal to than parent
        if (node->m_ll != nullptr && node->m_ll->data() >= node->data())
        {
            // Invalid tree
            return false;
        }

        // If right child exists, and is less than parent
        if (node->m_rl != nullptr && node->m_rl->data() <= node->data())
        {
            // Invalid tree
            return false;
        }

        // If there is a left child
        if (node->m_ll != nullptr)
        {
            // Check it (return a boolean)
            leftSide = VerifyHelper(node->m_ll);
        }

        // If there is a right child
        if (node->m_rl != nullptr)
        {
            // Check it (return a boolean)
            rightSide = VerifyHelper(node->m_rl);
        }

        // If either of the checks came back false
        if (!leftSide || !rightSide)
        {
            // The tree is invalid
            return false;
        }
        else // Otherwise
        {
            // Tree is okay :)
            return true;
        }
    }
}

/*
Filters the binary search tree according to a passed function
 */
template <class T> void BinarySearchTree<T>::filter(function<bool(const T)> isIn)
{
    // If the root exists
    if (root != nullptr)
    {
        // If the function call on the root holds true
        if (isIn(root->data()) == true)
        {
            // Call helper function to iterate over rest of tree
            FilterHelper(isIn, root);
        }
        else if (isIn(root->data()) == false) // Otherwise, if it doesn't
        {
            // Remove root (replace with new one if need be
            RemoveRoot();

            // Retry the calling of this function (until root is sufficient!)
            filter(isIn);
        }
    }
}

/*
Filter helper function (recursive)
 */
template <class T> void BinarySearchTree<T>::FilterHelper(function<bool(const T)> isIn, Node *node)
{
    // If passed node exists
    if (node != nullptr)
    {
        // If the function call on this node's data holds true
        if (isIn(node->data()) == true)
        {
            // Go down rabbit holes (iterate)

            // If left child exists
            if (node->m_ll != nullptr)
            {
                // Recursive call on left subtree
                FilterHelper(isIn, node->m_ll);
            }

            // If right child exists
            if (node->m_rl != nullptr)
            {
                // Recursive call on right subtree
                FilterHelper(isIn, node->m_rl);
            }
        }
        else if (isIn(node->data()) == false) // Otherwise, doesn't hold
        {
            // Rabbit hole

            // If left child exists
            if (node->m_ll != nullptr)
            {
                // Recursive call on left subtree
                FilterHelper(isIn, node->m_ll);
            }

            // If right child exists
            if (node->m_rl != nullptr)
            {
                // Recursive call on right subtree
                FilterHelper(isIn, node->m_rl);
            }

            // Delete the node
            DeleteHelper(root, node->data());
        }
    }
}

/**
Removes the root (replacing accordingly)
*/
template <class T> void BinarySearchTree<T>::RemoveRoot()
{
    // If the root exists
    if (root != nullptr)
    {
        // If root has no children
        if (root->m_ll == nullptr && root->m_rl == nullptr)
        {
            root = nullptr;

            delete root;
        }

        // If root has only right child
        else if (root->m_ll == nullptr && root->m_rl != nullptr)
        {
            Node *temp = root->m_rl;

            root = temp;
        }

        // If root has left child and (maybe right)
        else if (root->m_ll != nullptr)
        {
            ReplaceWithLeftChildMaximum(root, root->m_ll);
        }
    }
}

/*
Finds the maximum of a left subtree, stores that maximum, deletes it's node, and reassigns the subtree root
to the value of the maximum
 */
template <class T> void BinarySearchTree<T>::ReplaceWithLeftChildMaximum(Node* parent, Node* leftChild)
{
    // If the parent and left child both exist
    if (leftChild != nullptr && parent != nullptr)
    {
        // Find maximum of left subtree
        T max = FindMaximum(leftChild);

        // Delete node based on that maximum
        DeleteHelper(parent, max);

        // Change the parent nodes value to the maximum
        parent->data() = max;
    }
}

/*
Finds the maximum of any given subtree
 */
template <class T> T BinarySearchTree<T>::FindMaximum(Node *subRoot)
{
    // If the sub tree exists
    if (subRoot != nullptr)
    {
        // If the subtree has a right child
        if (subRoot->m_rl != nullptr)
        {
            // Find maximum of the right child (recursive)
            T findResult = FindMaximum(subRoot->m_rl);

            // If findResult exists
            if (findResult)
            {
                // Return
                return findResult;
            }
        }
        // Otherwise, if the right child doesn't exist
        else if (subRoot->m_rl == nullptr)
        {
            // This node is the maximum - so return
            return subRoot->data();
        }
    }
}

/*
Deletes the whole tree (while loop)
 */
template <class T> void BinarySearchTree<T>::deleteTree(Node* node)
{
    // While the root exists
    while (root != nullptr)
    {
        // Remove it
        RemoveRoot();
    }
}


#endif
