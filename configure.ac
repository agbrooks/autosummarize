#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.69])
AC_INIT([autosummarize], [0.0.1], [andrewgrantbrooks@gmail.com])
AC_CONFIG_SRCDIR([src/Sentence.cpp])
AC_CONFIG_HEADERS([config.h])

AM_INIT_AUTOMAKE([subdir-objects foreign -Wall -Wextra -Wpedantic])

AC_CONFIG_FILES([Makefile])

# Checks for programs.
AC_PROG_CXX
AC_PROG_CC

# Checks for libraries.

# Checks for header files.
AC_CHECK_HEADER_STDBOOL

# Checks for typedefs, structures, and compiler characteristics.
AX_CHECK_COMPILE_FLAG([-std=c++14])
AX_CHECK_COMPILE_FLAG([-fopenmp])

# Checks for library functions.
AC_CHECK_FUNCS([floor])

AC_OUTPUT
