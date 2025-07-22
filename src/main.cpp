#include "../libs/all_libs.hpp"
using json = nlohmann::json;

void shuffle_users_vector(std::vector<User> &users){
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(users.begin(), users.end(), g);
}

int main(){

    std::vector<User> users_vector = get_users_from_json("users.json");
    shuffle_users_vector(users_vector);

    AVL users_avl = get_avl_from_vector(users_vector);
    Red_Black users_red_black = get_red_black_from_vector(users_vector);

    users_avl.printTree();
    users_red_black.printTree();

    remove_primes_IDs(users_avl);
    remove_primes_IDs(users_red_black);

    users_avl.printTree();
    users_red_black.printTree();

    return 0;
}