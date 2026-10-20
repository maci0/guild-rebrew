#pragma optimize("s", on)

typedef struct Obj616426 {
	char pad00[8];
	void* f08;
	int f0c;
	int f10;
	int pad14[2];
	int f1c;
	int f20;
	int pad24[3];
	void* f30;
	void* f34;
	void* f38;
	void* f3c;
	char pad40[0x420];
	int f460;
	int f464;
	int f468;
	int f46c;
} Obj616426;

typedef int (__stdcall* Hr1)(void*);
typedef int (__stdcall* Hr3)(void*, int, void*);
typedef void (__stdcall* Void6)(void*, int, int, int, int, int);
typedef void (__stdcall* Void1)(void*);

int __fastcall fcn_00615e99(Obj616426* self, int ignored, int arg);
int __stdcall fcn_00611be1(void* a, int b, int c, int d);

#pragma optimize("y", off)

/* ADDRESS: GOLDTL 0x00616426 */
int __fastcall fcn_00616426(Obj616426* a0)
{
	int out;
	int hr;

	if (a0->f468 == 0)
		return 0;
	hr = ((Hr1) (*(char**) a0->f08 + 0x8c))(a0->f08);
	if (hr < 0)
		return hr;
	if (a0->f46c == 0) {
		if (a0->f460 == 1)
			hr = ((Hr3) (*(char**) a0->f34 + 0x3c))(a0->f34, a0->f464, &out);
		else
			hr = ((Hr3) (*(char**) a0->f30 + 0x3c))(a0->f30, 0, &out);
		if (hr < 0)
			return hr;
		((Void6) (*(char**) a0->f08 + 0x70))(a0->f08, a0->f20, 0, 0, out, 0);
		((Void1) (*(char**) out + 8))((void*) out);
	}
	if (a0->f460 != 1) {
		if (a0->f1c > 1)
			fcn_00611be1(a0->f30, 0, 0, -1);
		hr = fcn_00615e99(a0, 0, a0->f464);
		if (hr < 0)
			return hr;
	}
	a0->f468 = 0;
	return 0;
}
