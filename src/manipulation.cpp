#include "../libs/all_libs.hpp"
using json = nlohmann::json;

std::vector<User> Manipulation::get_users_from_json(std::string file){
    std::vector<User> users;

    std::ifstream input(file);
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