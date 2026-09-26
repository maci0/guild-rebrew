// FUNCTION: GOLDTL 0x00546850
// SIZE: 746

extern unsigned char g_7766bb;
extern unsigned short g_774970;
extern int g_6b8010;
extern int g_7f4e68[];
extern char g_6a585c[];
extern char g_6a584c[];
extern char g_6a5834[];
extern char g_6a5824[];
extern char g_6a5818[];
extern char g_6a5804[];
extern char g_6a57f8[];
extern char g_6a57ec[];
extern char g_6a57d8[];

char* __cdecl gm_SearchTable67(int id);
unsigned short* __cdecl fcn_00508e40(int id);
int __cdecl fcn_00445600(int a, int b, int c, char* name);
void __cdecl fcn_00546720(unsigned char* p, char* fmt, int v);

void __cdecl fcn_00546850(unsigned char* p)
{
	char* r;
	unsigned short* o;
	int v;

	if (g_7766bb == 0 || *(int*) (p + 0x88) != 0) {
		return;
	}
	switch (*p) {
	case 0x1b:
		r = gm_SearchTable67(*(int*) (p + 0xac));
		if (r != 0) {
			fcn_00546720(p, g_6a585c, *(int*) (r + 0x61));
		}
		break;
	case 0x1c:
		r = gm_SearchTable67(*(int*) (p + 0xac));
		if (r != 0 && *(int*) (r + 0x61) != 0) {
			fcn_00546720(p, g_6a584c, *(int*) (r + 0x61));
		}
		break;
	case 0x1e:
		r = gm_SearchTable67(*(int*) (p + 0xac));
		if (r != 0 && *(int*) (r + 0x61) != 0) {
			fcn_00546720(p, g_6a5834, *(int*) (r + 0x61));
		}
		break;
	case 0x1f:
		r = gm_SearchTable67(*(int*) (p + 0xac));
		if (r != 0 && *(int*) (r + 0x61) != 0) {
			fcn_00546720(p, g_6a5824, *(int*) (r + 0x61));
		}
		break;
	case 2:
		r = gm_SearchTable67(*(int*) (p + 0x10));
		if (r != 0 && *(int*) (r + 0x61) != 0) {
			fcn_00546720(p, g_6a5824, *(int*) (r + 0x61));
		}
		break;
	case 0x40:
		r = gm_SearchTable67(*(int*) (p + 0xac));
		if (r != 0 && *(int*) (r + 0x61) != 0 && *(short*) (p + 8) == (short) g_774970) {
			fcn_00546720(p, g_6a5818, *(int*) (r + 0x61));
		}
		break;
	case 0x35:
		o = fcn_00508e40(*(int*) (p + 0xbc));
		if (o != 0 && *o == g_774970 && g_6b8010 == 0) {
			v = fcn_00445600(0, 0x40, 0, g_6a5804);
			if (v != 0) {
				fcn_00546720(p, g_6a57d8, v);
			}
		}
		break;
	case 0x6b:
		if (*(int*) (p + 0x70) == 2 && g_6b8010 == 0 && (g_7f4e68[g_774970 * 135] & 0x20000) == 0) {
			v = fcn_00445600(0, 0x40, 0, g_6a57f8);
			if (v != 0) {
				fcn_00546720(p, g_6a57d8, v);
			}
		}
		break;
	case 0x1a:
		r = gm_SearchTable67(*(int*) (p + 0xd0));
		if (r != 0 && *(int*) (r + 0x61) != 0) {
			fcn_00546720(p, g_6a57ec, *(int*) (r + 0x61));
		}
		break;
	case 4:
		if (*(unsigned short*) (p + 8) == g_774970 && *(int*) (p + 0xc8) != 0) {
			r = gm_SearchTable67(*(int*) (p + 0xbc));
			if (r != 0 && *(int*) (r + 0x61) != 0) {
				fcn_00546720(p, g_6a57d8, *(int*) (r + 0x61));
			}
		}
		break;
	}
}
