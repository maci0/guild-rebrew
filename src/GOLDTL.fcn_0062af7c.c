#pragma optimize("y", off)

/* Constructor-shaped body: links the object into the list headed at
   0x775f60, binds its device at +0x4, queries two device descriptions
   through vtable slots 0x1c/0x24, initialises a 40-byte BITMAPINFOHEADER
   at +0x70, creates a memory DC (+0x6c) and a DIB section (+0x98/+0xa0),
   then selects the bitmap (+0x9c). Native ABI is fastcall with the object
   in ECX, one stack argument and callee stack cleanup (ret 4). */

typedef struct Vtbl62af7c {
	char pad0[4];
	void (__stdcall* m04)(void*);
	char pad8[0x14];
	void (__stdcall* m1c)(void*, void*);
	char pad20[4];
	void (__stdcall* m24)(void*, void*);
} Vtbl62af7c;

typedef struct Bmi62af7c {
	int size;
	int width;
	int height;
	unsigned short planes;
	unsigned short bitcount;
	int compression;
	int sizeImage;
	int xpels;
	int ypels;
	int clrUsed;
	int clrImportant;
} Bmi62af7c;

typedef struct Desc62af7c {
	char pad0[0xc];
	int flags;
	char pad10[0xc4];
} Desc62af7c;

typedef struct Rect62af7c {
	int left;
	int top;
	int right;
	int bottom;
} Rect62af7c;

typedef struct Obj62af7c {
	char pad0[4];
	void* device;
	char pad8[4];
	void* field0c;
	char pad10[0x40];
	int field50;
	int field54;
	int field58;
	int field5c;
	char pad60[0xc];
	void* hdc;
	Bmi62af7c bmi;
	void* hbitmap;
	void* hold;
	void* bits;
	int fielda4;
	char pada8[4];
	void* next;
} Obj62af7c;

extern int __stdcall fcn_005ef863(void* device, void* out);
extern int __fastcall fcn_0062ae93(void* self);

/* ADDRESS: GOLDTL 0x0062af7c */
int __fastcall fcn_0062af7c(Obj62af7c* self, int ignored, int arg)
{
	Rect62af7c rect;
	Desc62af7c desc;
	void* hdc;
	void* hbitmap;
	int hr;

	self->next = *(void**) 0x775f60;
	self->device = (void*) arg;
	*(void**) 0x775f60 = self;
	((Vtbl62af7c*) *(int*) self->device)->m04(self->device);
	((Vtbl62af7c*) *(int*) self->device)->m1c(self->device, &desc);
	((Vtbl62af7c*) *(int*) self->device)->m24(self->device, &rect);
	self->field50 = desc.flags & 0x20000000;
	self->field58 = 0x40;
	self->field5c = 0x10;
	self->field54 = 0x15;
	hr = fcn_0062ae93(self);
	if (hr < 0) {
		return hr;
	}
	hr = fcn_005ef863(self->device, &self->field0c);
	if (hr < 0) {
		return hr;
	}
	memset(&self->bmi, 0, sizeof(self->bmi));
	self->bmi.size = 0x28;
	self->bmi.width = 0x100;
	self->bmi.height = 0x100;
	self->bmi.planes = 1;
	self->bmi.compression = 0;
	self->bmi.bitcount = 0x20;
	self->fielda4 = 0x15;
	hdc = (*(void* (__stdcall**) (void*)) 0x66202c)(0);
	self->hdc = hdc;
	if (hdc == 0) {
		return (int) 0x8007000e;
	}
	self->bmi.height = -self->bmi.height;
	hbitmap = (*(void* (__stdcall**) (void*, void*, int, void**, void*, int)) 0x662038)(self->hdc, &self->bmi, 0, &self->bits, 0, 0);
	self->hbitmap = hbitmap;
	self->bmi.height = -self->bmi.height;
	if (hbitmap == 0) {
		return (int) 0x8007000e;
	}
	(*(int (__stdcall**) (void*, int)) 0x662030)(self->hdc, 2);
	(*(int (__stdcall**) (void*, int)) 0x662034)(self->hdc, 0);
	(*(unsigned long (__stdcall**) (void*, unsigned long)) 0x662050)(self->hdc, 0xffffff);
	self->hold = (*(void* (__stdcall**) (void*, void*)) 0x66204c)(self->hdc, self->hbitmap);
	return 0;
}
