typedef struct Req {
	unsigned short* s;
	int id;
	int arg;
	int dir;
	int pad;
} Req;
// SIZE 0x14

extern float g_10096cc;
extern float g_10096ec;

unsigned short* __cdecl gm_QueryEntities(int a, int b, int c, int d);
float* __cdecl gm_LookupSpecialObject(int id);
int __cdecl gm_UseSpecialObject(char* e, Req* r);

/* ADDRESS: GOLDTL 0x0049aa80 */
int __cdecl ai_RunEducationObject(char* entity, int* action)
{
	float* objData;
	unsigned short* slot;
	Req req;

	slot = gm_QueryEntities(*(int*) (entity + 0x178), 1, 1, action[1]);
	if (!slot) {
		return 0;
	}
	objData = gm_LookupSpecialObject(*slot);
	if (objData) {
		req.s = slot;
		req.id = -1;
		req.arg = -1;
		req.dir = 0;
		req.pad = 0;
		if (gm_UseSpecialObject(entity, &req) == 1) {
			if (req.dir == 1) {
				g_10096ec = g_10096cc * objData[3];
				return 0x1e;
			}
			if (req.dir == -1) {
				g_10096ec = -(g_10096cc * objData[3]);
			}
			return 0x1e;
		}
	}
	return 0;
}
