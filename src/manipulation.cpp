#include "../libs/all_libs.hpp"
#include <cmath> // Para sqrt

using json = nlohmann::json;

void Manipulation::shuffle_users_vector(std::vector<User>& users) {
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(users.begin(), users.end(), g);
}

std::vector<User> Manipulation::get_users_from_json(std::string file) {
    std::vector<User> users;
    std::ifstream input(file);
    if (!input.is_open()) {
        std::cerr << "Erro ao abrir o arquivo JSON: " << file << std::endl;
        return users;
    }
    json users_json_file;
    input >> users_json_file;

    for (auto& element : users_json_file) {
        users.emplace_back(
            element["login"].get<std::string>(),
            element["userid"].get<int>(),
            element["region"].get<int>(),
            element["password"].get<std::string>()
        );
    }
    return users;
}

AVL Manipulation::get_avl_from_vector(const std::vector<User>& users) {
    AVL avl_tree;
    for (const auto& user : users) {
        avl_tree.insert(user);
    }
    return avl_tree;
}

Red_Black Manipulation::get_red_black_from_vector(const std::vector<User>& users) {
    Red_Black rb_tree;
    for (const auto& user : users) {
        rb_tree.insert(user);
    }
    return rb_tree;
}

// Função para verificar se um número é primo
bool is_prime(int n) {
    if (n <= 1) return false;
    for (int i = 2; i * i <= n; ++i) {
        if (n % i == 0) return false;
    }
    return true;
}

void Manipulation::remove_primes_IDs(Tree& tree, const std::vector<User>& users) {
    std::vector<User> users_to_remove;
    for(const auto& user : users){
        if(is_prime(user.userid)){
            users_to_remove.push_back(user);
        }
    }

    for (const auto& user : users_to_remove) {
        tree.remove(user);
    }
}