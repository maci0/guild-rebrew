// FUNCTION: GOLDTL 0x004f53a0
// SIZE: 776

/* Same by-value request struct as fcn_004f5300: caller 0x4f56b0 copies 0x2d bytes. */
// SIZE 0x2d
typedef struct tag_req_2d_c {
	char raw[0x2d];
} req_2d_c;

unsigned char* __cdecl fcn_00508e40(int);
void __cdecl fcn_0051af00(void*, int, ...);
void __cdecl fcn_005015e0(char** out, int a2, int a3, int id);
int __cdecl fcn_0051e070(void);

int __cdecl fcn_004f53a0(void* a1, req_2d_c s, int b)
{
	char* nm;
	char name[0x80] = "Geb\xe4ude";
	unsigned short w;
	unsigned char* p;
	int v = (b <= 1);

	fcn_005015e0(&nm, 0, 0, *(int*) ((char*) &s + 0x21));
	if (nm != 0) {
		fcn_0051af00(name, (int) "%1G", nm);
	}
	p = fcn_00508e40(*(int*) ((char*) &s + 0x12));
	if (p != 0) {
		w = *(unsigned short*) p;
	} else {
		w = 0xfffe;
	}
	switch (*(int*) ((char*) &s + 0x1c) & 0xff) {
	case 0x11:
		fcn_0051af00(a1, v + 0x1455, (char*) &s + 4);
		break;
	case 0x12:
		fcn_0051af00(a1, v + 0x145a, (char*) &s + 4);
		break;
	case 0x13:
		fcn_0051af00(a1, v + 0x145f, w, (char*) &s + 4);
		break;
	case 0x14:
		fcn_0051af00(a1, v + 0x1464, (char*) &s + 4, w);
		break;
	case 0x15:
		fcn_0051af00(a1, v + 0x1469, (char*) &s + 4, w);
		break;
	case 0x16:
		fcn_0051af00(a1, v + 0x146e, w, (char*) &s + 4);
		break;
	case 0x17:
		fcn_0051af00(a1, v + 0x1473, (char*) &s + 4, w);
		break;
	case 0x18:
		switch (fcn_0051e070()) {
		case 0:
		case 1:
			fcn_0051af00(a1, v + 0x1478, (char*) &s + 4, w, name);
			break;
		case 2:
			fcn_0051af00(a1, v + 0x1478, (char*) &s + 4, name, w);
			break;
		}
		break;
	case 0x19:
		fcn_0051af00(a1, v + 0x147d, w, (char*) &s + 4);
		break;
	case 0x1a:
		fcn_0051af00(a1, v + 0x1482, (char*) &s + 4, w);
		break;
	case 0x1b:
		fcn_0051af00(a1, v + 0x1487, (char*) &s + 4);
		break;
	case 0x1c:
		fcn_0051af00(a1, v + 0x148c, (char*) &s + 4, w);
		break;
	}
	return 0;
}
