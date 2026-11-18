struct rec_4cc590 {
	char pad0[2];
	char kind;
	char pad3;
	int id;
	char pad8[0x164];
	int owner;
	char pad170[0xac];
};
// SIZE 0x21c

extern char g_7f4ca0[];
extern int g_14cbca0;
extern int gm_NextEntityId;
extern char cm_LastEntityId[];
extern int(__stdcall* g_662318)(void);

void __cdecl srv_SeedRandom(int);
int __cdecl fcn_004c4dc0(unsigned char*, int);
char* __cdecl gm_StartFilteredEntitySearch(int, int, int);
unsigned short __cdecl fcn_0050a7e0(int, int, int, int, int, int, int, int);
char* __cdecl gm_FindRecordById(int);
void __cdecl fcn_004fe470(int, int, int, int, int);
char* __cdecl gm_AllocObjekt(int, int, int);
void __cdecl fcn_004ce9e0(struct rec_4cc590*);


/* ADDRESS: GOLDTL 0x004cc590 */
int __cdecl fcn_004cc590(unsigned char* request, char* response)
{
	char* e;
	char* r;
	int id;

	if (g_14cbca0 != -1)
		gm_NextEntityId = *(int*) (request + 0x10);
	else
		*(int*) (request + 0x22) = g_662318();
	if (response != 0) {
		response[0] = 2;
		response[1] = 1;
		*(int*) (response + 6) = 0;
	}
	srv_SeedRandom(*(int*) (request + 0x22));
	if (*(int*) (request + 0x17) == -1) {
		e = 0;
	} else {
		*(int*) (request + 0x17) = fcn_004c4dc0(request, *(int*) (request + 0x17));
		e = gm_StartFilteredEntitySearch(1, 1, *(int*) (request + 0x17));
		if (e == 0)
			return 1;
	}
	id = fcn_0050a7e0(request[0x14], -1, -1, 0x14, 0, request[0x1f], request[0x20], 0);
	if (id == 0xffff)
		return 1;
	if (*(int*) (request + 0x1b) != -1 && (r = gm_FindRecordById(*(int*) (request + 0x1b))) != 0)
		fcn_004fe470(((struct rec_4cc590*)g_7f4ca0)[id].id, *(int*) (e + 1), *(int*) (r + 2), 0, 0);
	else
		fcn_004fe470(((struct rec_4cc590*)g_7f4ca0)[id].id, *(int*) (e + 1), -1, 0, 0);
	((struct rec_4cc590*)g_7f4ca0)[id].owner = 0;
	((struct rec_4cc590*)g_7f4ca0)[id].kind = 0xd;
	if (request[0x21] != 0) {
		gm_AllocObjekt(((struct rec_4cc590*)g_7f4ca0)[id].id, request[0x21], 1);
		fcn_004ce9e0(&((struct rec_4cc590*)g_7f4ca0)[id]);
	}
	(*(int*)cm_LastEntityId) = ((struct rec_4cc590*)g_7f4ca0)[id].id;
	if (response != 0) {
		response[0] = 1;
		response[1] = 1;
		*(struct rec_4cc590**) (response + 6) = &((struct rec_4cc590*)g_7f4ca0)[id];
	}
	return 0;
}
