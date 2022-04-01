/**
 * @file bst.cpp
 * @author Erfan Rasti (erfanrasty@gmail.com)
 * @brief
 * @version 1.0.7
 * @date 2022-04-01
 *
 * @copyright Copyright (c) 2022
 *
 */

// Adding header files
#include "bst.h"

Node::Node()
    : value(0)
    , left(nullptr)
    , right(nullptr)
{
    /**
     * @brief Default constructor
     */

    std::cout << "Node default constructor called" << std::endl;
}

Node::Node(int _value, Node* _left, Node* _right)
    : value(_value)
    , left(_left)
    , right(_right)
{
    /**
     * @brief Construct a new Node object
     *
     * @param _value Value of the node
     * @param _left Left child of the node
     * @param _right Right child of the node
     */

    std::cout << "Node constructor called" << std::endl;
}

Node::Node(const Node& node)
    : value(node.value)
    , left(node.left)
    , right(node.right)
{
    /**
     * @brief Copy constructor
     *
     * @param node Node to copy
     */

    std::cout << "Node copy constructor called" << std::endl;
}

std::ostream& operator<<(std::ostream& stream, const Node& node)
{
    /**
     * @brief Overloaded << operator
     *
     * @param stream Stream to print
     * @param node Node to print
     * @return std::ostream&
     */

    std::cout << "Node operator << called" << std::endl;

    stream << "adress of node: " << &node << std::endl;
    stream << "value of node: " << node.value << std::endl;
    stream << "adress of left child: " << node.left << std::endl;
    stream << "adress of right child: " << node.right << std::endl;

    return stream;
}

std::partial_ordering Node::operator<=>(const Node& node) const
{
    /**
     * @brief Overloaded operator <=> with Node
     *
     * @param node Node to compare
     * @return std::partial_ordering
     */

    std::cout << "Node operator <=> with Node called" << std::endl;

    return value <=> node.value;
}

bool Node::operator==(const Node& node) const
{
    /**
     * @brief Overloaded operator == with Node
     *
     * @param node Node to compare
     * @return true if equal
     * @return false if not equal
     */

    std::cout << "Node operator == with Node called" << std::endl;

    return value == node.value;
}

std::partial_ordering Node::operator<=>(int _value) const
{
    /**
     * @brief Overloaded operator <=> with int
     *
     * @param _value Value to compare
     * @return std::partial_ordering
     */

    std::cout << "Node operator <=> with int called" << std::endl;

    return value <=> _value;
}

bool Node::operator==(int _value) const
{
    /**
     * @brief Overloaded operator == with int
     *
     * @param _value Value to compare
     * @return true if equal
     * @return false if not equal
     */

    std::cout << "Node operator == with int called" << std::endl;

    return value == _value;
}

Node*& BST::get_root() const
{
    /**
     * @brief Getter for root
     *
     * @return Node*&
     */

    std::cout << "BST get_root called" << std::endl;

    return const_cast<Node*&>(root);
}

void BST::bfs(std::function<void(Node*& node)> func) const
{
    /**
     * @brief Breadth first search
     *
     * @param func Function to call on each node
     */

    std::cout << "BST bfs called" << std::endl;

    std::queue<Node*> queue;
    // queue for storing nodes to apply func on

    queue.push(root);

    while (!queue.empty()) {

        Node* node { queue.front() };

        // Popping the front element
        queue.pop();

        func(node);

        // Adding child nodes to the queue

        if (node->left != nullptr)
            queue.push(node->left);

        if (node->right != nullptr)
            queue.push(node->right);
    }
}

size_t BST::length() const
{
    /**
     * @brief Get the length of the tree
     *
     * @return size_t
     */

    std::cout << "BST length called" << std::endl;

    size_t length { 0 };

    BST::bfs([&length](Node*& node) {
        length++;
    });

    return length;
}

bool BST::add_node(int _value)
{
    /**
     * @brief Add a node to the tree
     *
     * @param _value Value of the node
     * @return true Node added successfully
     * @return false Node not added
     */

    std::cout << "BST add_node called" << std::endl;

    Node** node { &root };
    // node: copy of refrence of root

    while (true) {
        if ((*node) == nullptr) {
            // if node is nullptr, add the node
            (*node) = new Node(_value, nullptr, nullptr);
            return true;
        }

        if (_value < (*node)->value) {
            // if value is less than the node, go left
            if ((*node)->left == nullptr) {
                (*node)->left = new Node(_value, nullptr, nullptr);

                return true;

            } else {
                node = &((*node)->left);
            }

        } else if (_value > (*node)->value) {
            // if value is greater than the node, go right
            if ((*node)->right == nullptr) {
                (*node)->right = new Node(_value, nullptr, nullptr);

                return true;

            } else {
                node = &((*node)->right);
            }

        } else {
            return false;
        }
    }

    return false;
}
Node** BST::find_node(int _value) const
{
    /**
     * @brief Find a node in the tree
     *
     * @param _value Value of the node
     * @return Node** Pointer to the node if found else nullptr
     */

    std::cout << "BST find_node called" << std::endl;

    Node** node { const_cast<Node**>(&root) };
    // node: copy of refrence of root

    while (true) {
        if ((*node) == nullptr) {
            // if node is nullptr, return nullptr
            return nullptr;
        }

        if (_value < (*node)->value) {
            // if value is less than the node, go left
            node = &((*node)->left);

        } else if (_value > (*node)->value) {
            // if value is greater than the node, go right
            node = &((*node)->right);

        } else {
            return node;
        }
    }

    return nullptr;
}

Node** BST::find_parrent(int _value) const
{
    /**
     * @brief Find the parrent of a node
     *
     * @param _value Value of the node
     * @return Node** or nullptr
     */

    std::cout << "BST find_parrent called" << std::endl;

    Node** node { const_cast<Node**>(&root) };
    Node** parrent { nullptr };
    // node: copy of refrence of root

    while (true) {
        if ((*node) == nullptr) {
            // if node is nullptr, return nullptr
            return nullptr;
        }

        if (_value < (*node)->value) {
            // if value is less than the node, go left
            parrent = node;
            node = &((*node)->left);

        } else if (_value > (*node)->value) {
            // if value is greater than the node, go right
            parrent = node;
            node = &((*node)->right);

        } else {
            return parrent;
        }
    }

    return nullptr;
}

Node** BST::find_successor(int _value) const
{
    /**
     * @brief Find the successor of a node
     *
     * @param _value Value of the node
     * @return Node** or nullptr
     */

    std::cout << "BST find_successor called" << std::endl;

    Node** node { find_node(_value) };

    if (node == nullptr)
        return nullptr;

    if ((*node)->left != nullptr) {
        // if node has a left child, return the rightmost child of the left child
        node = &((*node)->left);

        while ((*node)->right != nullptr)
            node = &((*node)->right);

        return node;

    } else {
        return node;
    }

    return nullptr;
}

bool BST::delete_node(int _value)
{
    /**
     * @brief Delete a node from the tree
     *
     * @param _value Value of the node
     * @return true Node deleted successfully
     * @return false Node not deleted
     */

    std::cout << "BST delete_node called" << std::endl;

    Node** node { find_node(_value) };

    if (node == nullptr)
        return false;

    if ((*node)->left == nullptr && (*node)->right == nullptr) {
        // if the node has no children, delete it
        delete (*node);
        (*node) = nullptr;

        return true;

    } else if ((*node)->left == nullptr) {
        // if the node has no left child, replace it with its right child
        Node* rightChildOfnode { (*node)->right };
        delete (*node);
        (*node) = rightChildOfnode;

        return true;

    } else if ((*node)->right == nullptr) {
        // if the node has no right child, replace it with its left child
        Node* leftChildOfnode { (*node)->left };
        delete (*node);
        (*node) = leftChildOfnode;

        return true;

    } else {
        // if the node has both children, replace it with its successor
        Node** successor { find_successor(_value) };
        (*node)->value = (*successor)->value;

        delete (*successor);
        (*successor) = nullptr;

        return true;
    }

    return false;
}

std::ostream& operator<<(std::ostream& stream, const BST& _bst)
{
    /**
     * @brief Overload the << operator
     *
     * @param stream Output stream
     * @param _bst BST object
     * @return std::ostream&
     */

    std::cout << "BST << operator called" << std::endl;

    stream << std::string(80, '*') << std::endl;

    _bst.bfs([&stream](Node*& node) {
        stream << std::left << std::setw(17) << node
               << "=> value:" << std::left << std::setw(10) << node->value
               << "left:" << std::left << std::setw(16) << node->left
               << "right:" << std::left << std::setw(16) << node->right << std::endl;
    });

    stream << "binary search tree size: " << _bst.length() << std::endl;
    stream << std::string(80, '*') << std::endl;

    return stream;
}

BST::BST()
{
    /**
     * @brief Default constructor
     */

    std::cout << "BST default constructor called" << std::endl;

    root = nullptr;
}

BST::BST(const BST& _bst)
{
    /**
     * @brief Copy constructor
     *
     * @param _bst BST object
     */

    std::cout << "BST copy constructor called" << std::endl;

    root = nullptr;

    _bst.bfs([this](Node*& node) {
        add_node(node->value);
    });
}

BST::BST(BST&& _bst)
{
    /**
     * @brief Move constructor
     *
     * @param _bst BST object
     */

    std::cout << "BST move constructor called" << std::endl;

    root = _bst.root;
    _bst.root = nullptr;
}
