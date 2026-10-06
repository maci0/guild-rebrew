typedef struct
{
	char b[0x4a4];
} fcn_00449f90_Part;
// SIZE 0x4a4

typedef struct
{
	char pad000[0xf4];
	fcn_00449f90_Part parts[3];
	fcn_00449f90_Part extra;
} fcn_00449f90_Mesh;
// SIZE 0x1384

extern int g_67ac90;

int __cdecl fcn_00449b60(char* s);
void __cdecl fcn_00439fa0(char* o);
void __cdecl fcn_00449ba0(char* o, void* part, char* name);
char __cdecl fcn_00449db0(char* a, int b, int mode, char* key, char* val);

// FUNCTION: GOLDTL 0x449f90
void __cdecl fcn_00449f90(char* o, void* part, char* name)
{
	int i;
	int n;
	char buf[0x100];

	if (part != 0) {
		if (fcn_00449b60(name) == 0) {
			return;
		}
		if (*(fcn_00449f90_Mesh**) (o + 0x1ec) == 0) {
			fcn_00439fa0(o);
		}
		fcn_00449ba0(o, part, name);
		return;
	}
	fcn_00449db0(name, 0, 0, buf, 0);
	if (fcn_00449b60(buf) == 0) {
		return;
	}
	if (*(fcn_00449f90_Mesh**) (o + 0x1ec) == 0) {
		fcn_00439fa0(o);
	}
	fcn_00449ba0(o, &(*(fcn_00449f90_Mesh**) (o + 0x1ec))->parts[0], buf);
	if (fcn_00449db0(name, 0, -1, buf, 0) && fcn_00449b60(buf) != 0) {
		fcn_00449ba0(o, &(*(fcn_00449f90_Mesh**) (o + 0x1ec))->extra, buf);
	}
	if ((g_67ac90 & 0x7f) == 1) {
		n = 1;
		for (i = 1; i < 3; i++) {
			if (n >= 3) {
				break;
			}
			if (fcn_00449db0(name, 0, i, buf, 0) && fcn_00449b60(buf) != 0) {
				fcn_00449ba0(o, &(*(fcn_00449f90_Mesh**) (o + 0x1ec))->parts[n], buf);
				n++;
			}
		}
	}
}
