typedef struct {
	int day;
	int hour;
	int min;
	unsigned short sec;
} Time;

extern int g_7f4c00;
extern int g_7f4c04;
extern int g_7f4c08;
extern unsigned short g_7f4c0c;
extern unsigned short g_774970;
extern int gm_RichterKatholisch;
extern int gm_RichterEvangelisch;
extern float g_6652c8;
extern char g_7f4ca4[];

int __cdecl gm_WalkEntityChain(unsigned short);
int __cdecl gm_RandomMod(int);
void __cdecl fcn_00500bb0(Time*, int, int, int);
void __cdecl fcn_004c5530(char*);
void __cdecl fcn_004c6b20(int, int, int);
void __cdecl fcn_004c4510(void*, int);
void __cdecl fcn_004c4570(int, int, int, void*);
void __cdecl fcn_004c5360(void);
void __cdecl fcn_004c5980(void*);
int __cdecl srv_GetEntityOfficeSlot(unsigned char*, void*, void*);
int __cdecl fcn_004e8240(unsigned char, int, int, int, int);

/* ADDRESS: GOLDTL 0x004f6850 */
void __cdecl fcn_004f6850(unsigned short* a0, int a1)
{
	char v12;
	int n;
	char msg[0xf8];
	char b9[0x144];
	int id;
	char* p;
	char* pkt;
	int* list;

	n = gm_WalkEntityChain((unsigned short) a0[0]);

	switch (a1) {
	case 0:
		msg[4] = 0x5c;
		msg[0x36] = 1;
		*(int*) (msg + 0x28) = g_7f4c00;
		*(int*) (msg + 0x2c) = g_7f4c04;
		*(int*) (msg + 0x30) = g_7f4c08;
		*(unsigned short*) (msg + 0x34) = g_7f4c0c;
		fcn_00500bb0((Time*) (msg + 0x28), 1, 0, 0);
		*(int*) (msg + 8) = *(int*) (a0 + 2);
		*(int*) (msg + 0xc) = -1;
		*(int*) (msg + 0x58) = 3;
		*(int*) (msg + 0x5c) = 1;
		fcn_004c5530(msg);
		return;
	case 1:
		msg[4] = 0x5b;
		msg[0x36] = 1;
		*(int*) (msg + 0x28) = g_7f4c00;
		*(int*) (msg + 0x2c) = g_7f4c04;
		*(int*) (msg + 0x30) = g_7f4c08;
		*(unsigned short*) (msg + 0x34) = g_7f4c0c;
		fcn_00500bb0((Time*) (msg + 0x28), 1, 0, 0);
		*(int*) (msg + 8) = *(int*) (a0 + 2);
		*(int*) (msg + 0xc) = -1;
		*(int*) (msg + 0x58) = (int) ((float) n * g_6652c8);
		*(int*) (msg + 0x5c) = 1;
		fcn_004c5530(msg);
		return;
	case 2:
		msg[4] = 0x5c;
		msg[0x36] = 1;
		*(int*) (msg + 0x28) = g_7f4c00;
		*(int*) (msg + 0x2c) = g_7f4c04;
		*(int*) (msg + 0x30) = g_7f4c08;
		*(unsigned short*) (msg + 0x34) = g_7f4c0c;
		fcn_00500bb0((Time*) (msg + 0x28), 1, 0, 0);
		*(int*) (msg + 8) = *(int*) (a0 + 2);
		*(int*) (msg + 0xc) = -1;
		*(int*) (msg + 0x58) = 3;
		*(int*) (msg + 0x5c) = 3;
		fcn_004c5530(msg);
		return;
	case 3:
		msg[4] = 0x5b;
		msg[0x36] = 1;
		*(int*) (msg + 0x28) = g_7f4c00;
		*(int*) (msg + 0x2c) = g_7f4c04;
		*(int*) (msg + 0x30) = g_7f4c08;
		*(unsigned short*) (msg + 0x34) = g_7f4c0c;
		fcn_00500bb0((Time*) (msg + 0x28), 1, 0, 0);
		*(int*) (msg + 8) = *(int*) (a0 + 2);
		*(int*) (msg + 0xc) = -1;
		*(int*) (msg + 0x58) = (int) ((float) n * g_6652c8);
		*(int*) (msg + 0x5c) = 4;
		fcn_004c5530(msg);
		return;
	case 4:
		fcn_004c6b20(*(int*) (a0 + 2), 1, 0);
		return;
	case 5:
		fcn_004e8240(((char*) a0)[0x166], 0, 0, 4, 0xff);
		return;
	case 6:
		fcn_004c6b20(*(int*) (a0 + 2), 2, 0);
		return;
	case 7:
		v12 = (char) (((unsigned char*) a0)[0xd] > 2 ? 2 : 1);
		fcn_004c4510(a0, *(int*) (a0 + 2));
		fcn_004c4570(1, 1, 0xd, &v12);
		fcn_004c5360();
		return;
	case 8:
		fcn_004c6b20(*(int*) (a0 + 2), 3, 0);
		return;
	case 9:
		fcn_004c6b20(*(int*) (a0 + 2), 0xff, 1);
		pkt = b9 + 0x18;
		list = (int*) (pkt + 0x34);
		id = *(int*) (a0 + 2);
		list[0] = id;
		list[1] = *(int*) (gm_RichterKatholisch + 4);
		list[2] = *(int*) (gm_RichterEvangelisch + 4);
		n = 3;
		for (p = (char*) 0x7f4ca2; n < 0x10 && (int) p < 0x85a0a2; p += 0x21c) {
			if (id != *(int*) (p + 2) &&
			    (p[0] == 6 || p[0] == 7 || p[0] == 5)) {
				list[n] = *(int*) (p + 2);
				n++;
			}
		}
		*(char*) (pkt + 0x30) = (char) n;
		*(int*) (pkt + 0x0c) = *(int*) (g_7f4ca4 + (unsigned int) g_774970 * 0x21c);
		*(int*) (pkt + 0x14) = -1;
		*(int*) (pkt + 0x18) = g_7f4c00;
		*(int*) (pkt + 0x1c) = g_7f4c04;
		*(int*) (pkt + 0x20) = g_7f4c08;
		*(unsigned short*) (pkt + 0x24) = g_7f4c0c;
		fcn_00500bb0((Time*) (pkt + 0x18), 0x18, 0, 0);
		/* packed packet fields: 2-byte hour override, then 4 zeroed bytes */
		*(unsigned short*) (pkt + 0x1c) = 10;
		*(int*) (pkt + 0x1e) = 0;
		*(char*) (pkt + 0x08) = 5;
		*(char*) (pkt + 0x7c) = (char) gm_RandomMod(5);
		*(char*) (pkt + 0x7d) = 0;
		*(char*) (pkt + 0x26) = 0x22;
		if (((char*) a0)[2] == 6 || ((char*) a0)[2] == 7) {
			*(char*) (pkt + 0x26) = 0xa2;
		}
		fcn_004c5980(pkt);
		if (srv_GetEntityOfficeSlot((unsigned char*) a0, b9 + 0x12c, b9) == 0) {
			return;
		}
		fcn_004e8240(*(int*) b9, 0, 0, 3, 0xff);
		return;
	default:
		return;
	}
}
