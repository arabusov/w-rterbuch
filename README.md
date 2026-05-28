# Flash cards

[![fcc CI](https://github.com/arabusov/w-rterbuch/actions/workflows/c-cpp.yml/badge.svg)](https://github.com/arabusov/w-rterbuch/actions/workflows/c-cpp.yml)
[![Coverage
Status](https://coveralls.io/repos/github/arabusov/w-rterbuch/badge.svg)](https://coveralls.io/github/arabusov/w-rterbuch)

## Binaries:

  - `fcadd DICT WORD1 WORD2`: adds (WORD1, WORD2) to DICT file
  - `fcc DICT`: command-line interface to the test facility
  - `fctui DICT`: TUI interface to the test facility
  - `fc2anki DICT`: converts `.dict` format to an Anki-compatible forman

## Data format:

The DICT file is a simple text file. Each record posesses one line.
There are four space-separated fields per one record. In one record
words are limited with 31 8-bit characters.

## Features:

  - `fcadd` checks for existing words (only first column)
