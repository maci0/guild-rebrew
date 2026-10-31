extern float g_662914;
extern float g_662c98;
extern unsigned char g_773d75;
extern char g_7f4ca0[];

int __cdecl gm_ResolveEntityById(char**, int, int, int);
char* __cdecl gm_LookupEntityRecordById(int);
int __cdecl fcn_00510500(int);
int __cdecl gm_RandomMod(int);
float __cdecl fcn_0050f980(unsigned int, unsigned int, unsigned int);
int __cdecl io_FormatTextBuffer(char*, int, int, int, int);
int __cdecl fcn_00545d40(int, int, char*, int, int, char*);
int __cdecl fcn_004c51a0(int, int, int, int);

/* ADDRESS: GOLDTL 0x0057c9f0 */
void __cdecl fcn_0057c9f0(char* a0)
{
	char buf[512];
	int handle;
	int bonus;
	float radius;
	unsigned int level;
	int base;
	int kind;
	int count;
	int found;
	unsigned short* ent;
	char* p;

	found = 0;
	gm_ResolveEntityById(&handle, 0, 0, *(int*) (a0 + 0x10));
	if (handle == 0) {
		return;
	}
	ent = (unsigned short*) gm_LookupEntityRecordById(*(int*) (a0 + 0xc));
	if (ent == 0) {
		return;
	}
	kind = fcn_00510500(handle);
	if (kind == 3) {
		level = *(int*) (a0 + 0xac);
		base = 0;
		bonus = 0;
		if (level < 4) {
			base = 0x14;
			bonus = -0xf;
		}
		else if (level < 7) {
			base = 0xa;
			bonus = -5;
		}
		bonus += 0x19;
		radius = (float) base + g_662c98;
		count = (gm_RandomMod(0x18) & 0xffff) + 0xf;
	}
	else if (kind == 2) {
		level = *(int*) (a0 + 0xac);
		base = 0;
		bonus = 0;
		if (level < 4) {
			base = 0xa;
			bonus = -5;
		}
		bonus += 0xf;
		radius = (float) base + g_662914;
		count = (gm_RandomMod(0x10) & 0xffff) + 0xc;
	}
	else {
		radius = 70.0f;
		bonus = 0xa;
		count = (gm_RandomMod(8) & 0xffff) + 0xa;
	}
	count <<= 5;
	for (p = g_7f4ca0; p < g_7f4ca0 + 0x65400; p += 0x21c) {
		if (*(unsigned short*) p != 0xffff && p != (char*) ent
			&& *(unsigned char*) (p + 2) < 0xa) {
			if (radius < fcn_0050f980(*ent, *(unsigned short*) p, 1)) {
				found++;
			}
		}
	}
	bonus += found;
	found = bonus * count;
	io_FormatTextBuffer(buf, 0x41fa, handle, bonus, found);
	fcn_00545d40(*(int*) (ent + 2), -1, buf + 0x14, 1, 0x5fa, 0);
	fcn_004c51a0(*(int*) (ent + 2), -1, g_773d75, found);
}
