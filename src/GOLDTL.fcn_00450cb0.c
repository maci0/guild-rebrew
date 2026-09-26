// FUNCTION: GOLDTL 0x450cb0
// SIZE: 139

// SIZE 0xc
typedef struct Light {
	int a;
	int used;
	int b;
} Light;

extern int g_6b86fc;
extern void* g_6b870c;
extern int g_6b8700;
extern char* g_1041d00;
extern char* g_6b86e0;
extern char* g_6b86e4;
extern char* g_6b86e8;
extern char* g_6b86ec;
extern int g_6b86f0;
extern int g_6b86f4;
extern int g_6b86f8;
extern int g_67a370;

void __cdecl fcn_004379a0(int, int, int, void*, int);
void __cdecl fcn_00450d40(void);

void __cdecl fcn_00450cb0(int ctx, unsigned char mask)
{
	int i;

	for (i = 0; i < g_6b86fc; i++) {
		((Light*)g_6b870c)[i].used = 0;
	}
	g_6b8700 = 0;
	(*(int*)&g_1041d00) = 0;
	(*(int*)&g_6b86ec) = 0;
	(*(int*)&g_6b86e8) = 0;
	(*(int*)&g_6b86e4) = 0;
	(*(int*)&g_6b86e0) = 0;
	g_6b86f8 = 0;
	g_6b86f4 = 0;
	g_6b86f0 = 0;
	fcn_004379a0(g_67a370, 0, (mask << 4) | 0x4e, fcn_00450d40, ctx);
}
