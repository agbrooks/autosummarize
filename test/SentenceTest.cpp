#include "Sentence.hpp"
#include "SentenceTest.hpp"

/**
 * A string with no words creates a sentence with no words.
 */
void
SentenceTestCase::test_trivial_strings()
{
        Sentence s1 = Sentence(empty);
        Sentence s2 = Sentence(space);
        Sentence s3 = Sentence(fancyspace);

        CPPUNIT_ASSERT(s1.words.size() == 0);
        CPPUNIT_ASSERT(s2.words.size() == 0);
        CPPUNIT_ASSERT(s3.words.size() == 0);
}

/**
 * A string with a few, normalized words creates a sentence with those words.
 */
void
SentenceTestCase::test_simple_strings()
{
        Sentence s = Sentence(simple);
        CPPUNIT_ASSERT(s.text == simple);
        CPPUNIT_ASSERT(s.words == hello_unit_testing);
}


/**
 * A string with words that require normalization creates a sentence with
 * normalized words.
 */
void
SentenceTestCase::test_complex_strings()
{
        Sentence s1 = Sentence(caps);
        Sentence s2 = Sentence(complex);
        CPPUNIT_ASSERT(s1.words == hello_unit_testing);
        CPPUNIT_ASSERT(s2.words == hello_unit_testing);
}

void SentenceTestCase::setUp() {}
void SentenceTestCase::tearDown() {}


