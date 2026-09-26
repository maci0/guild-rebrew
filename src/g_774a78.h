#ifndef G_774A78_H
#define G_774A78_H

/* GOLDTL 0x774a78: head of a singly linked list of these. */
typedef struct Node {
	int id;
	int f4;
	char pad8[0xc - 0x8];
	char recs[7][8];
	float scale;
	struct Node* next;
} Node;
// SIZE 0x4c

#endif
