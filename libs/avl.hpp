#pragma once

#include "tree.hpp"

class AVL : public Tree {
private:
    int height(Node* node);
    int get_balance(Node* node);
    void update_height(Node* node);
    Node* rotate_right(Node* y);
    Node* rotate_left(Node* x);
    Node* balance(Node* node);
    Node* insert_private(Node* node, User user) override;
    Node* remove_private(Node* node, User user) override;
};