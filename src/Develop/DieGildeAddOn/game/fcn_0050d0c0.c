extern unsigned char g_773d75;
extern char g_7f4ca0[][0x21c];

typedef struct {
	unsigned short id;
	unsigned char type;
	char pad[0x21c - 3];
} H50d0c0;

int __cdecl fcn_0050d2a0(void*);
int __cdecl fcn_00502cd0(int, int, ...);
int __cdecl fcn_00502850(void);
float __cdecl fcn_0050bb50(int, char);

/* ADDRESS: GOLDTL 0x0050d0c0 */
int __cdecl fcn_0050d0c0(char* e, int flag)
{
	char* h;
	char* s;
	unsigned int i;
	int r;

	r = 0;
	if (*(unsigned short*) (e + 0x27) != 0xffff) {
		i = *(unsigned short*) (e + 0x27);
		if ((unsigned char) g_7f4ca0[i][2] < 0xa) {
			r = fcn_0050d2a0(g_7f4ca0[i]);
		}
	}
	if (flag != 0) {
		s = (char*) fcn_00502cd0(*(int*) (e + 0x5d), 2, 6, 0, 0x2a);
		if (s != 0) {
			s = (char*) fcn_00502cd0(*(int*) (s + 0x14), 1, 5);
			if (s != 0) {
				do {
					r = (int) (fcn_0050bb50(*(unsigned short*) s, g_773d75)
					           + (float) r);
					s = (char*) fcn_00502850();
				} while (s != 0);
			}
		}
	}
	return r;
}
