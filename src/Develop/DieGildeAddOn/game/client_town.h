#ifndef CLIENT_TOWN_H
#define CLIENT_TOWN_H

/* Existing inferred layout names retained for both client users. */
typedef struct {
	int x0;
	char p4[0xc];
	unsigned short w;
	char p12[6];
	float f;
	char p1c[0x14];
	float f30;
	float f34;
	char p38[0x18];
	struct {
		unsigned char kind;
		char pad[3];
		float v;
	} ent[4];
	char p70[0x10];
} Cell502450;
/* Native cell stride 0x80. */

typedef struct {
	Cell502450 c[85];
	char tail[0x10];
} Row502450;
/* Native row stride 0x2a90; complete array extent and owner unknown. */

extern Row502450 g_85ab80[];

#endif
