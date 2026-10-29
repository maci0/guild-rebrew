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
void __cdecl fcn_004ff0f0(unsigned int unused)
{
	Slot4ff0f0* p;
	char* q;
	int v;
	int id;

	(void) unused;
	*(int*) 0x773d48 = 0;
	p = (Slot4ff0f0*) 0x7f4ca2;
	do {
		if (*(int*) 0x773d48 > 0x40) {
			fcn_00535960();
			*(int*) 0x773d48 = 0;
		}
		if (p->kind == 0x12) {
			v = 8;
			id = p->id;
			fcn_004c4510((char*) p - 2, id);
			fcn_004c4570(1, 1, 2, (char*) &v);
			fcn_004c5360();
			++*(int*) 0x773d48;
		}
		p++;
	} while ((int) p < 0x85a0a2);
	q = (char*) 0x7f4ca2;
	do {
		if (*(int*) 0x773d48 > 0x40) {
			fcn_00535960();
			*(int*) 0x773d48 = 0;
		}
		if ((((Slot4ff0f0*) q)->kind < 10 || ((Slot4ff0f0*) q)->kind == 0x14)
		    && ((Slot4ff0f0*) q)->active != 0) {
			fcn_004fe5f0(q - 2);
			v = ((Slot4ff0f0*) q)->value;
			if ((float) v == ((Slot4ff0f0*) q)->pos - *(float*) 0x6628a0
			    && ((Slot4ff0f0*) q)->flag != 0) {
				if (((Slot4ff0f0*) q)->b7 != 0) {
					fcn_004c6150(((Slot4ff0f0*) q)->id, (char*) 0x696508);
				}
				else {
					fcn_004c6150(((Slot4ff0f0*) q)->id, (char*) 0x696514);
				}
				++*(int*) 0x773d48;
			}
		}
		q += 0x21c;
	} while ((int) q < 0x85a0a2);
	fcn_004ff8f0();
	*(int*) 0x773d48 = 0;
}
