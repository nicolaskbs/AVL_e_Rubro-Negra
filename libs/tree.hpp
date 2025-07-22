// uma árvore tem nó user
// inserção, remoção e print implementados no modelo BST
// a diferença ocorre no balanceamento

#pragma once

#include "node.hpp"

class Tree {

private:

    Node* pointer_to_root = nullptr;
    void printTree_private(Node* root_of_subtree,
                           const std::string& prefix = "",
                           bool is_left = true);
    void insert_non_empty(User user, Node* current_node, Node* pai);
    void recursive_remove(User user, Node* current_node);
    Node* find_leaf(User user, Node* current_node);

public:
    void printTree();
    void insert(User user);
    void remove(User user);
    virtual void balance() = 0;

};