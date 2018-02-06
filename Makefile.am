AM_CPPFLAGS = -std=c++14 -I$(top_srcdir)/src -Wall -Wextra -Wpedantic

program_cxx_source = \
	src/KeywordExtractor.cpp \
	src/Sentence.cpp \
	src/Sparsetence.cpp \
	src/SparsetenceFactory.cpp \
	src/TextRank.cpp

bin_PROGRAMS = autosummarize

autosummarize_SOURCES = \
	$(program_cxx_source) \
	src/Main.cpp

check_PROGRAMS = unit_tests

unit_tests_SOURCES = \
	test/Main.cpp \
	test/SentenceTest.cpp \
	$(program_cxx_source)

unit_tests_CFLAGS = -fPIC
unit_tests_CXXFLAGS = $(unit_tests_CFLAGS)
unit_tests_LDFLAGS = -lcppunit

TESTS = $(check_PROGRAMS)
