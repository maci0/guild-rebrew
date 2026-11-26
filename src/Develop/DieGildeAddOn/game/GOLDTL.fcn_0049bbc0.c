typedef struct Req {
	unsigned short* s;
	int id;
	int arg;
	int dir;
	int pad;
} Req;
// SIZE 0x14

extern float g_1008574[];
extern float g_10099d0[8];

unsigned short* __cdecl fcn_00502cd0(int a, int b, int c, int d);
float* __cdecl gm_LookupSpecialObject(int id);
int __cdecl gm_UseSpecialObject(char* e, Req* r);

/* ADDRESS: GOLDTL 0x0049bbc0 */
int __cdecl ai_RunUseParfuem(char* actor, int* itemArgs, int* animData)
{
	float* props;
	unsigned short* slot;
	Req req;

	slot = fcn_00502cd0(*(int*) (actor + 0x178), 1, 1, itemArgs[1]);
	if (!slot) {
		return 0;
	}
	props = gm_LookupSpecialObject(*slot);
	if (props) {
		req.s = slot;
		req.id = animData[1];
		req.arg = animData[2];
		if (gm_UseSpecialObject(actor, &req) == 1) {
			if (req.dir == 1) {
				g_10099d0[0] = g_1008574[animData[4] * 37 + 0] * props[3];
				g_10099d0[2] = g_1008574[animData[4] * 37 + 2] * props[3];
				g_10099d0[4] = g_1008574[animData[4] * 37 + 4] * props[3];
				g_10099d0[6] = g_1008574[animData[4] * 37 + 6] * props[3];
				return 0x23;
			}
			if (req.dir == -1) {
				g_10099d0[0] = -(g_1008574[animData[4] * 37 + 0] * props[3] * 0.5f);
				g_10099d0[2] = -(g_1008574[animData[4] * 37 + 2] * props[3] * 0.5f);
				g_10099d0[4] = -(g_1008574[animData[4] * 37 + 4] * props[3] * 0.5f);
				g_10099d0[6] = -(g_1008574[animData[4] * 37 + 6] * props[3] * 0.5f);
			}
			return 0x23;
		}
	}
	return 0;
}
