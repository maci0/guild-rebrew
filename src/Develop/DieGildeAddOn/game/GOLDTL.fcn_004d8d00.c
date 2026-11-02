/*
 * Task progression pass.
 *
 * Walks the 0x2c-byte task records of the current round at a0 + 0x94, resolves
 * the target object of each live task and hands it to the per-type progress
 * handler. One loop, eight-way dispatch on the task state.
 *
 * Status: SIZE_MISMATCH, 4648 against the native 4640 bytes, 371 matching
 * bytes. All eight dispatch bodies are transcribed in native body order
 * (5, 1, 2, 3, 6, 4, 7, 8) and the frame matches the native 0x138. The
 * reference stores -1 to p->timer as an immediate and keeps every
 * fcn_004c6680/fcn_004c67c0 call tail separate; here the state -1 test is
 * spelled ~p->type == 0, and the two case-6 tails evaluate ent34(obj) into n
 * ahead of the call, so the compiler cannot share those tails either.
 */
extern int g_772ea4;		/* 0x00772ea4 */

void __cdecl fcn_004c5420(int, int, int, int, int);
int __cdecl fcn_004c4450(int);
int __cdecl fcn_004c6940(void*, int, void*);
int __cdecl fcn_004c67c0(int, void*);
int __cdecl fcn_004cec00(int, int, int*, int*);
void __cdecl fcn_0045b920(int, int, int, float*);
int __cdecl CompareVector3WithinTolerance(float*, float*, float);
char* __cdecl gm_LookupEntityRecordById(int);
char* __cdecl gm_LookupEntityRecordIn32SlotTable(int);
char* __cdecl fcn_004ce610(char*);
unsigned short* __cdecl fcn_004ce680(char*);
float __cdecl fcn_004cefb0(char*, int);
float __cdecl fcn_004cf000(void*, int, int);
unsigned short __cdecl gm_RandomMod(int);
unsigned int __cdecl fcn_004e6cb0(int);
int __cdecl fcn_005c6270(void*, int);
char* __cdecl fcn_004ceac0(char*, char*);
int __cdecl fcn_004d1020(char*, char*, char*, int, int);
char __cdecl fcn_0045b990(char*, float*, int*, int*, int*);
int __cdecl fcn_004d31d0(char*, int, int, int, unsigned int*, unsigned int*);
char* __cdecl fcn_00445600(int, int, int, char*);
void __cdecl fcn_00455350(char*, float*, float*);
int __cdecl fcn_004ce270(char*, char*);
int __cdecl fcn_004c6820(int, void*);
int __cdecl fcn_004c6680(char*, int, int, char*);
unsigned int __cdecl fcn_004d89c0(int, unsigned int, int);
int __cdecl sprintf(char*, char*, ...);
int __cdecl _ftol(void);

typedef struct TaskRec {
	int type;		/* 0x00 */
	int state;		/* 0x04 */
	int timer;		/* 0x08 */
	char c0c;		/* 0x0c */
	char pad0d[3];
	int f10;		/* 0x10 */
	int f14;		/* 0x14 */
	int f18;		/* 0x18 */
	char c1c;		/* 0x1c */
	char c1d;		/* 0x1d */
	char pad1e[2];
	int f20;		/* 0x20 */
	int f24;		/* 0x24 */
	int pad28;		/* 0x28 */
} TaskRec;

typedef struct MsgRec {
	int f[11];
} MsgRec;

static int ent34(char* e)
{
	return *(int*)(*(int*)(e + 0x184) + 0x34);
}

/* ADDRESS: GOLDTL 0x004d8d00 */
void __cdecl fcn_004d8d00(char* a0)
{
	char b118[0x30];
	char be8[0x30];
	char bb8[0x30];
	char b88[0x30];
	int v84;
	int v80;
	int i;
	int v68;
	MsgRec msg;
	float vec[4];
	int v28;
	int v24;
	char* tgt;
	char* base;
	char* ent;
	int v14;
	int v10;
	char* obj;
	TaskRec* p;
	char* e;
	unsigned int u;
	int n;

	v68 = 0;
	base = (char*)*(int*)(*(int*)0x67a370 + 0xb0);
	for (i = 0; i < 0x10; i++) {
		if (g_772ea4)
			return;
		p = (TaskRec*)(a0 + 0x94) + i;
		if (p)
			msg = *(MsgRec*)p;
		if (!p->state || ~p->type == 0)
			continue;
		obj = (p->state == 5)
		    ? gm_LookupEntityRecordById(p->type)
		    : gm_LookupEntityRecordIn32SlotTable(p->type);
		ent = fcn_004ce610(obj);
		if (!obj || *((unsigned char*)obj + 8) == 0) {
			if (ent) {
				p->type = -1;
				p->state = 0;
				return;
			}
		}
		switch (p->state) {
		case 5:
			if (p->timer != 1 && !fcn_004c4450(p->timer))
				break;
			p->timer = -1;
			msg.f[0] = *(int*)(obj + 4);
			msg.f[1] = 0;
			fcn_004c6940(obj, 7, msg.f);
			p->timer = fcn_004c67c0((int)msg.f, (void*)*(int*)(a0 + 0x10));
			break;
		case 1:
			if (p->timer != 1 && !fcn_004c4450(p->timer))
				break;
			p->timer = -1;
			if (!p->c0c) {
				if (!fcn_004cec00(p->f10, p->f14, &v10, &v14))
					break;
				sprintf(be8, (char*)0x68b85c, *(int*)(obj + 4));
				p->c0c = 1;
				fcn_004c6940(obj, 6, msg.f);
				p->timer = fcn_004c6680(be8, v10, v14, 0);
			} else {
				fcn_0045b920((int)base, p->f10, p->f14, vec);
				if (!CompareVector3WithinTolerance(vec,
					(float*)(ent34(obj) + 0x4c), 30.0f))
					break;
				msg.f[0] = *(int*)(obj + 4);
				msg.f[1] = 0;
				fcn_004c6940(obj, 6, msg.f);
				msg.f[3] = *(int*)(obj + 4);
				msg.f[4] = 0;
				p->timer = fcn_004c67c0((int)&msg.f[3], (void*)*(int*)(a0 + 0x10));
			}
			break;
		case 2:
			if (p->timer != 1 && !fcn_004c4450(p->timer))
				break;
			p->timer = -1;
			tgt = gm_LookupEntityRecordIn32SlotTable(p->f10);
			if (tgt) {
				if (*((unsigned char*)tgt + 8) == 0
				    || *(int*)(ent34(tgt) + 0x218) == 1
				    || obj == 0 || *((unsigned char*)obj + 8) == 0) {
					msg.f[0] = *(int*)(obj + 4);
					msg.f[1] = 0;
					fcn_004c6940(obj, 6, msg.f);
					p->timer = fcn_004c67c0((int)msg.f, (void*)*(int*)(a0 + 0x10));
					break;
				}
			}
			if (*(int*)(ent + 0x58) == 1 || *(int*)(ent + 0x58) == 2) {
				n = (int)fcn_004ce680(obj);
				if (n && *(int*)(n + 0x20) <= 0) {
					msg.f[0] = *(int*)(obj + 4);
					msg.f[1] = 0;
					fcn_004c6940(obj, 6, msg.f);
					p->timer = fcn_004c67c0((int)msg.f, (void*)*(int*)(a0 + 0x10));
					break;
				}
			}
			v24 = 1;
			if (*(int*)ent == 0x174) {
				v24 = 0;
				if (!p->c1d && !p->c0c) {
					if (fcn_004cec00(p->f14, p->f18, &v10, &v14)) {
						p->f14 = v10;
						p->f18 = v14;
						fcn_004c6680((char*)ent34(obj), v10, v14, 0);
						p->c0c = 1;
					}
				} else if (*(int*)(*(int*)(obj + 0x184) + 0x128) == 0
				    && p->c0c) {
					fcn_0045b920((int)base, p->f14, p->f18, vec);
					v24 = CompareVector3WithinTolerance(vec,
					    (float*)(ent34(obj) + 0x4c), 120.0f) != 0;
				}
			} else if (*(int*)ent == 0x176) {
				if (tgt) {
					if (fcn_004cefb0(obj, ent34(tgt)) > *(float*)(ent + 0xc))
						v24 = 0;
					if (!p->c0c) {
						if (fcn_004cefb0(obj, ent34(tgt)) > *(float*)(ent + 0xc) * *(double*)0x6629f8)
							v24 = 0;
					}
				} else {
					if (fcn_004cf000(obj, p->f14, p->f18) > *(float*)(ent + 0xc))
						v24 = 0;
					if (!p->c0c) {
						if (fcn_004cf000(obj, p->f14, p->f18) > *(float*)(ent + 0xc) * *(double*)0x6629f8)
							v24 = 0;
					}
				}
			} else {
				if (tgt) {
					if (fcn_004cefb0(obj, ent34(tgt)) > *(float*)(ent + 0xc))
						v24 = 0;
				} else {
					if (fcn_004cf000(obj, p->f14, p->f18) > *(float*)(ent + 0xc))
						v24 = 0;
				}
			}
			if (*((unsigned char*)p + 0x1d) != v24
			    || *(int*)(ent + 0x128) == 0) {
				*((unsigned char*)p + 0x1d) = (unsigned char)v24;
				if (v24) {
					if (*(int*)(ent + 0x58) != 2) {
						n = gm_RandomMod(0xff) & 0xffff;
						if (*(int*)(obj + 0x16c) == *(int*)0x772e98)
							v80 = (int)((double)(unsigned int)*((unsigned char*)ent + 4)
							    * *(double*)0x6640e8
							    * (double)(unsigned int)*((unsigned char*)obj + 0x83)
							    * *(float*)0x68b798);
						else
							v80 = (int)((double)(unsigned int)*((unsigned char*)ent + 4)
							    * *(double*)0x6640e8
							    * (double)(unsigned int)*((unsigned char*)obj + 0x83));
						if (n <= 0xff - v80)
							v24 = 0;
					} else {
						v24 = 1;
					}
					if (v24) {
						u = fcn_004e6cb0(*((unsigned char*)ent + 6)
						    - *((unsigned char*)ent + 5));
						u += *((unsigned char*)ent + 5);
						if (tgt)
							p->f24 = (int)((double)u
							    * *(float*)(tgt + 0x1c)
							    * *(double*)0x6640e8);
						else
							p->f24 = (int)((double)u
							    * *(double*)0x664f20);
					} else {
						p->f24 = 0;
					}
					p->f20 = v24;
					if (v24 && *(int*)(obj + 0x16c)
					    && fcn_005c6270((void*)*(int*)(obj + 0x16c), 0x2b9))
						p->f24 = (int)(p->f24 * *(float*)0x664144);
					if (*(int*)(*(int*)0x772f24 + 4) == *(int*)0x68b79c
					    && *(int*)(ent + 0x58) == 0 && tgt) {
						v80 = 0;
						n = *((unsigned char*)*(int*)0x772eb4 + 0x30);
						for (v84 = 0; v84 < n; v84++) {
							if (*(int*)((char*)*(int*)0x772eb4 + 0x34 + v84 * 4) != -1
							    && a0 != (char*)(0x9b0e20 + v84 * 0x35c)) {
								v80 = 0x9b0e20 + v84 * 0x35c;
								break;
							}
						}
						e = fcn_004ceac0((char*)v80, tgt);
						if (*(int*)(e + 8) == -1 || fcn_004c4450(*(int*)(e + 8))) {
							*(int*)(e + 8) = -1;
							if (*(int*)(e + 4) == 0) {
								n = (int)fcn_004ce680(tgt);
								if (n && *(int*)(n + 0x20) >= 1) {
									fcn_004c5420(*(int*)(obj + 4), 0x1c8, 4, 0x20000000, 0);
									*(int*)(e + 8) = fcn_004d1020((char*)v80, tgt, obj, 0, 0);
								}
							}
						}
					}
				}
			}
			if (*(int*)(ent + 0x58) == 0) {
				if (p->c1d)
					goto lvl3;
				if (*(int*)(*(int*)(obj + 0x184) + 0x128) != 0)
					goto tail1;
				if (p->c1c)
					goto tail1;
				if (!fcn_0045b990(base, (float*)(ent34(obj) + 0x4c),
					&v10, &v14, &v28))
					break;
				p->f14 = v10;
				p->f18 = v14;
				sprintf(b88, (char*)0x68b85c, *(int*)(obj + 4));
				p->timer = fcn_004c6680((char*)ent34(obj), v14, v10, b88);
				goto after2;
			}
			if (*(int*)(ent + 0x58) == 1 || *(int*)ent == 0x176) {
				if (p->c1d)
					goto lvl3;
				if (*(int*)(*(int*)(obj + 0x184) + 0x128) != 0)
					goto tail1;
				if (p->c1c)
					goto tail1;
				if (!fcn_0045b990(base, (float*)(ent34(obj) + 0x4c),
					&v84, &v80, &v28))
					break;
				if (tgt) {
					if (!fcn_0045b990(base,
						(float*)(ent34(tgt) + 0x4c),
						&p->f14, &p->f18, &v28))
						break;
				}
				if (fcn_004d31d0(obj, p->f14, p->f18,
					(int)(*(float*)(ent + 0xc)
					/ *(float*)(base + 0x10)
					* *(double*)0x664128), &v10, &v14))
					p->timer = fcn_004c6680((char*)ent34(obj),
					    v10, v14, 0);
			}
tail1:
			if (!p->c1d)
				goto tail1_body;
lvl3:
			if (*(int*)(*(int*)(obj + 0x184) + 0x128) != 0)
				goto tail1_body;
			if (*(int*)(ent + 0x58) != 2 || !p->f20)
				goto tail2;
			fcn_004c5420(*(int*)(obj + 4), 0x1c8, 4, 0x20000000, 0);
			fcn_004c6940(obj, 2, p);
			msg.f[0] = *(int*)(obj + 4);
			msg.f[1] = 0;
			if (!fcn_0045b990(base, (float*)(ent34(obj) + 0x4c),
				(int*)0x102d020, (int*)0x102d024, &v28))
				break;
			if (fcn_004d31d0(obj, *(int*)0x102d020, *(int*)0x102d024, 0xc,
				(unsigned int*)&v10, (unsigned int*)&v14))
				p->timer = fcn_004c6680((char*)ent34(obj), v10, v14, 0);
			p->timer = fcn_004c67c0((int)msg.f, (void*)*(int*)(a0 + 0x10));
			goto after2;
tail2:
			fcn_004c5420(*(int*)(obj + 4), 0x1c8, 4, 0x20000000, 0);
			p->timer = fcn_004c6940(obj, 2, p);
tail1_body:
			if (*(int*)ent != 0x16e && *(int*)ent != 0x172)
				break;
			if (!p->f20)
				break;
			if (!fcn_0045b990(base, (float*)(ent34(obj) + 0x4c),
				(int*)0x102d020, (int*)0x102d024, &v28))
				break;
			if (fcn_004d31d0(obj, *(int*)0x102d020, *(int*)0x102d024, 0xc,
				(unsigned int*)&v10, (unsigned int*)&v14))
				p->timer = fcn_004c6680((char*)ent34(obj), v10, v14, 0);
			msg.f[0] = *(int*)(obj + 4);
			msg.f[1] = 0;
			p->timer = fcn_004c67c0((int)msg.f, (void*)*(int*)(a0 + 0x10));
			goto after2;
		case 3:
			if (p->timer != 1 && !fcn_004c4450(p->timer))
				break;
			p->timer = -1;
			if (!p->c0c) {
				if (!CompareVector3WithinTolerance(vec,
					(float*)(ent34(obj) + 0x4c), 50.0f)) {
					if (fcn_004cec00(p->f10, p->f14, &v10, &v14)) {
						sprintf(bb8, (char*)0x68b85c, *(int*)(obj + 4));
						p->c0c = 1;
						p->timer = fcn_004c6940(obj, 6, msg.f);
						p->timer = fcn_004c6680(bb8, v10, v14, 0);
					}
				}
			}
			fcn_0045b920((int)base, p->f10, p->f14, vec);
			if (!CompareVector3WithinTolerance(vec,
				(float*)(ent34(obj) + 0x4c), 50.0f))
				break;
			msg.f[0] = *(int*)(obj + 4);
			msg.f[1] = 0;
			fcn_004c6940(obj, 1, msg.f);
			p->timer = fcn_004c67c0((int)msg.f, (void*)*(int*)(a0 + 0x10));
			break;
		case 6:
			if (p->timer != 1 && !fcn_004c4450(p->timer))
				break;
			p->timer = -1;
			if (!fcn_00445600(0, 0x40, 0, (char*)&p->f10)) {
				fcn_004c6940(obj, 6, msg.f);
				msg.f[0] = *(int*)(obj + 4);
				msg.f[1] = 0;
				p->timer = fcn_004c67c0((int)msg.f, (void*)*(int*)(a0 + 0x10));
			}
			if (!*((unsigned char*)p + 0x22)) {
				if (*(int*)(*(int*)(obj + 0x184) + 0x128) == 0) {
					p->c0c = 1;
					fcn_004c6940(obj, 6, msg.f);
					if (!fcn_004cec00(*((unsigned char*)p + 0x20),
						*((unsigned char*)p + 0x21), &v10, &v14))
						break;
					n = ent34(obj);
					p->timer = fcn_004c6680((char*)n, v10, v14, 0);
				} else {
					fcn_0045b920((int)base, *((unsigned char*)p + 0x20),
					    *((unsigned char*)p + 0x21), vec);
					if (!CompareVector3WithinTolerance(vec,
						(float*)(ent34(obj) + 0x4c), 50.0f))
						break;
					fcn_004c6940(obj, 4, msg.f);
					*((unsigned char*)msg.f + 0x22) = 1;
					p->timer = fcn_004c6820(*(int*)(a0 + 0x10), msg.f);
				}
			} else if (*((unsigned char*)p + 0x22) == 1) {
				if (*(int*)(*(int*)(obj + 0x184) + 0x128) != 0)
					break;
				n = (int)fcn_00445600(0, 0x100, 0,
				    (char*)(*(int*)(obj + 0x16c) == *(int*)0x772e9c
					? 0x68bf70 : 0x68bf58));
				fcn_00455350((char*)n, (float*)(n + 0x4c), vec);
				if (!fcn_0045b990(base, (float*)(n + 0x4c), &v10, &v14, &v28))
					break;
				if (!fcn_004cec00(v10, v14, &v10, &v14))
					break;
				*((unsigned char*)msg.f + 0x20) = (unsigned char)v10;
				*((unsigned char*)msg.f + 0x21) = (unsigned char)v14;
				fcn_004c6820(*(int*)(a0 + 0x10), msg.f);
				*((unsigned char*)msg.f + 0x22) = 2;
				n = ent34(obj);
				p->timer = fcn_004c6680((char*)n, v10, v14, 0);
			} else if (*((unsigned char*)p + 0x22) == 2) {
				fcn_0045b920((int)base, *((unsigned char*)p + 0x20),
				    *((unsigned char*)p + 0x21), vec);
				if (!CompareVector3WithinTolerance(vec,
					(float*)(ent34(obj) + 0x4c), 50.0f))
					break;
				fcn_004c6940(obj, 5, msg.f);
				msg.f[0] = *(int*)(obj + 4);
				msg.f[1] = 0;
				p->timer = fcn_004c67c0((int)msg.f, (void*)*(int*)(a0 + 0x10));
			}
			break;
		case 4:
			if (p->timer != 1 && !fcn_004c4450(p->timer))
				break;
			p->timer = -1;
			e = fcn_00445600(0, 0x40, 0, (char*)&p->f10);
			if (!e)
				goto case4b;
			v68 = *(int*)(e + 0x204);
			fcn_00455350(e, (float*)(e + 0x4c), vec);
			if (v68) {
				if (!fcn_004ce270(obj, (char*)v68))
					goto case4b;
				if (*((unsigned char*)v68 + 8) != 0
				    && CompareVector3WithinTolerance(vec,
					(float*)(ent34((char*)v68) + 0x4c), 49.5f))
					goto case4b;
			}
			if (!p->c0c) {
				if (!CompareVector3WithinTolerance(vec,
					(float*)(ent34(obj) + 0x4c), 49.5f)) {
					if (fcn_004cec00(p->f20, p->f24, &v10, &v14)) {
						p->c0c = 1;
						p->f20 = v10;
						p->f24 = v14;
						fcn_004c6940(obj, 6, msg.f);
						p->timer = fcn_004c6680((char*)(*(int*)(*(int*)(obj + 0x184) + 0x34)), v10, v14, 0);
						goto after2;
					}
				}
			}
			if (p->c0c == 1
			    && *(int*)(*(int*)(obj + 0x184) + 0x128) == 0
			    && !CompareVector3WithinTolerance(vec,
				(float*)(ent34(obj) + 0x4c), 49.5f)) {
				p->c0c = 0;
				goto after2;
			}
			if (!CompareVector3WithinTolerance(vec,
				(float*)(ent34(obj) + 0x4c), 49.5f))
				break;
			fcn_004c6940(obj, 3, msg.f);
			msg.f[0] = *(int*)(obj + 4);
			msg.f[1] = 0;
			p->timer = fcn_004c67c0((int)msg.f, (void*)*(int*)(a0 + 0x10));
			break;
case4b:
			fcn_00455350(e, (float*)(e + 0x4c), vec);
			if (fcn_004ce270(obj, (char*)*(int*)(e + 0x204))) {
				if (*((unsigned char*)v68 + 8) != 0
				    && CompareVector3WithinTolerance(vec,
					(float*)(ent34((char*)v68) + 0x4c), 49.5f)) {
					p->timer = fcn_004d89c0((int)a0, (unsigned int)obj,
					    *(int*)(e + 0x204));
					goto after2;
				}
			}
			if (*((unsigned char*)v68 + 8) != 0)
				break;
			msg.f[0] = *(int*)(obj + 4);
			msg.f[1] = 0;
			p->timer = fcn_004c67c0((int)msg.f, (void*)*(int*)(a0 + 0x10));
			break;
		case 7:
			if (p->timer != 1 && !fcn_004c4450(p->timer))
				break;
			p->timer = -1;
			if (!p->c0c) {
				if (!fcn_004cec00(p->f10, p->f14, &v10, &v14))
					break;
				sprintf(b118, (char*)0x68b85c, *(int*)(obj + 4));
				p->c0c = 1;
				fcn_004c6940(obj, 6, msg.f);
				p->timer = fcn_004c6680(b118, v10, v14, 0);
			} else {
				fcn_0045b920((int)base, p->f10, p->f14, vec);
				if (!CompareVector3WithinTolerance(vec,
					(float*)(ent34(obj) + 0x4c), 30.0f))
					break;
				msg.f[0] = *(int*)(obj + 4);
				msg.f[1] = 0;
				fcn_004c6940(obj, 6, msg.f);
				p->timer = fcn_004c67c0((int)msg.f, (void*)*(int*)(a0 + 0x10));
			}
			break;
		case 8:
			if (p->timer != 1 && !fcn_004c4450(p->timer))
				break;
			p->timer = -1;
			if (p->c0c)
				break;
			p->c0c = 1;
			p->timer = fcn_004c6940(obj, 6, msg.f);
			break;
after2:
			;
		}
		*(int*)0x9b0000 += 0x1f;
	}
}
