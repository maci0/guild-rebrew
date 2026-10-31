/*
 * Family tree window builder.
 *
 * Opens the tree view window and prepares the root entity: the window handle,
 * the tree mode, the title string and the graphics state are set up before the
 * walk over the family records starts.
 *
 * Reconstructed range 0x5d0660..0x5d07a0. The native body continues with the
 * record walk from 0x5d07a0 through 0x5d1785; that part (including the
 * memset(-1) tables the walk clears) is not reconstructed here.
 */

extern int g_772500;			/* 0x00772500 char* */
extern int g_772514;			/* 0x00772514 */
extern int g_100f1dc;			/* 0x0100f1dc */

int __cdecl fcn_0057ec20(int);
void __cdecl fcn_0057e880(int, int, int, int);
int __cdecl gm_LookupEntityRecordById(unsigned int);
int __cdecl fcn_00470820(int, int, char*);
int __cdecl d2_SetOverlayAnimation(int, int);
int __cdecl fcn_00471b60(int);
int __cdecl d2_SetForm(int, int);
int __cdecl io_AppendText(int);

/* ADDRESS: GOLDTL 0x005d0660 */
void __cdecl fcn_005d0660(unsigned int a0, unsigned char a1, int a2, unsigned int a3)
{
	int win;
	int count;
	int rows;
	char* ent;

	if (!fcn_0057ec20(1)) {
		return;
	}
	fcn_0057e880(6, 0, 0, 0);
	ent = (char*) gm_LookupEntityRecordById(a0);
	if (!ent) {
		return;
	}
	win = fcn_00470820(0, 0, (char*) 0x6acab0);
	d2_SetOverlayAnimation(0, 0);
	fcn_00471b60(win);
	d2_SetForm(win, 2);
	io_AppendText(a2 ? a2 : 0x9f);
	d2_SetForm(win, 1);
	count = 1;
	g_100f1dc = -1;
	rows = *(int*) (0x1015f4c + g_772514 * 0x3cc);
}
