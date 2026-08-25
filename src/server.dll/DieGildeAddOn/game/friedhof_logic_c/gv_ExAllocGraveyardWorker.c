/* gv_ExAllocGraveyardWorker - allocates a graveyard worker entity of type
 * 0x1b/0x1c: validates the request against the resolved entity, finds a free
 * grave slot (or reuses one marked 0xf), initializes it from the matched
 * production entry, and returns the new grave id (0xffff on failure). */

// CFLAGS: /O2 /Gd
// FUNCTION: SERVER 0x10011bf0
// SYMBOL: _gv_ExAllocGraveyardWorker

extern char* dword_100a8c30;
extern int g_1003546c;
extern int g_10035434;
extern int g_10030b6c;
extern int dword_1002574c[];
extern unsigned char byte_100a9820[];
extern unsigned char byte_1014d8e0[];
extern int __cdecl gm_ResolveEntityById(void** dynamic, void** existing, void** static_ptr, int entity_id);
extern int __cdecl gv_CheckSlotActive(void* worker, int worktype);
extern void* __cdecl GetSlotEntry(void* worker, int worktype, unsigned char job);
extern int __cdecl ahm_RandomBelow(int n);
extern float __cdecl gm_RandomFloat01(void);
extern void __cdecl LogMessageInternal(char* module, unsigned int line, char* msg, int severity);
extern void* __cdecl memset(void* dest, int c, unsigned int size);
extern char* __cdecl strcpy(char* dest, const char* src);

int __cdecl gv_ExAllocGraveyardWorker(void* req)
{
	void* entry;
	int i;
	void* entity;
	void* slot;
	void* workers;
	void* p;
	unsigned short* gp;
	unsigned char* gcp;
	char* grave;
	int chosen;
	int count;
	int job_id;
	int j;
	unsigned char field_id;

	if (*(int*) ((char*) req + 0x15) != 0x1b && *(int*) ((char*) req + 0x15) != 0x1c)
		return -6;
	gm_ResolveEntityById(&entity, 0, 0, *(int*) ((char*) req + 8));
	if (!entity ||
	    *(unsigned short*) ((char*) entity + 0x27) == 0xffff ||
	    (char*) 0x100358a0 + *(unsigned short*) ((char*) entity + 0x27) * 0x21c == (char*) g_1003546c)
		return -1;
	field_id = *(unsigned char*) entity;
	if (dword_100a8c30[field_id + field_id * 588] != 0x1d)
		return -2;
	workers = *(void**) ((char*) entity + 0x65);
	if (!workers)
		return -3;
	if (!gv_CheckSlotActive(workers, *(int*) ((char*) req + 0xc)))
		return -4;
	slot = GetSlotEntry(workers, *(int*) ((char*) req + 0xc), *(unsigned char*) ((char*) req + 0x10));
	if (!slot)
		return 0xffff;
	j = 0;
	count = dword_1002574c[*(int*) ((char*) req + 0xc)];
	if (count <= 0)
		goto fail_ffff;
	job_id = *(int*) ((char*) req + 0x11);
	p = *(void**) ((char*) slot + 0x10);
	for (; j < count; j++, p = (char*) p + 0x44) {
		entry = p;
		if (*(int*) p == job_id)
			break;
	}
	if (!entry || *(int*) entry != job_id)
		goto fail_ffff;
	for (gp = (unsigned short*) 0x100358a0, chosen = 0; gp < (unsigned short*) 0x1009aca0;
	     gp = (unsigned short*) ((char*) gp + 0x21c), chosen++) {
		if (*gp == 0xffff)
			break;
	}
	if (chosen == 0x300) {
		for (gcp = (unsigned char*) 0x100358a2, chosen = 0; gcp < (unsigned char*) 0x1009aca2;
		     gcp = (unsigned char*) gcp + 0x21c, chosen++) {
			if (*gcp == 0xf)
				break;
		}
		if (chosen == 0x300) {
			LogMessageInternal((char*) 0x1002d48c, 0x6ef, (char*) 0x1002d4bc, 1);
fail_ffff:
			return 0xffff;
		}
	}
	if (*(unsigned char*) ((char*) 0x100358a2 + chosen * 0x21c) == 0xf)
		g_10035434--;
	grave = (char*) 0x100358a0 + chosen * 0x21c;
	memset(grave, 0, 0x21c);
	*(unsigned short*) grave = 0xffff;
	*(int*) (grave + 4) = -1;
	memset(grave + 0x5c, -1, 32);
	*(int*) (grave + 0x170) = (int) entity;
	*(int*) (grave + 0x16c) = (int) entity;
	*(int*) (grave + 4) = g_10030b6c++;
	*(volatile unsigned short*) grave = (unsigned short) chosen;
	g_10035434++;
	*(unsigned char*) (grave + 2) = 0x14;
	*(int*) (grave + 0x1f0) = 0;
	*(int*) (grave + 0x210) = -1;
	*(unsigned char*) (grave + 0x215) = 0;
	*(unsigned char*) (grave + 0x216) = 0;
	*(unsigned char*) (grave + 0x217) = 0;
	*(unsigned char*) (grave + 0x218) = 1;
	*(float*) (grave + 0x1e4) = 1.0f;
	*(unsigned char*) (grave + 8) = 0x64;
	*(unsigned short*) (grave + 0xa) = 0x10;
	*(unsigned char*) (grave + 0x164) = 0;
	*(unsigned char*) (grave + 0x166) = 0;
	*(unsigned char*) (grave + 0x165) = *(unsigned char*) ((char*) req + 0x15);
	*(unsigned char*) (grave + 0x1f4) = 0;
	*(int*) (grave + 0x190) = 4;
	*(int*) (grave + 0x194) = 0;
	*(unsigned char*) (grave + 0xd) = 1;
	*(int*) (grave + 0x18c) = -1;
	*(int*) (grave + 0x20c) = -1;
	*(unsigned short*) (grave + 0x50) = 0x7fff;
	for (j = 0; j < 5; j++)
		*(unsigned char*) (grave + 0x80 + j) = *(unsigned char*) ((char*) entry + 0x24 + j) >> 1;
	*(unsigned char*) (grave + 9) = *(unsigned char*) ((char*) entry + 0x38);
	strcpy((char*) grave + 0x30, (char*) entry + 4);
	strcpy((char*) grave + 0x40, (char*) entry + 0x14);
	*(int*) (grave + 0x10) = 0;
	*(float*) (grave + 0x14) = 1000.0f / (gm_RandomFloat01() * 4.0f + 8.0f);
	*(int*) (grave + 0x18) = 0;
	*(float*) (grave + 0x1c) = 1000.0f;
	*(int*) (grave + 0x20) = 0;
	*(int*) (grave + 0x24) = 0;
	*(unsigned short*) (grave + 0x28) = 0;
	*(int*) (grave + 0x2c) = 0;
	for (i = 0; i < 0x300; i++) {
		byte_1014d8e0[i * 0x300 + *(unsigned short*) grave] = 0;
		byte_100a9820[i * 0x300 + *(unsigned short*) grave] = (unsigned char) ahm_RandomBelow(0x40) - 0x20;
		byte_100a9820[*(unsigned short*) grave * 0x300 + i] = (unsigned char) ahm_RandomBelow(0x40) - 0x20;
		byte_1014d8e0[*(unsigned short*) grave * 0x300 + i] = 0;
	}
	if (*(int*) entry == *(int*) ((char*) slot + 4)) {
		count = dword_1002574c[*(int*) ((char*) req + 0xc)];
		if (count > 0) {
			p = *(void**) ((char*) slot + 0x10);
			for (j = 0; j < count; j++, p = (char*) p + 0x44) {
				if (*(int*) p == -1)
					continue;
				if (*(int*) p != *(int*) entry) {
					*(int*) ((char*) slot + 4) = *(int*) p;
					goto clear_entry;
				}
			}
		}
		*(int*) ((char*) slot + 4) = -1;
		*(unsigned short*) ((char*) slot + 8) = 0xffff;
	}
clear_entry:
	memset(entry, 0, 0x44);
	*(int*) entry = -1;
	return *(unsigned short*) grave;
}
