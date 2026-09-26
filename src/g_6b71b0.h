#ifndef G_6B71B0_H
#define G_6B71B0_H

/* GOLDTL 0x6b71b0: 10 named channels. */
typedef struct {
	char name[0x100];
	int handle;
	unsigned char active;
	unsigned char b105;
	unsigned char b106;
	unsigned char b107;
	int f108;
	int f10c;
	char pad110[0x128 - 0x110];
} Chan;
// SIZE 0x128

#endif
