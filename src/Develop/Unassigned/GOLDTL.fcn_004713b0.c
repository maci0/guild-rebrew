#include <string.h>

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

#include "client_types.h"
extern D2_FORM_RECORD g_1038140[];
extern int g_14ce86c;

char* __cdecl d3_FindTextureByName(char* name);
void __cdecl fcn_0045d090(char* p, int a);
void __cdecl d2_BlitBufferToSurface(int a, int b, int c, int d, int e, int f, int g, int h);

/* ADDRESS: GOLDTL 0x004713b0 */
void __cdecl d2_CaptureFormPageTextures(int slot, char* upperName, char* lowerName)
{
	Obj* form;
	char* upperTex;
	char* lowerTex;

	form = &((Obj*)g_1038140)[slot];
	upperTex = 0;
	if (upperName) {
		strcpy(form->name1, upperName);
		upperTex = d3_FindTextureByName(upperName);
		if (upperTex) {
			fcn_0045d090(upperTex, g_14ce86c);
			d2_BlitBufferToSurface(0, 0, *(int*) (upperTex + 0x64), *(int*) (upperTex + 0x64), *(int*) (upperTex + 0x50), 0, 0, form->h1);
		}
	}
	if (lowerName) {
		strcpy(form->name2, lowerName);
		lowerTex = d3_FindTextureByName(lowerName);
		if (lowerTex) {
			fcn_0045d090(lowerTex, g_14ce86c);
			d2_BlitBufferToSurface(0, 0, *(int*) (lowerTex + 0x64), *(int*) (form->h2 + 8), *(int*) (lowerTex + 0x50), 0, *(int*) (upperTex + 0x64), (int) form->h2);
		}
	}
}
