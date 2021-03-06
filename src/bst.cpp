/**
 * @file bst.cpp
 * @author Erfan Rasti (erfanrasty@gmail.com)
 * @brief
 * @version 1.1.5
 * @date 2022-05-09
 *
 * @copyright Copyright (c) 2022
 *
 */

// Adding header files
#include "bst.h"

// Debug section

// #define DEBUG

#ifdef DEBUG
#define DEBUG_MSG(str)                 \
    do {                               \
        std::cout << str << std::endl; \
    } while (false)
#else
#define DEBUG_MSG(str) \
    do {               \
    } while (false)
#endif

BST::Node::Node()
    : value(0)
    , left(nullptr)
    , right(nullptr)
{
    /**
     * @brief Default constructor
     */

    DEBUG_MSG("Node default constructor called");
}

BST::Node::Node(int _value, Node* _left, Node* _right)
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

    DEBUG_MSG("Node constructor called");
}

BST::Node::Node(const Node& node)
    : value(node.value)
    , left(node.left)
    , right(node.right)
{
    /**
     * @brief Copy constructor
     *
     * @param node Node to copy
     */

    DEBUG_MSG("Node copy constructor called");
}

std::ostream& operator<<(std::ostream& stream, const BST::Node& node)
{
    /**
     * @brief Overloaded << operator
     *
     * @param stream Stream to print
     * @param node Node to print
     * @return std::ostream&
     */

    DEBUG_MSG("Node operator << called");

    stream << "adress of node: " << &node << std::endl;
    stream << "value of node: " << node.value << std::endl;
    stream << "adress of left child: " << node.left << std::endl;
    stream << "adress of right child: " << node.right << std::endl;

    return stream;
}

std::partial_ordering BST::Node::operator<=>(const Node& node) const
{
    /**
     * @brief Overloaded operator <=> with Node
     *
     * @param node Node to compare
     * @return std::partial_ordering
     */

    DEBUG_MSG("Node operator <=> with Node called");

    return value <=> node.value;
}

bool BST::Node::operator==(const Node& node) const
{
    /**
     * @brief Overloaded operator == with Node
     *
     * @param node Node to compare
     * @return true if equal
     * @return false if not equal
     */

    DEBUG_MSG("Node operator == with Node called");

    return value == node.value;
}

std::partial_ordering BST::Node::operator<=>(int _value) const
{
    /**
     * @brief Overloaded operator <=> with int
     *
     * @param _value Value to compare
     * @return std::partial_ordering
     */

    DEBUG_MSG("Node operator <=> with int called");

    return value <=> _value;
}

bool BST::Node::operator==(int _value) const
{
    /**
     * @brief Overloaded operator == with int
     *
     * @param _value Value to compare
     * @return true if equal
     * @return false if not equal
     */

    DEBUG_MSG("Node operator == with int called");

    return value == _value;
}

BST::Node*& BST::get_root() const
{
    /**
     * @brief Getter for root
     *
     * @return Node*&
     */

    DEBUG_MSG("BST get_root called");

    return const_cast<Node*&>(root);
}

void BST::bfs(std::function<void(Node*& node)> func) const
{
    /**
     * @brief Breadth first search
     *
     * @param func Function to call on each node
     */

    DEBUG_MSG("BST bfs called");

    std::queue<Node*> queue;
    // queue for storing nodes to apply func on

    if (root != nullptr) {
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
}

size_t BST::length() const
{
    /**
     * @brief Get the length of the tree
     *
     * @return size_t
     */

    DEBUG_MSG("BST length called");

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

    DEBUG_MSG("BST add_node called");

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
BST::Node** BST::find_node(int _value) const
{
    /**
     * @brief Find a node in the tree
     *
     * @param _value Value of the node
     * @return Node** Pointer to the node if found else nullptr
     */

    DEBUG_MSG("BST find_node called");

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

BST::Node** BST::find_parrent(int _value) const
{
    /**
     * @brief Find the parrent of a node
     *
     * @param _value Value of the node
     * @return Node** or nullptr
     */

    DEBUG_MSG("BST find_parrent called");

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

BST::Node** BST::find_successor(int _value) const
{
    /**
     * @brief Find the successor of a node
     *
     * @param _value Value of the node
     * @return Node** or nullptr
     */

    DEBUG_MSG("BST find_successor called");

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

bool BST::delete_node(int _value) const
{
    /**
     * @brief Delete a node from the tree
     *
     * @param _value Value of the node
     * @return true Node deleted successfully
     * @return false Node not deleted
     */

    DEBUG_MSG("BST delete_node called");

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
        Node* rightChildOfNode { (*node)->right };
        delete (*node);
        (*node) = rightChildOfNode;

        return true;

    } else if ((*node)->right == nullptr) {
        // if the node has no right child, replace it with its left child
        Node* leftChildOfNode { (*node)->left };
        delete (*node);
        (*node) = leftChildOfNode;

        return true;

    } else {
        // if the node has both children, replace it with its successor
        Node** successor { find_successor(_value) };

        if ((*successor)->left == nullptr) {
            // if the successor has no left child, replace the value of node with the value of successor
            (*node)->value = (*successor)->value;
            delete (*successor);
            (*successor) = nullptr;

            return true;

        } else {
            // if the successor has a left child, replace value of node with the value of successor
            // then replace the successor with the left child of the successor
            Node* leftChildOfSuccessor { (*successor)->left };
            (*node)->value = (*successor)->value;
            delete (*successor);
            (*successor) = leftChildOfSuccessor;

            return true;
        }
    }

    return false;
}

std::ostream& operator<<(std::ostream& stream, const BST& bst)
{
    /**
     * @brief Overload the << operator
     *
     * @param stream Output stream
     * @param bst BST object
     * @return std::ostream&
     */

    DEBUG_MSG("BST << operator called");

    stream << std::string(80, '*') << std::endl;

    bst.bfs([&stream](BST::Node*& node) {
        stream << std::left << std::setw(17) << node
               << "=> value:" << std::left << std::setw(10) << node->value
               << "left:" << std::left << std::setw(16) << node->left
               << "right:" << std::left << std::setw(16) << node->right << std::endl;
    });

    stream << "binary search tree size: " << bst.length() << std::endl;
    stream << std::string(80, '*') << std::endl;

    return stream;
}

BST::BST()
    : root { nullptr }
{
    /**
     * @brief Default constructor
     */

    DEBUG_MSG("BST default constructor called");
}

BST::BST(const BST& bst)
{
    /**
     * @brief Copy constructor
     *
     * @param bst BST object
     */

    DEBUG_MSG("BST copy constructor called");

    root = nullptr;

    bst.bfs([this](Node*& node) {
        add_node(node->value);
    });
}

BST::BST(BST&& bst)
{
    /**
     * @brief Move constructor
     *
     * @param bst BST object
     */

    DEBUG_MSG("BST move constructor called");

    root = bst.root;
    bst.root = nullptr;
}

BST::BST(std::initializer_list<int> listOfNodeValues)
{
    /**
     * @brief Initializer list constructor
     *
     * @param list Initializer list
     */

    DEBUG_MSG("BST initializer list constructor called");

    root = nullptr;

    for (auto& nodeValueItr : listOfNodeValues)
        add_node(nodeValueItr);
}

BST::~BST()
{
    /**
     * @brief Destructor
     */

    DEBUG_MSG("BST destructor called");

    std::vector<Node*> nodes;
    bfs([&nodes](BST::Node*& node) { nodes.push_back(node); });

    for (auto& node : nodes)
        delete node;

    root = nullptr;
}

const BST& BST::operator++() const
{
    /**
     * @brief Overload the pre-increment operator
     *
     * @return const BST&
     */

    DEBUG_MSG("BST pre-increment operator called");

    bfs([](Node*& node) {
        node->value++;
    });

    return *this;
}

const BST BST::operator++(int) const
{
    /**
     * @brief Overload the post-increment operator
     *
     * @return const BST
     */

    DEBUG_MSG("BST post-increment operator called");

    BST bst { *this };

    ++(*this);

    return bst;
}

BST& BST::operator=(const BST& bst)
{
    /**
     * @brief Overload the assignment operator
     *
     * @param bst BST object
     * @return BST&
     */

    DEBUG_MSG("BST assignment operator called");

    if (this != &bst) {
        BST::~BST();

        bst.bfs([this](BST::Node*& node) {
            add_node(node->value);
        });
    }

    return *this;
}

BST& BST::operator=(BST&& bst)
{
    /**
     * @brief Overload the move assignment operator
     *
     * @param bst BST object
     * @return BST&
     */

    DEBUG_MSG("BST move assignment operator called");

    if (this != &bst) {
        BST::~BST();

        root = bst.root;
        bst.root = nullptr;
    }

    return *this;
}