#include <stdio.h>
#include <string.h>
extern int g_14cbca0, gm_NextEntityId, g_773dd8; extern void* g_6b7fdc;
void __cdecl d3_SelectSceneContext(int a, int b);
int __cdecl gm_LookupEntityRecordById(int id);
char* __cdecl gm_AllocGebaeude(char typ, unsigned short id);
int __cdecl vfs_ResolvePath(char* path, int a, int b, char* out);
int __cdecl fcn_004488e0(char* path, int a, int b);
void __cdecl d3_SetNodePosition(int h, void* p);
void __cdecl d3_SetObjectRotation(int h, void* p);
void __cdecl d3_SetObjectGroundPosition(int h, void* p);
void __cdecl d3_BindEntitySceneObject(int h, void* p, int n);
void __cdecl lc_GetBauplatzPrefix(int id, char* dst);
int __cdecl lc_GetGebaeudeBauplatz(char* name, void* p);
void __cdecl d3_VisitSceneObjects(int a, int b, int c, int d, void* out);
void __cdecl fcn_005982d0(void);
void __cdecl ReportClientMessage(char* msg);
void __cdecl fcn_004550b0(int a, int b);
#include "Develop/Units/d3/d3_object.h"
#include "Develop/DieGildeAddOn/game/game_data.h"
typedef struct BuildingProto { unsigned char kind; char name[0x24c]; } BuildingProto;
void __cdecl fcn_0052d9d0(void* p);
void __cdecl fcn_004bd4e0(int a, int b);
#include "Develop/DieGildeAddOn/game/building_prototype.h"
/* ADDRESS: GOLDTL 0x004cc820 */
int __cdecl cm_ExCreateGeb(char* request, char* out)
{
	char name[260];
	char tmp[128];
	char found[260];
	char path[260];
	char msg[256];
	char shortname[84];
	int pos[4];
	struct {
		int items[32];
		int count;
	} list;
	unsigned char* geb;
	unsigned char* model;
	int saved;
	int i;
	int handle;
	unsigned int kind;

	model = (unsigned char*) gm_LookupEntityRecordById(*(int*) (request + 0x10));
	if (model == 0)
		return 1;
	if (g_14cbca0 != -1)
		gm_NextEntityId = *(int*) (request + 0x14);
	geb = (unsigned char*) gm_AllocGebaeude(*(char*) (request + 0x18),
	                                        *(unsigned short*) model);
	if (geb == 0)
		return 1;
	*(int*) 0x68a9d4 = *(int*) (geb + 1);
	kind = *geb;
	/* Prefix literal at native 0x6798d4. */
	strcpy(name, "gb_");
	strcat(name, ((char*)&((BUILDING_PROTOTYPE*)lpGebaeudePROT)[kind] + 1));
	strupr(name + 2);
	for (i = 0; i < 4; i++) {
		if (i != 0)
			sprintf(path, "%sgebaeude/*%s_%c.ogr", (char*) 0x7e1ae0, name,
			        (char) (i + '@'));
		else
			sprintf(path, "%sgebaeude/*%s.ogr", (char*) 0x7e1ae0, name);
		if (vfs_ResolvePath(path, (int) g_6b7fdc, (int) g_6b7fdc, found) != 0)
			goto load;
	}
	goto done;
load:
	saved = d3_CurrentContextIndex;
	d3_SelectSceneContext(0, 1);
	pos[0] = *(int*) (request + 0x19);
	pos[1] = *(int*) (request + 0x1d);
	pos[2] = *(int*) (request + 0x21);
	handle = fcn_004488e0(path, 0, 0);
	if (handle == 0) {
		sprintf(name,
		        "cm_ExCreateGeb(): Could not load 3D-Object-Group '%s'...",
		        path);
		goto destroy;
	}
	memset(shortname, 0, sizeof shortname);
	d3_SetNodePosition(handle, &pos[0]);
	d3_SetObjectRotation(handle, request + 0x29);
	d3_SetObjectGroundPosition(handle, pos);
	d3_BindEntitySceneObject(handle, geb, 2);
	lc_GetBauplatzPrefix(*geb, tmp);
	strcpy(shortname, tmp);
	sprintf(name, "cm_ExCreateGeb(): bauplatze name:%s", tmp);
	if (lc_GetGebaeudeBauplatz(shortname, geb) != 0) {
		memset(&list, 0, sizeof list);
		d3_VisitSceneObjects(g_67a370, *(int*)(shortname + 0x50), 0x2c0, (int) fcn_005982d0, &list);
		for (i = 0; i < list.count; i++) {
			if (g_773dd8 != 0)
				fcn_004550b0(list.items[i], g_773dd8);
			sprintf(msg, "cm_ExCreateGeb(): killing objectname: %s",
			        list.items[i]);
			sprintf(msg, "cm_ExCreateGeb(): killing objectptr: %s",
			        list.items[i]);
			d3_DestroyObject((D3_OBJECT*)list.items[i]);
		}
	} else {
		ReportClientMessage("cm_ExCreateGeb(): could not lc_GetGebaeudeBauplatz()...");
	}
	fcn_0052d9d0(geb);
	fcn_004bd4e0(*(int*) (geb + 0x61), *geb);
destroy:
	d3_SelectSceneContext(saved, 1);
done:
	if (out != 0) {
		out[0] = 1;
		out[1] = 2;
		*(void**) (out + 6) = geb;
	}
	return 0;
}
