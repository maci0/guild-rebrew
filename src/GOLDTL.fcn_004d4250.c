extern char* g_67a370;
extern float g_664330;

char* __cdecl fcn_004ce610(char*);
unsigned short* __cdecl fcn_004ce680(char*);
char __cdecl fcn_0045b990(char*, float*, int*, int*, float*);
unsigned char* __cdecl fcn_004d2f70(char*);
int __cdecl fcn_004d3330(char*, int, int, int, unsigned int*, unsigned int*);
int __cdecl fcn_004d1020(char*, char*, char*, int, int);
char* __cdecl fcn_004d3600(char*);
int __cdecl fcn_004d13d0(char*, char*, char*);
char* __cdecl fcn_004d36e0(char*);
int __cdecl fcn_004d1320(char*, char*, char*);
void __cdecl fcn_004d1570(char*, char*);
int __cdecl fcn_004d14b0(char*, char*);
char* __cdecl fcn_004d34f0(char*);
int __cdecl fcn_004d1250(char*, char*, char*);

/* ADDRESS: GOLDTL 0x004d4250 */
void __cdecl fcn_004d4250(char* rec, char* e)
{
	char* ent;
	char* obj;
	char* map;
	unsigned int v5;
	float f4;

	if (!e || !*(char**) (e + 0x184) || (*(char*) (e + 8) && *(int*) (*(char**) (*(char**) (e + 0x184) + 0x34) + 0x218) != 1)) {
		switch (*(char*) (e + 0x1c4)) {
		case 0:
			obj = fcn_004ce610(e);
			if (*(int*) (obj + 0x58) == 1 || *(int*) (obj + 0x58) == 2) {
				if (*(int*) ((char*) fcn_004ce680(e) + 0x20) <= 0) {
					break;
				}
			}
			if (*(int*) (obj + 0x58) != 2) {
				obj = (char*) fcn_004d2f70(e);
				if (obj != 0) {
					fcn_004d1020(rec, e, obj, 0, 0);
					return;
				}
			} else {
				map = *(char**) (g_67a370 + 0xb0);
				ent = *(char**) (e + 0x184);
				if (fcn_0045b990(map, (float*) (*(char**) (ent + 0x34) + 0x4c), (int*) &v5, (int*) &e, &f4)) {
					obj = (char*) fcn_004d3330(e, v5, (int) e, (int) (g_664330 / *(float*) (map + 0x10)), &v5, (unsigned int*) &e);
					if (obj != 0) {
						fcn_004d1020(rec, e, 0, v5, (int) e);
						return;
					}
				}
			}
			break;
		case 1:
			obj = fcn_004d3600(e);
			if (obj != 0) {
				fcn_004d13d0(rec, e, obj);
				return;
			}
			break;
		case 2:
			obj = fcn_004d36e0(e);
			if (obj != 0) {
				fcn_004d1320(rec, e, obj);
				return;
			}
			break;
		case 3:
			fcn_004d1570(rec, e);
			break;
		case 4:
			fcn_004d14b0(rec, e);
			return;
		case 5:
			obj = fcn_004d34f0(e);
			if (obj != 0) {
				fcn_004d1250(rec, e, obj);
				return;
			}
			break;
		}
	}
}
