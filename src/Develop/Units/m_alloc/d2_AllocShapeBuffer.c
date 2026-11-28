extern char d2_ShapeTag[];
extern char d2_ShapeSurfTag[];
extern char d2_ShapeUCoordsTag[];


void* __cdecl m_alloc(int, char*);

/* ADDRESS: GOLDDE 0x00469bc0 */
void* __cdecl d2_AllocShapeBuffer(int wordCount, int entryCount, int unused)
{
	void* p;

	p = m_alloc(0x38, d2_ShapeTag);
	*(int*) ((char*) p + 0x24) = wordCount;
	*(int*) ((char*) p + 0x28) = (int) m_alloc(wordCount * 4, d2_ShapeSurfTag);
	*(int*) ((char*) p + 0x2c) = entryCount;
	*(int*) ((char*) p + 0x30) = (int) m_alloc(entryCount * 12, d2_ShapeUCoordsTag);
	return p;
}
