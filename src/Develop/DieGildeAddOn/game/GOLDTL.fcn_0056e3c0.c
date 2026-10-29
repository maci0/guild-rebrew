extern char g_7f4c00[];
extern char g_7f4ca0[];
extern char g_68cb58[];
extern char g_6b5c60[];
extern int g_773da8;

char* __cdecl fcn_00508e40(int);
void __cdecl fcn_00500bb0(int*, int, int, int);
int __cdecl fcn_00426cc0(int);
void __cdecl fcn_00428720(int);
void __cdecl fcn_00529160(int, int, unsigned short, int);
void __cdecl fcn_0051af00(int*, unsigned int, ...);
void __cdecl he_MessageBoxQuickjump(unsigned int, int, char*, int, int, int, int, char*, char*);
void __cdecl fcn_00406120(int);
char* __cdecl fcn_0040c120(int, int, int);
char* __cdecl fcn_004934c0(char*);
void __cdecl fcn_005099e0(char*, char*);
void __cdecl fcn_004c4510(int, int);
void __cdecl fcn_004c4570(int, int, int, int*);
void __cdecl fcn_004c5360(void);
int __cdecl fcn_0050a710(char*);
void __cdecl fcn_004c57e0(int, int);
int __cdecl fcn_004c4450(int);
int* __cdecl fcn_004c4480(int);
int __cdecl fcn_004c5980(int);
int __cdecl fcn_004e6a30(int);
void __cdecl fcn_00546190(char*);

/* ADDRESS: GOLDTL 0x0056e3c0 */
void __cdecl fcn_0056e3c0(char* a0)
{
	char* s;
	char* obj;
	char* p;
	char c;
	int v;
	int i;
	unsigned int idx;
	char buf[0x514];

	if (*(int*) (a0 + 0x70) == -1) {
		goto tail;
	}
	s = fcn_00508e40(*(int*) (a0 + 0xac));
	if (s == 0) {
		goto tail;
	}
	if (*(int*) (s + 0x20c) != -1 && *(int*) (a0 + 0x70) != 6) {
		*(int*) (a0 + 0x52) = *(int*) g_7f4c00;
		*(int*) (a0 + 0x56) = *(int*) (g_7f4c00 + 4);
		*(int*) (a0 + 0x5a) = *(int*) (g_7f4c00 + 8);
		*(unsigned short*) (a0 + 0x5e) = *(unsigned short*) (g_7f4c00 + 0xc);
		fcn_00500bb0((int*) (a0 + 0x52), 0, 5, 0);
		return;
	}
	switch (*(int*) (a0 + 0x70)) {
	case -2:
	case -1:
		goto tail;
	case 0:
		obj = *(char**) (s + 0x184);
		if (obj == 0) {
			if ((*(unsigned char*) (a0 + 0x78) & 2) == 0) {
				goto tail;
			}
			*(int*) (a0 + 0x70) = 3;
			return;
		}
		if (*(int*) (obj + 0x28) != -1) {
			fcn_00428720(fcn_00426cc0(*(int*) (obj + 0x28)));
		}
		fcn_00529160(0, 0, *(unsigned short*) s, 0);
		if ((*(unsigned char*) (a0 + 0x78) & 2) != 0) {
			p = *(char**) (s + 0x16c);
			if (p != 0) {
				idx = *(unsigned short*) (p + 0x27);
				c = *(char*) (g_7f4ca0 + 2 + idx * 0x21c);
				if (c == 6 || c == 7) {
					fcn_0051af00((int*) (buf + 0x114), 0x42f4, *(unsigned short*) s, (int) p);
					v = *(int*) (p + 1);
					he_MessageBoxQuickjump(*(unsigned int*) (g_7f4ca0 + 4 + idx * 0x21c), v, buf + 0x120, 0, 0x60a, v, -1, g_6b5c60, g_6b5c60);
				}
			}
		}
		*(int*) (s + 0x16c) = 0;
		*(int*) (a0 + 0x70) = *(int*) (a0 + 0x70) + 1;
		return;
	case 1:
		obj = *(char**) (s + 0x184);
		if (obj != 0 && *(int*) (obj + 0x28) != -1) {
			return;
		}
		*(int*) (a0 + 0x70) = *(int*) (a0 + 0x70) + 1;
		return;
	case 2:
		obj = *(char**) (s + 0x184);
		if (obj != 0) {
			fcn_00406120((int) obj);
			p = fcn_0040c120((int) *(char**) (s + 0x184), 0x36, 1);
			if (p != 0) {
				memcpy(p + 0xf0, g_68cb58, 0x19);
			}
		}
		*(int*) (a0 + 0x52) = *(int*) g_7f4c00;
		*(int*) (a0 + 0x56) = *(int*) (g_7f4c00 + 4);
		*(int*) (a0 + 0x5a) = *(int*) (g_7f4c00 + 8);
		*(unsigned short*) (a0 + 0x5e) = *(unsigned short*) (g_7f4c00 + 0xc);
		fcn_00500bb0((int*) (a0 + 0x52), 0, 0x1e, 0);
		*(int*) (a0 + 0x70) = *(int*) (a0 + 0x70) + 1;
		if ((*(unsigned char*) (a0 + 0x78) & 4) != 0) {
			goto tail;
		}
		return;
	case 3:
		c = *(char*) (s + 2);
		if (c != 6 && c != 7) {
			fcn_00500bb0((int*) (a0 + 0x52), 0, 2, 0);
			*(int*) (a0 + 0x70) = 4;
			return;
		}
		for (i = 0; i < 0x45; i++) {
			*(int*) (buf + i * 4) = 0;
		}
		*(char*) (buf + 0x08) = 8;
		*(int*) (buf + 0x18) = *(int*) g_7f4c00;
		*(int*) (buf + 0x1c) = *(int*) (g_7f4c00 + 4);
		*(int*) (buf + 0x20) = *(int*) (g_7f4c00 + 8);
		*(unsigned short*) (buf + 0x24) = *(unsigned short*) (g_7f4c00 + 0xc);
		*(char*) (buf + 0x26) = 0xa0;
		fcn_00500bb0((int*) (buf + 0x18), 0, 0x1e, 0);
		s = *(char**) (s + 4);
		*(int*) (buf + 0x14) = -1;
		*(int*) (buf + 0x0c) = (int) s;
		*(char*) (buf + 0x30) = 1;
		*(int*) (buf + 0x34) = (int) s;
		*(int*) (a0 + 0xb4) = fcn_004c5980((int) buf);
		fcn_00500bb0((int*) (a0 + 0x52), 0, 1, 0);
		*(int*) (a0 + 0x70) = 6;
		return;
	case 4:
		p = fcn_004934c0(s);
		if (p == 0) {
			*(int*) (a0 + 0x70) = 5;
			return;
		}
		fcn_005099e0(s, p);
		c = *(char*) (s + 2);
		if ((c == 6 || c == 7 || c == 5) && *(unsigned char*) (p + 0xd) < *(unsigned char*) (s + 0xd)) {
			fcn_004c4510((int) p, *(int*) (p + 4));
			fcn_004c4570(1, 1, 0xd, (int*) (s + 0xd));
			fcn_004c5360();
		}
		fcn_004c57e0(*(int*) (s + 4), fcn_0050a710(s));
		fcn_00546190(a0);
		return;
	case 5:
		fcn_005099e0(s, (char*) g_773da8);
		fcn_004c57e0(*(int*) (s + 4), fcn_0050a710(s));
		fcn_00546190(a0);
		return;
	case 6:
		v = fcn_004c4450(*(int*) (a0 + 0xb4));
		if (v == 0) {
			return;
		}
		if (v != 2) {
			*(int*) (a0 + 0x52) = *(int*) g_7f4c00;
			*(int*) (a0 + 0x56) = *(int*) (g_7f4c00 + 4);
			*(int*) (a0 + 0x5a) = *(int*) (g_7f4c00 + 8);
			*(unsigned short*) (a0 + 0x5e) = *(unsigned short*) (g_7f4c00 + 0xc);
			*(int*) (a0 + 0xb0) = *(int*) fcn_004c4480(*(int*) (a0 + 0xb4));
			fcn_00500bb0((int*) (a0 + 0x52), 2, 0, 0);
			*(int*) (a0 + 0x70) = 7;
			return;
		}
		goto label_7b3;
	case 7:
		if (*(unsigned char*) (s + 8) != 0) {
			goto tail;
		}
		if (fcn_004e6a30(*(int*) (a0 + 0xb0)) != 0) {
			*(int*) (a0 + 0x52) = *(int*) g_7f4c00;
			*(int*) (a0 + 0x56) = *(int*) (g_7f4c00 + 4);
			*(int*) (a0 + 0x5a) = *(int*) (g_7f4c00 + 8);
			*(unsigned short*) (a0 + 0x5e) = *(unsigned short*) (g_7f4c00 + 0xc);
			fcn_00500bb0((int*) (a0 + 0x52), 2, 0, 0);
			return;
		}
		*(int*) (a0 + 0xb4) = -1;
		*(int*) (a0 + 0xb0) = -1;
		goto label_7b3;
	default:
		return;
	}
label_7b3:
	*(int*) (a0 + 0x52) = *(int*) g_7f4c00;
	*(int*) (a0 + 0x56) = *(int*) (g_7f4c00 + 4);
	*(int*) (a0 + 0x5a) = *(int*) (g_7f4c00 + 8);
	*(int*) (a0 + 0x70) = 4;
	*(unsigned short*) (a0 + 0x5e) = *(unsigned short*) (g_7f4c00 + 0xc);
	return;
tail:
	fcn_00546190(a0);
}
