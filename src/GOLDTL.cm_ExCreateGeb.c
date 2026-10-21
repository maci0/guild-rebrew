#include <stdio.h>
#include <string.h>

void __cdecl d3_DestroyObject(int a, int b);
int __cdecl fcn_00508e40(int id);
char* __cdecl gm_AllocGebaeude(char typ, unsigned short id);
int __cdecl fcn_0042f690(char* path, int a, int b, char* out);
int __cdecl fcn_004488e0(char* path, int a, int b);
void __cdecl fcn_00438b40(int h, void* p);
void __cdecl fcn_00438cb0(int h, void* p);
void __cdecl fcn_00598860(int h, void* p);
void __cdecl fcn_00510820(int h, void* p, int n);
void __cdecl fcn_00597ff0(int id, char* dst);
int __cdecl fcn_005985f0(char* name, void* p);
void __cdecl fcn_004379a0(int a, int b, int c, int d, void* out);
void __cdecl fcn_005982d0(void);
void __cdecl fcn_0041d9e0(char* msg);
void __cdecl fcn_004550b0(int a, int b);
void __cdecl d3_DestroyObject(int a);
void __cdecl fcn_0052d9d0(void* p);
void __cdecl fcn_004bd4e0(int a, int b);

/* ADDRESS: GOLDTL 0x004cc820 */
int __cdecl cm_ExCreateGeb(char* a0, char* out)
{
	char name[260];
	char tmp[128];
	char path[260];
	char msg[256];
	char shortname[84];
	int pos[3];
	struct {
		int items[32];
		int count;
	} list;
	unsigned char* geb;
	unsigned char* model;
	int saved;
	int i;
	int handle;

	model = (unsigned char*) fcn_00508e40(*(int*) (a0 + 0x10));
	if (model == 0)
		return 1;
	if (*(int*) 0x14cbca0 != -1)
		*(int*) 0x699364 = *(int*) (a0 + 0x14);
	geb = (unsigned char*) gm_AllocGebaeude(*(char*) (a0 + 0x18),
	                                        *(unsigned short*) model);
	if (geb == 0)
		return 1;
	*(int*) 0x68a9d4 = *(int*) (geb + 1);
	/* Game string table entry holding the building file prefix "gb_". */
	strcpy(name, (char*) 0x6798d4);
	strcat(name, (char*) (*(int*) 0x868050 + (unsigned int) *geb * 0x24d + 1));
	strupr(name + 2);
	for (i = 0; i < 4; i++) {
		if (i != 0)
			sprintf(path, "%sgebaeude/*%s_%c.ogr", (char*) 0x7e1ae0, name,
			        (char) (i + '@'));
		else
			sprintf(path, "%sgebaeude/*%s.ogr", (char*) 0x7e1ae0, name);
		if (fcn_0042f690(path, *(int*) 0x6b7fdc, *(int*) 0x6b7fdc, tmp) != 0)
			break;
	}
	if (i == 4)
		goto done;
	saved = *(int*) 0x6b8010;
	d3_DestroyObject(0, 1);
	pos[0] = *(int*) (a0 + 0x19);
	pos[1] = *(int*) (a0 + 0x1d);
	pos[2] = *(int*) (a0 + 0x21);
	handle = fcn_004488e0(path, 0, 0);
	if (handle == 0) {
		sprintf(path,
		        "cm_ExCreateGeb(): Could not load 3D-Object-Group '%s'...",
		        name);
		goto destroy;
	}
	memset(&list, 0, sizeof list);
	/* Native passes the dword at shortname+0x50 here; it is still zero. */
	fcn_004379a0(*(int*) 0x67a370, 0, 0x2c0, (int) fcn_005982d0, &list);
	fcn_00438b40(handle, &pos[0]);
	fcn_00438cb0(handle, a0 + 0x29);
	fcn_00598860(handle, &list);
	fcn_00510820(handle, geb, 2);
	fcn_00597ff0(*geb, tmp);
	strcpy(shortname, tmp);
	sprintf(path, "cm_ExCreateGeb(): bauplatze name:%s", tmp);
	if (fcn_005985f0(shortname, geb) != 0) {
		for (i = 0; i < list.count; i++) {
			if (*(int*) 0x773dd8 != 0)
				fcn_004550b0(list.items[i], *(int*) 0x773dd8);
			sprintf(msg, "cm_ExCreateGeb(): killing objectname: %s",
			        list.items[i]);
			sprintf(msg, "cm_ExCreateGeb(): killing objectptr: %s",
			        list.items[i]);
			d3_DestroyObject(list.items[i]);
		}
	} else {
		fcn_0041d9e0("cm_ExCreateGeb(): could not lc_GetGebaeudeBauplatz()...");
	}
	fcn_0052d9d0(geb);
	fcn_004bd4e0(*(int*) (geb + 0x61), *geb);
destroy:
	d3_DestroyObject(saved, 1);
done:
	if (out != 0) {
		out[0] = 1;
		out[1] = 2;
		*(void**) (out + 6) = geb;
	}
	return 0;
}
