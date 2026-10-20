typedef struct VTBL_614789 VTBL_614789;
struct VTBL_614789 {
	void* pad_000[0x20];
	void (__stdcall* m80)(void* obj, void* arg);
	void (__stdcall* m84)(void* obj, void* arg);
	void* pad_088[6];
	void (__stdcall* ma0)(void* obj, void* arg);
	void* pad_0a4[9];
	void (__stdcall* mc8)(void* obj, int a, int b);
	void* pad_0cc[1];
	void (__stdcall* md0)(void* obj);
	void (__stdcall* md4)(void* obj, void* arg);
	void* pad_0d8[1];
	void (__stdcall* mdc)(void* obj, void* a);
};

typedef struct SELF_614789 SELF_614789;
struct SELF_614789 {
	char pad_000[8];
	VTBL_614789** dev;
	char pad_00c[0x14 - 0xc];
	int f14;
	char pad_018[0x28 - 0x18];
	int f28;
	int f2c;
	char pad_030[0x470 - 0x30];
	void* f470;
	void* f474;
};

/* ADDRESS: GOLDTL 0x00614789 */
int __fastcall fcn_00614789(SELF_614789* self)
{
	int* handle;

	handle = &self->f470;
	if (*handle == 0) {
		(*self->dev)->md0(self->dev);
		(*self->dev)->ma0(self->dev, &self->f474);
		(*self->dev)->mc8(self->dev, 7, self->f14);
		(*self->dev)->md4(self->dev, handle);
	}
	(*self->dev)->mdc(self->dev, *handle);
	(*self->dev)->m80(self->dev, &self->f28);
	(*self->dev)->m84(self->dev, &self->f2c);
	return 0;
}
