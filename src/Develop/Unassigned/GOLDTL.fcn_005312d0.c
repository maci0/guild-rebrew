extern int main_LoopFlags;



char* __cdecl evt_FindScriptById(int);
void __cdecl fcn_005373e0(int, unsigned int);

void __cdecl fcn_005312d0(int a)
{
	unsigned int fl;
	char* r;

	fl = ((*(unsigned int*)&main_LoopFlags) & 0xffffff3f) | 0x100200;
	for (r = evt_FindScriptById(a); r != 0 && (r[0x124] & 1) != 0; r = evt_FindScriptById(a)) {
		fcn_005373e0(0, fl);
	}
}
