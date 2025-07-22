#include "../libs/all_libs.hpp"

void Tree::printTree_private(Node* root_of_subtree,
                     const std::string& prefix = "",
                     bool is_left = true){

    if (root_of_subtree == nullptr) {
        return;
    }

    if (root_of_subtree->right_child) {
        printTree_private(root_of_subtree->right_child, 
                  prefix + (is_left ? "│   " : "    "), 
                  false);
    }

    std::cout << prefix 
              << (is_left ? "└── " : "┌── ") 
              << root_of_subtree->user.userid
              << std::endl;

    if (root_of_subtree->left_child) {
        printTree_private(root_of_subtree->left_child,
                  prefix + (is_left ? "    " : "│   "),
                  true);
    }
}

void Tree::printTree(){
    printTree_private(pointer_to_root, "", true);
}

void Tree::insert(User user){
    if(this->pointer_to_root == nullptr){
        this->pointer_to_root = new Node(user, nullptr);
    } else{
        insert_non_empty(user, this->pointer_to_root, nullptr);
    }
}

void Tree::insert_non_empty(User user,
                            Node* current_node, 
                            Node* parent){
    bool is_left_side;
    if(user.userid <= current_node->user.userid ){
        parent = current_node;
        current_node = current_node->left_child;
        is_left_side = true;
    } else if(user.userid  > current_node->user.userid ){
        parent = current_node;
        current_node = current_node->right_child;
        is_left_side = false;
    }
    if(current_node == nullptr){
        current_node = new Node(user, parent);
        if(is_left_side){
            parent->left_child = current_node;
        } else{
            parent->right_child = current_node;
        }
        return;
    }
    insert_non_empty(user, current_node, parent);
}

void Tree::remove(User user){
    recursive_remove(user, this->pointer_to_root);
}

void Tree::recursive_remove(User user, Node* current_node){
    if(current_node == nullptr){
        return;
    }
    if(current_node->user.userid < user.userid){
        recursive_remove(user, current_node->right_child);
    } else if(current_node->user.userid > user.userid){
        recursive_remove(user, current_node->left_child);
    } else {
        if(current_node->left_child == nullptr 
            && current_node->right_child == nullptr){
            if(current_node->parent == nullptr){
            } else if(current_node->parent->left_child == current_node){
                current_node->parent->right_child = nullptr;
            } else {
                current_node->parent->right_child = nullptr;
            }
            delete current_node;
            //this->quantidade_nodes--;
        } else {
            Node* folha = find_leaf(user, current_node);
            current_node->user = folha->user;
            recursive_remove(folha->user, folha);
        }
    }
}

Node* Tree::find_leaf(User user, Node* current_node){
    if(current_node->left_child != nullptr){
        current_node = current_node->left_child;
        while(current_node->right_child){
            current_node = current_node->right_child;
        }
    } else {
        current_node = current_node->right_child;
        while(current_node->left_child){
            current_node = current_node->left_child;
        }
    }
    return current_node;
}