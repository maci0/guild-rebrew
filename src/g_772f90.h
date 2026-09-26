#ifndef G_772F90_H
#define G_772F90_H

/* GOLDTL 0x772fdc points to a shuffled deck of these; a g_772f90 slot holds
 * one drawn entry. */
typedef struct {
	char b;
	char c;
	char d;
	char e;
	char k;
	char pad5[3];
	int f;
} Draw772;
// SIZE 0xc

/* GOLDTL 0x772f90: 3 slots, saved and loaded field by field. */
typedef struct {
	int active;
	Draw772 v;
	int y;
	int x;
} Slot772f90;
// SIZE 0x18

/* GOLDTL 0x772fe4 points to g_772fe0 of these. */
typedef struct {
	int key;
	int a;
	int b;
} Rec772fe4;
// SIZE 0xc

#endif
