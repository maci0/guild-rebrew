


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

extern char* tp_ch_ActionQueue;

/* ADDRESS: GOLDDE 0x0040b200 */
void __cdecl ch_ClearSceneActionFinishCallbacks(int key)
{
	int i;

	for (i = 0; i < 2000; i++) {
		if (((T40c300*)tp_ch_ActionQueue)[i].on != 0 && ((T40c300*)tp_ch_ActionQueue)[i].a != 0 && ((T40c300*)tp_ch_ActionQueue)[i].owner != 0
		    && *(int*) (((T40c300*)tp_ch_ActionQueue)[i].owner + 0x88) == key && ((T40c300*)tp_ch_ActionQueue)[i].b != 0) {
			((T40c300*)tp_ch_ActionQueue)[i].b = 0;
		}
	}
}
