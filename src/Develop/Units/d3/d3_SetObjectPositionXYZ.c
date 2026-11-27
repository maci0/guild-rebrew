typedef struct {
	int a;
	int b;
	int c;
	int d;
} D3_OBJ_POS_ARG;

void __cdecl d3_SetObjectPosition(int, void*);

/* ADDRESS: GOLDTL 0x00438c80 */
void __cdecl d3_SetObjectPositionXYZ(int a, int b, int c, int d)
{
	D3_OBJ_POS_ARG t;

	t.a = b;
	t.b = c;
	t.c = d;
	d3_SetObjectPosition(a, &t);
}
