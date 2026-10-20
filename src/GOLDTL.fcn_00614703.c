#pragma optimize("s", on)

typedef struct OBJ_614703 OBJ_614703;
struct OBJ_614703 {
	char pad_000[8];
	void* f08;
	int f0c;
	int f10;
	int f14;
	int f18;
	int f1c;
	char pad_020[0x454];
	int f474;
	int f478;
	void* f47c;
	void* f480;
	float f484;
	float f488;
};

typedef struct VTBL_614703 VTBL_614703;
struct VTBL_614703 {
	char pad_000[4];
	void (__stdcall* m04)(void* obj);
};

extern int __stdcall fcn_0060ff98(void* a1, int* a2, int* a3, int* a4, int a5,
	int* a6, int a7);

/* ADDRESS: GOLDTL 0x00614703 */
int __fastcall fcn_00614703(OBJ_614703* self, int edxarg, void* a1, int a2,
	int a3, int a4, int a5, int a6)
{
	if (a1 == 0) {
		return (int) 0x8876086c;
	}
	self->f08 = a1;
	(*(VTBL_614703**) a1)->m04(a1);
	self->f0c = a2;
	self->f1c = a3;
	self->f10 = a4;
	self->f14 = a5;
	self->f18 = a6;
	fcn_0060ff98(a1, &self->f0c, &self->f0c, &self->f1c, 0, &self->f10, 0);
	self->f484 = 0.0f;
	self->f474 = 0;
	self->f478 = 0;
	self->f488 = 1.0f;
	self->f47c = *(void**) &self->f0c;
	self->f480 = *(void**) &self->f0c;
	return 0;
}
