#include <string.h>

#include <cppunit/TestCase.h>
#include <cppunit/extensions/HelperMacros.h>

class SentenceTestCase : public CppUnit::TestCase
{
        CPPUNIT_TEST_SUITE(SentenceTestCase);

        CPPUNIT_TEST(test_trivial_strings);
        CPPUNIT_TEST(test_simple_strings);
        CPPUNIT_TEST(test_complex_strings);

        CPPUNIT_TEST_SUITE_END();

public:
        void setUp();
        void tearDown();

protected:
        void test_trivial_strings();
        void test_simple_strings();
        void test_complex_strings();

private:
        /* Test fixtures */
        std::string empty      = "";
        std::string space      = "    ";
        std::string fancyspace = " \t\n  \n";
        std::string simple     = "hello unit testing";
        std::string caps       = "HeLLo uNIT tEsTINg";
        std::string complex    = "Hello, UNIT\nTESTING!";

        std::vector<std::string> hello_unit_testing = {"hello", "unit", "testing"};
};
