


// SIZE 0xc
typedef struct {
	int tag;
	int id;
	int who;
} Msg;

extern char g_6a5894[];

char* __cdecl gm_StartFilteredEntitySearch(int, ...);
char* __cdecl gm_AddObjekt(void);
char* __cdecl gm_FindNextFilteredEntity(void);
char* __cdecl fcn_00502cd0(int, int, int, ...);
char* __cdecl gm_LookupEntityRecordById(int k);
void __cdecl cm_SendLogAction(char* s);
void __cdecl cm_SendTraceEnd(char* s);
void __cdecl cm_RequestJoinLeaveElection(Msg* msg);

void __cdecl he_PruneStammtischSeats(void)
{
	char* e;
	char* w;
	char* u;
	int i;

	for (e = gm_StartFilteredEntitySearch(1, 5, 0x16); e != 0; e = gm_FindNextFilteredEntity()) {
		w = fcn_00502cd0(*(int*) (e + 0x5d), 1, 0, 0x120);
		if (w == 0) {
			continue;
		}
		w = fcn_00502cd0(*(int*) (w + 0x14), 1, 0, 0x12d);
		if (w == 0) {
			continue;
		}
		for (i = 0; i < 4; i++) {
			if (((int*) (w + 0x1c))[i] == -1) {
				continue;
			}
			u = gm_LookupEntityRecordById(((int*) (w + 0x1c))[i]);
			if (u == 0 || u[8] == 0 || u[2] == 0xf) {
				Msg msg;

				msg.tag = 0x6c656176;
				msg.who = *(int*) (e + 1);
				msg.id = ((int*) (w + 0x1c))[i];
				cm_SendLogAction(g_6a5894);
				cm_RequestJoinLeaveElection(&msg);
				cm_SendTraceEnd(g_6a5894);
			}
		}
	}
}
