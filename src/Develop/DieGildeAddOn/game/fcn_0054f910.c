char* __cdecl gm_LookupEntityRecordById(int id);
int __cdecl fcn_00500bb0(char* sel, int a, int b, int c);
int __cdecl fcn_004f4f60(int a, int b, int c, int d, int e);
float __cdecl fcn_00507e70(char* a, char* b, int c);
float __cdecl fcn_0042e450(void);
int __cdecl fcn_004c5420(int a, int b, int c, int d, int e);
int __cdecl fcn_004c5620(char* e, int a);
int __cdecl io_FormatTextBuffer(char* buf, int fmt, ...);
int __cdecl fcn_00545d40(int a, int b, char* s, int c, int d, int e);
int __cdecl fcn_004e7b70(char* e, void* a, void* b);
int __cdecl fcn_0042e410(int code);
float __cdecl gm_GetEntitySkill(char* e, int a);
int __cdecl fcn_004ec2d0(char* e, int a, int b);
int __cdecl fcn_004c54c0(int a, int b, int c, int d);
int __cdecl fcn_00500de0(char* p, int id, int a, int b, int c);
int __cdecl fcn_004c5530(void* p);

/* ADDRESS: GOLDTL 0x0054f910 */
int __cdecl fcn_0054f910(char* ent)
{
	char* e1;
	char* e2;
	unsigned char flags;
	int v;
	int w;
	int dmg;
	float f;
	char text[0x100];
	int blk[0x3e];
	int tmp[4];

	*(int*) (ent + 0x84) = -1;
	*(int*) (ent + 0x52) = *(int*) 0x7f4c00;
	*(int*) (ent + 0x56) = *(int*) 0x7f4c04;
	*(int*) (ent + 0x5a) = *(int*) 0x7f4c08;
	*(short*) (ent + 0x5e) = *(short*) 0x7f4c0c;
	fcn_00500bb0(ent + 0x52, 0x18, 0, 0);
	flags = *(unsigned char*) (ent + 0x78);
	*(short*) (ent + 0x56) = 6;
	*(int*) (ent + 0x58) = 0x1e;
	if ((flags & 2) == 0) {
		return 0;
	}
	e1 = gm_LookupEntityRecordById(*(int*) (ent + 0xac));
	e2 = gm_LookupEntityRecordById(*(int*) (ent + 0xb0));
	if (e1 == 0 || e2 == 0) {
		if ((*(int*) (e1 + 0x1c8) & 0x400) != 0
		    || (*(int*) (e2 + 0x1c8) & 0x400) != 0) {
			*(int*) (ent + 0x52) = *(int*) 0x7f4c00;
			*(int*) (ent + 0x56) = *(int*) 0x7f4c04;
			*(int*) (ent + 0x5a) = *(int*) 0x7f4c08;
			*(short*) (ent + 0x5e) = *(short*) 0x7f4c0c;
			fcn_00500bb0(ent + 0x52, 2, 0, 0);
			*(int*) (ent + 0x84) = fcn_004c5620(ent, -1);
			return 0;
		}
	}
	v = -1;
	w = *(int*) (e1 + 0x170);
	if (w == 0) {
		w = *(int*) (e2 + 0x170);
	}
	if (w != 0) {
		v = *(int*) (w + 1);
	}
	fcn_004f4f60(4, 1, *(int*) (e1 + 4), *(int*) (e2 + 4), v);
	if (*(unsigned char*) (e2 + 2) == 6
	    || *(unsigned char*) (e2 + 2) == 7) {
		goto big;
	}
	f = fcn_00507e70(e2, e1, 3);
	f = f + fcn_0042e450();
	if (f >= 1.0f) {
		fcn_004c5420(*(int*) (e1 + 4), 0x1c8, 4, 0x400, 0);
		fcn_004c5420(*(int*) (e2 + 4), 0x1c8, 4, 0x400, 0);
		*(int*) (ent + 0x52) = *(int*) 0x7f4c00;
		*(int*) (ent + 0x56) = *(int*) 0x7f4c04;
		*(int*) (ent + 0x5a) = *(int*) 0x7f4c08;
		*(short*) (ent + 0x5e) = *(short*) 0x7f4c0c;
		fcn_00500bb0(ent + 0x52, 0x18, 0, 0);
		*(short*) (ent + 0x56) = 6;
		*(int*) (ent + 0x58) = 0x1e;
		if (*(unsigned char*) (e1 + 2) == 6
		    || *(unsigned char*) (e1 + 2) == 7) {
			io_FormatTextBuffer(text, 0x1d83,
			    *(unsigned short*) (e2), ent + 0x52,
			    *(unsigned short*) (e2), *(int*) (e1 + 4));
			fcn_00545d40(*(int*) (e1 + 4), *(int*) (e1 + 4),
			    text, 0, 0x5fa, (int) (char*) 0x6a5b08);
		}
		*(int*) (ent + 0x84) = fcn_004c5620(ent, 2);
		return 0;
	}
	v = 0;
	if (*(unsigned char*) (e1 + 2) == 6
	    || *(unsigned char*) (e1 + 2) == 7) {
		io_FormatTextBuffer(text, 0x1d81,
		    (*(unsigned char*) (e2 + 9) != 0) + 0x1d68,
		    *(unsigned short*) (e2), *(unsigned short*) (e2),
		    *(int*) (e1 + 4));
		fcn_00545d40(*(int*) (e1 + 4), *(int*) (e1 + 4),
		    text, 0, 0x5fa, 0);
	}
	if (*(unsigned char*) (e2 + 0x166) != 0) {
		w = fcn_004e7b70(e2, tmp, &tmp[2]);
		if (w != 0) {
			v = tmp[1];
		} else {
			v = (fcn_0042e410(3) & 0xffff) + 1;
		}
	}
	f = gm_GetEntitySkill(e1, 4) * 8.0f;
	w = (int) f;
	dmg = -9 - w - (fcn_0042e410(8) & 0xffff);
	fcn_004ec2d0(e2, v, dmg);
	fcn_004c54c0(*(int*) (e2 + 4), *(int*) (e1 + 4), -0x14, 1);
	*(int*) (ent + 0x52) = *(int*) 0x7f4c00;
	*(int*) (ent + 0x56) = *(int*) 0x7f4c04;
	*(int*) (ent + 0x5a) = *(int*) 0x7f4c08;
	*(short*) (ent + 0x5e) = *(short*) 0x7f4c0c;
	fcn_00500bb0(ent + 0x52, 0, 2, 0);
	*(int*) (ent + 0x84) = fcn_004c5620(ent, -1);
	return 0;
big:
	for (w = 0; w < 0x3e; w++) {
		blk[w] = 0;
	}
	*(int*) (&blk[3]) = *(int*) (e2 + 4);
	*(int*) (&blk[4]) = *(int*) (e2 + 4);
	*((unsigned char*) &blk[6]) = 0x46;
	*((unsigned char*) &blk[0x12]) = 9;
	*(int*) (&blk[0x1b]) = *(int*) (ent + 4);
	fcn_00500de0((char*) &blk[0x0c], *(unsigned short*) (e2), 6, 0, 0);
	fcn_004c5530(&blk[5]);
	*(int*) (ent + 0x52) = *(int*) 0x7f4c00;
	*(int*) (ent + 0x56) = *(int*) 0x7f4c04;
	*(int*) (ent + 0x5a) = *(int*) 0x7f4c08;
	*(short*) (ent + 0x5e) = *(short*) 0x7f4c0c;
	fcn_00500bb0(ent + 0x52, 0x18, 0, 0);
	*(short*) (ent + 0x56) = 6;
	*(int*) (ent + 0x58) = 0x1e;
	*(int*) (ent + 0x84) = fcn_004c5620(ent, 1);
	fcn_004c5420(*(int*) (e1 + 4), 0x1c8, 4, 0x400, 0);
	fcn_004c5420(*(int*) (e2 + 4), 0x1c8, 4, 0x400, 0);
	return 0;
}
