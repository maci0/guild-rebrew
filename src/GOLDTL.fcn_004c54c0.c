/* ADDRESS: GOLDTL 0x0067db50 */
extern float g_67db50;
/* ADDRESS: GOLDTL 0x0067db54 */
extern float g_67db54;



void __cdecl fcn_004c4330(void*);

void __cdecl fcn_004c54c0(int a1, int a2, int a3, int a4)
{
	char buf[0x9c];

	buf[0] = 0x1b;
	*(int*) (buf + 0x10) = a1;
	*(int*) (buf + 0x14) = a2;
	*(int*) (buf + 0x18) = a3;
	*(int*) (buf + 0x1c) = a4;
	*(int*) (buf + 0x20) = (*(int*)&g_67db54);
	*(int*) (buf + 0x24) = (int) g_67db50;
	fcn_004c4330(buf);
}
