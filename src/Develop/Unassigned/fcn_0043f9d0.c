typedef struct
{
	char pad0000[0x30];
	int anims[8];
	char pad0050[0x7e24 - 0x50];
	char names[8][0x40];
} fcn_0043f9d0_Floor;
// SIZE 0x8024

void __cdecl fcn_0043bf20(char*);
int __cdecl fcn_0043f7e0(fcn_0043f9d0_Floor*, char* name, int slot);

/* ADDRESS: GOLDTL 0x0043f9d0 */
void __cdecl fcn_0043f9d0(fcn_0043f9d0_Floor* o)
{
	int i;

	if (o == 0) {
		return;
	}
	fcn_0043bf20((char*) o);
	for (i = 0; i < 8; i++) {
		fcn_0043f7e0(o, o->names[i], i);
	}
}
