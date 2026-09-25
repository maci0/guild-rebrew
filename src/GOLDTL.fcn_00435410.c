// FUNCTION: GOLDTL 0x00435410
// SIZE: 226

typedef struct Mesh435410 Mesh435410;

// SIZE 0x60
typedef struct {
	void* fn[24];
} VT435410;

struct Mesh435410 {
	VT435410* vt;
};

typedef long(__stdcall* Lock435410)(Mesh435410* m, int flags, void** out);
typedef long(__stdcall* Unlock435410)(Mesh435410* m);

extern void* g_6b5de0;
long __stdcall fcn_00601a9b(int nfaces, int nverts, int opts, int fvf, void* dev, Mesh435410** out);

Mesh435410* __cdecl fcn_00435410(char* e)
{
	Mesh435410* m;
	void* vb;
	void* ib;
	void* src;
	int n;
	int n2;
	void* src2;

	fcn_00601a9b(*(int*) (e + 0x4c), *(int*) (e + 0x290), 0x6c0, 0x112, g_6b5de0, &m);
	if (((Lock435410) m->vt->fn[22])(m, 0, &ib) >= 0) {
		n = *(int*) (e + 0x4c) * 4;
		src = *(void**) (e + 0x288);
		__asm {
			mov edi, ib
			mov esi, src
			mov ebx, n
			lea ecx, [edi+edi*2]
			and ecx, 3
			sub ebx, ecx
			jle short L1
			rep movsb
			mov ecx, ebx
			and ebx, 3
			shr ecx, 2
			rep movsd
		L1:
			add ecx, ebx
			rep movsb
		}
		((Unlock435410) m->vt->fn[23])(m);
	}
	if (((Lock435410) m->vt->fn[16])(m, 0, &vb) >= 0) {
		n2 = *(int*) (e + 0x4c) * 6;
		src2 = *(void**) (e + 0x298);
		__asm {
			mov edi, vb
			mov esi, src2
			mov ebx, n2
			lea ecx, [edi+edi*2]
			and ecx, 3
			sub ebx, ecx
			jle short L2
			rep movsb
			mov ecx, ebx
			and ebx, 3
			shr ecx, 2
			rep movsd
		L2:
			add ecx, ebx
			rep movsb
		}
		((Unlock435410) m->vt->fn[17])(m);
	}
	return m;
}
