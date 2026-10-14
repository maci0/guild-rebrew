


typedef struct
{
	char type;
	char name[0x40];
} Name41;
// SIZE 0x41

extern char* g_99ec10;

int __cdecl fcn_0065f220(char*, char*);

int __cdecl fcn_00501490(char* name)
{
	int i;

	for (i = 0; i < 0x2dc; i++) {
		if (fcn_0065f220(name, ((Name41*)g_99ec10)[i].name) == 0) {
			return i;
		}
	}
	return 0;
}
