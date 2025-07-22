#pragma once

#include "user.hpp"

enum Color { RED, BLACK };

struct Node {

    User user;
    Node* left_child = nullptr;
    Node* right_child = nullptr;
    Node* parent = nullptr;
    int height;
    Color color;

    Node(User u, 
        Node* p) 
        : user(u),
        parent(p) {}

};
