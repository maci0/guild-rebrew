extern unsigned char* g_868050;
extern char* g_99ec10;

// FUNCTION: GOLDTL 0x510820

int sprintf(char*, const char*, ...);
void __cdecl fcn_00442d50(char*, int);
void __cdecl fcn_005105a0(char*);
void __cdecl fcn_005107f0(void);

void __cdecl fcn_00510820(char* obj, unsigned char* ent, int kind)
{
	unsigned char* t;
	void** p;

	switch (kind) {
	case 2:
		t = g_868050 + *ent * 0x24d;
		sprintf(obj, "gb_%s", t + 1);
		*(char**) (ent + 0x61) = obj;
		if (*t != 10) {
			*(int*) (obj + 0x220) = 3;
			if (*(int*) (obj + 0x218) == 1 && (ent[0x5a] & 1) == 0) {
				fcn_00442d50(obj, 1);
			}
		} else {
			*(int*) (obj + 0x220) = 0;
			*(int*) (obj + 0x224) = 0;
		}
		break;
	case 1:
		sprintf(obj, "ob_%s", g_99ec10 + *(unsigned short*) ent * 0x41 + 1);
		*(int*) (obj + 0x220) = 4;
		break;
	}
	fcn_005105a0(obj);
	*(unsigned char**) (obj + 0x204) = ent;
	p = *(void***) (obj + 0x1ec);
	if (p != 0) {
		*p = (void*) fcn_005107f0;
	}
}
