/*
 * Scene walk callback: advances the building animation clocks and the walk
 * state of one object.
 *
 * The millisecond stamp drives both halves. Half one walks the building
 * extension (stride 0x4a4, three 0x7c slots each) and advances the animation
 * clock of every live slot; half two walks the path state at o+0x1d0. Both
 * halves carry the fraction of the clock into the whole-unit counter, clamp
 * the frame cursor through fcn_004321a0, and finish by pushing the frame
 * position and rotation into the object.
 */

#include <math.h>

/* Native record strides: the walk frame is 0x58 bytes, the building frame
 * 0xc0. Indexing through these types is what turns the multiplies into the
 * lea chains MSVC emits for array subscripts. */
typedef struct WalkRec {
	char b[0x58];
} WalkRec;

typedef struct BldFrm {
	char b[0xc0];
} BldFrm;

typedef struct ClampBlk {
	int a;
	int b;
	int c;
} ClampBlk;

typedef struct Frame {
	unsigned char pad_00[3];	/* 0x00 */
	signed char sb;			/* 0x03 */
	float f14;			/* 0x04 */
	float f18;			/* 0x08 */
	int i0c;			/* 0x0c */
	float neg[3];			/* 0x10 */
	int i1c;			/* 0x1c */
	int i20;			/* 0x20 */
	int i24;			/* 0x24 */
	int i28;			/* 0x28 */
	int i2c;			/* 0x2c */
	int i30;			/* 0x30 */
	int i34;			/* 0x34 */
	int i38;			/* 0x38 */
	int i3c;			/* 0x3c */
	int i40;			/* 0x40 */
	float tan[3];			/* 0x44 */
	int i50;			/* 0x50 */
	int i54;			/* 0x54 */
	int i58;			/* 0x58 */
	int i5c;			/* 0x5c */
	int i60;			/* 0x60 */
	int i64;			/* 0x64 */
	int i68;			/* 0x68 */
	int i6c;			/* 0x6c */
	float vec[3];			/* 0x70 */
	int i7c;			/* 0x7c */
	int i80;			/* 0x80 */
	int i84;			/* 0x84 */
	int i88;			/* 0x88 */
	int i8c;			/* 0x8c */
	float out[3];			/* 0x90 */
	int i9c;			/* 0x9c */
	float tA0;			/* 0xa0 */
} Frame;

int __cdecl fcn_004321a0(ClampBlk flags, int v, int lo, int hi, int max);
void __cdecl fcn_00438ac0(char*, int);
void __cdecl fcn_00438b40(char*, float*);
void __cdecl fcn_00438cb0(char*, float*);
void __cdecl fcn_004311a0(char*, char*, int, int, int);
void __cdecl fcn_00431330(char*, char*, int, int, int);
void __cdecl fcn_00431dd0(char*, char*, int, int, float*);
void __cdecl fcn_00451340(float*, float*, float, float*);
void __cdecl fcn_00455140(char*, float*, float*);
float __cdecl fcn_004517e0(float, float, float, float, float);
int __cdecl CompareVector3WithinTolerance(float*, float*, float);
void __cdecl fcn_004321f0(void*, void*, void*);
void __cdecl fcn_004316c0(char*);
void __cdecl fcn_00433780(char*);
void __cdecl fcn_00435500(char*, char*);
char __cdecl fcn_0045cbe0(char*, unsigned int);


/* Native frame slots, addressed through the aggregate. */
#define now (*(unsigned int*) ((char*) fs + 0x58))
#define delta (*(int*) ((char*) fs + 0x20))
#define i (*(int*) ((char*) fs + 0x5c))
#define j (*(int*) ((char*) fs + 0x54))
#define boff (*(int*) ((char*) fs + 0x3c))
#define hi (*(int*) ((char*) fs + 0x08))
#define lo (*(int*) ((char*) fs + 0x50))
#define max (*(int*) ((char*) fs + 0x2c))
#define bit (*(int*) ((char*) fs + 0x60))
#define off (*(int*) ((char*) fs + 0x64))
#define r (*(int*) ((char*) fs + 0x68))
#define ext (*(char**) ((char*) fs + 0x7c))
#define frames (*(char**) ((char*) fs + 0x84))
#define sfr (*(char**) ((char*) fs + 0x8c))
#define bld (*(char**) ((char*) fs + 0x1c))
#define cnt (*(int*) ((char*) fs + 0x24))
#define n (*(int*) ((char*) fs + 0x28))
#define saved (*(int*) ((char*) fs + 0x34))
#define g (*(float*) ((char*) fs + 0x6c))
#define t (*(float*) ((char*) fs + 0xa0))

#define SI(p) (*(int*) (p))
#define SF(p) (*(float*) (p))
#define SB(p) (*(unsigned char*) (p))
#define SP(p) (*(char**) (p))
#define QI(p, n) (*(int*) ((char*) (p) + (n)))
#define WR(e) ((char*) ((WalkRec*) (sfr) + (e)))
#define BF(e) ((char*) ((BldFrm*) (frames) + (e)))

/* ADDRESS: GOLDTL 0x00432480 */
char __cdecl fcn_00432480(char* o, void* ctx)
{
	Frame frame;
	Frame* fs;
	char* slot;
	char* owner;
	char* st;
	int flags;
	int cur;
	int prev;
	char* nd;
	float f;

	fs = &frame;
	prev = SI(o + 0x40);
	now = (unsigned int) ctx & 0x7fffffff;
	delta = (int) now - prev;
	SI(o + 0x40) = (int) now;
	if (delta == 0) {
		return 1;
	}
	ext = SP(o + 0x1ec);
	if (ext != 0) {
		if ((int) ctx >= 0 && SI(o + 0x1cc) != 0 &&
		    !(SB(ext + 0x163d) & 0x40) && SI(o + 0x218) == 4) {
			fcn_0045cbe0(o, now);
		}
		n = (unsigned char) SB(ext + 0x163c);
		if (n != 0) {
			i = 0;
			boff = 0;
	bldloop:
			bld = ext + boff;
			if (SB(bld + 0x594) != 0) {
				j = 0;
	slotloop:
				slot = bld + 0x41c + j;
				owner = SP(slot + 0x68);
				if (owner == 0 || !(SB(slot + 0x74) & 2)) {
					goto slotnext;
				}
				flags = SB(slot + 0x6d);
				lo = SI(owner + 0x150);
				if (flags & 0x10) {
					hi = SI(owner + 0x148) - 1;
					if (SB(owner + 0x169) == 0) {
						SI(slot + 0xc) = 0;
					}
				} else {
					hi = SI(owner + 0x154);
				}
				max = SI(owner + 0x148);
				SB(slot + 0x6d) = (unsigned char) (flags & ~0x20);
				SI(owner + 0x158) = SI(0x6b8008);
				fcn_00438ac0(o, 1);

				/* interval to clock fraction */
				cur = SI(slot + 0x34);
				prev = SI(slot + 0x38);
				fs->sb = 0;
				if (cur != prev) {
					if (prev > (int) now) {
						SF(slot + 0x40) = SF(slot + 0x44) +
							(SF(slot + 0x48) - SF(slot + 0x44)) *
							((float) (unsigned int) ((int) now - cur) /
							 (float) (prev - cur));
					} else {
						f = SF(slot + 0x48);
						SI(slot + 0x38) = 0;
						SI(slot + 0x34) = 0;
						SF(slot + 0x40) = f;
						if (f == 0.0f) {
							fs->sb = 1;
						}
					}
				}

				/* clock carry */
				flags = SB(slot + 0x74);
				bit = (flags >> 1) & 1;
				f = (float) bit * SF(slot + 0x60) * (float) delta +
					SF(slot + 0x64);
				SF(slot + 0x64) = f;
				if (SB(slot + 0x6d) & 2) {
					SI(slot + 8) -= (int) f;
				} else {
					SI(slot + 8) += (int) f;
				}
				SF(slot + 0x64) = f - (float) (int) f;

				/* cursor step, retried until the cursor lands in range */
	adv:
				flags = SB(slot + 0x6d);
				if (flags & 2) {
					if (SI(slot + 8) >= 0) {
						goto geom;
					}
					if (SI(slot + 4) > lo) {
						SI(slot) = SI(slot) - 1;
						SI(slot + 4) = fcn_004321a0(
							*(ClampBlk*) (slot + 0x6c),
							SI(slot), lo, hi, max);
						frames = SP(owner + 0x15c);
						SI(slot + 8) = QI(frames +
							SI(slot + 4) * 0xc0, 4) + SI(slot + 8);
						goto geom;
					}
					SB(slot + 0x74) &= ~0x10;
					if (flags & 1) {
						SI(slot + 8) = -SI(slot + 8);
						SI(slot) = lo;
						flags &= ~2;
						SB(slot + 0x6d) = (unsigned char) flags;
						SI(slot + 4) = fcn_004321a0(
							*(ClampBlk*) (slot + 0x6c),
							lo, lo, hi, max);
						if ((unsigned char) SB(slot + 0x6c) > 0) {
							SB(slot + 0x6c) = (unsigned char)
								(SB(slot + 0x6c) - 1);
							if (SB(slot + 0x6c) == 1) {
								SB(slot + 0x6d) |= 0x10;
							}
						}
						goto geom;
					}
					if ((unsigned char) SB(slot + 0x6c) > 0) {
						SB(slot + 0x6c) = (unsigned char)
							(SB(slot + 0x6c) - 1);
						if (SB(slot + 0x6c) == 1) {
							SB(slot + 0x6d) |= 0x10;
						}
					}
					SI(slot) = hi;
					frames = SP(owner + 0x15c);
					SI(slot + 8) = QI(BF(hi), 4) + SI(slot + 8);
					goto clamp1;
				}

				/* forward step */
				frames = SP(owner + 0x15c);
				cur = SI(slot);
				if (SI(slot + 8) < QI(BF(cur), 4)) {
					goto geom;
				}
				prev = cur + 1;
				if (prev < hi) {
					SI(slot + 8) -= QI(BF(cur), 4);
					SI(slot) = prev;
				} else if (flags & 0x10) {
					SI(slot + 8) = QI(BF(cur), 4) - 1;
					saved = hi;
					fs->sb = 1;
				} else if (flags & 1) {
					SB(slot + 0x6d) = (unsigned char) (flags | 2);
					SI(slot) = SI(slot + 4);
					SI(slot + 8) = QI(BF(cur), 4) -
						((SB(slot + 0x74) >> 1) & 1) - 1;
					if ((unsigned char) SB(slot + 0x6c) > 0) {
						SB(slot + 0x6c) = (unsigned char)
							(SB(slot + 0x6c) - 1);
						if (SB(slot + 0x6c) == 1) {
							SB(slot + 0x6d) |= 0x10;
						}
					}
				} else {
					SB(slot + 0x74) &= ~0x10;
					if ((unsigned char) SB(slot + 0x6c) > 0) {
						SB(slot + 0x6c) = (unsigned char)
							(SB(slot + 0x6c) - 1);
						if (SB(slot + 0x6c) == 1) {
							SB(slot + 0x6d) |= 0x10;
						}
					}
					SI(slot + 8) -= QI(BF(cur), 4);
					SI(slot) = lo;
					if (SB(owner + 0x169) == 0) {
						fcn_004311a0(o, slot, SI(slot + 0xc), hi,
							(SI(slot + 0x70) << 30) >> 30);
					}
				}
	clamp1:
				SI(slot + 4) = fcn_004321a0(*(ClampBlk*) (slot + 0x6c),
					SI(slot), lo, hi, max);

	geom:
				if (SB(slot + 0x74) & 4) {
					frames = SP(owner + 0x15c);
					cur = SI(slot);
					r = QI(BF(cur), 4) / 2;
					if (SI(slot + 8) >= 0 &&
					    SI(slot + 8) < QI(BF(cur), 4)) {
						r = SI(slot + 8);
					}
					fcn_00431dd0(o, slot, cur, r, fs->out);
					if (fabs(fs->out[0] - SF(slot + 0x4c)) <
					    SF(slot + 0x5c) &&
					    fabs(fs->out[2] - SF(slot + 0x54)) <
					    SF(slot + 0x5c)) {
						SB(slot + 0x74) |= 8;
						SI(slot + 8) = r;
						fs->sb = 1;
					}
				}
				if (fs->sb) {
					goto post;
				}
				off = SI(slot + 8);
				if (off < 0) {
					goto adv;
				}
				frames = SP(owner + 0x15c);
				if (off >= QI(BF(SI(slot)), 4)) {
					if (!(SB(slot + 0x6d) & 2)) {
						goto adv;
					}
				}
				if (off < QI(BF(SI(slot + 4)), 4)) {
					goto post;
				}
				if (SB(slot + 0x6d) & 2) {
					goto adv;
				}

	post:
				if (SB(owner + 0x169) == 0) {
					fcn_00431330(o, slot, SI(slot + 8), SI(slot),
						(SI(slot + 0x70) << 30) >> 30);
				}
				if (SI(slot + 0x14) != -1 && SI(slot + 0x18) != -1 &&
				    SI(slot + 0x1c) != -1 && SI(slot + 0x30) != 0 &&
				    SI(slot) >= SI(slot + 0x14)) {
					cur = SI(slot);
					if (cur >= SI(slot + 0x18)) {
						if (SB(slot + 0x74) & 0x40) {
							SB(slot + 0x74) &= ~0x40;
							SI(slot + 0x30) = 0;
							SI(slot + 0x1c) = -1;
							SI(slot + 0x18) = -1;
							SI(slot + 0x14) = -1;
						}
					} else {
						if (!(SB(slot + 0x74) & 0x40)) {
							SB(slot + 0x74) |= 0x40;
							SI(slot + 0x20) = QI(SP(slot + 0x30), 0x4c);
							SI(slot + 0x24) = QI(SP(slot + 0x30), 0x50);
							SI(slot + 0x28) = QI(SP(slot + 0x30), 0x54);
						}
						frames = SP(owner + 0x15c);
						prev = SI(slot + 4);
						t = (float) SI(slot + 8) /
							(float) QI(BF(cur), 4);
						fcn_00451340(
							(float*) (BF(cur) +
								SI(slot + 0x1c) * 0x18 + 0x54),
							(float*) (BF(prev) +
								SI(slot + 0x1c) * 0x18 + 0x54),
							t, fs->vec);
						fs->tan[0] = SF(BF(SI(slot + 0x14)) +
							SI(slot + 0x1c) * 0x18 + 0x54) - fs->vec[0];
						fs->tan[1] = SF(BF(SI(slot + 0x14)) +
							SI(slot + 0x1c) * 0x18 + 0x58) - fs->vec[1];
						fs->tan[2] = SF(BF(SI(slot + 0x14)) +
							SI(slot + 0x1c) * 0x18 + 0x5c) - fs->vec[2];
						fcn_00455140(o, fs->tan, fs->vec);
						nd = SP(slot + 0x30);
						fs->vec[0] = fs->vec[2] * SF(nd + 0x1ac) +
							fs->vec[1] * SF(nd + 0x19c) +
							fs->vec[0] * SF(nd + 0x18c) + SF(slot + 0x20);
						fs->vec[1] = fs->vec[2] * SF(nd + 0x1b0) +
							fs->vec[1] * SF(nd + 0x1a0) +
							fs->vec[0] * SF(nd + 0x190) + SF(slot + 0x24);
						fs->vec[2] = fs->vec[2] * SF(nd + 0x1b4) +
							fs->vec[1] * SF(nd + 0x1a4) +
							fs->vec[0] * SF(nd + 0x194) + SF(slot + 0x28);
						fcn_00438b40(o, fs->vec);
					}
				}

				if (fs->sb) {
					SB(slot + 0x74) &= ~2;
					if (!(SB(slot + 0x6d) & 8)) {
						if (SB(owner + 0x169) == 0) {
							fcn_004311a0(o, slot, SI(slot + 0xc),
								saved,
								(SI(slot + 0x70) << 30) >> 30);
						}
						fcn_00435500(ext + boff + 0xf4, owner);
					} else {
						SB(slot + 0x6d) |= 0x20;
					}
				}

	slotnext:
				j += 0x7c;
				if (j < 0x174) {
					goto slotloop;
				}
			}
			i++;
			boff += 0x4a4;
			if (i < n) {
				goto bldloop;
			}
		}
	}

	/* half two: walk state */
	fcn_004316c0(o);
	st = SP(o + 0x1d0);
	if (st == 0) {
		return 1;
	}
	if (!(SB(st + 0x34) & 2)) {
		return 1;
	}
	cnt = SI(st);
	sfr = SP(st + 0x40);
	flags = SB(st + 0x2d);
	SB(st + 0x2d) = (unsigned char) (flags & ~0x20);
	bit = ((flags & ~0x20) >> 1) & 1;
	if (bit) {
		cur = SI(st + 8);
		fs->f18 = (float) SI(st + 0xc) / (float) QI(WR(cur), 0);
		fs->f14 = 1.0f - fs->f18;
	} else {
		cur = SI(st + 4);
		fs->f14 = (float) SI(st + 0xc) / (float) QI(WR(cur), 0);
		fs->f18 = 1.0f - fs->f14;
	}

	if (SB(st + 0x2d) & 4) {
		if (bit) {
			prev = SI(st + 4);
			cur = SI(st + 8);
			fs->neg[0] = -SF(WR(cur) + 0x20);
			fs->neg[1] = -SF(WR(cur) + 0x24);
			fs->neg[2] = -SF(WR(cur) + 0x28);
			fs->tan[0] = -SF(WR(cur) + 0x30);
			fs->tan[1] = -SF(WR(cur) + 0x34);
			fs->tan[2] = -SF(WR(cur) + 0x38);
			fs->vec[0] = fcn_004517e0(SF(sfr + prev * 0x58 + 4),
				SF(sfr + cur * 0x58 + 4), fs->tan[0], fs->neg[0], fs->f14);
			fs->vec[1] = fcn_004517e0(SF(sfr + prev * 0x58 + 8),
				SF(sfr + cur * 0x58 + 8), fs->tan[1], fs->neg[1], fs->f14);
			fs->vec[2] = fcn_004517e0(SF(WR(prev) + 0xc),
				SF(WR(cur) + 0xc), fs->tan[2], fs->neg[2], fs->f14);
			fs->vec[0] += SF(st + 0x14);
			fs->vec[1] += SF(st + 0x18);
			fs->vec[2] += SF(st + 0x1c);
			fcn_00438b40(o, fs->vec);
			if (SI(o + 0x218) < 5) {
				fs->neg[0] = -SF(WR(cur) + 0x40);
				fs->neg[1] = -SF(WR(cur) + 0x44);
				fs->neg[2] = -SF(WR(cur) + 0x48);
				fs->tan[0] = -SF(WR(cur) + 0x4c);
				fs->tan[1] = -SF(WR(cur) + 0x50);
				fs->tan[2] = -SF(WR(cur) + 0x54);
				fs->vec[0] = fcn_004517e0(SF(WR(prev) + 0x14),
					SF(WR(cur) + 0x14), fs->tan[0], fs->neg[0], fs->f14);
				fs->vec[1] = fcn_004517e0(SF(WR(prev) + 0x18),
					SF(WR(cur) + 0x18), fs->tan[1], fs->neg[1], fs->f14);
				fs->vec[2] = fcn_004517e0(SF(WR(prev) + 0x1c),
					SF(WR(cur) + 0x1c), fs->tan[2], fs->neg[2], fs->f14);
				fs->vec[0] += SF(st + 0x20);
				fs->vec[1] += SF(st + 0x24);
				fs->vec[2] += SF(st + 0x28);
				fcn_00438cb0(o, fs->vec);
			}
		} else {
			prev = SI(st + 4);
			cur = SI(st + 8);
			g = fs->f18;
			fs->vec[0] = fcn_004517e0(SF(sfr + cur * 0x58 + 4),
				SF(sfr + prev * 0x58 + 4),
				-SF(WR(prev) + 0x30),
				-SF(WR(prev) + 0x20), g);
			fs->vec[1] = fcn_004517e0(SF(sfr + cur * 0x58 + 8),
				SF(sfr + prev * 0x58 + 8),
				-SF(WR(prev) + 0x34),
				-SF(WR(prev) + 0x24), g);
			fs->vec[2] = fcn_004517e0(SF(WR(cur) + 0xc),
				SF(WR(prev) + 0xc),
				-SF(WR(prev) + 0x38),
				-SF(WR(prev) + 0x28), g);
			fs->vec[0] += SF(st + 0x14);
			fs->vec[1] += SF(st + 0x18);
			fs->vec[2] += SF(st + 0x1c);
			fcn_00438b40(o, fs->vec);
			if (SI(o + 0x218) < 5) {
				fs->vec[0] = fcn_004517e0(SF(WR(cur) + 0x14),
					SF(WR(prev) + 0x14),
					-SF(WR(prev) + 0x4c),
					-SF(WR(prev) + 0x40), g);
				fs->vec[1] = fcn_004517e0(SF(WR(cur) + 0x18),
					SF(WR(prev) + 0x18),
					-SF(WR(prev) + 0x50),
					-SF(WR(prev) + 0x44), g);
				fs->vec[2] = fcn_004517e0(SF(WR(cur) + 0x1c),
					SF(WR(prev) + 0x1c),
					-SF(WR(prev) + 0x54),
					-SF(WR(prev) + 0x48), g);
				fs->vec[0] += SF(st + 0x20);
				fs->vec[1] += SF(st + 0x24);
				fs->vec[2] += SF(st + 0x28);
				fcn_00438cb0(o, fs->vec);
			}
		}
	} else {
		prev = SI(st + 4);
		cur = SI(st + 8);
		fs->vec[0] = SF(sfr + prev * 0x58 + 4) * fs->f18 +
			SF(sfr + cur * 0x58 + 4) * fs->f14;
		fs->vec[1] = SF(sfr + prev * 0x58 + 8) * fs->f18 +
			SF(sfr + cur * 0x58 + 8) * fs->f14;
		fs->vec[2] = SF(WR(prev) + 0xc) * fs->f18 +
			SF(WR(cur) + 0xc) * fs->f14;
		if (CompareVector3WithinTolerance(fs->vec, (float*) 0x662d70, 0.0f) == 0) {
			fs->vec[0] += SF(st + 0x14);
			fs->vec[1] += SF(st + 0x18);
			fs->vec[2] += SF(st + 0x1c);
			fcn_00438b40(o, fs->vec);
		}
		if (SI(o + 0x218) < 5) {
			fs->vec[0] = SF(WR(prev) + 0x14) * fs->f18 +
				SF(WR(cur) + 0x14) * fs->f14 +
				SF(st + 0x20);
			fs->vec[1] = SF(WR(prev) + 0x18) * fs->f18 +
				SF(WR(cur) + 0x18) * fs->f14 +
				SF(st + 0x24);
			fs->vec[2] = SF(WR(prev) + 0x1c) * fs->f18 +
				SF(WR(cur) + 0x1c) * fs->f14 +
				SF(st + 0x28);
			fcn_00438cb0(o, fs->vec);
		}
	}

	/* drop the frame table of the segment that just ended */
	flags = SB(st + 0x2d);
	fs->sb = 0;
	if ((flags & 4) && (flags & 0x10) && !(flags & 1) &&
	    !(SB(st + 0x34) & 0x20)) {
		cur = SI(st);
		if (SI(st + 4) < cur - 1) {
			SB(st + 0x34) |= 0x20;
			sfr = SP(st + 0x40) + cur * 0x58;
			SI(sfr - 0x38) = 0;
			SI(sfr - 0x34) = 0;
			SI(sfr - 0x30) = 0;
			SI(sfr - 0x80) = 0;
			SI(sfr - 0x7c) = 0;
			SI(sfr - 0x78) = 0;
			SI(sfr - 0x18) = 0;
			SI(sfr - 0x14) = 0;
			SI(sfr - 0x10) = 0;
			SI(sfr - 0x64) = 0;
			SI(sfr - 0x60) = 0;
			SI(sfr - 0x5c) = 0;
		}
	}

	/* walk clock carry */
	flags = SB(st + 0x34);
	bit = (flags >> 1) & 1;
	f = (float) bit * SF(st + 0x38) * (float) delta + SF(st + 0x3c);
	SF(st + 0x3c) = f;
	if (SB(st + 0x2d) & 2) {
		SI(st + 0xc) -= (int) f;
	} else {
		SI(st + 0xc) += (int) f;
	}
	SF(st + 0x3c) = f - (float) (int) f;

	sfr = SP(st + 0x40);
	flags = SB(st + 0x2d);
adv2:
	if (flags & 2) {
		if (SI(st + 0xc) >= 0) {
			goto chk2;
		}
		if (SI(st + 8) > 0) {
			goto back2;
		}
		if (flags & 0x10) {
			SI(st + 4) = 0;
			SI(st + 0xc) = 0;
			fs->sb = 1;
			goto cl2;
		}
		if (flags & 1) {
			SI(st + 0xc) = -SI(st + 0xc);
			SB(st + 0x34) &= ~0x10;
			SB(st + 0x2d) = (unsigned char) (flags & ~2);
			SI(st + 4) = 0;
			goto dec2c;
		}
		prev = cnt - 1;
		SI(st + 4) = prev;
		SI(st + 0xc) = SI(st + 0xc) + QI(WR(prev), 0);
		SB(st + 0x34) &= ~0x10;
		goto dec2c;
	back2:
		prev = SI(st + 4) - 1;
		if (prev == 0 && (flags & 0x10)) {
			fs->sb = 1;
			SI(st + 4) = 0;
			SI(st + 0xc) = 0;
			goto cl2;
		}
		SB(st + 0x34) &= ~0x10;
		SI(st + 0xc) = SI(st + 0xc) + QI(sfr + SI(st + 8) * 0x58, 0);
		SI(st + 4) = prev;
		goto cl2;
	dec2c:
		if ((unsigned char) SB(st + 0x2c) > 0) {
			SB(st + 0x2c) = (unsigned char) (SB(st + 0x2c) - 1);
			if (SB(st + 0x2c) == 1) {
				SB(st + 0x2d) |= 0x10;
			}
		}
	cl2:
		SI(st + 8) = fcn_004321a0(*(ClampBlk*) (st + 0x2c),
			SI(st + 4), 0, cnt - 1, cnt);
		goto place2;
	}

	/* forward step */
	cur = SI(st + 4);
	off = SI(st + 0xc);
	if (off < QI(WR(cur), 0)) {
		goto chk2;
	}
	prev = cur + 1;
	if (prev < cnt - 1) {
		goto fwd2;
	}
	if (!(flags & 1)) {
		goto fwd2;
	}
	SB(st + 0x2d) = (unsigned char) (flags | 2);
	SI(st + 4) = SI(st + 8);
	SI(st + 0xc) = QI(WR(cur), 0) -
		((SB(st + 0x34) >> 1) & 1) - 1;
	goto cl2b;
fwd2:
	if (cur < cnt - 1) {
		if (!(prev < cnt - 1)) {
			if (!(flags & 0x10)) {
				goto prune;
			}
			if (!(flags & 1)) {
				goto reset;
			}
		}
	prune:
		if ((SB(st + 0x34) & 0x10) && !(flags & 0x11) && (flags & 4)) {
			fcn_004321f0(sfr + (SI(st) - 1) * 0x58, sfr, sfr + 0x58);
			SB(st + 0x34) &= ~0x10;
		}
		SI(st + 0xc) = SI(st + 0xc) - QI(sfr + SI(st + 4) * 0x58, 0);
		SI(st + 4) = SI(st + 4) + 1;
		goto cl2b;
	}

reset:
	if (flags & 0x10) {
		if (flags & 1) {
			SB(st + 0x2d) = (unsigned char) (flags | 2);
			SI(st + 4) = SI(st + 8);
			SI(st + 0xc) = QI(WR(cur), 0) -
				((SB(st + 0x34) >> 1) & 1) - 1;
			goto cl2b;
		}
		SI(st) = SI(st) - 1;
		fs->sb = 1;
		SI(st + 4) = SI(st);
		SI(st + 0xc) = QI(sfr + SI(st + 4) * 0x58, 0) - 1;
		goto cl2b;
	}
	if (flags & 1) {
		SB(st + 0x2d) = (unsigned char) (flags | 2);
		SI(st + 4) = SI(st + 8);
		SI(st + 0xc) = QI(WR(cur), 0) -
			((SB(st + 0x34) >> 1) & 1) - 1;
		goto cl2b;
	}
	SI(st + 0xc) = off - QI(WR(cur), 0);
	SI(st + 4) = 0;
	if ((unsigned char) SB(st + 0x2c) > 0) {
		SB(st + 0x2c) = (unsigned char) (SB(st + 0x2c) - 1);
		if (SB(st + 0x2c) == 1) {
			SB(st + 0x2d) |= 0x10;
		}
	}

cl2b:
	SI(st + 8) = fcn_004321a0(*(ClampBlk*) (st + 0x2c),
		SI(st + 4), 0, cnt - 1, cnt);
	goto place2;

place2:
	if (fs->sb) {
		frames = sfr + SI(st + 8) * 0x58;
		fs->vec[0] = SF(frames + 4) + SF(st + 0x14);
		fs->vec[1] = SF(frames + 8) + SF(st + 0x18);
		fs->vec[2] = SF(frames + 0xc) + SF(st + 0x1c);
		fcn_00438b40(o, fs->vec);
		fs->vec[0] = SF(frames + 0x14) + SF(st + 0x20);
		fs->vec[1] = SF(frames + 0x18) + SF(st + 0x24);
		fs->vec[2] = SF(frames + 0x1c) + SF(st + 0x28);
		fcn_00438cb0(o, fs->vec);
		if (SB(st + 0x2d) & 8) {
			SB(st + 0x34) &= ~2;
			SB(st + 0x2d) |= 0x20;
			return 1;
		}
		fcn_00433780(o);
		return 1;
	}

chk2:
	if (SI(st + 0xc) < 0) {
		flags = SB(st + 0x2d);
		goto adv2;
	}
	if (SI(st + 0xc) >= QI(sfr + SI(st + 4) * 0x58, 0)) {
		if (!(SB(st + 0x2d) & 2)) {
			flags = SB(st + 0x2d);
			goto adv2;
		}
	}
	if (SI(st + 0xc) >= QI(sfr + SI(st + 8) * 0x58, 0)) {
		return 1;
	}
	if (SB(st + 0x2d) & 2) {
		flags = SB(st + 0x2d);
		goto adv2;
	}
	return 1;
}
