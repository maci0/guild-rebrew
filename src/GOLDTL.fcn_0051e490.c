extern int g_6a23b8;
extern int g_6a23bc;
extern char g_6a23c0;
extern char g_6a23b0[];
extern int g_6a23ac;
extern char g_868060[];
extern char g_6a375c;
extern char g_7f4c00[];
extern unsigned short g_774970;
extern char g_773d75;
extern char g_7f4ca0[];
extern char g_773de8;
extern char g_7747b4[];
extern char g_7e2480[];
extern char g_7f3ac4[];
extern unsigned short g_7ea3c0[];
extern char* g_7746c4;
extern char* g_7746c8;
extern char* g_7746cc;

char* __cdecl m_alloc(int, char*);
void __cdecl m_FreeTracked(void*);
unsigned int __cdecl vfs_fwrite(void*, int, int, void*);
void __cdecl fcn_0041bb70(unsigned int, char*, char*, char*);
int __cdecl gm_WalkEntityChain(int);
int __cdecl fcn_0050b710(int, int);

/* ADDRESS: GOLDTL 0x0051e490 */
int __cdecl fcn_0051e490(void* a0, int a1)
{
	char hdr[0x18];
	char name[0x20];
	char zq[4];
	char b0;
	char b1;
	char b2;
	char b3;
	unsigned int v11;
	unsigned int v13;
	unsigned int v31;
	unsigned int v22;
	unsigned int tmp;
	char v14;
	char v15;
	char* buf;
	char* base;
	char* t;
	char* p;
	char* s;
	unsigned int r;
	int i;
	int j;
	int n;

	*(int*) hdr = g_6a23b8;
	*(int*) (hdr + 9) = 0;
	*(short*) (hdr + 0xd) = 0;
	*(int*) (hdr + 0xc) = g_6a23bc;
	hdr[0x10] = g_6a23c0;
	hdr[0x17] = 0;
	zq[0] = 0;
	zq[1] = 0;
	zq[2] = 0;
	zq[3] = 0;
	tmp = -1;
	i = 0;
	buf = m_alloc(0xe100, g_6a23b0);
	v11 = 0x1005a;
	g_6a23ac = 0x1005a;
	r = vfs_fwrite(&v11, 4, 1, a0);
	if (r == 0) {
		return 0;
	}
	r = vfs_fwrite(&a1, 1, 1, a0);
	if (r == 0) {
		return 0;
	}
	base = g_868060 + g_773d75 * 0x2f4;
	t = base;
	p = name;
	while ((*p++ = *t++) != 0) {
	}
	v13 = *(unsigned int*) (base + 0x40);
	v31 = *(unsigned int*) (base + 0x44);
	v14 = *(char*) (base + 0x48);
	v15 = g_6a375c;
	if (vfs_fwrite(name, 0x20, 1, a0) == 0) {
		return 0;
	}
	if (vfs_fwrite(&v13, 8, 1, a0) == 0) {
		return 0;
	}
	if (vfs_fwrite(&v14, 1, 1, a0) == 0) {
		return 0;
	}
	if (vfs_fwrite(&v15, 1, 1, a0) == 0) {
		return 0;
	}
	if (vfs_fwrite(g_7f4c00, 0xe, 1, a0) == 0) {
		return 0;
	}
	if (g_774970 != 0xffff) {
		n = g_774970;
		p = g_7f4ca0 + n * 0x21c;
		if (vfs_fwrite(p + 0x30, 0x10, 1, a0) == 0) {
			return 0;
		}
		if (vfs_fwrite(p + 0x40, 0x10, 1, a0) == 0) {
			return 0;
		}
		if (vfs_fwrite(p + 0x0c, 1, 1, a0) == 0) {
			return 0;
		}
		if (vfs_fwrite(p + 0x54, 4, 1, a0) == 0) {
			return 0;
		}
		if (vfs_fwrite(p + 0x164, 1, 1, a0) == 0) {
			return 0;
		}
		if (vfs_fwrite(p + 0x166, 1, 1, a0) == 0) {
			return 0;
		}
		if (vfs_fwrite(p + 0x0d, 1, 1, a0) == 0) {
			return 0;
		}
		tmp = gm_WalkEntityChain(g_774970);
		tmp = fcn_0050b710((int) tmp, g_773d75);
		if (vfs_fwrite(&tmp, 4, 1, a0) == 0) {
			return 0;
		}
		s = p + 9;
	} else {
		/* uncertain: b0..b3 have no store in the native body */
		if (vfs_fwrite(hdr, 0x10, 1, a0) == 0) {
			return 0;
		}
		if (vfs_fwrite(&b1, 1, 1, a0) == 0) {
			return 0;
		}
		if (vfs_fwrite(&b3, 1, 1, a0) == 0) {
			return 0;
		}
		if (vfs_fwrite(&b0, 1, 1, a0) == 0) {
			return 0;
		}
		if (vfs_fwrite(zq, 4, 1, a0) == 0) {
			return 0;
		}
		s = &b2;
	}
	if (vfs_fwrite(s, 1, 1, a0) == 0) {
		return 0;
	}
	if (vfs_fwrite(&g_773de8, 1, 1, a0) == 0) {
		return 0;
	}
	v22 = -1;
	if (g_7746c4 != 0) {
		v22 = *(unsigned int*) (g_7746c4 + 1);
	} else if (g_7746c8 != 0) {
		v22 = *(unsigned int*) (g_7746c8 + 1);
	}
	vfs_fwrite(&v22, 4, 1, a0);
	if (g_7746cc != 0) {
		v22 = *(unsigned int*) (g_7746cc + 2);
	} else {
		v22 = -1;
	}
	vfs_fwrite(&v22, 4, 1, a0);
	for (n = 0; n < 8; n++) {
		vfs_fwrite(g_7f3ac4 + n * 8, 4, 1, a0);
	}
	tmp = 0x78;
	do {
		p = buf + i * 3 + 1;
		j = 0xa0;
		do {
			fcn_0041bb70((unsigned int) g_7ea3c0[i], p - 1, p, p + 1);
			i = i + 1;
			p = p + 3;
			j = j - 1;
		} while (j != 0);
		tmp = tmp - 1;
	} while (tmp != 0);
	r = vfs_fwrite(buf, 0xe100, 1, a0);
	if (r == 0) {
		return 0;
	}
	if (buf != 0) {
		m_FreeTracked(buf);
	}
	vfs_fwrite(g_7747b4, 4, 1, a0);
	vfs_fwrite(g_7e2480, 0x60, 1, a0);
	return 1;
}
