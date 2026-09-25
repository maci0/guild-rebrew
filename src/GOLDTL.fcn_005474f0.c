// FUNCTION: GOLDTL 0x005474f0
// SIZE: 206

// SIZE 0xc
typedef struct {
	int tag;
	int id;
	int who;
} Msg;

extern char g_6a5894[];

char* __cdecl gm_StartFilteredEntitySearch(int, ...);
char* __cdecl gm_AddObjekt(void);
char* __cdecl fcn_00502cd0(int, int, int, ...);
char* __cdecl fcn_00508e40(int k);
void __cdecl fcn_004c4eb0(char* s);
void __cdecl fcn_004c4ef0(char* s);
void __cdecl fcn_004c6900(Msg* msg);

void __cdecl fcn_005474f0(void)
{
	char* e;
	char* w;
	char* u;
	int i;

	for (e = gm_StartFilteredEntitySearch(1, 5, 0x16); e != 0; e = gm_AddObjekt()) {
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
			u = fcn_00508e40(((int*) (w + 0x1c))[i]);
			if (u == 0 || u[8] == 0 || u[2] == 0xf) {
				Msg msg;

				msg.tag = 0x6c656176;
				msg.who = *(int*) (e + 1);
				msg.id = ((int*) (w + 0x1c))[i];
				fcn_004c4eb0(g_6a5894);
				fcn_004c6900(&msg);
				fcn_004c4ef0(g_6a5894);
			}
		}
	}
}
