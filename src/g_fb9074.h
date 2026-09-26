#ifndef G_FB9074_H
#define G_FB9074_H

/* GOLD 0xfb9074 points to g_fb9084 texture slots; refs > 0 marks one in use. */
typedef struct TexSlot {
	char name[0x40];
	int refs;
	char pad[0x3c];
} TexSlot;
// SIZE 0x80

#endif
