


#define MIN(a, b) ((a) < (b) ? (a) : (b))
#define MAX(a, b) ((a) < (b) ? (b) : (a))

extern unsigned short g_774970;
extern char g_774964;

unsigned char* __cdecl gm_LookupEntityRecordById(int);
void __cdecl fcn_005356b0(void*);
void __cdecl fcn_0059a340(void);
void __cdecl fcn_004e89e0(unsigned char*, int);

int __cdecl fcn_004cd690(char* x, char* out)
{
	unsigned char* e;
	int v;

	e = gm_LookupEntityRecordById(*(int*) (x + 0x10));
	if (out != 0) {
		out[0] = 2;
		out[1] = 0;
		*(int*) (out + 6) = 0;
	}
	if (e == 0)
		return 1;
	v = e[0x1b1] + *(int*) (x + 0x14);
	e[0x1b1] = MIN(MAX(v, 0), 0xff);
	e[0x1b1] = MAX(0, e[0x1b1]);
	if (*(unsigned short*) e == g_774970 && g_774964 != 0 && e[0x1b1] > 0)
		fcn_005356b0(fcn_0059a340);
	fcn_004e89e0(e, *(int*) (x + 0x18));
	if (out != 0)
		out[0] = 1;
	return 0;
}
