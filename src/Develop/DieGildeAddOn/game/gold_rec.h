#ifndef GOLD_REC_H
#define GOLD_REC_H

/* GOLD spawn/list bookkeeping tables.  GOLD_rec is a 24-byte-stride pool
 * with 42 entries; GOLD_limit is a global word threshold.  Field names come
 * from the functions that use them. */

typedef struct {
	char pad00[4];
	int f04;
	char pad08[0x166 - 0x08];
	unsigned char b166;
	char pad167;
	unsigned char b168;
	unsigned char b169;
} GOLDUser;

typedef struct {
	int id;
	int f04;
	int f08;
	unsigned char flag;
	char pad0d[3];
	int val;
	int pad14;
} GOLDRec;

extern GOLDRec GOLD_rec[42];
extern unsigned short GOLD_limit;

#endif
