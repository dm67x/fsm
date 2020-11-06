#include "parser.hpp"
#include <cstdlib>
#include <iostream>

int main(int argc, char** argv)
{
    (void)argc;
    (void)argv;

    FSM<char> fsm;
    State s1 = fsm.new_state();
    State s2 = fsm.new_state(true);
    State s3 = fsm.new_state();

    fsm.new_link(s1, s2, 'a')
        ->new_link(s1, s3, 'b')
        ->new_link(s2, s3, 'a')
        ->new_link(s2, s2, 'b')
        ->new_link(s3, s3, 'a')
        ->new_link(s3, s3, 'b');

    std::cout << fsm << std::endl;

    return EXIT_SUCCESS;
}