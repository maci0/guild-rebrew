#include <string.h>

#include "client_types.h"
#include "client_packet_builder.h"

extern unsigned char* lpGebaeudeINST;
extern unsigned char* lpGebaeudePROT;
extern unsigned short* g_773da8;
extern unsigned char g_773d75;
extern char g_7f4ca0[];
extern pos14_7f4c00 g_7f4c00;
extern double g_6640e8;
extern double g_664128;
extern double g_662908;
extern float g_665368;
extern void (__stdcall* g_662068)(unsigned int);

void __cdecl fcn_004c5420(int, int, int, int, int);
void __cdecl fcn_004c4700(int, int, int, void*);
void __cdecl fcn_004c53a0(void);
void __cdecl fcn_004c4570(int, int, int, void*);
void __cdecl fcn_004c5360(void);
void __cdecl fcn_004c5120(int);
void __cdecl fcn_004c5a60(int, int, int);
void __cdecl fcn_004c5f60(int, int, int);
void __cdecl fcn_004c5530(void*);
void __cdecl fcn_004c54c0(int, int, int, int);
void __cdecl fcn_004c51a0(int, int, unsigned char, int);
void __cdecl fcn_004c6090(char*, int, int, int);
void __cdecl fcn_004f3ef0(char*);
void __cdecl fcn_0050ff70(char*, int);
unsigned char* __cdecl fcn_0050dc90(unsigned char*);
unsigned char* __cdecl fcn_004ec7d0(unsigned char*);
int __cdecl fcn_004ee160(char*);
int __cdecl gm_AccumulateTyped2(char*);
int __cdecl gm_SearchTable67(int);
int __cdecl fcn_0050c4e0(unsigned char*);
unsigned short* __cdecl gm_NextEntityQueryMatch(void);
int __cdecl fcn_0050cf50(char*, int);
unsigned short __cdecl gm_RandomMod(int);
int __cdecl fcn_00507380(int);
void __cdecl fcn_005049c0(int);
void* __cdecl gm_StartFilteredEntitySearch(int, ...);
void* __cdecl gm_FindNextFilteredEntity(void);
int __cdecl fcn_00505d00(char*, int*);
float __cdecl fcn_0050b8d0(unsigned char*, int, int, int);
void* __cdecl sim_StartEntityQueryByType(unsigned char*);
unsigned char* __cdecl fcn_005049a0(unsigned char*);
int __cdecl fcn_004fe470(int, int, int, int, int);
void __cdecl fcn_00500bb0(pos14_7f4c00*, int, int, int);
void __cdecl fcn_00535960(void);
int __cdecl fcn_0050c1b0(unsigned char*, int, int*);
unsigned short* __cdecl fcn_00502cd0(int, int, ...);
int __cdecl fcn_0050b810(int, char);
int __cdecl fcn_0050f950(int, int);

/* ADDRESS: GOLDTL 0x005422c0 */
void __cdecl fcn_005422c0(unsigned int arg)
{
	unsigned char* rec;
	unsigned char* def;
	unsigned char* tile;
	unsigned char* tile2;
	unsigned char* obj;
	unsigned char* q;
	unsigned char* r;
	unsigned char* p;
	unsigned char* slot;
	int out[16];
	int buf4[4];
	unsigned char msg[0x2e8];
	int count;
	int n;
	int i;
	int j;
	int a;
	int idx;
	int off;
	int id2;
	int zero;
	int v;
	int b1;
	float f;
	char cv;
	char delta;

	count = 0;
	n = 0x100;
	rec = lpGebaeudeINST;
	do {
		if (*rec != 0 && *(unsigned short*) (rec + 0x27) == (unsigned short) arg) {
			def = lpGebaeudePROT + *rec * 0x24d;
			*(int*) (rec + 0x4d) = 0;
			*(int*) (rec + 0x51) = 0;
			*(int*) (rec + 0x55) = 0;
			if ((*(unsigned short*) (rec + 0x5a) & 0x3800) != 0) {
				fcn_004c5420(*(int*) (rec + 1), 0x5a, 2, 0, 0x3800);
				count++;
			}
			v = *def;
			if (v != 4 && v != 0x10 && v != 0x13) {
				if (v == 5) {
					zero = 0;
					fcn_004c4510((char*) rec, *(int*) (rec + 1));
					for (i = 0; i < 3; i++) {
						fcn_004c4700(4, 1, (int) (rec - g_aed32c) + 0x71 + i * 12, &zero);
					}
					fcn_004c53a0();
					count++;
					off = (arg & 0xffff) * 0x21c;
					v = *(unsigned char*) (g_7f4ca0 + off + 2);
					if (v != 6 && v != 7) {
						if (gm_AccumulateTyped2(g_7f4ca0 + off) < 160000) {
							fcn_004c5150(*(int*) (g_7f4ca0 + off + 4), -1, (char) g_773d75, *(unsigned char*) (def + 0x247) * 16000);
							count++;
						}
					}
				}
				else if (v == 0xd || v == 0xc || v == 0xb) {
					if (*(unsigned short*) (rec + 0x27) == g_773da8[0]) {
						obj = fcn_0050dc90(rec);
						if (obj == 0) {
							count++;
							fcn_004c6090((char*) rec, 1, 0, *(unsigned char*) (def + 0x223));
						}
						else if ((*(unsigned char*) (obj + 0x1b4) & 1) == 0) {
							buf4[0] = *(int*) (obj + 0x1b4) | 1;
							buf4[1] = *(int*) (obj + 0x1b8);
							buf4[2] = *(int*) (obj + 0x1bc);
							buf4[3] = *(int*) (obj + 0x1c0);
							fcn_004c4510((char*) obj, *(int*) (obj + 4));
							fcn_004c4570(4, 1, (int) (obj - g_aed32c) + 0x1b4, buf4);
							fcn_004c5360();
						}
					}
				}
				else if (v == 0x1d) {
					fcn_004f3ef0((char*) rec);
				}
			}
			else {
				obj = (unsigned char*) fcn_00502cd0(*(int*) (rec + 0x5d), 1, 0, 0xca);
				while (obj != 0) {
					count++;
					if (*(unsigned char*) (obj + 0x37) > 5) {
						r = (unsigned char*) gm_SearchTable67(*(int*) (obj + 0x2a));
						if (r != 0) {
							cv = (char) (*(unsigned char*) (obj + 0x37) - fcn_0050c4e0(r) * 2);
							if (cv < 0) {
								cv = 0;
							}
							fcn_004c4510((char*) obj, *(int*) (obj + 2));
							fcn_004c4570(1, 1, (int) (obj - g_aed32c) + 0x37, &cv);
							fcn_004c5360();
						}
						else {
							fcn_004c5120(*(int*) (obj + 2));
						}
					}
					else {
						fcn_004c5a60(*(int*) (rec + 1), -1, *(int*) (obj + 2));
					}
					obj = (unsigned char*) gm_NextEntityQueryMatch();
				}
			}
			if (*(unsigned short*) (rec + 0x25) == g_773da8[0]
			    && (*(unsigned char*) (rec + 0x5a) & 3) == 0
			    && *def != 1 && *def != 3 && *def != 6 && *def != 0xa
			    && *def != 0xb && *def != 0xc && *def != 0xd && *def != 0xf
			    && *def != 0x1c && *def != 0x1b && *def != 0x1a && *def != 0x19
			    && *def != 0x18 && *def != 0x17) {
				(msg + 0xf8)[4] = 0x1b;
				*(int*) ((msg + 0xf8) + 8) = *(int*) (g_773da8 + 2);
				*(int*) ((msg + 0xf8) + 0xc) = -1;
				(msg + 0xf8)[0x36] = 2;
				*(int*) ((msg + 0xf8) + 0x58) = *(int*) (rec + 1);
				*(int*) ((msg + 0xf8) + 0x5c) = fcn_0050cf50((char*) rec, *(signed char*) (rec + 0x5c));
				fcn_004c5530((msg + 0xf8));
			}
			off = (arg & 0xffff) * 0x21c;
			v = *(unsigned char*) (g_7f4ca0 + off + 2);
			if (v == 0xd || v == 0 || *(int*) (g_7f4ca0 + off + 4) == -1) {
				fcn_004c5f60(*(int*) (rec + 1), *(int*) (g_773da8 + 2), *(int*) (g_773da8 + 2));
				count++;
				v = *def;
				if (v != 0xd && v != 0xc && v != 0xb) {
					msg[4] = 0x1b;
					*(int*) (msg + 8) = *(int*) (g_773da8 + 2);
					*(int*) (msg + 0xc) = -1;
					msg[0x36] = 2;
					*(int*) (msg + 0x58) = *(int*) (rec + 1);
					*(int*) (msg + 0x5c) = fcn_0050cf50((char*) rec, *(signed char*) (rec + 0x5c));
					fcn_004c5530(msg);
					count++;
					for (i = 0; i < 768; i++) {
						slot = g_7f4ca0 + i * 0x21c;
						if (*(unsigned char**) (slot + 0x16c) == rec) {
							memset(msg, 0, 0xf8);
							msg[4] = 0x31;
							*(int*) (msg + 8) = *(int*) (g_773da8 + 2);
							*(int*) (msg + 0xc) = *(int*) (rec + 1);
							*(pos14_7f4c00*) (msg + 0x28) = g_7f4c00;
							msg[0x36] = 1;
							*(int*) (msg + 0x5c) = *(int*) (slot + 4);
							fcn_004c5530(msg);
							count++;
						}
					}
				}
			}
			if (gm_RandomMod(100) > 0x1e
			    && *def != 0xd && *def != 0xc && *def != 0xb && *def != 0x10
			    && (*(unsigned char*) (rec + 0x5a) & 1) == 0
			    && *def != 0xa) {
				fcn_0050ff70((char*) rec, -(gm_RandomMod(3) & 0xffff) - 2);
				count++;
			}
		}
		rec += 0xa9;
		n--;
	} while (n != 0);

	idx = arg & 0xffff;
	off = idx * 0x21c;
	v = fcn_00507380(*(unsigned char*) (g_7f4ca0 + off + 0x164));
	if (v >= 2 && v <= 5) {
		fcn_005049c0(v);
	}
	p = (unsigned char*) gm_StartFilteredEntitySearch(1, 6);
	while (p != 0) {
		if (*(unsigned short*) (p + 0x27) == (unsigned short) arg) {
			tile = g_7f4ca0 + (*(unsigned short*) (p + 0x27)) * 0x21c;
			if (*(lpGebaeudePROT + *p * 0x24d) != 0x1e) {
				if (fcn_00505d00((char*) p, (int*) msg)) {
					for (a = 0; a < 2; a++) {
						for (j = 0; j < 12; j++) {
							f = fcn_0050b8d0(tile, *p, -1, a);
							v = (int) (((double) *(int*) (p + 0x3d) * g_6640e8) * f);
							id2 = ((int*) msg)[1 + a * 12 + j];
							if (id2 == 0xffff) {
								continue;
							}
							tile2 = g_7f4ca0 + id2 * 0x21c;
							r = (unsigned char*) *(int*) (tile2 + 0x184);
							if (r != 0) {
								r[0x8c] &= 0xfb;
							}
							else if (*(int*) (tile2 + 0x170) != 0) {
								q = (unsigned char*) sim_StartEntityQueryByType(*(unsigned char**) (tile2 + 0x170));
								if (q != 0 && *(int*) (q + 2) != -1) {
									count++;
									fcn_004fe470(*(int*) (tile2 + 4), *(int*) (*(int*) (tile2 + 0x170) + 1), *(int*) (q + 2), 0, 0);
								}
							}
							else {
								q = fcn_005049a0(p);
								if (q != 0 && *(int*) (q + 2) != -1) {
									count++;
									fcn_004fe470(*(int*) (tile2 + 4), *(int*) (p + 1), *(int*) (q + 2), 0, 0);
								}
							}
							if (*(unsigned char*) (tile2 + 2) != 0x14) {
								fcn_004c51a0(*(int*) (tile2 + 4), *(int*) (tile + 4), g_773d75, v);
							}
							count++;
							delta = 0;
							if (*(int*) (p + 0x3d) < 100) {
								if (fcn_0050f950(idx, *(unsigned short*) tile2) > -120) {
									b1 = (100 - *(int*) (p + 0x3d)) / 3;
									if (b1 < 1) {
										b1 = 1;
									}
									delta = (char) -b1;
								}
							}
							else if (*(int*) (p + 0x3d) > 100) {
								if (fcn_0050f950(idx, *(unsigned short*) tile2) < 100) {
									b1 = (*(int*) (p + 0x3d) - 100) / 3;
									if (b1 < 1) {
										b1 = 1;
									}
									delta = (char) b1;
								}
							}
							if (delta != 0) {
								count++;
								fcn_004c54c0(*(int*) (tile + 4), *(int*) (tile2 + 4), (int) delta, 0);
							}
							fcn_004c4510((char*) tile2, *(int*) (tile2 + 4));
							fcn_004c4570(4, 1, 0x19c, &v);
							fcn_004c5360();
							count++;
							b1 = fcn_0050f950(idx, *(unsigned short*) tile2) + delta;
							if (b1 < -26) {
								if (-((int) (gm_RandomMod(0x4a) & 0xffff)) > b1) {
									if (gm_RandomMod(100) > 0x32) {
										memset((msg + 0x1f0), 0, 0xf8);
										(msg + 0x1f0)[4] = 0x33;
										*(int*) ((msg + 0x1f0) + 8) = *(int*) (g_7f4ca0 + off + 4);
										*(int*) ((msg + 0x1f0) + 0xc) = *(int*) (p + 1);
										*(pos14_7f4c00*) ((msg + 0x1f0) + 0x28) = g_7f4c00;
										(msg + 0x1f0)[0x36] = 1;
										*(int*) ((msg + 0x1f0) + 0x58) = *(int*) (tile2 + 4);
										fcn_00500bb0((pos14_7f4c00*) ((msg + 0x1f0) + 0x28), (gm_RandomMod(6) & 0xffff) + 4, 0, 0);
										fcn_004c5530((msg + 0x1f0));
										count++;
									}
									else {
										memset((msg + 0xf8), 0, 0xf8);
										(msg + 0xf8)[4] = 0x34;
										*(int*) ((msg + 0xf8) + 8) = *(int*) (g_7f4ca0 + off + 4);
										*(int*) ((msg + 0xf8) + 0xc) = *(int*) (p + 1);
										*(pos14_7f4c00*) ((msg + 0xf8) + 0x28) = g_7f4c00;
										(msg + 0xf8)[0x36] = 1;
										*(int*) ((msg + 0xf8) + 0x58) = *(int*) (tile2 + 4);
										fcn_00500bb0((pos14_7f4c00*) ((msg + 0xf8) + 0x28), (gm_RandomMod(6) & 0xffff) + 4, 0, 0);
										fcn_004c5530((msg + 0xf8));
										count++;
									}
								}
								v = *(unsigned char*) (tile2 + 0x165);
								if (v == 2 || v == 1 || v == 0x13 || v == 0x14 || v == 0x10 || v == 0xf) {
									fcn_004c4510((char*) tile2, *(int*) (tile2 + 4));
									b1 = *(unsigned char*) (tile2 + 0x82);
									cv = (char) (int) ((double) b1 * g_664128 + g_662908);
									if (b1 > g_665368) {
										fcn_004c4570(1, 1, (int) (tile2 - g_aed32c) + 0x82, &cv);
									}
									b1 = *(unsigned char*) (tile2 + 0x83);
									cv = (char) (int) ((double) b1 * g_664128 + g_662908);
									if (b1 > g_665368) {
										fcn_004c4570(1, 1, (int) (tile2 - g_aed32c) + 0x83, &cv);
									}
									fcn_004c5360();
									count++;
								}
							}
						}
					}
					for (j = 0; j < 12; j++) {
						f = fcn_0050b8d0(tile, *p, -1, 0);
						v = (int) (((double) *(int*) (p + 0x3d) * g_6640e8) * f);
						id2 = ((int*) msg)[0x19 + j];
						if (id2 != 0xffff) {
							tile2 = g_7f4ca0 + id2 * 0x21c;
							fcn_004c51a0(*(int*) (tile2 + 4), *(int*) (tile + 4), g_773d75, v);
							fcn_004c4510((char*) tile2, *(int*) (tile2 + 4));
							fcn_004c4570(4, 1, 0x19c, &v);
							fcn_004c5360();
							count += 2;
						}
					}
				}
			}
			else {
				r = (unsigned char*) fcn_004ec7d0(p);
				if (r != 0) {
					v = fcn_004ee160((char*) p);
					fcn_004c51a0(*(int*) (r + 4), *(int*) (tile + 4), g_773d75, v);
					count++;
				}
			}
		}
		p = (unsigned char*) gm_FindNextFilteredEntity();
	}

	if (count > 0x20) {
		fcn_00535960();
		g_662068(0x14);
		count = 0;
	}
	p = (unsigned char*) gm_StartFilteredEntitySearch(1, 4, idx);
	while (p != 0) {
		if (fcn_0050c1b0(p, idx, out) != 0) {
			if (out[12]) {
				r = (unsigned char*) fcn_00502cd0(*(int*) (p + 0x5d), 2, 6, 0, 0xe8);
				if (r != 0) {
					v = fcn_0050b810(*(int*) (r + 0x14), (char) g_773d75);
					if (v > 0) {
						count++;
						fcn_004c5150(*(int*) (g_7f4ca0 + (*(unsigned short*) (p + 0x27)) * 0x21c + 4), *(int*) (r + 2), (char) g_773d75, v);
					}
				}
			}
			if (out[15]) {
				r = (unsigned char*) fcn_00502cd0(*(int*) (p + 0x5d), 1, 0, 0xf0);
				if (r != 0) {
					v = fcn_0050b810(*(int*) (r + 0x14), (char) g_773d75);
					if (v > 0) {
						count++;
						fcn_004c5150(*(int*) (g_7f4ca0 + (*(unsigned short*) (p + 0x27)) * 0x21c + 4), *(int*) (r + 2), (char) g_773d75, v);
					}
				}
			}
		}
		p = (unsigned char*) gm_FindNextFilteredEntity();
		if (count > 0x20) {
			fcn_00535960();
			g_662068(0x14);
			count = 0;
		}
	}
}
