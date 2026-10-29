

extern char g_1043370[];
char __cdecl fcn_0045b990(int rec, int key, int* a, int* b, int* c);
int __cdecl fcn_00405a50(int a, int b, unsigned char id, int x, int y);

int __cdecl fcn_00405c00(int key, unsigned char id, int x, int y)
{
	int a;
	int b;
	int c;
	int rec;

	rec = ((int*)g_1043370)[id * 247];
	if (rec != 0 && fcn_0045b990(rec, key, &a, &b, &c)) {
		return fcn_00405a50(a, b, id, x, y);
	}
	return -1;
}
