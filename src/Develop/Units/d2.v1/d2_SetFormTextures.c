typedef struct Obj {
	char pad0[0x190];
	int used;
	int pad194;
	int ready;
	char pad19c[0x1ac - 0x19c];
	int h1;
	char* h2;
	char name1[0x40];
	char name2[0x40];
	char pad234[0x2bc - 0x234];
} Obj;
// SIZE 0x2bc

#include "Develop/client_types.h"
extern D2_FORM_RECORD d2_Forms[];

void __cdecl d2_ResetFormBackground(int k);
void __cdecl d2_CaptureFormPageTextures(int k, char* a, char* b);
void __cdecl d2_RenderFormToTextures(int k);

/* ADDRESS: GOLDTL 0x004712d0 */
int __cdecl d2_SetFormTextures(int formId, char* topTex, char* bottomTex)
{
	Obj* form;

	form = &((Obj*)d2_Forms)[formId];
	if (!form->used) {
		return 0;
	}
	if (!form->ready) {
		return 0;
	}
	if (topTex && bottomTex) {
		d2_ResetFormBackground(formId);
		d2_CaptureFormPageTextures(formId, topTex, bottomTex);
		d2_RenderFormToTextures(formId);
	}
	return 1;
}
