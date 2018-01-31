#include <cppunit/TestCase.h>
#include <cppunit/ui/text/TextTestRunner.h>

#include "SentenceTest.hpp"

int
main(int argc, char **argv)
{
        (void) argc;
        (void) argv;

        /* Text runner */
        CppUnit::TextTestRunner runner;

        /* Test cases */
        SentenceTestCase sentence_test;
        runner.addTest(&sentence_test);

        /* Run tests */
        runner.run();
        return 0;
}
