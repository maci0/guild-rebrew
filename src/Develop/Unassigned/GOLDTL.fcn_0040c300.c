


// SIZE 0x194
typedef struct {
	int a;
	int b;
	char pad[1];
	char on;
	char pad2[0xa];
	char* owner;
	char pad3[0x17c];
} T40c300;

extern char* g_6b5c20;

void __cdecl fcn_0040c300(int key)
{
	int i;

	for (i = 0; i < 2000; i++) {
		if (((T40c300*)g_6b5c20)[i].on != 0 && ((T40c300*)g_6b5c20)[i].a != 0 && ((T40c300*)g_6b5c20)[i].owner != 0
		    && *(int*) (((T40c300*)g_6b5c20)[i].owner + 0x88) == key && ((T40c300*)g_6b5c20)[i].b != 0) {
			((T40c300*)g_6b5c20)[i].b = 0;
		}
	}
}
