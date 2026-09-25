// GLOBAL: GOLDTL 0x662910
extern float g_662910;
// GLOBAL: GOLD 0x5eb7f0
extern float g_662910;

/* Owned (both targets) by src/GOLDTL.fcn_005b24b0.c. */
extern unsigned char g_773d75;

void* __cdecl fcn_00508e40(int);
int __cdecl fcn_0050dac0(unsigned short);
void __cdecl fcn_004ae080(char*, char*, int*, int*);
int __cdecl fcn_0064eeec(char*);
int __cdecl fcn_0050b710(int, unsigned char);
void __cdecl fcn_0051af00(void*, int, ...);

// SIZE 0x21c
typedef struct {
	unsigned short id;
	char pad0[2];
	int key;
	unsigned char active;
	unsigned char side;
	char pad1[0x15a];
	unsigned char cls;
	char pad1b;
	unsigned char kind;
	char pad2[2];
	unsigned char grade;
	char pad3[0xb2];
} Rec21c;

extern Rec21c g_7f4ca0[768];

int __cdecl fcn_004ae0f0(int);
unsigned short __cdecl fcn_0042e410(int);

// FUNCTION: GOLDTL 0x4ae130
// SIZE: 60

/* The original translation unit held this callee in the same file as
 * fcn_004af2f0, and msvc6's same-TU callee analysis is what keeps `w` in edx
 * across the call site below; without the body in view the allocator spills
 * `w` to a callee-saved register (object 267 bytes instead of 264). */
int __cdecl fcn_004ae130(unsigned short a1)
{
	int o;

	o = (a1 & 0xffff) * 540;
	if (*(unsigned short*) (0x7f4ca0 + o) != 0xffff
	    && *(unsigned char*) (0x7f4ca8 + o) > 0
	    && *(unsigned char*) (0x7f4ca2 + o) < 0xa) {
		return 1;
	}
	return 0;
}

// FUNCTION: GOLDTL 0x4ae1c0
// SIZE: 70

int __cdecl fcn_004ae1c0(int a1)
{
	unsigned char c;
	unsigned char f;

	a1 &= 0xffff;
	if (*(unsigned short*) (0x7f4ca0 + a1 * 540) == 0xffff) {
		return 0;
	}
	c = *(unsigned char*) (0x7f4ca8 + a1 * 540);
	if (c <= 0) {
		return 0;
	}
	f = *(unsigned char*) (0x7f4ca2 + a1 * 540);
	if (f < 0xa && f != 6 && f != 7) {
		return 1;
	}
	return 0;
}

// FUNCTION: GOLDTL 0x4ae210
// SIZE: 65

int __cdecl fcn_004ae210(int a1)
{
	unsigned char c;
	unsigned char f;

	a1 &= 0xffff;
	if (*(unsigned short*) (0x7f4ca0 + a1 * 540) != 0xffff) {
		c = *(unsigned char*) (0x7f4ca8 + a1 * 540);
		if (c > 0) {
			f = *(unsigned char*) (0x7f4ca2 + a1 * 540);
			if (f == 6 || f == 7) {
				return 1;
			}
		}
	}
	return 0;
}

// FUNCTION: GOLDTL 0x4ae2a0
// SIZE: 273

#pragma optimize("y", off)
int __cdecl fcn_004ae2a0(int mode, int* pairs, int idx, char* text, void* out)
{
	char buf[0x200];
	Rec21c* r;
	int i;
	int p;
	int n;

	if (mode == 1) {
		r = (Rec21c*) fcn_00508e40(pairs[idx * 2 + 1]);
		if (r == 0 || r->active == 0 || r->kind != 0xf) {
			return 0;
		}
	} else {
		for (i = 0; ; i++) {
			if (i >= 768) {
				return 0;
			}
			if (fcn_004ae130((unsigned short) i) != 0 && g_7f4ca0[i].kind == 0xf) {
				break;
			}
		}
		r = &g_7f4ca0[i];
		if (mode == 0) {
			pairs[idx * 2 + 1] = r->key;
		}
		if (r == 0) {
			return 0;
		}
	}
	n = 0x200;
	p = (int) buf;
	__asm {
		mov edi, p
		mov ebx, n
		xor eax, eax
		lea ecx, [edi+edi*2]
		and ecx, 3
		sub ebx, ecx
		jle short L1
		rep stosb
		mov ecx, ebx
		and ebx, 3
		shr ecx, 2
		rep stosd
	L1:
		add ecx, ebx
		rep stosb
	}
	fcn_004ae080(text, buf, &p, &n);
	fcn_0051af00(out, (int) buf, r->id);
	return 1;
}
#pragma optimize("", on)

// FUNCTION: GOLDTL 0x4ae3c0
// SIZE: 278

#pragma optimize("y", off)
int __cdecl fcn_004ae3c0(int mode, int* pairs, int idx, char* text, void* out)
{
	char buf[0x200];
	Rec21c* r;
	int i;
	int p;
	int n;

	if (mode == 1) {
		r = (Rec21c*) fcn_00508e40(pairs[idx * 2 + 1]);
		if (r == 0 || r->active == 0 || r->kind != 0x15) {
			return 0;
		}
	} else {
		for (i = 0; ; i++) {
			if (i >= 768) {
				return 0;
			}
			if ((fcn_004ae130((unsigned short) i) != 0 && g_7f4ca0[i].kind == 0x1a) || g_7f4ca0[i].kind == 0x15) {
				break;
			}
		}
		r = &g_7f4ca0[i];
		if (mode == 0) {
			pairs[idx * 2 + 1] = r->key;
		}
		if (r == 0) {
			return 0;
		}
	}
	n = 0x200;
	p = (int) buf;
	__asm {
		mov edi, p
		mov ebx, n
		xor eax, eax
		lea ecx, [edi+edi*2]
		and ecx, 3
		sub ebx, ecx
		jle short L1
		rep stosb
		mov ecx, ebx
		and ebx, 3
		shr ecx, 2
		rep stosd
	L1:
		add ecx, ebx
		rep stosb
	}
	fcn_004ae080(text, buf, &p, &n);
	fcn_0051af00(out, (int) buf, r->id);
	return 1;
}
#pragma optimize("", on)

// FUNCTION: GOLD 0x4ae3a0
// SIZE: 608
// FUNCTION: GOLDTL 0x4ae4e0
// SIZE: 608

#pragma optimize("y", off)
int __cdecl fcn_004ae4e0(int mode, int* pairs, int idx, char* text, void* out)
{
	char buf[0x200];
	Rec21c* r;
	Rec21c* found;
	int sel;
	int j;
	int left;
	int n;
	int p;

	n = 0x200;
	p = (int) buf;
	__asm {
		mov edi, p
		mov ebx, n
		xor eax, eax
		lea ecx, [edi+edi*2]
		and ecx, 3
		sub ebx, ecx
		jle short L1
		rep stosb
		mov ecx, ebx
		and ebx, 3
		shr ecx, 2
		rep stosd
	L1:
		add ecx, ebx
		rep stosb
	}
	{
		int rest;

		fcn_004ae080(text, buf, &p, &rest);
		if (rest != 1 || (sel = fcn_0064eeec(text + p)) < 0 || sel > 2) {
			sel = 1;
		}
	}
	if (mode == 1) {
		r = (Rec21c*) fcn_00508e40(pairs[idx * 2 + 1]);
		if (r == 0 || r->active <= 0 || r->grade == 0) {
			return 0;
		}
		goto send;
	}
	if (sel == 0) {
		r = 0;
		j = fcn_0042e410(0x300);
		left = 0x300;
		do {
			if (fcn_004ae130((unsigned short) j) != 0 && g_7f4ca0[j].grade >= 0x1e && g_7f4ca0[j].grade <= 0x21) {
				r = &g_7f4ca0[j];
				break;
			}
			left--;
			j = (j + 1) % 0x300;
		} while (left != 0);
	} else if (sel == 1) {
		r = 0;
		j = fcn_0042e410(0x300);
		left = 0x300;
		do {
			if (fcn_004ae1c0(j) != 0 && g_7f4ca0[j].grade >= 0x1e && g_7f4ca0[j].grade <= 0x21) {
				r = &g_7f4ca0[j];
				break;
			}
			left--;
			j = (j + 1) % 0x300;
		} while (left != 0);
	} else {
		found = 0;
		r = 0;
		j = fcn_0042e410(0x300);
		left = 0x300;
		do {
			if (found == 0 && fcn_004ae1c0(j) != 0 && g_7f4ca0[j].grade >= 0x1e && g_7f4ca0[j].grade <= 0x21) {
				found = &g_7f4ca0[j];
			} else if (fcn_004ae210(j) != 0 && g_7f4ca0[j].grade >= 0x1e && g_7f4ca0[j].grade <= 0x21) {
				r = &g_7f4ca0[j];
				break;
			}
			left--;
			j = (j + 1) % 0x300;
		} while (left != 0);
		if (r == 0) {
			r = found;
		}
	}
	if (r == 0) {
		return 0;
	}
	if (mode == 0) {
		pairs[idx * 2 + 1] = r->key;
	}
send:
	fcn_0051af00(out, (int) buf, r->id);
	return 1;
}
#pragma optimize("", on)

// FUNCTION: GOLDTL 0x4ae740
// SIZE: 761

#pragma optimize("y", off)
int __cdecl fcn_004ae740(int mode, int* pairs, int idx, char* text, void* out)
{
	char buf[0x200];
	Rec21c* r;
	Rec21c* found;
	int sel;
	int j;
	int left;
	int next;
	int n;
	int p;

	n = 0x200;
	p = (int) buf;
	__asm {
		mov edi, p
		mov ebx, n
		xor eax, eax
		lea ecx, [edi+edi*2]
		and ecx, 3
		sub ebx, ecx
		jle short L1
		rep stosb
		mov ecx, ebx
		and ebx, 3
		shr ecx, 2
		rep stosd
	L1:
		add ecx, ebx
		rep stosb
	}
	{
		int rest;

		fcn_004ae080(text, buf, &p, &rest);
		if (rest != 1 || (sel = fcn_0064eeec(text + p)) < 0 || sel > 2) {
			sel = 1;
		}
	}
	if (mode == 1) {
		r = (Rec21c*) fcn_00508e40(pairs[idx * 2 + 1]);
		if (r == 0 || r->active <= 0 || r->kind == 0) {
			return 0;
		}
		goto send;
	}
	if (sel == 0) {
		r = 0;
		j = fcn_0042e410(0x300);
		left = 0x300;
		do {
			if (g_7f4ca0[j].side == 1 && fcn_004ae130((unsigned short) j) != 0 && fcn_004ae0f0(g_7f4ca0[j].key) != 0
			    && g_7f4ca0[j].kind > 0 && g_7f4ca0[j].kind != 0xf && g_7f4ca0[j].kind != 0x1a && g_7f4ca0[j].kind != 0x15) {
				r = &g_7f4ca0[j];
				break;
			}
			next = (j + 1) % 0x300;
			left--;
			j = next;
		} while (left != 0);
	} else if (sel == 1) {
		r = 0;
		j = fcn_0042e410(0x300);
		left = 0x300;
		do {
			if (g_7f4ca0[j].side == 1 && fcn_004ae1c0(j) != 0 && fcn_004ae0f0(g_7f4ca0[j].key) != 0
			    && g_7f4ca0[j].kind > 0 && g_7f4ca0[j].kind != 0xf && g_7f4ca0[j].kind != 0x1a && g_7f4ca0[j].kind != 0x15) {
				r = &g_7f4ca0[j];
				break;
			}
			next = (j + 1) % 0x300;
			left--;
			j = next;
		} while (left != 0);
	} else {
		found = 0;
		r = 0;
		j = fcn_0042e410(0x300);
		left = 0x300;
		do {
			if (g_7f4ca0[j].side == 1) {
				if (found == 0 && fcn_004ae1c0(j) != 0
				    && g_7f4ca0[j].kind > 0 && g_7f4ca0[j].kind != 0xf && g_7f4ca0[j].kind != 0x1a && g_7f4ca0[j].kind != 0x15) {
					if (fcn_004ae0f0(g_7f4ca0[j].key) != 0) {
						found = &g_7f4ca0[j];
					}
				} else if (fcn_004ae210(j) != 0 && fcn_004ae0f0(g_7f4ca0[j].key) != 0
				    && g_7f4ca0[j].kind > 0 && g_7f4ca0[j].kind != 0xf && g_7f4ca0[j].kind != 0x1a && g_7f4ca0[j].kind != 0x15) {
					r = &g_7f4ca0[j];
					break;
				}
			}
			next = (j + 1) % 0x300;
			left--;
			j = next;
		} while (left != 0);
		if (r == 0) {
			r = found;
		}
	}
	if (r == 0) {
		return 0;
	}
	if (mode == 0) {
		pairs[idx * 2 + 1] = r->key;
	}
send:
	fcn_0051af00(out, (int) buf, r->id);
	return 1;
}
#pragma optimize("", on)

// FUNCTION: GOLDTL 0x4aea40
// SIZE: 764

#pragma optimize("y", off)
int __cdecl fcn_004aea40(int mode, int* pairs, int idx, char* text, void* out)
{
	char buf[0x200];
	Rec21c* r;
	Rec21c* found;
	int sel;
	int j;
	int left;
	int next;
	int n;
	int p;

	n = 0x200;
	p = (int) buf;
	__asm {
		mov edi, p
		mov ebx, n
		xor eax, eax
		lea ecx, [edi+edi*2]
		and ecx, 3
		sub ebx, ecx
		jle short L1
		rep stosb
		mov ecx, ebx
		and ebx, 3
		shr ecx, 2
		rep stosd
	L1:
		add ecx, ebx
		rep stosb
	}
	{
		int rest;

		fcn_004ae080(text, buf, &p, &rest);
		if (rest != 1 || (sel = fcn_0064eeec(text + p)) < 0 || sel > 2) {
			sel = 1;
		}
	}
	if (mode == 1) {
		r = (Rec21c*) fcn_00508e40(pairs[idx * 2 + 1]);
		if (r == 0 || r->active <= 0 || r->kind == 0) {
			return 0;
		}
		goto send;
	}
	if (sel == 0) {
		r = 0;
		j = fcn_0042e410(0x300);
		left = 0x300;
		do {
			if (g_7f4ca0[j].side == 0 && fcn_004ae130((unsigned short) j) != 0
			    && g_7f4ca0[j].kind > 0 && g_7f4ca0[j].kind != 0xf && g_7f4ca0[j].kind != 0x1a && g_7f4ca0[j].kind != 0x15 && fcn_004ae0f0(g_7f4ca0[j].key) != 0) {
				r = &g_7f4ca0[j];
				break;
			}
			next = (j + 1) % 0x300;
			left--;
			j = next;
		} while (left != 0);
	} else if (sel == 1) {
		r = 0;
		j = fcn_0042e410(0x300);
		left = 0x300;
		do {
			if (g_7f4ca0[j].side == 0 && fcn_004ae1c0(j) != 0
			    && g_7f4ca0[j].kind > 0 && g_7f4ca0[j].kind != 0xf && g_7f4ca0[j].kind != 0x1a && g_7f4ca0[j].kind != 0x15 && fcn_004ae0f0(g_7f4ca0[j].key) != 0) {
				r = &g_7f4ca0[j];
				break;
			}
			next = (j + 1) % 0x300;
			left--;
			j = next;
		} while (left != 0);
	} else {
		found = 0;
		r = 0;
		j = fcn_0042e410(0x300);
		left = 0x300;
		do {
			if (g_7f4ca0[j].side == 0) {
				if (found == 0 && fcn_004ae1c0(j) != 0
				    && g_7f4ca0[j].kind > 0 && g_7f4ca0[j].kind != 0xf && g_7f4ca0[j].kind != 0x1a && g_7f4ca0[j].kind != 0x15) {
					if (fcn_004ae0f0(g_7f4ca0[j].key) != 0) {
						found = &g_7f4ca0[j];
					}
				} else if (fcn_004ae210(j) != 0
				    && g_7f4ca0[j].kind > 0 && g_7f4ca0[j].kind != 0xf && g_7f4ca0[j].kind != 0x1a && g_7f4ca0[j].kind != 0x15 && fcn_004ae0f0(g_7f4ca0[j].key) != 0) {
					r = &g_7f4ca0[j];
					break;
				}
			}
			next = (j + 1) % 0x300;
			left--;
			j = next;
		} while (left != 0);
		if (r == 0) {
			r = found;
		}
	}
	if (r == 0) {
		return 0;
	}
	if (mode == 0) {
		pairs[idx * 2 + 1] = r->key;
	}
send:
	fcn_0051af00(out, (int) buf, r->id);
	return 1;
}
#pragma optimize("", on)

// FUNCTION: GOLDTL 0x4aed40
// SIZE: 772

#pragma optimize("y", off)
int __cdecl fcn_004aed40(int mode, int* pairs, int idx, char* text, void* out)
{
	char buf[0x200];
	Rec21c* r;
	Rec21c* found;
	int sel;
	int j;
	int left;
	int next;
	int n;
	int p;

	n = 0x200;
	p = (int) buf;
	__asm {
		mov edi, p
		mov ebx, n
		xor eax, eax
		lea ecx, [edi+edi*2]
		and ecx, 3
		sub ebx, ecx
		jle short L1
		rep stosb
		mov ecx, ebx
		and ebx, 3
		shr ecx, 2
		rep stosd
	L1:
		add ecx, ebx
		rep stosb
	}
	{
		int rest;

		fcn_004ae080(text, buf, &p, &rest);
		if (rest != 1 || (sel = fcn_0064eeec(text + p)) < 0 || sel > 2) {
			sel = 1;
		}
	}
	if (mode == 2) {
		return 0;
	}
	if (mode == 1) {
		r = (Rec21c*) fcn_00508e40(pairs[idx * 2 + 1]);
		if (r == 0 || r->active <= 0 || r->kind == 0) {
			return 0;
		}
		goto send;
	}
	if (sel == 0) {
		r = 0;
		j = fcn_0042e410(0x300);
		left = 0x300;
		do {
			if (fcn_004ae130((unsigned short) j) != 0
			    && g_7f4ca0[j].kind > 0 && g_7f4ca0[j].kind != 0xf && g_7f4ca0[j].kind != 0x1a && g_7f4ca0[j].kind != 0x15 && fcn_004ae0f0(g_7f4ca0[j].key) != 0) {
				r = &g_7f4ca0[j];
				break;
			}
			next = (j + 1) % 0x300;
			left--;
			j = next;
		} while (left != 0);
	} else if (sel == 1) {
		r = 0;
		j = fcn_0042e410(0x300);
		left = 0x300;
		do {
			if (fcn_004ae1c0(j) != 0
			    && g_7f4ca0[j].kind > 0 && g_7f4ca0[j].kind != 0xf && g_7f4ca0[j].kind != 0x1a && g_7f4ca0[j].kind != 0x15 && fcn_004ae0f0(g_7f4ca0[j].key) != 0) {
				r = &g_7f4ca0[j];
				break;
			}
			next = (j + 1) % 0x300;
			left--;
			j = next;
		} while (left != 0);
	} else {
		found = 0;
		r = 0;
		j = fcn_0042e410(0x300);
		left = 0x300;
		do {
			if (found == 0 && fcn_004ae1c0(j) != 0
			    && g_7f4ca0[j].kind > 0 && g_7f4ca0[j].kind != 0xf && g_7f4ca0[j].kind != 0x1a && g_7f4ca0[j].kind != 0x15) {
				if (fcn_004ae0f0(g_7f4ca0[j].key) != 0) {
					found = &g_7f4ca0[j];
				}
			} else if (fcn_004ae210(j) != 0
			    && g_7f4ca0[j].kind > 0 && g_7f4ca0[j].kind != 0xf && g_7f4ca0[j].kind != 0x1a && g_7f4ca0[j].kind != 0x15 && fcn_004ae0f0(g_7f4ca0[j].key) != 0) {
				r = &g_7f4ca0[j];
				break;
			}
			next = (j + 1) % 0x300;
			left--;
			j = next;
		} while (left != 0);
		if (r == 0) {
			r = found;
		}
	}
	if (r == 0) {
		return 0;
	}
	if (mode == 0) {
		pairs[idx * 2 + 1] = r->key;
	}
send:
	fcn_0051af00(out, (int) buf, r->id);
	return 1;
}
#pragma optimize("", on)

// FUNCTION: GOLDTL 0x4af2f0
// SIZE: 264
// FUNCTION: GOLD 0x4af1b0
// SIZE: 264

/* The reference builds a frame (push ebp; mov ebp,esp; sub esp,0x200) and
 * addresses the 0x200 scratch buffer off ebp; section 13 of
 * docs/msvc6-c-shapes.md. */
#pragma optimize("y", off)
int __cdecl fcn_004af2f0(int a1, int a2, int a3, char* a4, int a5)
{
	char buf[0x200];
	unsigned short w;
	char* p;
	int n;
	int r;
	void* e;

	if (a1 != 2 || a2 == 0 || a3 == 8) {
		return 0;
	}
	e = fcn_00508e40(*(int*) ((char*) a2 + a3 * 8 + 4));
	if (e == 0) {
		return 0;
	}
	w = *(unsigned short*) e;
	if (fcn_004ae130(w) == 0) {
		return 0;
	}
	r = fcn_0050dac0(w);
	n = 0x200;
	p = buf;
	/* The original's zero-fill is the 24-byte hand-written block-fill prelude
	 * (docs/msvc6-c-shapes.md section 11, docs/codegen-walls.md section 6b);
	 * no msvc6 C spelling emits it.  Reproduced as a block-fill with ordinary
	 * named operands. */
	__asm {
		mov edi, p
		mov ebx, n
		xor eax, eax
		lea ecx, [edi+edi*2]
		and ecx, 3
		sub ebx, ecx
		jle short L1
		rep stosb
		mov ecx, ebx
		and ebx, 3
		shr ecx, 2
		rep stosd
	L1:
		add ecx, ebx
		rep stosb
	}
	fcn_004ae080(a4, buf, &n, (int*) &p);
	n = fcn_0064eeec(a4 + n);
	fcn_0051af00(a5, buf,
	    fcn_0050b710((int) (((float) n * g_662910) * (float) r),
	    g_773d75),
	    g_773d75);
	return 1;
}

// FUNCTION: GOLD 0x4af3f0
// SIZE: 720
// FUNCTION: GOLDTL 0x4af530
// SIZE: 710

#pragma optimize("y", off)
int __cdecl fcn_004af530(int mode, int* pairs, int idx, char* text, void* out)
{
	char buf[0x200];
	Rec21c* r;
	Rec21c* found;
	int sel;
	int j;
	int left;
	int next;
	int n;
	int p;

	n = 0x200;
	p = (int) buf;
	__asm {
		mov edi, p
		mov ebx, n
		xor eax, eax
		lea ecx, [edi+edi*2]
		and ecx, 3
		sub ebx, ecx
		jle short L1
		rep stosb
		mov ecx, ebx
		and ebx, 3
		shr ecx, 2
		rep stosd
	L1:
		add ecx, ebx
		rep stosb
	}
	{
		int rest;

		fcn_004ae080(text, buf, &p, &rest);
		if (rest != 1 || (sel = fcn_0064eeec(text + p)) < 0 || sel > 2) {
			sel = 1;
		}
	}
	if (mode == 1) {
		r = (Rec21c*) fcn_00508e40(pairs[idx * 2 + 1]);
		if (r == 0 || r->active <= 0) {
			return 0;
		}
		goto send;
	}
	if (sel == 0) {
		r = 0;
		j = fcn_0042e410(0x300);
		left = 0x300;
		do {
			if (fcn_004ae130((unsigned short) j) != 0
			    && g_7f4ca0[j].cls >= 0xd && g_7f4ca0[j].cls <= 0x12 && fcn_004ae0f0(g_7f4ca0[j].key) != 0) {
				r = &g_7f4ca0[j];
				break;
			}
			next = (j + 1) % 0x300;
			left--;
			j = next;
		} while (left != 0);
	} else if (sel == 1) {
		r = 0;
		j = fcn_0042e410(0x300);
		left = 0x300;
		do {
			if (fcn_004ae1c0(j) != 0
			    && g_7f4ca0[j].cls >= 0xd && g_7f4ca0[j].cls <= 0x12 && fcn_004ae0f0(g_7f4ca0[j].key) != 0) {
				r = &g_7f4ca0[j];
				break;
			}
			next = (j + 1) % 0x300;
			left--;
			j = next;
		} while (left != 0);
	} else {
		found = 0;
		r = 0;
		j = fcn_0042e410(0x300);
		left = 0x300;
		do {
			if (found == 0 && fcn_004ae1c0(j) != 0
			    && g_7f4ca0[j].cls >= 0xd && g_7f4ca0[j].cls <= 0x12) {
				if (fcn_004ae0f0(g_7f4ca0[j].key) != 0) {
					found = &g_7f4ca0[j];
				}
			} else if (fcn_004ae210(j) != 0
			    && g_7f4ca0[j].cls >= 0xd && g_7f4ca0[j].cls <= 0x12 && fcn_004ae0f0(g_7f4ca0[j].key) != 0) {
				r = &g_7f4ca0[j];
				break;
			}
			next = (j + 1) % 0x300;
			left--;
			j = next;
		} while (left != 0);
		if (r == 0) {
			r = found;
		}
	}
	if (r == 0) {
		return 0;
	}
	if (mode == 0) {
		pairs[idx * 2 + 1] = r->key;
	}
send:
	fcn_0051af00(out, (int) buf, r->id);
	return 1;
}
#pragma optimize("", on)

// FUNCTION: GOLDTL 0x4afd70
// SIZE: 405

#pragma optimize("y", off)
int __cdecl fcn_004afd70(int mode, int* pairs, int idx, char* text, void* out)
{
	char buf[0x200];
	int steps[4];
	Rec21c* r;
	int n;
	int p;
	int i;
	int step;
	int left;
	int next;

	r = 0;
	if (mode == 2) {
		return 0;
	}
	n = 0x200;
	p = (int) buf;
	__asm {
		mov edi, p
		mov ebx, n
		xor eax, eax
		lea ecx, [edi+edi*2]
		and ecx, 3
		sub ebx, ecx
		jle short L1
		rep stosb
		mov ecx, ebx
		and ebx, 3
		shr ecx, 2
		rep stosd
	L1:
		add ecx, ebx
		rep stosb
	}
	{
		int rest;

		fcn_004ae080(text, buf, &p, &rest);
	}
	if (mode == 1) {
		r = (Rec21c*) fcn_00508e40(pairs[idx * 2 + 1]);
		if (r == 0 || r->active <= 0) {
			return 0;
		}
		goto send;
	}
	for (i = 0; i < 0x300; i++) {
		steps[0] = 3;
		steps[1] = 5;
		steps[2] = 7;
		steps[3] = 11;
		step = steps[fcn_0042e410(4)];
		i = fcn_0042e410(0x300);
		left = 0x300;
		do {
			if (fcn_004ae210(i) != 0 && fcn_004ae0f0(g_7f4ca0[i].key) != 0) {
				r = &g_7f4ca0[i];
				break;
			}
			next = (i + step) % 0x300;
			left--;
			i = next;
		} while (left != 0);
	}
	if (r == 0) {
		return 0;
	}
	if (mode == 0) {
		pairs[idx * 2 + 1] = r->key;
	}
send:
	fcn_0051af00(out, (int) buf, r->id);
	return 1;
}
#pragma optimize("", on)
