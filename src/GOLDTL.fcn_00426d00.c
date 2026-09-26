// FUNCTION: GOLD 0x4284e0
// SIZE: 80
// FUNCTION: GOLDTL 0x426d00
// SIZE: 79

// SIZE 0xc98
typedef struct {
	char name[0xc98];
} T426d00;

extern char* g_6b7e94;
int __cdecl fcn_0065f220(char*, char*);

T426d00* __cdecl fcn_00426d00(char* name)
{
	int i;

	for (i = 0; i < 0x80; i++) {
		if (fcn_0065f220(((T426d00*)g_6b7e94)[i].name, name) == 0) {
			return &((T426d00*)g_6b7e94)[i];
		}
	}
	return 0;
}
