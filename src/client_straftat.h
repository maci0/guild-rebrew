#ifndef CLIENT_STRAFTAT_H
#define CLIENT_STRAFTAT_H

#pragma pack(push, 1)
typedef struct {
	int id;
	char name[14];
	int unk_12;
	int target_id;
	short count;
	unsigned char kind;
	int unk_1d;
	int unk_21;
	unsigned int state;
	char unk_29[4];
} STRAFTAT_RECORD;
#pragma pack(pop)
/* SIZE 0x2d */

extern STRAFTAT_RECORD g_9a3800[512];

#endif
