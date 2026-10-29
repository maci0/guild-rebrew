#include <string.h>

// SIZE 0xcc
struct query_40f4b0 {
	char name[0x40];
	char found[0x80];
	int count;
	int result;
	char flag;
};

extern char g_6b5c60[];
extern int g_67a370;

int __cdecl fcn_0040f470();
void __cdecl fcn_004379a0(char*, int, int, int (__cdecl*)(), struct query_40f4b0*);

/* ADDRESS: GOLDTL 0x0040f4b0 */
int __cdecl fcn_0040f4b0(char** args, char* pflag)
{
	struct query_40f4b0 q;

	strcpy(q.name, *args);
	q.found[0] = (*(char*)g_6b5c60);
	q.count = 0;
	q.result = 0;
	q.flag = *pflag;
	if (q.name[0] != 0) {
		fcn_004379a0(((char*)g_67a370), 0, 0xc0, fcn_0040f470, &q);
	}
	return 0;
}
