#include "../libs/all_libs.hpp"

void Red_Black::rotate_left(Node* x) {
    Node* y = x->right_child;
    x->right_child = y->left_child;
    if (y->left_child != nullptr) {
        y->left_child->parent = x;
    }
    y->parent = x->parent;
    if (x->parent == nullptr) {
        this->root = y;
    } else if (x == x->parent->left_child) {
        x->parent->left_child = y;
    } else {
        x->parent->right_child = y;
    }
    y->left_child = x;
    x->parent = y;
}

void Red_Black::rotate_right(Node* y) {
    Node* x = y->left_child;
    y->left_child = x->right_child;
    if (x->right_child != nullptr) {
        x->right_child->parent = y;
    }
    x->parent = y->parent;
    if (y->parent == nullptr) {
        this->root = x;
    } else if (y == y->parent->left_child) {
        y->parent->left_child = x;
    } else {
        y->parent->right_child = x;
    }
    x->right_child = y;
    y->parent = x;
}

void Red_Black::insert_fixup(Node* z) {
    while (z != root && z->parent->color == RED) {
        if (z->parent == z->parent->parent->left_child) {
            Node* y = z->parent->parent->right_child;
            if (y != nullptr && y->color == RED) {
                z->parent->color = BLACK;
                y->color = BLACK;
                z->parent->parent->color = RED;
                z = z->parent->parent;
            } else {
                if (z == z->parent->right_child) {
                    z = z->parent;
                    rotate_left(z);
                }
                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                rotate_right(z->parent->parent);
            }
        } else {
            Node* y = z->parent->parent->left_child;
            if (y != nullptr && y->color == RED) {
                z->parent->color = BLACK;
                y->color = BLACK;
                z->parent->parent->color = RED;
                z = z->parent->parent;
            } else {
                if (z == z->parent->left_child) {
                    z = z->parent;
                    rotate_right(z);
                }
                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                rotate_left(z->parent->parent);
            }
        }
    }
    root->color = BLACK;
}

void Red_Black::insert(User user) {
    Node* z = new Node(user, nullptr);
    Node* y = nullptr;
    Node* x = this->root;

    while (x != nullptr) {
        y = x;
        if (z->user.userid < x->user.userid) {
            x = x->left_child;
        } else {
            x = x->right_child;
        }
    }

    z->parent = y;
    if (y == nullptr) {
        root = z;
    } else if (z->user.userid < y->user.userid) {
        y->left_child = z;
    } else {
        y->right_child = z;
    }

    z->color = RED;
    insert_fixup(z);
}

void Red_Black::transplant(Node* u, Node* v) {
    if (u->parent == nullptr) {
        root = v;
    } else if (u == u->parent->left_child) {
        u->parent->left_child = v;
    } else {
        u->parent->right_child = v;
    }
    if (v != nullptr) {
        v->parent = u->parent;
    }
}

Node* Red_Black::find_min(Node* node){
    while(node->left_child != nullptr){
        node = node->left_child;
    }
    return node;
}


void Red_Black::remove_fixup(Node* x) {
    while (x != root && (x == nullptr || x->color == BLACK)) {
        if (x == (x ? x->parent->left_child : nullptr) ) {
            Node* w = x ? x->parent->right_child : nullptr;
            if (w && w->color == RED) {
                w->color = BLACK;
                if(x) x->parent->color = RED;
                if(x) rotate_left(x->parent);
                w = x ? x->parent->right_child : nullptr;
            }
            if (w && (w->left_child == nullptr || w->left_child->color == BLACK) &&
                (w->right_child == nullptr || w->right_child->color == BLACK)) {
                w->color = RED;
                x = x->parent;
            } else if(w) {
                if (w->right_child == nullptr || w->right_child->color == BLACK) {
                    if(w->left_child) w->left_child->color = BLACK;
                    w->color = RED;
                    rotate_right(w);
                    w = x->parent->right_child;
                }
                w->color = x->parent->color;
                x->parent->color = BLACK;
                if(w->right_child) w->right_child->color = BLACK;
                rotate_left(x->parent);
                x = root;
            } else {
                x = root;
            }
        } else {
            Node* w = x ? x->parent->left_child : nullptr;
            if (w && w->color == RED) {
                w->color = BLACK;
                if(x) x->parent->color = RED;
                if(x) rotate_right(x->parent);
                w = x ? x->parent->left_child : nullptr;
            }
            if (w && (w->right_child == nullptr || w->right_child->color == BLACK) &&
                (w->left_child == nullptr || w->left_child->color == BLACK)) {
                w->color = RED;
                x = x->parent;
            } else if (w) {
                if (w->left_child == nullptr || w->left_child->color == BLACK) {
                    if(w->right_child) w->right_child->color = BLACK;
                    w->color = RED;
                    rotate_left(w);
                    w = x->parent->left_child;
                }
                w->color = x->parent->color;
                x->parent->color = BLACK;
                if(w->left_child) w->left_child->color = BLACK;
                rotate_right(x->parent);
                x = root;
            } else {
                x = root;
            }
        }
    }
    if (x != nullptr) {
        x->color = BLACK;
    }
}

Node* Red_Black::remove_private(Node* node, User user) {
    Node* z = root;
    while(z != nullptr){
        if(z->user.userid == user.userid){
            break;
        }
        if(z->user.userid < user.userid){
            z = z->right_child;
        } else {
            z = z->left_child;
        }
    }
    if(z == nullptr){
        return root; // not found
    }

    Node* y = z;
    Node* x = nullptr;
    Color y_original_color = y->color;

    if (z->left_child == nullptr) {
        x = z->right_child;
        transplant(z, z->right_child);
    } else if (z->right_child == nullptr) {
        x = z->left_child;
        transplant(z, z->left_child);
    } else {
        y = find_min(z->right_child);
        y_original_color = y->color;
        x = y->right_child;
        if (y->parent == z) {
            if(x) x->parent = y;
        } else {
            transplant(y, y->right_child);
            y->right_child = z->right_child;
            y->right_child->parent = y;
        }
        transplant(z, y);
        y->left_child = z->left_child;
        y->left_child->parent = y;
        y->color = z->color;
    }
    delete z;
    if (y_original_color == BLACK) {
        remove_fixup(x);
    }
    return root;
}