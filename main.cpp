#include "test/TestTransformable.hpp"
#include <iostream>

using std::cout;
using std::cerr;
using std::endl;

/// @brief Main where all exceptions are caught
/// @details Better to never use abort(), but instead throwing errors to ensure cleanup of SDL.
void safe_main()
{
    SDL::init();
    SDL::init_image();

    TestTransformable().run();
}

int main(int argc, char* argv[])
{
    // Lazyfoo says with SDL, main should have argc and argv arguments to be cross-plateform:
    // https://lazyfoo.net/tutorials/SDL/01_hello_SDL/index2.php

    try
    {
        safe_main();
    }
    catch(const std::exception& e)
    {
        cerr << "Fatal error:" << endl;
        cerr << e.what() << endl;
    }
    catch(...)
    {
        cerr << "Fatal unkown error, aborting." << endl;
    }

    return 0;
}
