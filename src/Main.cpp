#include <iostream>

#include "Sentence.hpp"

using namespace std;

void
print_strings(vector<string> &strings)
{
        for (const string &s : strings)
        {
                cout << s << " ";
        }
        cout << "\n";
}


int
main(int argc, char **argv)
{
        (void) argc;
        (void) argv;
        const string test1 = "Well, hello there, world!";
        const string test2 = "How about another sentence?";
        Sentence sent1(test1);
        Sentence sent2(test2);
        print_strings(sent1.words);
        print_strings(sent2.words);
        cout << test1;
        cout << test2;
}
