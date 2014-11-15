simpleipc
=========

Simple interprocess communication for C++ programs in POSIX
environments (POSIX only for now).

## Goals

This library is meant to be a small and safe library for asynchronous
communication between programs written in C++11. The primary
communication methods are message passing via file descriptors, or
shared memory (via mmap).

The message passing paradigm is safe and runs on a separate
thread. Reading messages occur in delegates, and it is up to the user
to ensure that the messages are consumed quickly enough and interact
with other running threads in a safe manner.

If more speed is necessary, shared memory is a faster approach but
requires additional mechanisms from the user to ensure algorithm
correctness.
