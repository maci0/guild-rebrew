int __cdecl gm_GetEntityType(void*);

/* ADDRESS: GOLDTL 0x00502a20 */
int* __cdecl fcn_00502a20(void)
{
	char* p;
	char* q;
	int limit;
	int save;
	int next;
	char b;
	char arr;
	char hit;
	int v;

	hit = 0;
	if (!*(int*) 0x99ec10) {
		return 0;
	}
	p = (char*) *(int*) 0x773da4;
	if (!p) {
		return 0;
	}
	limit = *(int*) 0x773d8c;
	b = *(char*) 0x773d99;
	if (*(char*) 0x773d90) {
		*(char*) 0x773d90 = 0;
		if (b && *(int*) (p + 0x14)) {
			save = *(int*) 0x868058;
			*(int*) (save * 4 + 0x8f9500) = *(int*) (p + 0x14);
			save++;
			*(int*) 0x868058 = save;
		}
		else {
			save = *(int*) 0x868058;
		}
		if (*(unsigned short*) p) {
			*(int*) 0x773d94 = 1;
		}
		goto match;
	}
	arr = *(char*) 0x773d98;
	if (arr) {
		p += 0x43;
		*(int*) 0x773da4 = (int) p;
		if (*(unsigned short*) p) {
			(*(int*) 0x773d94)++;
		}
		if (*(int*) 0x773d94 >= limit) {
			return 0;
		}
		while (*(unsigned short*) p == 0) {
			p += 0x43;
			*(int*) 0x773da4 = (int) p;
		}
	}
	if (*(int*) 0x773d94 >= limit) {
		return 0;
	}
	if (!arr) {
		p = (char*) *(int*) (p + 0x3f);
		*(int*) 0x773da4 = (int) p;
		if (!p) {
			if (!b) {
				return 0;
			}
			save = *(int*) 0x868058;
			if (!save) {
				return 0;
			}
			p = (char*) *(int*) (save * 4 + 0x8f94fc);
			save--;
			*(int*) 0x868058 = save;
			*(int*) 0x773da4 = (int) p;
			if (*(int*) (p + 0x14)) {
				*(int*) (save * 4 + 0x8f9500) = *(int*) (p + 0x14);
				save++;
				*(int*) 0x868058 = save;
			}
			goto match;
		}
		if (b && *(int*) (p + 0x14)) {
			save = *(int*) 0x868058;
			*(int*) (save * 4 + 0x8f9500) = *(int*) (p + 0x14);
			save++;
			*(int*) 0x868058 = save;
			goto match;
		}
	}
	save = *(int*) 0x868058;
match:
	if (*(int*) 0x773d94 >= limit) {
		return 0;
	}
	do {
		if (*(char*) 0x773d9a) {
			hit = 1;
		}
		next = save;
		if (*(int*) 0x69938c != 0x7fff) {
			if ((int) *(unsigned short*) p != *(int*) 0x69938c) {
				goto fail;
			}
			hit = 1;
		}
		if (*(int*) 0x699390 != -1) {
			if (*(int*) (p + 2) != *(int*) 0x699390) {
				goto fail;
			}
			hit = 1;
		}
		if (*(unsigned short*) 0x699394 != 0xffff) {
			v = gm_GetEntityType(p);
			limit = *(int*) 0x773d8c;
			save = *(int*) 0x868058;
			b = *(char*) 0x773d99;
			if ((unsigned short) v != *(unsigned short*) 0x699394) {
				p = (char*) *(int*) 0x773da4;
				goto fail;
			}
			hit = 1;
		}
		if (*(char*) 0x699396 != -1) {
			if (*(char*) (*(int*) 0x99ec10 + *(unsigned short*) p * 0x41) != *(char*) 0x699396) {
				goto fail;
			}
			hit = 1;
			goto found;
		}
		if (!hit) {
			goto fail;
		}
found:
		q = p;
		goto nextcheck;
fail:
		hit = 0;
		arr = *(char*) 0x773d98;
		if (arr) {
			p += 0x43;
			*(int*) 0x773da4 = (int) p;
			if (*(unsigned short*) p) {
				(*(int*) 0x773d94)++;
			}
			if (*(int*) 0x773d94 >= limit) {
				goto nextcheck;
			}
			while (*(unsigned short*) p == 0) {
				p += 0x43;
				*(int*) 0x773da4 = (int) p;
			}
			goto nextcheck;
		}
		p = (char*) *(int*) (p + 0x3f);
		*(int*) 0x773da4 = (int) p;
		if (!p) {
			goto unlink;
		}
		if (b && *(int*) (p + 0x14)) {
			*(int*) (save * 4 + 0x8f9500) = *(int*) (p + 0x14);
			save++;
			*(int*) 0x868058 = save;
		}
nextcheck:
		if (p) {
			goto decide;
		}
unlink:
		if (!b) {
			return 0;
		}
		if (!save) {
			return 0;
		}
		p = (char*) *(int*) (save * 4 + 0x8f94fc);
		save--;
		*(int*) 0x868058 = save;
		*(int*) 0x773da4 = (int) p;
		if (*(int*) (p + 0x14)) {
			*(int*) (save * 4 + 0x8f9500) = *(int*) (p + 0x14);
			save++;
			*(int*) 0x868058 = save;
		}
decide:
		if (hit) {
			return (int*) p;
		}
		if (*(int*) 0x773d94 > limit) {
			*(int*) 0x773da4 = 0;
			return 0;
		}
		if ((unsigned int) p < (unsigned int) (*(int*) 0x868054 + 0x14f218)) {
			continue;
		}
		*(int*) 0x773da4 = 0;
		return 0;
	} while (1);
}
