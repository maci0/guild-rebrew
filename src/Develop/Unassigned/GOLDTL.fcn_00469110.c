/* ADDRESS: GOLDTL 0x01015ea0 */
extern char* g_1015ea0;


void __cdecl fcn_00469090(int);

/* ADDRESS: GOLDTL 0x00469110 */
void __cdecl fcn_00469110(int index, int a2)
{
	*(int*) ((char*) g_1015ea0 + index * 0x2f4 + 0x18) = a2;
	fcn_00469090(index);
}
