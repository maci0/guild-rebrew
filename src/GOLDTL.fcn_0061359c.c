#include <string.h>
#include "Develop/Units/d3/forward_decls_61500.h"

__declspec(dllimport) void* __stdcall CreateFontIndirectA(const void* desc);

typedef struct FontObj61359c {
	char pad0[8];
	void* font;
	char data[0x3c];
	void* slot48;
	int* item4c;
} FontObj61359c;

typedef void (__stdcall* ReleaseFn)(void*);


/* Native ABI is thiscall: self in ecx, two stack arguments, ret 8. MSVC 6 C
 * rejects __thiscall, so the second declared parameter absorbs edx and
 * stays unused; __fastcall also keeps the callee-pops ret 8. */
/* ADDRESS: GOLDTL 0x0061359c */
int __fastcall fcn_0061359c(FontObj61359c* self, int unused, int* id, const void* desc)
{
	int hr;

	(void) unused;
	if (id == 0 || desc == 0)
		return (int) 0x8876086c;
	hr = fcn_0062b5d0((int) id, &self->slot48);
	if (hr < 0)
		return hr;
	self->font = CreateFontIndirectA(desc);
	if (self->font == 0)
		return (int) 0x8007000e;
	self->item4c = id;
	(*(ReleaseFn*) (*(char**) id + 4))((void*) id);
	memcpy(self->data, desc, 0x3c);
	return 0;
}
