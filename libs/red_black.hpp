#pragma once

#include "tree.hpp"

class Red_Black : public Tree {
private:
    void rotate_left(Node* x);
    void rotate_right(Node* y);
    void insert_fixup(Node* z);
    void transplant(Node* u, Node* v);
    Node* find_min(Node* node);
    void remove_fixup(Node* x);
    Node* remove_private(Node* node, User user) override;

public:
    void insert(User user);
};