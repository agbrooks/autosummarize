#include <algorithm>
#include <ctype.h>
#include <iostream>
#include <regex>
#include <sstream>
#include <string>
#include <vector>

#include "Sentence.hpp"

/**
 * Construct a sentence from the text in that sentence, including trailing
 * punctuation.
 *
 * `text` must be non-NULL.
 */
Sentence::Sentence(const string &text)
        : text(text)
{
        extract_words();
}

/**
 * From a string representing the text of several sentences, produce several
 * Sentences.
 *
 * text is assumed non-NULL.
 */
const vector<Sentence>
Sentence::to_sentences(const string &text)
{
        const std::regex eof_sentence("[.!\?]");
        std::vector<Sentence> sentences;

        /*
         * Split on regex for end of sentence, and generate sentence strings.
         * We use separate iterators for the sentence and the terminator
         * associated with each sentence so that we can extract both.
         */

        std::sregex_token_iterator sentence_iter(
                text.begin(),
                text.end(),
                eof_sentence,
                -1);
        std::sregex_token_iterator terminator_iter(
                text.begin(),
                text.end(),
                eof_sentence,
                0);
        std::sregex_token_iterator end;

        /* Add all sentences. */
        while (sentence_iter != end)
        {
                string sentence_text = *sentence_iter;
                if (sentence_text.length() > 0)
                {
                        string sentence_terminator;
                        if (terminator_iter != end)
                        {
                                sentence_terminator = *terminator_iter;
                        } else {
                                sentence_terminator = "";
                        }
                        sentences.push_back(
                                Sentence(sentence_text + sentence_terminator)
                                );
                }
                sentence_iter++;
                if (terminator_iter != end)
                {
                        terminator_iter++;
                }
        }

        return sentences;
}

/**
 * Initialize the Sentence's 'words' vector from its text.
 */
void
Sentence::extract_words()
{
        string s;
        istringstream wordstream(text);
        while (wordstream >> s)
        {
                words.push_back(normalize_word(s));
        }
}

/**
 * 'Normalize' a word in a sentence.
 * This entails converting it to lowercase, then removing all punctuation
 * and whitespace.
 *
 * The word in question is assumed non-NULL.
 */
const string
Sentence::normalize_word(const string &str)
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
