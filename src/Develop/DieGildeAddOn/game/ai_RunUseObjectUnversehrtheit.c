typedef struct Req {
	unsigned short* s;
	int id;
	int arg;
	int dir;
	int pad;
} Req;
// SIZE 0x14

extern float g_1009760;
extern float g_1009780;

unsigned short* __cdecl gm_QueryEntities(int a, int b, int c, int d);
float* __cdecl gm_LookupSpecialObject(int id);
int __cdecl gm_UseSpecialObject(char* e, Req* r);

/* ADDRESS: GOLDTL 0x0049ace0 */
int __cdecl ai_RunUseObjectUnversehrtheit(char* entity, int* args)
{
	float* objDef;
	unsigned short* item;
	Req req;

	item = gm_QueryEntities(*(int*) (entity + 0x178), 1, 1, args[1]);
	if (!item) {
		return 0;
	}
	objDef = gm_LookupSpecialObject(*item);
	if (objDef) {
		req.s = item;
		req.id = -1;
		req.arg = -1;
		req.dir = 0;
		req.pad = 0;
		if (gm_UseSpecialObject(entity, &req) == 1) {
			if (req.dir == 1) {
				g_1009780 = g_1009760 * objDef[3];
				return 0x1f;
			}
			if (req.dir == -1) {
				g_1009780 = -(g_1009760 * objDef[3]);
			}
			return 0x1f;
		}
	}
	return 0;
}
