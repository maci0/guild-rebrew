extern char* __cdecl fcn_00508e40(int);
extern void __cdecl fcn_00529160(int, int, int, int);
extern char* __cdecl fcn_00503fe0(int, int, int);
extern void __cdecl fcn_004c5da0(int, int, int, int, int, char*);
extern int __cdecl fcn_004a57a0(char*, int, int, char*, int, int, unsigned int*);
extern int __cdecl fcn_004f45b0(char*);
extern int __cdecl gm_WalkEntityChain(int);
extern int __cdecl fcn_0050b710(int, int);
extern int __cdecl gm_RandomMod(int);
extern void __cdecl fcn_00579390(char*, char*);
extern void __cdecl fcn_00579410(char*, char*);
extern void __cdecl fcn_004c5530(char*);
extern void __cdecl fcn_00546190(char*);
extern void __cdecl fcn_00500bb0(char*, int, int, int);

typedef struct Req578 {
	int a;
	int b;
	int c;
	int d;
} Req578;

typedef struct Msg578 {
	char pad0[4];
	unsigned char kind;
	char pad5[7];
	int f0c;
	int f10;
	int f14;
	int f18;
	char pad1c[0x10];
	int f2c;
	int f30;
	int f34;
	unsigned short f38;
	unsigned char f3a;
	char pad3b[0x21];
	int f5c;
	int f60;
	int f64;
	int f68;
} Msg578;

/* Death-pact action state machine; resolves the target entity and reports the
 * chosen announcement to the message queue. */
/* ADDRESS: GOLDTL 0x00578ed0 */
void __cdecl fcn_00578ed0(char* a0)
{
	Msg578 msg;
	Req578 req;
	char* ent;
	char* e;
	unsigned int found;
	int state;
	int k;
	int ref;
	int idx;

	ent = fcn_00508e40(*(int*) (a0 + 0xac));
	state = *(int*) (a0 + 0x70);
	if (state == -1 || state == -2) {
		if (ent != 0)
			fcn_00529160(0, 0, *(unsigned short*) ent, 0);
		fcn_00546190(a0);
		return;
	}
	if (ent == 0) {
		fcn_00546190(a0);
		return;
	}
	if (*(unsigned char*) (ent + 8) == 0) {
		fcn_00529160(0, 0, *(unsigned short*) ent, 0);
		fcn_00546190(a0);
		return;
	}
	switch (state) {
	case 0:
		fcn_00529160(0, 0, *(unsigned short*) ent, (int) a0);
		*(int*) (a0 + 0x84) = -1;
		*(int*) (a0 + 0x70) += 1;
		return;
	case 1:
		e = fcn_00503fe0(1, 1, *(int*) (a0 + 0xb4 + *(int*) (a0 + 0xb0) * 4));
		if (e == 0) {
			*(int*) (a0 + 0x70) = -1;
			return;
		}
		fcn_004c5da0(*(int*) (a0 + 0xac), *(int*) (e + 1), -1, 0, 1, (char*) 0x6a7f08);
		*(int*) (a0 + 0x70) += 1;
		return;
	case 2:
		e = fcn_00508e40(*(int*) (a0 + 0xac));
		if (e == 0) {
			*(int*) (a0 + 0x70) = -1;
			return;
		}
		if (*(int*) (*(int*) (e + 0x184) + 0x128) != 0) {
			*(int*) (a0 + 0x52) = *(int*) 0x7f4c00;
			*(int*) (a0 + 0x56) = *(int*) 0x7f4c04;
			*(int*) (a0 + 0x5a) = *(int*) 0x7f4c08;
			*(unsigned short*) (a0 + 0x5e) = *(unsigned short*) 0x7f4c0c;
			fcn_00500bb0(a0 + 0x52, 0, 10, 0);
			return;
		}
		if (fcn_004a57a0((char*) ((*(unsigned short*) (a0 + 8)) * 0x21c + 0x7f4ca0),
				0x700408, 4, a0 + 0xc8, 0, 0x42c80000, &found) == 0) {
			*(int*) (a0 + 0x70) = -1;
			return;
		}
		ref = fcn_004f45b0((char*) ((found & 0xffff) * 0x21c + 0x7f4ca0));
		k = fcn_0050b710(gm_WalkEntityChain(found), *(unsigned char*) 0x773d75);
		*(unsigned short*) (a0 + 0xc8 + *(int*) (a0 + 0xb0) * 2) = (unsigned short) found;
		if (k > ref &&
		    (*(unsigned char*) ((found & 0xffff) * 0x21c + 0x7f4e6c) & 1) == 0) {
			if (*(unsigned char*) ((found & 0xffff) * 0x21c + 0x7f4ca2) == 6 ||
			    *(unsigned char*) ((found & 0xffff) * 0x21c + 0x7f4ca2) == 7) {
				msg.f0c = *(int*) ((found & 0xffff) * 0x21c + 0x7f4ca4);
				msg.f10 = msg.f0c;
				msg.f64 = msg.f0c;
				msg.kind = 0x8b;
				msg.f2c = *(int*) 0x7f4c00;
				msg.f30 = *(int*) 0x7f4c04;
				msg.f34 = *(int*) 0x7f4c08;
				msg.f38 = *(unsigned short*) 0x7f4c0c;
				msg.f3a = 9;
				msg.f14 = 0;
				msg.f18 = 0;
				msg.f5c = *(int*) (a0 + 0xc);
				msg.f60 = *(int*) (a0 + 0xac);
				msg.f68 = ref;
				fcn_004c5530((char*) &msg);
			} else {
				req.a = *(int*) (a0 + 0xc);
				req.b = *(int*) (a0 + 0xac);
				req.c = *(int*) ((found & 0xffff) * 0x21c + 0x7f4ca4);
				req.d = ref;
				if ((gm_RandomMod(2) & 0xffff) != 0)
					fcn_00579390((char*) &req, (char*) ((found & 0xffff) * 0x21c + 0x7f4ca0));
				else
					fcn_00579410((char*) &req, (char*) ((found & 0xffff) * 0x21c + 0x7f4ca0));
			}
		}
		idx = *(int*) (a0 + 0xb0) + 1;
		*(int*) (a0 + 0xb0) = idx;
		if (idx < 5 && *(int*) (a0 + 0xb4 + idx * 4) != 0) {
			*(int*) (a0 + 0x70) -= 1;
			return;
		}
		*(int*) (a0 + 0x70) += 1;
		return;
	case 3:
		e = fcn_00508e40(*(int*) (a0 + 0xac));
		if (e == 0 || *(int*) (e + 0x16c) == 0) {
			*(int*) (a0 + 0x70) = -1;
			return;
		}
		fcn_004c5da0(*(int*) (a0 + 0xac), *(int*) (*(int*) (e + 0x16c) + 1), -1, 0, 0,
			(char*) 0x6a7f08);
		*(int*) (a0 + 0x70) += 1;
		return;
	case 4:
		e = fcn_00508e40(*(int*) (a0 + 0xac));
		if (e == 0 || *(int*) (e + 0x16c) == 0 ||
		    *(int*) (*(int*) (e + 0x184) + 0x128) == 0) {
			*(int*) (a0 + 0x70) = -1;
			return;
		}
		*(int*) (a0 + 0x52) = *(int*) 0x7f4c00;
		*(int*) (a0 + 0x56) = *(int*) 0x7f4c04;
		*(int*) (a0 + 0x5a) = *(int*) 0x7f4c08;
		*(unsigned short*) (a0 + 0x5e) = *(unsigned short*) 0x7f4c0c;
		fcn_00500bb0(a0 + 0x52, 0, 4, 0);
		return;
	default:
		return;
	}
}
