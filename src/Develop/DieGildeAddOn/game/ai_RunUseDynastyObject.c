typedef struct Req {
	unsigned short* s;
	int id;
	int arg;
	int dir;
	int pad;
} Req;
// SIZE 0x14

extern float g_10097f4;
extern float g_1009814;

unsigned short* __cdecl gm_QueryEntities(int a, int b, int c, int d);
float* __cdecl gm_LookupSpecialObject(int id);
int __cdecl gm_UseSpecialObject(char* e, Req* r);

/* ADDRESS: GOLDTL 0x0049b120 */
/* ADDRESS: GOLDDE 0x00489b60 */
int __cdecl ai_RunUseDynastyObject(char* entity, int* itemReq, int* targetReq)
{
	float* itemProto;
	unsigned short* item;
	Req req;

	item = gm_QueryEntities(*(int*) (entity + 0x178), 1, 1, itemReq[1]);
	if (!item) {
		return 0;
	}
	itemProto = gm_LookupSpecialObject(*item);
	if (itemProto) {
		req.s = item;
		req.id = targetReq[1];
		req.arg = -1;
		if (gm_UseSpecialObject(entity, &req) == 1) {
			if (req.dir == 1) {
				g_1009814 = g_10097f4 * itemProto[3];
				return 0x20;
			}
			if (req.dir == -1) {
				g_1009814 = -(g_10097f4 * itemProto[3] * 0.5f);
			}
			return 0x20;
		}
	}
	return 0;
}
