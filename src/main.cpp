#include "parser.hpp"
#include "export.hpp"
#include <cstdlib>
#include <iostream>

int main(int argc, char** argv)
{
    (void)argc;
    (void)argv;

    Alphabet<char> alphabet;
    new_alphabet(alphabet, 'a', 'b');

    FSM<char> fsm(alphabet);
    State s1 = fsm.new_state();
    State s2 = fsm.new_state(true);
    State s3 = fsm.new_state();

    try {
        fsm.new_link(s1, s2, 'a')
            ->new_link(s1, s3, 'b')
            ->new_link(s2, s3, 'a')
            ->new_link(s2, s2, 'b')
            ->new_link(s3, s3, 'a')
            ->new_link(s3, s3, 'b');

        fsm_export::to_ppm(fsm, "exported");
    } catch (std::exception& ex) {
        std::cout << ex.what() << std::endl;
    }

    return EXIT_SUCCESS;
}