#ifndef G_68E020_H
#define G_68E020_H

/* GOLDTL 0x68e020: 32 entries keyed by a FourCC; state 0xff marks one the
 * savegame did not mention. */
typedef struct {
	int key;
	char name[0xf2 - 4];
	unsigned char state;
	char padf3;
} Entry68e020;
// SIZE 0xf4

#endif
