#include "../libs/all_libs.hpp"

int main() {
    // Ler o arquivo JSON e carregar em um vetor de structs
    std::vector<User> users_vector = Manipulation::get_users_from_json("data/users.json");

    // Embaralhar o vetor
    Manipulation::shuffle_users_vector(users_vector);

    // Inserir todos os usuários nas árvores
    std::cout << "Criando e populando a Árvore AVL..." << std::endl;
    AVL users_avl = Manipulation::get_avl_from_vector(users_vector);
    
    std::cout << "Criando e populando a Árvore Rubro-Negra..." << std::endl;
    Red_Black users_red_black = Manipulation::get_red_black_from_vector(users_vector);

    std::cout << "\n--- Árvore AVL Após Inserção ---" << std::endl;
    users_avl.printTree();

    std::cout << "\n--- Árvore Rubro-Negra Após Inserção ---" << std::endl;
    users_red_black.printTree();

    // Remover usuários com userid primo
    std::cout << "\nRemovendo usuários com UserID primo da Árvore AVL..." << std::endl;
    Manipulation::remove_primes_IDs(users_avl, users_vector);

    std::cout << "Removendo usuários com UserID primo da Árvore Rubro-Negra..." << std::endl;
    Manipulation::remove_primes_IDs(users_red_black, users_vector);

    std::cout << "\n--- Árvore AVL Após Remoção dos Primos ---" << std::endl;
    users_avl.printTree();

    std::cout << "\n--- Árvore Rubro-Negra Após Remoção dos Primos ---" << std::endl;
    users_red_black.printTree();

    return 0;
}