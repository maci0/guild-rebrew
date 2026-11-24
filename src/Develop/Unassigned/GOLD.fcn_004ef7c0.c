extern char* g_entity_type_table;
int __cdecl gv_CheckSlotActive(void*, int);
int __cdecl fcn_004f13d0(unsigned char*);

/* ADDRESS: GOLD 0x004ef7c0 */
void* __cdecl fcn_004ef7c0(void* a0, void* a1, void* a2, int (__cdecl* predicate)(void*, void*), int kind)
{
	unsigned char* type;
	char* group;
	unsigned char* end;

	type = (unsigned char*) ((g_entity_type_table + *(unsigned char*) a1) + *(unsigned char*) a1 * 588);
	group = *(char**) ((char*) a1 + 0x65);
	if (kind != 0xff && !gv_CheckSlotActive(group, kind))
		return 0;
	if (kind == 0) {
		end = (unsigned char*) *(int*) (group + 8) + ((int*) 0x5ee084)[type[0x247]] * 20;
	} else if (kind == 1) {
		end = (unsigned char*) *(int*) (group + 0xc) + ((int*) 0x5ee094)[type[0x247]] * 20;
	} else if (kind == 2) {
		end = (unsigned char*) *(int*) (group + 0x10) + ((int*) 0x5ee0a4)[type[0x247]] * 20;
	} else if (kind == 3) {
		end = (unsigned char*) *(int*) (group + 0x14) + ((int*) 0x5ee0b4)[type[0x247]] * 20;
	} else if (kind == 0xff) {
		end = (unsigned char*) *(int*) (group + 0x1c) + fcn_004f13d0((unsigned char*) a1) * 20;
	} else {
		return 0;
	}
	if (!a2) {
		if (kind == 0) {
			a2 = *(void**) (group + 8);
		} else if (kind == 1) {
			a2 = *(void**) (group + 0xc);
		} else if (kind == 2) {
			a2 = *(void**) (group + 0x10);
		} else if (kind == 3) {
			a2 = *(void**) (group + 0x14);
		} else {
			a2 = *(void**) (group + 0x1c);
		}
	} else {
		a2 = (char*) a2 + 0x14;
	}
	while ((unsigned char*) a2 < end) {
		if (!predicate)
			return a2;
		if (predicate(a0, a2))
			return a2;
		a2 = (char*) a2 + 0x14;
	}
	return 0;
}
