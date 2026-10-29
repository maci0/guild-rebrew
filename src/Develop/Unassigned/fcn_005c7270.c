extern unsigned char* lpGebaeudePROT;

/* ADDRESS: GOLDTL 0x005c7270 */
int __cdecl fcn_005c7270(void* o, int type)
{
	unsigned char* p;
	signed char* e;
	int idx;

	if (!(o == 0)) {
    p = *(unsigned char**)((char*)o + 0x16c);
	if (p == 0) {
		goto fail;
	}
	idx = *p;
	e = lpGebaeudePROT + idx * 589;
	if (type == 0x172 || type == 0x174) {
		if (*e != 4) {
			goto fail;
		}
	}
	if (type == 0x158 || type == 0x160) {
		if (*e != 0x13) {
			goto fail;
		}
	}
	if (type == 0x16e || type == 0x176) {
		if (*e != 0x10) {
			goto fail;
		}
	}
	return 1;

fail:
	return 0;
} else {
		goto fail;
	}
}