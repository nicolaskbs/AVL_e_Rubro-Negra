#include "../libs/all_libs.hpp"

int AVL::height(Node* node) {
    return node ? node->height : 0;
}

void AVL::update_height(Node* node) {
    if (node) {
        node->height = 1 + std::max(height(node->left_child), height(node->right_child));
    }
}

int AVL::get_balance(Node* node) {
    return node ? height(node->left_child) - height(node->right_child) : 0;
}

Node* AVL::rotate_right(Node* node) {
    Node* right_node = node->left_child;
    Node* left_node = right_node->right_child;

    right_node->right_child = node;
    node->left_child = left_node;
    
    if (node->parent && node->parent->left_child == node){ 
        node->parent->left_child = right_node;
    } else if(node->parent) {
        node->parent->right_child = right_node;
    }
    right_node->parent = node->parent;
    node->parent = right_node;
    if(left_node) {
        left_node->parent = node;
    }

    update_height(node);
    update_height(right_node);

    return right_node;
}

Node* AVL::rotate_left(Node* node) {
    Node* right_node = node->right_child;
    Node* left_node = right_node->left_child;

    right_node->left_child = node;
    node->right_child = left_node;
    
    if (node->parent && node->parent->left_child == node){ 
        node->parent->left_child = right_node;
    } else if(node->parent){ 
        node->parent->right_child = right_node;
    }
    right_node->parent = node->parent;
    node->parent = right_node;
    if(left_node) {
        left_node->parent = node;
    }

    update_height(node);
    update_height(right_node);

    return right_node;
}

Node* AVL::balance(Node* node) {
    update_height(node);
    int balance = get_balance(node);

    if (balance > 1) {
        if (get_balance(node->left_child) < 0) {
            node->left_child = rotate_left(node->left_child);
        }
        return rotate_right(node);
    }
    if (balance < -1) {
        if (get_balance(node->right_child) > 0) {
            node->right_child = rotate_right(node->right_child);
        }
        return rotate_left(node);
    }
    return node;
}

Node* AVL::insert_private(Node* node, User user) {
    node = Tree::insert_private(node, user);
    return balance(node);
}

Node* AVL::remove_private(Node* node, User user) {
    if(node == nullptr) return node;
    
    if (user.userid < node->user.userid) {
        node->left_child = remove_private(node->left_child, user);
    } else if (user.userid > node->user.userid) {
        node->right_child = remove_private(node->right_child, user);
    } else {
        if (node->left_child == nullptr || node->right_child == nullptr) {
            Node* temp = node->left_child ? node->left_child : node->right_child;
            if (temp == nullptr) {
                temp = node;
                node = nullptr;
            } else {
                *node = *temp;
            }
            delete temp;
        } else {
            Node* temp = find_min(node->right_child);
            node->user = temp->user;
            node->right_child = remove_private(node->right_child, temp->user);
        }
    }

    if (node == nullptr) {
        return node;
    }

    return balance(node);
}