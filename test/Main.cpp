#include <cppunit/CompilerOutputter.h>
#include <cppunit/TestCase.h>
#include <cppunit/ui/text/TextTestRunner.h>

#include "SentenceTest.hpp"

int
main(int argc, char **argv)
{
        (void) argc;
        (void) argv;

        SentenceTestCase *sentence_test = new SentenceTestCase();

        /* Get top level suite from the registry */
        CppUnit::Test *suite = CppUnit::TestFactoryRegistry::getRegistry().makeTest();

        /* Setup a text test runner and add relevant tests */
        CppUnit::TextTestRunner runner;
        runner.addTest(suite);
        runner.addTest(sentence_test);

        runner.setOutputter( new CppUnit::CompilerOutputter( &runner.result(), std::cerr ));

        /* Run tests - give a non-zero exit code if unsuccessful! */
        return runner.run() ? 0 : 1;
}
