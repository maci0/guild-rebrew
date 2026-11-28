typedef struct VfsEntry {
	char name[0x30];
	int offset;
	void* data;
	int size;
	int kind;
	int refs;
	int flags;
	int stamp;
	char pad[8];
} VfsEntry;
// SIZE 0x54

extern char* d2_FileObjTable;
extern int g_772504;
extern int g_772508;
extern volatile int gm_GameTicks;

void __cdecl d2_FreeAnimTrackList(void* p);
void __cdecl m_FreeTracked(void* p);

/* ADDRESS: GOLDTL 0x00465850 */
int __cdecl vfs_EvictOldestCacheEntry(void)
{
	int i;
	int best;
	int stamp;

	best = -1;
	stamp = gm_GameTicks;
	for (i = 1; i < g_772504; i++) {
		if (((VfsEntry*)d2_FileObjTable)[i].stamp < stamp && ((VfsEntry*)d2_FileObjTable)[i].refs <= 0 && !(((VfsEntry*)d2_FileObjTable)[i].flags & 1)
		    && ((VfsEntry*)d2_FileObjTable)[i].data != 0 && ((VfsEntry*)d2_FileObjTable)[i].size != 0) {
			stamp = ((VfsEntry*)d2_FileObjTable)[i].stamp;
			best = i;
		}
	}
	if (best == -1) {
		return 0;
	}
	if (((VfsEntry*)d2_FileObjTable)[best].kind < 0x10) {
		d2_FreeAnimTrackList(((VfsEntry*)d2_FileObjTable)[best].data);
	} else {
		m_FreeTracked(((VfsEntry*)d2_FileObjTable)[best].data);
		((VfsEntry*)d2_FileObjTable)[best].data = 0;
	}
	((VfsEntry*)d2_FileObjTable)[best].data = 0;
	g_772508 -= ((VfsEntry*)d2_FileObjTable)[best].size;
	return 1;
}
