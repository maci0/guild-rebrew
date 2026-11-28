typedef struct
{
	char b[0x4a4];
} D3_MODEL_PART;
// SIZE 0x4a4

typedef struct
{
	char pad000[0xf4];
	D3_MODEL_PART parts[3];
	D3_MODEL_PART extra;
} D3_MODEL_MESH;
// SIZE 0x1384

#include "Develop/DieGildeAddOn/game/game_data.h"

int __cdecl d3_FindCachedModel(char* s);
void __cdecl d3_AddObjectDrawData(char* o);
void __cdecl d3_AttachModelPart(char* o, void* part, char* name);
char __cdecl d3_FormatModelVariantName(char* a, int b, int mode, char* key, char* val);

/* ADDRESS: GOLDTL 0x00449f90 */
/* ADDRESS: GOLDDE 0x00440670 */
void __cdecl d3_AttachCachedModelParts(char* o, void* part, char* name)
{
	int i;
	int n;
	char buf[0x100];

	if (part != 0) {
		if (d3_FindCachedModel(name) == 0) {
			return;
		}
		if (*(D3_MODEL_MESH**) (o + 0x1ec) == 0) {
			d3_AddObjectDrawData(o);
		}
		d3_AttachModelPart(o, part, name);
		return;
	}
	d3_FormatModelVariantName(name, 0, 0, buf, 0);
	if (d3_FindCachedModel(buf) == 0) {
		return;
	}
	if (*(D3_MODEL_MESH**) (o + 0x1ec) == 0) {
		d3_AddObjectDrawData(o);
	}
	d3_AttachModelPart(o, &(*(D3_MODEL_MESH**) (o + 0x1ec))->parts[0], buf);
	if (d3_FormatModelVariantName(name, 0, -1, buf, 0) && d3_FindCachedModel(buf) != 0) {
		d3_AttachModelPart(o, &(*(D3_MODEL_MESH**) (o + 0x1ec))->extra, buf);
	}
	if ((d3_LODMode & 0x7f) == 1) {
		n = 1;
		for (i = 1; i < 3; i++) {
			if (n >= 3) {
				break;
			}
			if (d3_FormatModelVariantName(name, 0, i, buf, 0) && d3_FindCachedModel(buf) != 0) {
				d3_AttachModelPart(o, &(*(D3_MODEL_MESH**) (o + 0x1ec))->parts[n], buf);
				n++;
			}
		}
	}
}
