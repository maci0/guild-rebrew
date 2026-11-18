extern int g_14cbca0;
extern int gm_NextEntityId;
extern int cm_LastEntityId;
extern char g_7f4ca0[];

int __cdecl fcn_0064d3f8(void);
void __cdecl fcn_0042e4c0(int a0);
int __cdecl fcn_004c4dc0(void* a0, int a1);
int __cdecl fcn_00503fe0(int a0, int a1, int a2);
int __cdecl fcn_0050a7e0(int a0, int a1, int a2, unsigned short a3,
                        int a4, int a5, int a6, int a7);

/* ADDRESS: GOLDTL 0x004c7790 */
int __cdecl fcn_004c7790(void* packet, char* reply)
{
	int v;
	int r;
	int arg;

	if (g_14cbca0 != -1) {
		gm_NextEntityId = *(int*) ((char*) packet + 0x10);
	} else {
		*(int*) ((char*) packet + 0x26) = fcn_0064d3f8();
	}
	fcn_0042e4c0(*(int*) ((char*) packet + 0x26));
	v = *(int*) ((char*) packet + 0x1f);
	if (v == -1) {
		arg = 0;
	} else {
		v = fcn_004c4dc0(packet, v);
		*(int*) ((char*) packet + 0x1f) = v;
		arg = fcn_00503fe0(1, 1, v);
		if (arg == 0)
			return 1;
	}
	r = (int) (unsigned short) fcn_0050a7e0(
		*(unsigned char*) ((char*) packet + 0x14),
		*(int*) ((char*) packet + 0x15),
		*(int*) ((char*) packet + 0x19),
		*(unsigned short*) ((char*) packet + 0x1d),
		arg,
		*(unsigned char*) ((char*) packet + 0x23),
		*(unsigned char*) ((char*) packet + 0x24),
		*(unsigned char*) ((char*) packet + 0x25));
	if (r == 0xffff)
		return 1;
	r = r * 540;
	cm_LastEntityId = *(int*) (g_7f4ca0 + r + 4);
	if (reply != 0) {
		reply[0] = 1;
		reply[1] = 1;
		*(char**) (reply + 6) = g_7f4ca0 + r;
	}
	return 0;
}
