typedef struct {
	char pad0[0x4];
	unsigned short count;
	char pad6[0x12];
	void** nodes;
} D2_ANIM_TRACK_LIST;
// SIZE 0x1c

void __cdecl d2_ReleaseSurfaceGroup(void*, D2_ANIM_TRACK_LIST*);
void __cdecl m_FreeTracked(void*);


/* ADDRESS: GOLDTL 0x0047b5d0 */
void __cdecl d2_FreeAnimTrackList(D2_ANIM_TRACK_LIST* l)
{
	int i;

	for (i = 0; i < l->count; i++)
		d2_ReleaseSurfaceGroup(l->nodes[i], l);
	m_FreeTracked(l->nodes);
	l->nodes = 0;
	m_FreeTracked(l);
}
