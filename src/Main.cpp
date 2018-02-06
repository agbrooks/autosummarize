#include <cmath>
#include <iostream>
#include <fstream>
#include <sstream>
#include <argp.h>
#include <unistd.h>

#include "TextRank.hpp"

#include "config.h"

class ProgramOptions
{
public:
        ProgramOptions(int argc, char **argv);

        bool          verbose;
        double        compression;
        double        pct_keywords;
        double        dee;
        double        tolerance;
        unsigned long max_iter;
        char          *textfile;

        void validate() const
        {
                if (compression <= 0.0 || compression > 1.0)
                {
                        cerr << "Compression should be between 0.0 and 1.0.";
                        exit(1);
                }
                if (pct_keywords <= 0.0 || pct_keywords > 1.0)
                {
                        cerr << "Pct. keywords should be between 0.0 and 1.0.";
                        exit(1);
                }
                if (dee <= 0.0 || dee >= 1.0)
                {
                        cerr << "d should be between 0.0 and 1.0.";
                        exit(1);
                }
                if (tolerance < 0)
                {
                        cerr << "WARNING: Tolerance is less than 0.0!\n";
                        cerr << "This means we'll never appear to converge.";
                }
        }

private:
        static constexpr bool         default_verbose      = false;
        static constexpr double       default_compression  = 0.35;
        static constexpr double       default_pct_keywords = 1.0;
        static constexpr double       default_dee          = 0.85;
        static constexpr double       default_tolerance    = 1e-10;
        static constexpr unsigned int default_max_iter     = 2000;
        static constexpr char         *default_textfile    = NULL;

        static error_t parse_opt(int key, char *arg, struct argp_state *state)
        {
                ProgramOptions *opts = static_cast<ProgramOptions *>(state->input);
                istringstream argstream;

                switch(key) {
                case 'v':
                        opts->verbose = true;
                        break;
                case 'c':
                        argstream.str(arg);
                        if (!(argstream >> opts->compression))
                        {
                                argp_usage(state);
                        }
                        break;
                case 'k':
                        argstream.str(arg);
                        if (!(argstream >> opts->pct_keywords))
                        {
                                argp_usage(state);
                        }
                        break;
                case 'd':
                        argstream.str(arg);
                        if (!(argstream >> opts->dee))
                        {
                                argp_usage(state);
                        }
                        break;
                case 't':
                        argstream.str(arg);
                        if (!(argstream >> opts->tolerance))
                        {
                                argp_usage(state);
                        }
                        break;
                case 'i':
                        argstream.str(arg);
                        if (!(argstream >> opts->max_iter))
                        {
                                argp_usage(state);
                        }
                        break;
                case ARGP_KEY_ARG:
                        opts->textfile = arg;
                        break;
                case ARGP_KEY_END:
                        opts->validate();
                        break;
                default:
                        return ARGP_ERR_UNKNOWN;
                }
                return 0;
        }

};

ProgramOptions::ProgramOptions(int argc, char **argv)
        : verbose(default_verbose),
          compression(default_compression),
          pct_keywords(default_pct_keywords),
          dee(default_dee),
          tolerance(default_tolerance),
          max_iter(default_max_iter),
          textfile(default_textfile)
{
        /*
         * XXX: We can't put these with the other static constexprs
         * in the class since doing so results in a linker error.
         * C++17 changes this behavior, but we're waiting until then.
         */
        static constexpr struct argp_option options[] = {
                {"compression", 'c', "percent (as float)", 0,
                 "percentage of sentences to retain, defaults to 0.35", 0},
                {"keywords", 'k', 0, 0,
                 "percentage of words to retain as sentence keywords, defaults to 1.0", 0},
                {"d", 'd', "float", 0,
                 "'d' parameter for TextRank, defaults to 0.85", 0},
                {"tolerance", 't', "float", 0,
                 "mean error after which we consider the scoring phase converged, defaults to 1e-10", 0},
                {"maxit", 'i', "int", 0,
                 "maximum number of scoring iterations to run, defaults to 2000", 0},
                // Use one empty struct to mark the end of the options.
                {}
        };

        static constexpr struct argp argp = {
                options,
                &parse_opt,
                "[FILENAME] (or stdin if unspecified)",
                "a TextRank-based automatic summarizer",
                0,
                0,
                0
        };

        if (argp_parse(&argp, argc, argv, 0, 0, this) != 0)
        {
                cerr << "Couldn't read command line arguments!\n";
                exit(1);
        }
}

const std::string
load_text(char *textfile)
{
        ifstream file_stream;
        stringstream buf;

        /* If no textfile specified, just read from stdin. */
        if (textfile == nullptr)
        {
                buf << cin.rdbuf();
        } else {
                file_stream.open(textfile);
                buf << file_stream.rdbuf();
        }

        return buf.str();
}

int
main(int argc, char **argv)
{
        /* Parse and validate program options. Quit if necessary. */
        const ProgramOptions opts(argc, argv);

        /* Read file or stdin, as indicated by the options. */
        const string text = load_text(opts.textfile);

        /* Construct sentences. */
        const vector<Sentence> sentences = Sentence::to_sentences(text);

        /* Rank all sentences. */
        const TextRank text_rank(sentences,
                           opts.pct_keywords,
                           opts.dee,
                           opts.max_iter,
                           opts.tolerance);

        /* Print the top n sentences to stdout. */
        const int how_many = std::ceil(sentences.size() * opts.compression);
        vector<unsigned int> ordering = text_rank.order;
        ordering.resize(how_many);
        for (unsigned int index : ordering)
        {
                cout << sentences[index].text;
        }
}
