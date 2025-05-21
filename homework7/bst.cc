#include "bst.h"
#include <functional>

// ---------------------------------------
// Node class
// Default constructor
Node::Node() {
    // TODO DONE: Implement this
    key = 0;
    parent = nullptr;
    right = nullptr;
    left = nullptr;
}

// Constructor
Node::Node(int in) {
    // TODO DONE: Implement this
    key = in;
    parent = nullptr;
    right = nullptr;
    left = nullptr;
}

// Destructor
Node::~Node() {
    //nothing needed
    // TODO DONE: Implement this
}

// Add parent 
void Node::add_parent(Node* in) {
    // TODO DONE: Implement this
    parent = in;
}

// Add to left of current node
void Node::add_left(Node* in) {
    // TODO DONE: Implement this
    left = in;
}

// Add to right of current node
void Node::add_right(Node* in) {
    // TODO DONE: Implement this
    right = in;
}

// Get key
int Node::get_key()
{
    // TODO DONE: Implement this
    return key;
}

// Get parent node
Node* Node::get_parent()
{
    // TODO DONE: Implement this
    return parent;
}

// Get left node
Node* Node::get_left()
{
    // TODO DONE: Implement this
    return left;
}

// Get right node
Node* Node::get_right()
{
    // TODO DONE: Implement this
    return right;
}

// Print the key to ostream to
// Do not change this
void Node::print_info(ostream& to)
{
    to << key << std::endl;
}
// ---------------------------------------


// ---------------------------------------
// BST class
// Walk the subtree from the given node

//add transplant function
void BST::transplant(Node* u, Node* v) {
    if (u->get_parent() == nullptr) {
        // u is the root
        root = v;
    } else if (u == u->get_parent()->get_left()) {
        u->get_parent()->add_left(v);
    } else {
        u->get_parent()->add_right(v);
    }
    if (v != nullptr) {
        v->add_parent(u->get_parent());
    }
}

void BST::inorder_walk(Node* in, ostream& to)
{
    // TODO DONE: Implement this
    if (in == nullptr) return;
    inorder_walk(in->get_left(), to);
    in->print_info(to);
    inorder_walk(in->get_right(), to);
}

// Constructor
BST::BST()
{
    // TODO DONE: Implement this
    root = nullptr;
}

// Destructor
BST::~BST()
{
    // TODO DONE: implement this
    std::function<void(Node*)> freeAll = [&](Node* node) {
        if (!node) return;
        freeAll(node->get_left());
        freeAll(node->get_right());
        delete node;
    };

    freeAll(root);
    root = nullptr;
}


// Insert a node to the subtree
void BST::insert_node(Node* in)
{
    // TODO DONE: Implement this
   
    Node* y = nullptr;
    Node* x = root;

    // Standard BST insert logic
    while (x != nullptr) {
        y = x;
        if (in->get_key() < x->get_key()) {
            x = x->get_left();
        } else {
            x = x->get_right();
        }
    }
    in->add_parent(y);

    // If tree was empty
    if (y == nullptr) {
        root = in;
    } else if (in->get_key() < y->get_key()) {
        y->add_left(in);
    } else {
        y->add_right(in);
    }
}


// Delete a node to the subtree
void BST::delete_node(Node* out)
{
    // TODO DONE: Implement this
    if (out == nullptr) return;

    // Case 1 or 2: out has at most one child
    if (out->get_left() == nullptr) {
        transplant(out, out->get_right());
    } 
    else if (out->get_right() == nullptr) {
        transplant(out, out->get_left());
    } 
    else {
        // out has two children: find successor
        Node* y = get_min(out->get_right());
        if (y->get_parent() != out) {
            // Move y's right child up
            transplant(y, y->get_right());
            // y takes out->right as its right child
            y->add_right(out->get_right());
            if (y->get_right() != nullptr) {
                y->get_right()->add_parent(y);
            }
        }
        // Replace out with y
        transplant(out, y);
        // y takes out->left as its left child
        y->add_left(out->get_left());
        if (y->get_left() != nullptr) {
            y->get_left()->add_parent(y);
        }
    }
    //delete the node
    delete out;
}

//minimum key in the BST
Node* BST::tree_min()
{
    // TODO DONE: Implement this
    return get_min(root);
}

// maximum key in the BST
Node* BST::tree_max()
{
    // TODO DONE: Implement this
    return get_max(root);
}

// Get the minimum node from the subtree of given node
Node* BST::get_min(Node* in)
{
    // TODO DONE: Implement this
    if (in == nullptr) return nullptr;
    while (in->get_left() != nullptr) {
        in = in->get_left();
    }
    return in;
}

// Get the maximum node from the subtree of given node
Node* BST::get_max(Node* in)
{
// TODO DONE: Implement this
    if (in == nullptr) return nullptr;
    while (in->get_right() != nullptr) {
        in = in->get_right();
    }
    return in;
}

// Get successor of the given node
Node* BST::get_succ(Node* in)
{
    // TODO DONE: Implement this
    if (in == nullptr) return nullptr;
    // If right subtree, successor is min of right subtree
    if (in->get_right() != nullptr) {
        return get_min(in->get_right());
    }
    //go up until find a node that is a left child
    Node* p = in->get_parent();
    Node* curr = in;
    while (p != nullptr && curr == p->get_right()) {
        curr = p;
        p = p->get_parent();
    }
    return p;
}

//get predecessor of the given node

Node* BST::get_pred(Node* in)
{
    // TODO DONE: Implement this
    if (in == nullptr) return nullptr;
    // If there's a left subtree, predecessor is max of left subtree
    if (in->get_left() != nullptr) {
        return get_max(in->get_left());
    }
    // Otherwise, go up until we find a node that is a right child
    Node* p = in->get_parent();
    Node* curr = in;
    while (p != nullptr && curr == p->get_left()) {
        curr = p;
        p = p->get_parent();
    }
    return p;
}

// Walk the BST from min to max
void BST::walk(ostream& to)
{
    inorder_walk(root, to);
    // TODO DONE: Implement this
}

// Search the tree for a given key
Node* BST::tree_search(int search_key)
{
    // TODO DONE: Implement this
    Node* x = root;
    while (x != nullptr) {
        if (search_key == x->get_key()) {
            return x;
        } else if (search_key < x->get_key()) {
            x = x->get_left();
        } else {
            x = x->get_right();
        }
    }
    return nullptr;
}
// ---------------------------------------