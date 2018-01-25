#include <algorithm>
#include <ctype.h>
#include <iostream>
#include <regex>
#include <sstream>
#include <string>
#include <vector>

#include "Sentence.hpp"

Sentence::Sentence(const string &text)
        : text(text)
{
        extract_words(text);
}

void
Sentence::extract_words(const string &text)
{
        string s;
        istringstream wordstream(text);
        while (wordstream >> s)
        {
                words.push_back(normalize_word(s));
        }
}

const string
Sentence::normalize_word(string &str)
{
        string normalized = str;

        // Downcase the string.
        for (char &c : normalized)
        {
                c = tolower(c);
        }

        // Remove any posessives or punctuation.
        const regex cleanup("('s)|([[:punct:]]+)|([[:space:]]+)");
        return regex_replace(normalized, cleanup, "");
}
