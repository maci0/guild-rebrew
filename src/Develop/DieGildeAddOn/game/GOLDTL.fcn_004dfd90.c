

typedef struct {
	char c[0x19];
} blk19;
// SIZE 0x19

blk19 g_68cb58 = { { 0x62, 0x65, 0x77, 0x65 } };
extern int g_772f44;

double __cdecl fcn_004ff040(char*);
void __cdecl fcn_00417b50(char*, int, float, float, float, float);
void __cdecl fcn_00406120(char*);
char* __cdecl fcn_0040c230(char*, void*, int, int, int);
void __cdecl fcn_004dfd10(char*);

int __cdecl fcn_004dfd90(char* e)
{
	char* o;

	if (fcn_004ff040(e) < 0.1) {
		fcn_00417b50(*(char**) (*(char**) (e + 0x184) + 0x34), 0x40, 0.25f, 0.1f, 0.14f, 55.0f);
		fcn_00406120(*(char**) (e + 0x184));
		o = fcn_0040c230(*(char**) (e + 0x184), fcn_004dfd10, 0x12, 0x36, 1);
		*(blk19*) (o + 0xf0) = g_68cb58;
		*(int*) (*(char**) (*(char**) (e + 0x184) + 0x34) + 0x220) = 0;
		g_772f44 = 1;
		return 1;
	}
	return 0;
}
