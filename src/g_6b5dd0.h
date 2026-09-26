#ifndef G_6B5DD0_H
#define G_6B5DD0_H

/* GOLDTL 0x6b5dd0 points to g_6b5de8 of these display adapter records. */
typedef struct {
	char pad0[0x418];
	unsigned long guid[4];
	char pad428[0x504 - 0x428];
	void* data;
} Adapter;
// SIZE 0x508

#endif
