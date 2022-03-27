============================================
Fast fuzzy search on 100 million DNA dataset
============================================

This repository contains the full source code for the benchmark testing
done in the article
`"Fast fuzzy search on 100 million DNA dataset" <https://www.ceptord.net/20220515-dna100m.html>`_.

How to run the benchmark test
=============================

.. important::

   This benchmark creates a 2GB text file that contains 100 million
   DNA sequences. Make sure that you have a enough disk space before
   running it!

You need `gcc` and `parallel` to run the benchmark test.

On Debian/Ubuntu, here is how to run the test::

   $ sudo apt install parallel build-essential
   $ make

This runs the 4 benchmark tests in the following order:

====== ==================================================
Test    Algorithm
====== ==================================================
bench0  The Wagner-Fischer algorithm
bench1  Myers' algorithm
bench2  Myers' algorithm + Reusing bit vectors
bench3  Myers' algorithm + Reusing bit vectors + Parallel
====== ==================================================
