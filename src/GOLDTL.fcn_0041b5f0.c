// SIZE 0x14
struct vertex_41b5f0 {
	float x;
	float y;
	float z;
	float rhw;
	int color;
};

extern int g_6777ac;
extern struct vertex_41b5f0* g_6b5df0;

void __cdecl fcn_0041d9e0(const char* msg);

// FUNCTION: GOLDTL 0x41b5f0
// SIZE: 269

/* dd_Line: queues a screen-space line as two vertices. */
void __cdecl fcn_0041b5f0(int x1, int y1, int x2, int y2, int color)
{
	if (g_6777ac == -1) {
		fcn_0041d9e0("dd_Line called w/o dd_BeginLines!");
	}
	if (g_6777ac < 0x40) {
		g_6b5df0[g_6777ac].x = (float) x1;
		g_6b5df0[g_6777ac].y = (float) y1;
		g_6b5df0[g_6777ac].z = 0.0f;
		g_6b5df0[g_6777ac].rhw = 1.0f;
		g_6b5df0[g_6777ac].color = color;
		g_6777ac++;
		g_6b5df0[g_6777ac].x = (float) x2;
		g_6b5df0[g_6777ac].y = (float) y2;
		g_6b5df0[g_6777ac].z = 0.0f;
		g_6b5df0[g_6777ac].rhw = 1.0f;
		g_6b5df0[g_6777ac].color = color;
		g_6777ac++;
	} else {
		fcn_0041d9e0("Too many lines in dd_Line(): Increase dd_MAX_LINES in d8_vesa.c!");
	}
}
