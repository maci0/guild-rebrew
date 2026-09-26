#ifndef OCTREE_H
#define OCTREE_H

/* Colour quantiser: g_6b6f20[level] points to that level's nodes
 * (8^level of them), g_6b6f40 is a heap of node references ordered by key,
 * and the palette it builds is g_6b6008[3][0x100] (r, g, b planes). */
typedef struct {
	unsigned int r;
	unsigned int g;
	unsigned int b;
	unsigned int count;
	unsigned int key;
	unsigned char mask;
	unsigned char idx;
	char pad[2];
} OctNode;
// SIZE 0x18

typedef struct {
	unsigned char lvl;
	char pad;
	unsigned short idx;
} OctRef;
// SIZE 0x4

#endif
