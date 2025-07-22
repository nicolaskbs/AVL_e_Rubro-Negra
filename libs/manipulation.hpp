#pragma once

#include <string>
#include <vector>
#include "user.hpp"
#include "avl.hpp"
#include "red_black.hpp"

namespace Manipulation {
    void shuffle_users_vector(std::vector<User>& users);
    std::vector<User> get_users_from_json(std::string file);
    AVL get_avl_from_vector(const std::vector<User>& users);
    Red_Black get_red_black_from_vector(const std::vector<User>& users);
    void remove_primes_IDs(Tree& tree, const std::vector<User>& users);
}