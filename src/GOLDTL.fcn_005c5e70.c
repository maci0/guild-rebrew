extern int g_775318;
extern char* g_1015ea0;
extern char* g_99ec10;
extern char* g_6abb00;
extern char* g_14b52c4;
extern float g_6629c8;

void* __cdecl fcn_00502cd0(int container_id, int arg_count, ...);
void* __cdecl fcn_00502850(void);
int __cdecl fcn_005c61e0(unsigned short id);
int __cdecl fcn_00471f80(int handle);
void __cdecl d2_SetElementValue(int handle, int element, int value, int extra);
void __cdecl fcn_00472640(int handle, int value);
void __cdecl fcn_00473750(int id, int value);
int __cdecl fcn_00466ee0(int x, int y, int id, int group, char* name);
void __cdecl fcn_0046b2b0(int handle);
int __cdecl fcn_0064d41a(char* buf, char* fmt, ...);

/* ADDRESS: GOLDTL 0x005c5e70 */
unsigned int __cdecl fcn_005c5e70(void)
{
	int* slot;
	unsigned int result;
	int container;
	unsigned short id;
	int handle;
	int used;
	unsigned short* match;
	int i;

	container = g_775318;
	result = 0;
	if (container == 0) {
		return 0;
	}
	for (slot = (int*) 0x776c64; (int) slot <= 0x776c93; slot += 2) {
		if (*slot != 0) {
			id = *(unsigned short*) *slot;
			if (fcn_00502cd0(*(int*) (container + 0x178), 1, 0, id) != 0) {
				handle = fcn_00471f80(slot[-1]);
				d2_SetElementValue(slot[-1], 0, *(unsigned int*) (*slot + 0xe), handle);
				fcn_0064d41a(g_1015ea0 + 0xcc + slot[-1] * 0x2f4, "%s~ %li %s",
				    *(unsigned int*) (id * 8 + 0x14a79c0), *(unsigned int*) (*slot + 0x1c), g_14b52c4);
				used = fcn_005c61e0(id);
				if (used != 0) {
					if (*(int*) (*slot + 0x21) != 0) {
						fcn_00472640(slot[-1], 0);
						*(float*) (g_1015ea0 + 500 + slot[-1] * 0x2f4) = g_6629c8
						    - (float) *(int*) (*slot + 0x1c) / (float) *(int*) (used + 4);
					}
					else {
						fcn_00472640(slot[-1], 1);
						*(unsigned int*) (g_1015ea0 + 0x60 + slot[-1] * 0x2f4) = 0;
						*(unsigned int*) (g_1015ea0 + 500 + slot[-1] * 0x2f4) = 0;
					}
				}
				if (handle != 0) {
					fcn_00473750(id + 0xdf, handle);
					result = 1;
				}
			}
			else {
				*slot = 0;
				fcn_0046b2b0(slot[-1]);
				slot[-1] = -1;
			}
		}
	}
	match = (unsigned short*) fcn_00502cd0(*(int*) (container + 0x178), 1, 5);
	for (;;) {
		if (match == 0) {
			return result;
		}
		if (g_99ec10[*match * 0x41] != 9) {
			for (i = 0; i < 6; i++) {
				if (*(unsigned short**) (i * 8 + 0x776c64) == match) {
					break;
				}
			}
			if (i == 6) {
				for (i = 0; i < 6; i++) {
					if (*(int*) (i * 8 + 0x776c64) == 0) {
						*(int*) (i * 8 + 0x776c64) = (int) match;
						handle = fcn_00466ee0((i % 3) * 0x38 + 0x15, (i / 3) * 0x36 + 0x4a,
						    *match + 0xdf, 10, g_6abb00);
						*(int*) (i * 8 + 0x776c60) = handle;
						*(unsigned int*) (g_1015ea0 + 0x1d0 + handle * 0x2f4) = 0x23;
						*(unsigned int*) (g_1015ea0 + 0x1dc + handle * 0x2f4) = 0xffffffff;
						*(unsigned int*) (g_1015ea0 + 0x1e0 + handle * 0x2f4) = 0;
						fcn_0064d41a(g_1015ea0 + 0xcc + handle * 0x2f4, "%s~ %li St",
						    *(unsigned int*) (*match * 8 + 0x14a79c0),
						    *(unsigned int*) (match + 0xe));
						used = fcn_005c61e0(*match);
						if (used != 0) {
							if (*(int*) ((char*) match + 0x21) != 0) {
								fcn_00472640(handle, 0);
								*(float*) (g_1015ea0 + 500 + handle * 0x2f4) = g_6629c8
								    - (float) *(int*) ((char*) match + 0x1c) / (float) *(int*) (used + 4);
							}
							else {
								fcn_00472640(handle, 1);
							}
						}
						break;
					}
				}
			}
		}
		match = (unsigned short*) fcn_00502850();
	}
}
