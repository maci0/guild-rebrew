#ifndef HE_ACTION_H
#define HE_ACTION_H

/* Native action stride is 0x14c. */
typedef struct HE_ACTION {
	unsigned char kind;
	char unk_01[3];
	int serial;
	unsigned short house;
	char unk_0a[2];
	int owner;
	int unk_10;
	int unk_14[12];
	char position[0x0e];
	char unk_52[0x0e];
	char unk_60[0x0e];
	char unk_6e[2];
	int unk_70;
	void* slot;
	unsigned char flags;
	char unk_79[3];
	void* data;
	int data_size;
	int unk_84;
	int unk_88;
	int unk_8c[8];
	char unk_ac[0xa0];
} HE_ACTION;

extern HE_ACTION he_ActionSlots[1024];

#endif
