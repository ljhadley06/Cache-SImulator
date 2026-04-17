# Cache Simulator (CS3339 - Spring 2026)

## Overview
This project implements a **set-associative cache simulator** in C++. The simulator models how a CPU cache processes memory references and determines whether each access results in a **cache hit or miss**.

The program takes cache configuration parameters and a list of memory addresses as input, then outputs the result of each memory access according to the specified cache behavior.

---

## Objectives
- Simulate a configurable cache system
- Understand **set-associative caching**
- Implement **tag matching and indexing**
- Practice file I/O and command-line arguments in C++

---

## Features
- Supports arbitrary cache sizes (`num_entries`)
- Supports configurable associativity (`associativity`)
- Implements:
  - Valid bits
  - Tag extraction
  - Set indexing
- FIFO (round-robin) replacement policy
- Outputs results in required format

---

## Cache Design

The cache is modeled as:
- A collection of **sets**
- Each set contains multiple **lines (blocks)**




