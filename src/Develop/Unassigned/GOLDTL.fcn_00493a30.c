#define MIN(a, b) ((a) < (b) ? (a) : (b))
#define MAX(a, b) ((a) > (b) ? (a) : (b))
extern float g_662910;
extern float g_6628a0;
extern float g_6628a8;

char* __cdecl gm_LookupEntityRecordById(int id);
float __cdecl fcn_0050f980(int a, int b, int c);
float __cdecl fcn_00507e70(char* a, char* b, int c);
int __cdecl fcn_005c6270(char* a1, int a2);

/* ADDRESS: GOLDTL 0x00493a30 */
int __cdecl fcn_00493a30(unsigned short* key, char* e)
{
	char* p1;
	char* p2;
	float f2;
	float f1;
	float g1;
	float g2;
	float v;
	float s;

	if (*(int*) (e + 0x48) == 1) {
		return 0;
	}
	if (*(int*) (e + 8) == 1) {
		return 0;
	}
	p1 = gm_LookupEntityRecordById(*(int*) (e + 0x18));
	p2 = gm_LookupEntityRecordById(*(int*) (e + 0x14));
	f1 = fcn_0050f980(*(unsigned short*) p1, *key, 1) * g_662910;
	f2 = fcn_0050f980(*(unsigned short*) p2, *key, 1) * g_662910;
	if (fcn_005c6270(p1, 0x22e) != 0) {
		f1 = f1 + 0.1f;
		f2 = f2 - 0.1f;
	}
	f1 = MIN(MAX(0.0f, f1), 1.0f);
	f2 = MIN(MAX(0.0f, f2), 1.0f);






	g1 = fcn_00507e70(p1, (char*) key, 4);
	g2 = fcn_00507e70(p2, (char*) key, 4);
	v = *(float*) (e + 4);
	s = g2 + v * v * 0.0025f;
	if (*(int*) (e + 0x44) != 0) {
		f1 = f1 * 1.1f;
		f2 = f2 * 0.9f;
	}
	return f1 + g1 > f2 + s;
}
