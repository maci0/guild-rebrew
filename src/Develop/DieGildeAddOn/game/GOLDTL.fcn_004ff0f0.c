#include "client_data.h"
extern int g_773d48;
#pragma pack(2)
typedef struct {
	unsigned char kind;
	char pad1[1];
	int id;
	unsigned char active;
	unsigned char b7;
	unsigned short value;
	char pad10[0x1e - 0xa];
	float pos;
	char pad22[0x182 - 0x22];
	int flag;
	char pad186[0x21c - 0x186];
} Slot4ff0f0;
#pragma pack()

void __cdecl fcn_00535960(void);
void __cdecl fcn_004c4510(char* base, int entity_id);
int __cdecl fcn_004c4570(unsigned char size, unsigned char count, unsigned short off, char* src);
void __cdecl fcn_004c5360(void);
float __cdecl fcn_004fe5f0(void*);
void __cdecl fcn_004c6150(int a1, char* a2);
void __cdecl fcn_004ff8f0(void);

/* ADDRESS: GOLDTL 0x004ff0f0 */
void __cdecl fcn_004ff0f0(void)
{
	Slot4ff0f0* p;

	int v;
	int id;


	g_773d48 = 0;
	p = (Slot4ff0f0*) g_7f4ca2;
	do {
		if (g_773d48 > 0x40) {
			fcn_00535960();
			g_773d48 = 0;
		}
		if (p->kind == 0x12) {
			id = p->id;
			v = 8;
			fcn_004c4510((char*) p - 2, id);
			fcn_004c4570(1, 1, 2, (char*) &v);
			fcn_004c5360();
			++g_773d48;
		}
		p++;
	} while ((int) p < (int) &g_7f4ca2[768]);
	p = (Slot4ff0f0*) g_7f4ca2;
	do {
		if (g_773d48 > 0x40) {
			fcn_00535960();
			g_773d48 = 0;
		}
		if ((p->kind < 10 || p->kind == 0x14)
		    && p->active != 0) {
			fcn_004fe5f0((char*) p - 2);
			v = p->value;
			if ((float) v == p->pos - 1.0f
			    && p->flag != 0) {
				if (p->b7 == 0) {
					fcn_004c6150(p->id, (char*) 0x696514);
				}
				else {
					fcn_004c6150(p->id, (char*) 0x696508);
				}
				++g_773d48;
			}
		}
		p++;
	} while ((int) p < (int) &g_7f4ca2[768]);
	fcn_004ff8f0();
	g_773d48 = 0;
}
