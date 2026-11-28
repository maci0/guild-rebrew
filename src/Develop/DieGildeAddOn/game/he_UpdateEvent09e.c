typedef struct Node {
	char pad0[0x52];
	char f52[0x1e];
	int f70;
	char pad74[0x38];
	int fac;
	int fb0;
} Node;
/* SIZE 0xb4 */

void* __cdecl gm_LookupEntityRecordById(int a);
void __cdecl gm_ModifyHealth(int a, int b);
void __cdecl gm_AddTime(char* p, int a, int b, int c);
void __cdecl he_FreeAction(Node* n);

/* ADDRESS: GOLDTL 0x0057c7b0 */
/* ADDRESS: GOLDDE 0x005625e0 */
void __cdecl he_UpdateEvent09e(Node* o)
{
	int n;
	void* a;
	void* b;
	int h;
	int m;

	n = o->f70;
	if (n == -1 || n == -2) {
		goto cleanup;


	}
	o->f70 = n + 1;
	a = gm_LookupEntityRecordById(o->fb0);
	b = gm_LookupEntityRecordById(o->fac);
	if (a == 0) {
		goto cleanup;


	}
	h = *(int*) ((char*) a + 0x194);
	if (h != 0) {
		gm_ModifyHealth(*(int*) ((char*) a + 4), -h);
		m = h / 2;
		if (m <= 2) {
			m = 2;
		}
		if (b != 0) {
			gm_ModifyHealth(*(int*) ((char*) b + 4), m);
		}
	}
	if (o->f70 < 2) {
		gm_AddTime(o->f52, 0x18, 0, 0);
		return;
	}
cleanup: he_FreeAction(o);
}
