#pragma once

#include "node.hpp"
#include <string>

class Tree {
protected:
    Node* root = nullptr;

    void printTree_private(Node* node, const std::string& prefix, bool is_left);
    virtual Node* insert_private(Node* node, User user);
    virtual Node* remove_private(Node* node, User user);
    Node* find_min(Node* node);
    void destroy_tree(Node* node);

public:
    Tree() = default;
    virtual ~Tree();

    void printTree();
    void insert(User user);
    void remove(User user);
};