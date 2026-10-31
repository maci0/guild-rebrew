extern float g_662910;
extern float g_662910;

/* Owned (both targets) by src/GOLDTL.fcn_005b24b0.c. */
extern unsigned char g_773d75;

void* __cdecl gm_LookupEntityRecordById(int);
#include "Develop/DieGildeAddOn/game/spiel.h"
void __cdecl fcn_004ae080(char*, char*, int*, int*);
int __cdecl fcn_0064eeec(char*);
int __cdecl fcn_0050b710(int, unsigned char);
void __cdecl io_FormatTextBuffer(void*, int, ...);

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

extern char g_7f4ca0[];

int __cdecl fcn_004ae0f0(int);
unsigned short __cdecl gm_RandomMod(int);


/* The original translation unit held this callee in the same file as
 * fcn_004af2f0, and msvc6's same-TU callee analysis is what keeps `w` in edx
 * across the call site below; without the body in view the allocator spills
 * `w` to a callee-saved register (object 267 bytes instead of 264). */
/* ADDRESS: GOLD 0x004adff0 */
/* ADDRESS: GOLDTL 0x004ae130 */
int __cdecl fcn_004ae130(unsigned short a1)
{
	int o;

	o = (a1 & 0xffff) * 540;
	if (*(unsigned short*) ((char*) g_7f4ca0 + o) != 0xffff
	    && *((unsigned char*) g_7f4ca0 + 8 + o) > 0
	    && *((unsigned char*) g_7f4ca0 + 2 + o) < 0xa) {
		return 1;
	}
	return 0;
}


/* ADDRESS: GOLD 0x004ae080 */
/* ADDRESS: GOLDTL 0x004ae1c0 */
int __cdecl fcn_004ae1c0(int a1)
{
	unsigned char c;
	unsigned char f;

	a1 &= 0xffff;
	if (*(unsigned short*) ((int) g_7f4ca0 + a1 * 540) == 0xffff) {
		return 0;
	}
	c = *(unsigned char*) ((int) g_7f4ca0 + 8 + a1 * 540);
	if (c <= 0) {
		return 0;
	}
	f = *(unsigned char*) ((int) g_7f4ca0 + 2 + a1 * 540);
	if (f < 0xa && f != 6 && f != 7) {
		return 1;
	}
	return 0;
}


/* ADDRESS: GOLD 0x004ae0d0 */
/* ADDRESS: GOLDTL 0x004ae210 */
int __cdecl fcn_004ae210(int a1)
{
	unsigned char c;
	unsigned char f;

	a1 &= 0xffff;
	if (*(unsigned short*) ((int) g_7f4ca0 + a1 * 540) != 0xffff) {
		c = *(unsigned char*) ((int) g_7f4ca0 + 8 + a1 * 540);
		if (c > 0) {
			f = *(unsigned char*) ((int) g_7f4ca0 + 2 + a1 * 540);
			if (f == 6 || f == 7) {
				return 1;
			}
		}
	}
	return 0;
}




#pragma optimize("y", off)
int __cdecl fcn_004ae2a0(int mode, int* pairs, int idx, char* text, void* out)
{
	char buf[0x200];
	Rec21c* r;
	int i;
	int p;
	int n;

	if (mode == 1) {
		r = (Rec21c*) gm_LookupEntityRecordById(pairs[idx * 2 + 1]);
		if (r == 0 || r->active == 0 || r->kind != 0xf) {
			return 0;
		}
	} else {
		for (i = 0; ; i++) {
			if (i >= 768) {
				return 0;
			}
			if (fcn_004ae130((unsigned short) i) != 0 && ((Rec21c*)g_7f4ca0)[i].kind == 0xf) {
				break;
			}
		}
		r = &((Rec21c*)g_7f4ca0)[i];
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
	io_FormatTextBuffer(out, (int) buf, r->id);
	return 1;
}
#pragma optimize("", on)




#pragma optimize("y", off)
int __cdecl fcn_004ae3c0(int mode, int* pairs, int idx, char* text, void* out)
{
	char buf[0x200];
	Rec21c* r;
	int i;
	int p;
	int n;

	if (mode == 1) {
		r = (Rec21c*) gm_LookupEntityRecordById(pairs[idx * 2 + 1]);
		if (r == 0 || r->active == 0 || r->kind != 0x15) {
			return 0;
		}
	} else {
		for (i = 0; ; i++) {
			if (i >= 768) {
				return 0;
			}
			if ((fcn_004ae130((unsigned short) i) != 0 && ((Rec21c*)g_7f4ca0)[i].kind == 0x1a) || ((Rec21c*)g_7f4ca0)[i].kind == 0x15) {
				break;
			}
		}
		r = &((Rec21c*)g_7f4ca0)[i];
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
	io_FormatTextBuffer(out, (int) buf, r->id);
	return 1;
}
#pragma optimize("", on)




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
		r = (Rec21c*) gm_LookupEntityRecordById(pairs[idx * 2 + 1]);
		if (r == 0 || r->active <= 0 || r->grade == 0) {
			return 0;
		}
		goto send;
	}
	if (sel == 0) {
		r = 0;
		j = gm_RandomMod(0x300);
		left = 0x300;
		do {
			if (fcn_004ae130((unsigned short) j) != 0 && ((Rec21c*)g_7f4ca0)[j].grade >= 0x1e && ((Rec21c*)g_7f4ca0)[j].grade <= 0x21) {
				r = &((Rec21c*)g_7f4ca0)[j];
				break;
			}
			left--;
			j = (j + 1) % 0x300;
		} while (left != 0);
	} else if (sel == 1) {
		r = 0;
		j = gm_RandomMod(0x300);
		left = 0x300;
		do {
			if (fcn_004ae1c0(j) != 0 && ((Rec21c*)g_7f4ca0)[j].grade >= 0x1e && ((Rec21c*)g_7f4ca0)[j].grade <= 0x21) {
				r = &((Rec21c*)g_7f4ca0)[j];
				break;
			}
			left--;
			j = (j + 1) % 0x300;
		} while (left != 0);
	} else {
		found = 0;
		r = 0;
		j = gm_RandomMod(0x300);
		left = 0x300;
		do {
			if (found == 0 && fcn_004ae1c0(j) != 0 && ((Rec21c*)g_7f4ca0)[j].grade >= 0x1e && ((Rec21c*)g_7f4ca0)[j].grade <= 0x21) {
				found = &((Rec21c*)g_7f4ca0)[j];
			} else if (fcn_004ae210(j) != 0 && ((Rec21c*)g_7f4ca0)[j].grade >= 0x1e && ((Rec21c*)g_7f4ca0)[j].grade <= 0x21) {
				r = &((Rec21c*)g_7f4ca0)[j];
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
	io_FormatTextBuffer(out, (int) buf, r->id);
	return 1;
}
#pragma optimize("", on)




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
		r = (Rec21c*) gm_LookupEntityRecordById(pairs[idx * 2 + 1]);
		if (r == 0 || r->active <= 0 || r->kind == 0) {
			return 0;
		}
		goto send;
	}
	if (sel == 0) {
		r = 0;
		j = gm_RandomMod(0x300);
		left = 0x300;
		do {
			if (((Rec21c*)g_7f4ca0)[j].side == 1 && fcn_004ae130((unsigned short) j) != 0 && fcn_004ae0f0(((Rec21c*)g_7f4ca0)[j].key) != 0
			    && ((Rec21c*)g_7f4ca0)[j].kind > 0 && ((Rec21c*)g_7f4ca0)[j].kind != 0xf && ((Rec21c*)g_7f4ca0)[j].kind != 0x1a && ((Rec21c*)g_7f4ca0)[j].kind != 0x15) {
				r = &((Rec21c*)g_7f4ca0)[j];
				break;
			}
			next = (j + 1) % 0x300;
			left--;
			j = next;
		} while (left != 0);
	} else if (sel == 1) {
		r = 0;
		j = gm_RandomMod(0x300);
		left = 0x300;
		do {
			if (((Rec21c*)g_7f4ca0)[j].side == 1 && fcn_004ae1c0(j) != 0 && fcn_004ae0f0(((Rec21c*)g_7f4ca0)[j].key) != 0
			    && ((Rec21c*)g_7f4ca0)[j].kind > 0 && ((Rec21c*)g_7f4ca0)[j].kind != 0xf && ((Rec21c*)g_7f4ca0)[j].kind != 0x1a && ((Rec21c*)g_7f4ca0)[j].kind != 0x15) {
				r = &((Rec21c*)g_7f4ca0)[j];
				break;
			}
			next = (j + 1) % 0x300;
			left--;
			j = next;
		} while (left != 0);
	} else {
		found = 0;
		r = 0;
		j = gm_RandomMod(0x300);
		left = 0x300;
		do {
			if (((Rec21c*)g_7f4ca0)[j].side == 1) {
				if (found == 0 && fcn_004ae1c0(j) != 0
				    && ((Rec21c*)g_7f4ca0)[j].kind > 0 && ((Rec21c*)g_7f4ca0)[j].kind != 0xf && ((Rec21c*)g_7f4ca0)[j].kind != 0x1a && ((Rec21c*)g_7f4ca0)[j].kind != 0x15) {
					if (fcn_004ae0f0(((Rec21c*)g_7f4ca0)[j].key) != 0) {
						found = &((Rec21c*)g_7f4ca0)[j];
					}
				} else if (fcn_004ae210(j) != 0 && fcn_004ae0f0(((Rec21c*)g_7f4ca0)[j].key) != 0
				    && ((Rec21c*)g_7f4ca0)[j].kind > 0 && ((Rec21c*)g_7f4ca0)[j].kind != 0xf && ((Rec21c*)g_7f4ca0)[j].kind != 0x1a && ((Rec21c*)g_7f4ca0)[j].kind != 0x15) {
					r = &((Rec21c*)g_7f4ca0)[j];
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
	io_FormatTextBuffer(out, (int) buf, r->id);
	return 1;
}
#pragma optimize("", on)




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
		r = (Rec21c*) gm_LookupEntityRecordById(pairs[idx * 2 + 1]);
		if (r == 0 || r->active <= 0 || r->kind == 0) {
			return 0;
		}
		goto send;
	}
	if (sel == 0) {
		r = 0;
		j = gm_RandomMod(0x300);
		left = 0x300;
		do {
			if (((Rec21c*)g_7f4ca0)[j].side == 0 && fcn_004ae130((unsigned short) j) != 0
			    && ((Rec21c*)g_7f4ca0)[j].kind > 0 && ((Rec21c*)g_7f4ca0)[j].kind != 0xf && ((Rec21c*)g_7f4ca0)[j].kind != 0x1a
			        && ((Rec21c*)g_7f4ca0)[j].kind != 0x15 && fcn_004ae0f0(((Rec21c*)g_7f4ca0)[j].key) != 0) {
				r = &((Rec21c*)g_7f4ca0)[j];
				break;
			}
			next = (j + 1) % 0x300;
			left--;
			j = next;
		} while (left != 0);
	} else if (sel == 1) {
		r = 0;
		j = gm_RandomMod(0x300);
		left = 0x300;
		do {
			if (((Rec21c*)g_7f4ca0)[j].side == 0 && fcn_004ae1c0(j) != 0
			    && ((Rec21c*)g_7f4ca0)[j].kind > 0 && ((Rec21c*)g_7f4ca0)[j].kind != 0xf && ((Rec21c*)g_7f4ca0)[j].kind != 0x1a
			        && ((Rec21c*)g_7f4ca0)[j].kind != 0x15 && fcn_004ae0f0(((Rec21c*)g_7f4ca0)[j].key) != 0) {
				r = &((Rec21c*)g_7f4ca0)[j];
				break;
			}
			next = (j + 1) % 0x300;
			left--;
			j = next;
		} while (left != 0);
	} else {
		found = 0;
		r = 0;
		j = gm_RandomMod(0x300);
		left = 0x300;
		do {
			if (((Rec21c*)g_7f4ca0)[j].side == 0) {
				if (found == 0 && fcn_004ae1c0(j) != 0
				    && ((Rec21c*)g_7f4ca0)[j].kind > 0 && ((Rec21c*)g_7f4ca0)[j].kind != 0xf && ((Rec21c*)g_7f4ca0)[j].kind != 0x1a && ((Rec21c*)g_7f4ca0)[j].kind != 0x15) {
					if (fcn_004ae0f0(((Rec21c*)g_7f4ca0)[j].key) != 0) {
						found = &((Rec21c*)g_7f4ca0)[j];
					}
				} else if (fcn_004ae210(j) != 0
				    && ((Rec21c*)g_7f4ca0)[j].kind > 0 && ((Rec21c*)g_7f4ca0)[j].kind != 0xf && ((Rec21c*)g_7f4ca0)[j].kind != 0x1a
				        && ((Rec21c*)g_7f4ca0)[j].kind != 0x15 && fcn_004ae0f0(((Rec21c*)g_7f4ca0)[j].key) != 0) {
					r = &((Rec21c*)g_7f4ca0)[j];
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
	io_FormatTextBuffer(out, (int) buf, r->id);
	return 1;
}
#pragma optimize("", on)




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
		r = (Rec21c*) gm_LookupEntityRecordById(pairs[idx * 2 + 1]);
		if (r == 0 || r->active <= 0 || r->kind == 0) {
			return 0;
		}
		goto send;
	}
	if (sel == 0) {
		r = 0;
		j = gm_RandomMod(0x300);
		left = 0x300;
		do {
			if (fcn_004ae130((unsigned short) j) != 0
			    && ((Rec21c*)g_7f4ca0)[j].kind > 0 && ((Rec21c*)g_7f4ca0)[j].kind != 0xf && ((Rec21c*)g_7f4ca0)[j].kind != 0x1a
			        && ((Rec21c*)g_7f4ca0)[j].kind != 0x15 && fcn_004ae0f0(((Rec21c*)g_7f4ca0)[j].key) != 0) {
				r = &((Rec21c*)g_7f4ca0)[j];
				break;
			}
			next = (j + 1) % 0x300;
			left--;
			j = next;
		} while (left != 0);
	} else if (sel == 1) {
		r = 0;
		j = gm_RandomMod(0x300);
		left = 0x300;
		do {
			if (fcn_004ae1c0(j) != 0
			    && ((Rec21c*)g_7f4ca0)[j].kind > 0 && ((Rec21c*)g_7f4ca0)[j].kind != 0xf && ((Rec21c*)g_7f4ca0)[j].kind != 0x1a
			        && ((Rec21c*)g_7f4ca0)[j].kind != 0x15 && fcn_004ae0f0(((Rec21c*)g_7f4ca0)[j].key) != 0) {
				r = &((Rec21c*)g_7f4ca0)[j];
				break;
			}
			next = (j + 1) % 0x300;
			left--;
			j = next;
		} while (left != 0);
	} else {
		found = 0;
		r = 0;
		j = gm_RandomMod(0x300);
		left = 0x300;
		do {
			if (found == 0 && fcn_004ae1c0(j) != 0
			    && ((Rec21c*)g_7f4ca0)[j].kind > 0 && ((Rec21c*)g_7f4ca0)[j].kind != 0xf && ((Rec21c*)g_7f4ca0)[j].kind != 0x1a && ((Rec21c*)g_7f4ca0)[j].kind != 0x15) {
				if (fcn_004ae0f0(((Rec21c*)g_7f4ca0)[j].key) != 0) {
					found = &((Rec21c*)g_7f4ca0)[j];
				}
			} else if (fcn_004ae210(j) != 0
			    && ((Rec21c*)g_7f4ca0)[j].kind > 0 && ((Rec21c*)g_7f4ca0)[j].kind != 0xf && ((Rec21c*)g_7f4ca0)[j].kind != 0x1a
			        && ((Rec21c*)g_7f4ca0)[j].kind != 0x15 && fcn_004ae0f0(((Rec21c*)g_7f4ca0)[j].key) != 0) {
				r = &((Rec21c*)g_7f4ca0)[j];
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
	io_FormatTextBuffer(out, (int) buf, r->id);
	return 1;
}
#pragma optimize("", on)




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
	e = gm_LookupEntityRecordById(*(int*) ((char*) a2 + a3 * 8 + 4));
	if (e == 0) {
		return 0;
	}
	w = *(unsigned short*) e;
	if (fcn_004ae130(w) == 0) {
		return 0;
	}
	r = gm_WalkEntityChain(w);
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
	io_FormatTextBuffer((void*) a5, (int) buf,
	    fcn_0050b710((int) (((float) n * g_662910) * (float) r),
	    g_773d75),
	    g_773d75);
	return 1;
}




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
		r = (Rec21c*) gm_LookupEntityRecordById(pairs[idx * 2 + 1]);
		if (r == 0 || r->active <= 0) {
			return 0;
		}
		goto send;
	}
	if (sel == 0) {
		r = 0;
		j = gm_RandomMod(0x300);
		left = 0x300;
		do {
			if (fcn_004ae130((unsigned short) j) != 0
			    && ((Rec21c*)g_7f4ca0)[j].cls >= 0xd && ((Rec21c*)g_7f4ca0)[j].cls <= 0x12 && fcn_004ae0f0(((Rec21c*)g_7f4ca0)[j].key) != 0) {
				r = &((Rec21c*)g_7f4ca0)[j];
				break;
			}
			next = (j + 1) % 0x300;
			left--;
			j = next;
		} while (left != 0);
	} else if (sel == 1) {
		r = 0;
		j = gm_RandomMod(0x300);
		left = 0x300;
		do {
			if (fcn_004ae1c0(j) != 0
			    && ((Rec21c*)g_7f4ca0)[j].cls >= 0xd && ((Rec21c*)g_7f4ca0)[j].cls <= 0x12 && fcn_004ae0f0(((Rec21c*)g_7f4ca0)[j].key) != 0) {
				r = &((Rec21c*)g_7f4ca0)[j];
				break;
			}
			next = (j + 1) % 0x300;
			left--;
			j = next;
		} while (left != 0);
	} else {
		found = 0;
		r = 0;
		j = gm_RandomMod(0x300);
		left = 0x300;
		do {
			if (found == 0 && fcn_004ae1c0(j) != 0
			    && ((Rec21c*)g_7f4ca0)[j].cls >= 0xd && ((Rec21c*)g_7f4ca0)[j].cls <= 0x12) {
				if (fcn_004ae0f0(((Rec21c*)g_7f4ca0)[j].key) != 0) {
					found = &((Rec21c*)g_7f4ca0)[j];
				}
			} else if (fcn_004ae210(j) != 0
			    && ((Rec21c*)g_7f4ca0)[j].cls >= 0xd && ((Rec21c*)g_7f4ca0)[j].cls <= 0x12 && fcn_004ae0f0(((Rec21c*)g_7f4ca0)[j].key) != 0) {
				r = &((Rec21c*)g_7f4ca0)[j];
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
	io_FormatTextBuffer(out, (int) buf, r->id);
	return 1;
}
#pragma optimize("", on)




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
		r = (Rec21c*) gm_LookupEntityRecordById(pairs[idx * 2 + 1]);
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
		step = steps[gm_RandomMod(4)];
		i = gm_RandomMod(0x300);
		left = 0x300;
		do {
			if (fcn_004ae210(i) != 0 && fcn_004ae0f0(((Rec21c*)g_7f4ca0)[i].key) != 0) {
				r = &((Rec21c*)g_7f4ca0)[i];
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
	io_FormatTextBuffer(out, (int) buf, r->id);
	return 1;
}
#pragma optimize("", on)

#pragma pack(push, 2)
typedef struct Pos14 {
	int a;
	short b0;
	short b1;
	int c;
	short d;
} Pos14;
#pragma pack(pop)
// SIZE 0xe

typedef struct Msg {
	int h0;
	int h4;
	unsigned char kind;
	char p9[3];
	int owner;
	int h10;
	int target;
	Pos14 when;
	unsigned char flags;
	char p27[9];
	unsigned char count;
	char p31[3];
	int ids[16];
	char p74[8];
	unsigned char code;
	unsigned char one;
	char p7e[0x114 - 0x7e];
} Msg;
// SIZE 0x114

#include "client_types.h"
extern pos14_7f4c00 g_7f4c00;
extern unsigned short g_774970;
extern char* gm_RichterKatholisch;
extern char* gm_RichterEvangelisch;

void __cdecl fcn_00500bb0(Pos14*, int, int, int);
void __cdecl fcn_004c5980(Msg*);

/* In this file for the same reason as fcn_004af2f0: with the bodies of
 * fcn_004ae130/1c0/210 in view, c2 keeps the zero in edx across the first
 * call; declared from another file the object is 16 bytes longer. */
/* ADDRESS: GOLDTL 0x004b0780 */
int __cdecl fcn_004b0780(int* pairs, int idx, char* text)
{
	int n;
	unsigned short* e;
	int codes[4];
	int i;
	int j;
	int key;

	e = (unsigned short*) gm_LookupEntityRecordById(pairs[idx * 2 + 1]);
	if (e == 0 || fcn_004ae130(*e) == 0) {
		return 0;
	}
	{
		char names[4][8] = {"SHAUFEN", "KOEPFEN", "GALGEN", "KANONE"};

		n = 4;
		codes[0] = 3;
		codes[1] = 0;
		codes[2] = 2;
		codes[3] = 4;
		if (text[0] != '-') {
			return 0;
		}
		for (i = 0; i < 4; i++) {
			if (memcmp(text + 1, names[i], strlen(names[i])) == 0) {
				break;
			}
		}
		if (i >= 4) {
			return 0;
		}
	}
	{
		int list[16];
		Msg msg;

		msg.kind = 5;
		msg.target = -1;
		msg.owner = ((Rec21c*)g_7f4ca0)[g_774970].key;
		msg.flags = 0;
		msg.code = (unsigned char) codes[i];
		msg.one = 1;
		list[1] = -1;
		key = *(int*) (e + 2);
		list[2] = *(int*) (gm_RichterKatholisch + 4);
		list[0] = key;
		list[3] = *(int*) (gm_RichterEvangelisch + 4);
		for (j = 0; j < 0x300; j++) {
			if (((Rec21c*)g_7f4ca0)[j].key != key && fcn_004ae1c0(j) != 0) {
				if (((Rec21c*)g_7f4ca0)[j].kind != 0) {
					list[1] = ((Rec21c*)g_7f4ca0)[j].key;
				}
			} else if (n < 16 && fcn_004ae210(j) != 0) {
				list[n] = ((Rec21c*)g_7f4ca0)[j].key;
				n++;
			}
		}
		if (list[1] == -1) {
			list[1] = list[n - 1];
			n--;
		}
		for (j = 0; j < n; j++) {
			msg.ids[j] = list[j];
		}
		for (j = n; j < 16; j++) {
			msg.ids[j] = -1;
		}
		msg.count = (unsigned char) n;
		msg.flags = 0x22;
		msg.when = (*(Pos14*)&g_7f4c00);
		fcn_00500bb0(&msg.when, 0x18, 0, 0);
		msg.when.b0 = 0xa;
		fcn_004c5980(&msg);
	}
	return 1;
}
unsigned char _dpad_7f4c0c[148];
