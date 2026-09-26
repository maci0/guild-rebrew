#ifndef HE_TABLES_H
#define HE_TABLES_H

/* GOLDTL tables cleared together by fcn_00545430:
 * g_7d2020 Deal[256], g_7dcae0 ApEvent[256], g_7dc6e0 Rec7dc6e0[64]. */

#pragma pack(2)
typedef struct {
	int a;
	int b;
	int c;
	short d;
} Pos14;
// SIZE 0xe
#pragma pack()

typedef struct {
	int id;
	char state;
	char pad5[3];
	int has_amount;
	int owner;
	int amount;
	Pos14 pos;
	char name[0x80];
} Deal;
// SIZE 0xa4

/* Registered by he_RegisterApEvent (fcn_00546ef0). */
typedef struct {
	char b0;
	char pad[3];
	int f4;
	int f8;
	int fc;
	char name[0x40];
} ApEvent;
// SIZE 0x50

typedef struct {
	int a;
	char* b;
	int c;
	int d;
} Rec7dc6e0;
// SIZE 0x10

#endif
