/* ADDRESS: GOLDTL 0x00662d40 */
extern float g_662d40[3];



void __cdecl fcn_00455140(int, void*, void*);

void __cdecl fcn_00587f40(char* obj)
{
	fcn_00455140(*(int*) (obj + 0x8c), (void*) g_662d40, obj + 0x24);
	fcn_00455140(*(int*) (obj + 0x8c), (void*) (g_662d40 + 8), obj + 0x44);
	fcn_00455140(*(int*) (obj + 0x8c), (void*) (g_662d40 + 4), obj + 0x34);
}
