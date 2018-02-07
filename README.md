# Autosummarize

## What is this?

It's a fast, TextRank-based autosummarizer!

The original TextRank algorithm is described by [Rada Mihalcea and Paul Tarau, "TextRank: Bringing Order into Texts"](https://web.eecs.umich.edu/~mihalcea/papers/mihalcea.emnlp04.pdf).

This program differs from the algorithm they describe in that it uses frequency-based keyword extraction for performing the sentence ranking step. Only words identified as keywords are used when computing inter-sentence similarity.

In general, you probably want to select a high percentage of words as "keywords" (the default is 100%). However, if you find the algorithm is running too slowly or would just like to experiment, you may want to decrease this percentage.

Note that certain words which do not impart very much 'meaning' to the text (eg, articles) will be unconditionally ignored when computing similarity.

## Building

Make sure that you have a fairly recent version of `gcc` and that your `libc` supports the `argp` API (it probably does if you're running Linux).

Compiling is straightforward and uses the familiar GNU Autotools build system.

1. `autoreconf --install`

2. `./configure`

3. `make`

(and, optionally, `make install`)

## Usage

Refer to the built-in help (`autosummarize --help`).

## Running tests

After building as usual, issue a `make check`.

Currently, unit test coverage is pretty low (I'm working on it ;) ).

## Caveats

* Autosummarize has no unicode support.

* Autosummarize is currently designed with English texts in mind.
