

// SIZE 0x21c
struct house {
	unsigned short id;
	unsigned char type;
	char pad3;
	int handle;
	char pad8[0x214];
};

#pragma pack(2)
// SIZE 0xe
struct pos14 {
	int a;
	int b;
	int c;
	short d;
};
#pragma pack()

extern struct pos14 g_7f4c00;
extern struct house g_7f4ca0[];
#include "client_packet_builder.h"
extern char g_6b5c60[];

char* __cdecl fcn_00508e40(int id);
int __cdecl fcn_00500cb0(struct pos14*, struct pos14*);
char* __cdecl gm_StartFilteredEntitySearch(int, int, int);
int __cdecl fcn_0050c710(char*, int, int);
int __cdecl fcn_0050c830(struct pos14*, struct pos14*, char*);

void __cdecl fcn_004c4670(int, int, short, unsigned char*);
void __cdecl fcn_004c5360(void);
void __cdecl fcn_00500bb0(struct pos14*, int, int, int);
char* __cdecl fcn_0050dc90(char*);
char* __cdecl fcn_00502cd0(int, int, int, int);
char* __cdecl gm_SetupEntityQuery(char*);
void __cdecl fcn_0051af00(char*, int, ...);
void __cdecl he_MessageBoxQuickjump(int, int, char*, int, int, int, int, char*, char*);
void __cdecl fcn_00529160(char*, int, int, int);
void __cdecl fcn_00546190(char*);

void __cdecl fcn_0057a3d0(char* e)
{
	char* who;
	char* q;
	char* r;
	char* s;
	unsigned char* p;
	unsigned char add;
	float skill;
	double months;
	int n;
	char buf[0x200];

	switch (*(int*) (e + 0x70)) {
	case 0:
		who = fcn_00508e40(*(int*) (e + 0xac));
		if (who != 0 && (unsigned char) who[*(int*) (e + 0xb0) + 0x80] < 252.0f
		    && fcn_00500cb0(&g_7f4c00, (struct pos14*) (e + 0xb8)) < 0) {
			q = gm_StartFilteredEntitySearch(1, 1, *(int*) (e + 0x10));
			if (q == 0) {
				break;
			}
			skill = (float) fcn_0050c710(q, 0xc, 1);
			n = fcn_0050c830((struct pos14*) (e + 0x60), &g_7f4c00, q);
			months = n * (1.0 / 30.0);
			add = (unsigned char) ((months * 8.0) * (skill * 0.01 + 1.0));
			p = (unsigned char*) &who[*(int*) (e + 0xb0) + 0x80];
			add = (unsigned char) (add / (*p * (1.0f / 252.0f) + 1.0));
			if (add + *p > 252.0f) {
				add = (unsigned char) (252.0f - *p);
			}
			fcn_004c4510(who, *(int*) (who + 4));
			fcn_004c4670(1, 1, (short) (who - g_aed32c + *(int*) (e + 0xb0) + 0x80), &add);
			fcn_004c5360();
			*(struct pos14*) (e + 0x52) = g_7f4c00;
			*(struct pos14*) (e + 0x60) = g_7f4c00;
			fcn_00500bb0((struct pos14*) (e + 0x52), 0, 0x1e, 0);
			return;
		}
		who = fcn_00508e40(*(int*) (e + 0xac));
		q = gm_StartFilteredEntitySearch(1, 1, *(int*) (e + 0x10));
		if (q == 0 || who == 0) {
			break;
		}
		r = fcn_0050dc90(q);
		if (r == 0 || !(r[0x1b4] & 1)) {
			s = fcn_00502cd0(*(int*) (q + 0x5d), 1, 1, *(int*) (e + 0xb4));
			if (s == 0) {
				s = gm_SetupEntityQuery(q);
			}
			if (s != 0) {
				fcn_0051af00(buf, 0x1bc8, *(unsigned short*) who, q);
				he_MessageBoxQuickjump(g_7f4ca0[*(unsigned short*) (e + 8)].handle, *(int*) (e + 0x10), buf, 0, 0x5f2,
				    *(int*) (q + 1), *(int*) (s + 2), g_6b5c60, "_NACHRICHTEN_HS_81");
			}
		}
		fcn_00529160(q, 0, *(unsigned short*) who, 0);
		fcn_00546190(e);
		return;
	case -2:
	case -1:
		break;
	default:
		return;
	}
	fcn_00546190(e);
}
