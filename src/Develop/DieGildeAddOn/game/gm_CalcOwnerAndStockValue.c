extern unsigned char g_773d75;
extern char g_7f4ca0[][0x21c];

typedef struct {
	unsigned short id;
	unsigned char type;
	char pad[0x21c - 3];
} OWNER_HEADER_STUB;

int __cdecl fcn_0050d2a0(void*);
int __cdecl fcn_00502cd0(int, int, ...);
int __cdecl fcn_00502850(void);
float __cdecl fcn_0050bb50(int id, unsigned char a);

/* ADDRESS: GOLDTL 0x0050d0c0 */
int __cdecl gm_CalcOwnerAndStockValue(char* bld, int flag)
{
	char* unused;
	char* slot;
	unsigned int i;
	int val;

	val = 0;
	if (*(unsigned short*) (bld + 0x27) != 0xffff) {
		i = *(unsigned short*) (bld + 0x27);
		if ((unsigned char) g_7f4ca0[i][2] < 0xa) {
			val = fcn_0050d2a0(g_7f4ca0[i]);
		}
	}
	if (flag != 0) {
		slot = (char*) fcn_00502cd0(*(int*) (bld + 0x5d), 2, 6, 0, 0x2a);
		if (slot != 0) {
			slot = (char*) fcn_00502cd0(*(int*) (slot + 0x14), 1, 5);
			if (slot != 0) {
				do {
					val = (int) (fcn_0050bb50(*(unsigned short*) slot,
					                          g_773d75)
					             + (float) val);
					slot = (char*) fcn_00502850();
				} while (slot != 0);
			}
		}
	}
	return val;
}
