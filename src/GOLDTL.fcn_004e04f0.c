char* __cdecl fcn_00508e40(int id);
float __cdecl fcn_00507f10(char* entity, int idx);
int __cdecl srv_GetEntityOfficeSlot(unsigned char* entity, void* role_out, void* slot_out);
int __cdecl fcn_004e8240(unsigned char id, unsigned char* ea, unsigned char* eb, int x1, int x2);
void __cdecl fcn_0051af00(void* out, int id, ...);
int __cdecl fcn_00545d40(int id, int arg, char* text1, unsigned char flags, int value, char* text2);

void __cdecl fcn_004e04f0(char* a0)
{
	char* v2;
	char* v3;
	char* p;
	int v4[6];
	int v5[6];
	char buf[0x400];

	v2 = fcn_00508e40(*(int*) (a0 + 0x34));
	v3 = fcn_00508e40(*(int*) (a0 + 0x38));
	if (v2 != 0 && v3 != 0) {
		if (!(fcn_00507f10(v2, 3) > fcn_00507f10(v3, 3)))
			v3 = v2;
		if (*(unsigned char*) (v3 + 0x166) != 0) {
			if (srv_GetEntityOfficeSlot((unsigned char*) v3, v5, v4) != 0) {
				if (*(int*) (a0 + 0xc) == *(int*) (0x7f4ca4 + *(unsigned short*) 0x774970 * 0x21c)) {
					fcn_004e8240(*(unsigned char*) v4, 0, 0, 4, 0xff);
					p = (char*) 0x7f4ca2;
					do {
						if (*p == 6 || *p == 7) {
							fcn_0051af00(buf, 0x10c7, *(unsigned short*) v3, (*(unsigned char*) (v3 + 9) != 0) + 0x10c8);
							fcn_00545d40(*(int*) (p + 2), -1, buf, 0, 0x5fe, (char*) 0x6b5c60);
						}
						p += 0x21c;
					} while ((int) p < 0x85a0a2);
				}
			}
		}
	}
}
