#include "../libs/all_libs.hpp"

Tree::~Tree() {
    destroy_tree(root);
}

void Tree::destroy_tree(Node* node) {
    if (node) {
        destroy_tree(node->left_child);
        destroy_tree(node->right_child);
        delete node;
    }
}

void Tree::printTree_private(Node* node, const std::string& prefix, bool is_left) {
    if (node == nullptr) {
        return;
    }

    if (node->right_child) {
        printTree_private(node->right_child, prefix + (is_left ? "│   " : "    "), false);
    }

    std::cout << prefix << (is_left ? "└── " : "┌── ");
    if (dynamic_cast<Red_Black*>(this) && node->color == RED) { // Cor para diferenciar nós vermelhos
        std::cout << "\033[31m" << node->user.userid << "\033[0m" << std::endl;
    } else {
        std::cout << node->user.userid << std::endl;
    }

    if (node->left_child) {
        printTree_private(node->left_child, prefix + (is_left ? "    " : "│   "), true);
    }
}

void Tree::printTree() {
    if (root == nullptr) {
        std::cout << "A árvore está vazia." << std::endl;
    } else {
        printTree_private(root, "", true);
    }
    std::cout << "----------------------------------------" << std::endl;
}

void Tree::insert(User user) {
    root = insert_private(root, user);
}

void Tree::remove(User user) {
    root = remove_private(root, user);
}

Node* Tree::insert_private(Node* node, User user) {
    if (node == nullptr) {
        return new Node(user, nullptr);
    }

    if (user.userid < node->user.userid) {
        node->left_child = insert_private(node->left_child, user);
        if(node->left_child) node->left_child->parent = node;
    } else if (user.userid > node->user.userid) {
        node->right_child = insert_private(node->right_child, user);
        if(node->right_child) node->right_child->parent = node;
    }
    return node;
}

Node* Tree::remove_private(Node* node, User user) {
    if (node == nullptr) {
        return node;
    }

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
    return node;
}

Node* Tree::find_min(Node* node) {
    Node* current = node;
    while (current && current->left_child != nullptr) {
        current = current->left_child;
    }
    return current;
}