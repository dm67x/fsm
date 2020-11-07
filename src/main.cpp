#include "fsm.hpp"
#include <cstdlib>
#include <iostream>

int main(int argc, char** argv)
{
    (void)argc;
    (void)argv;

    fsm::Alphabet<char> alphabet;
    fsm::new_alphabet(alphabet, 'a', 'b');

    fsm::FSM<char> fsm(alphabet);
    fsm::State s1 = fsm.new_state();
    fsm::State s2 = fsm.new_state(true);
    fsm::State s3 = fsm.new_state();

    try {
        fsm.new_link(s1, s2, 'a')
            ->new_link(s1, s3, 'b')
            ->new_link(s2, s3, 'a')
            ->new_link(s2, s2, 'b')
            ->new_link(s3, s3, 'a')
            ->new_link(s3, s3, 'b');

        std::cout << fsm << std::endl;
        fsm.to_dot("export.dot");
    } catch (std::exception& ex) {
        std::cout << ex.what() << std::endl;
    }

    return EXIT_SUCCESS;
}