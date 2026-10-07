// FUNCTION: GOLDTL 0x00426d50

#include <string.h>

typedef struct {
	char name[0x100];
	int id;
	int f104;
	char pad108[8];
	int f110;
	int f114;
	char pad118[4];
	char *src;
	int srclen;
	char pad124[4];
	int vars[0x2c0];
	int fc28;
	int ndebug;
	int *debug;
	char *stack;
	char *sp;
	char padc3c[0x20];
	int fc5c;
	int fc60;
	char padc64[0x2c];
	int fc90;
	char padc94[4];
} Script;
// SIZE 0xc98

extern char* g_6b7e94;
extern int g_6b7fdc;
extern int g_14cb430;
extern int g_14c93a0[0x800];
extern int g_6b8010;
extern int g_6791c8;
extern int g_6791cc;
extern char g_6790c8[];

void *__cdecl fcn_0042ff50(char *, char *, int);
int __cdecl fcn_0064d41a(char *, char *, ...);
void __cdecl fcn_0041d9e0(char *);
int __cdecl CloseVfsStream(void *);
char *__cdecl fcn_0041db70(int, char *);
int __cdecl vfs_ReadData(char *, int, int, void *);
int __cdecl fcn_00426ac0(char *, char *, int *);
void __cdecl fcn_0041ddd0(void *);

Script *__cdecl fcn_00426d50(char *name)
{
	void *f;
	char *out;
	char msg[0x200];
	Script *sc;
	char *tmp;
	int len;
	int i;

	f = fcn_0042ff50(name, "rb", g_6b7fdc);
	if (f == 0) {
		fcn_0064d41a(msg, "evt_LoadScript: Could not open t_vfs_file: %s!", name);
		fcn_0041d9e0(msg);
		return 0;
	}
	for (i = 0; i < 0x80; i++) {
		if (((Script*)g_6b7e94)[i].name[0] == 0) {
			break;
		}
	}
	if (i >= 0x80) {
		fcn_0064d41a(msg, "evt_LoadScript: Could not load script %s, because too many scripts are currently in memory!", name);
		CloseVfsStream(f);
		return 0;
	}
	g_14cb430 = i;
	sc = &((Script*)g_6b7e94)[i];
	tmp = fcn_0041db70(0xfa01, "ect_LoadScript:tmp");
	out = fcn_0041db70(0xfa01, "ect_LoadScript:output");
	memset(out, 0, 0xfa01);
	memset(tmp, 0, 0xfa01);
	vfs_ReadData(tmp, 0xfa00, 1, f);
	CloseVfsStream(f);
	len = fcn_00426ac0(tmp, out, g_14c93a0);
	for (sc->ndebug = 0; sc->ndebug < 0x800; sc->ndebug++) {
		if (g_14c93a0[sc->ndebug] == -1) {
			break;
		}
	}
	sc->debug = (int *) fcn_0041db70(sc->ndebug * 4, "evt:debuginfo");
	memcpy(sc->debug, g_14c93a0, sc->ndebug * 4);
	sc->src = fcn_0041db70(len + 1, "evt_LoadScript:sc->SourceCode");
	sc->srclen = len + 1;
	sc->f114 = 0;
	sc->f110 = 0;
	sc->fc28 = 0;
	strcpy(sc->src, out);
	strcpy(sc->name, name + strlen(g_6790c8));
	memset(sc->vars, 0, sizeof(sc->vars));
	if (tmp != 0) {
		fcn_0041ddd0(tmp);
	}
	if (out != 0) {
		fcn_0041ddd0(out);
	}
	sc->sp = sc->stack = fcn_0041db70(0x400, "evt:stack");
	sc->fc90 = g_6b8010;
	sc->f104 = g_6791c8;
	sc->fc60 = 0;
	sc->fc5c = 0;
	sc->id = g_6791cc;
	g_6791cc++;
	return sc;
}
