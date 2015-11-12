#ifndef TEST
#define TEST

#include "MemMgr.h"

extern int debug;
extern int blocks_written, blocks_read;

/* TESTING I/O */
void test_io();
void test_bigfile();
void test_structure();

#endif
