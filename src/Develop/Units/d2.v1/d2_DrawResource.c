extern int g_772504;

// SIZE 0x54
typedef struct {
	char p0[0x30];
	int x30;
	int x34;
	int p38;
	int type;
	int p40;
	int flags;
	int p48;
	int link;
	char p50[4];
} Rec;

extern char* d2_FileObjTable;
extern signed char g_772510;

int __cdecl d2_GetResourceData(int);
int __cdecl d2_DrawSpriteFromSet(int, int, int, int, int);


/* ADDRESS: GOLDTL 0x00469ea0 */
int __cdecl d2_DrawResource(int x, int y, int idx, int surface)
{
	int result;
	int base;

	result = 0;
	if (idx <= g_772504) {
		base = -1;
		if ((((Rec*)d2_FileObjTable)[idx].type == 5 || ((Rec*)d2_FileObjTable)[idx].type == 8) && ((Rec*)d2_FileObjTable)[idx].x30 == 0) {
			if (((Rec*)d2_FileObjTable)[((Rec*)d2_FileObjTable)[idx].link].x34 == 0) {
				result = d2_GetResourceData(idx);
			}
			base = idx;
			idx = ((Rec*)d2_FileObjTable)[idx].link;
		} else if (((Rec*)d2_FileObjTable)[idx].x34 == 0) {
			result = d2_GetResourceData(idx);
		}
		if (((Rec*)d2_FileObjTable)[idx].flags & 2) {
			idx += g_772510;
		}
		if (result == 0) {
			result = ((Rec*)d2_FileObjTable)[idx].x34;
		}
		switch ((base == -1) ? ((Rec*)d2_FileObjTable)[idx].type : ((Rec*)d2_FileObjTable)[base].type) {
		case 5:
		case 8:
			if (base != -1) {
				result = d2_DrawSpriteFromSet(x, y, surface, result, base - idx);
				break;
			}
		case 1:
		case 4:
			result = d2_DrawSpriteFromSet(x, y, surface, result, 0);
			break;
		case 2:
		case 3:
		case 6:
		case 7:
			return result;
		}
	}
	return result;
}
