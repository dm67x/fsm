#include "parser.hpp"
#include <cstdlib>
#include <iostream>

int main(int argc, char** argv)
{
    (void)argc;
    (void)argv;

    FST<char> fst;
    State s1 = fst.new_state();
    State s2 = fst.new_state(true);
    State s3 = fst.new_state();

    fst.new_link(s1, s2, 'a');
    fst.new_link(s1, s3, 'b');
    fst.new_link(s2, s3, 'a');
    fst.new_link(s2, s2, 'b');
    fst.new_link(s3, s3, 'a');
    fst.new_link(s3, s3, 'b');

    std::cout << fst << std::endl;

    return EXIT_SUCCESS;
}