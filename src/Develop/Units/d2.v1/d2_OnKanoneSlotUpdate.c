/* Inferred private view: only the index and 56-byte copy extent are known. */
struct DATENSATZ_KOPIE {
	int index;
	unsigned char unbekannt_04[52];
};

extern char d2_KanoneHitTable[];
extern int g_774a1c;

/* ADDRESS: GOLDTL 0x00586bd0 */
int __cdecl d2_OnKanoneSlotUpdate(struct DATENSATZ_KOPIE* datensatz)
{
	if (datensatz == 0) {
		return 0;
	}
	if (datensatz->index < 0 || datensatz->index >= 3) {
		return 0;
	}
	((struct DATENSATZ_KOPIE*) d2_KanoneHitTable)[datensatz->index] = *datensatz;
	g_774a1c = 1;
	return 1;
}
