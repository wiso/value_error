==========
ValueError
==========

This is a very simple library to handle value with errors, for example 3.1 +/- 1.2 and the common operation between them.

All the code is inspired by <complex> number library from the c++ standard library.

How to use
==========
This library is header-only, so just include it. You can specialize the template ValueErrorTemplate, or you can use the already defined typedef ValueErrorTemplate<double> ValueError;

Run tests
---------
In the directory test there are some unit test. To compile it, just use make command. You need gtest (http://code.google.com/p/googletest/). Fedora has its rpm package.