#pragma once

#include <string>
#include <vector>
#include <algorithm>
#include <random>

#include "user.hpp"
#include "avl.hpp"

namespace Manipulation {

    std::vector<User> get_users_from_json(std::string);

    void shuffle_users_vector(std::vector<User> &);

    AVL get_avl_from_vector(std::vector<User> &);

    Red_Black get_red_black_from_vector(std::vector<User> &);

    void remove_primes_IDs(AVL &);

    void remove_primes_IDs(Red_Black &);
}