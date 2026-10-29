/* Inferred private view: only the index and 56-byte copy extent are known. */
struct DATENSATZ_KOPIE {
	int index;
	unsigned char unbekannt_04[52];
};

extern char g_77dda0[];
extern int g_774a1c;

/* ADDRESS: GOLDTL 0x00586bd0 */
int __cdecl fcn_00586bd0(struct DATENSATZ_KOPIE* datensatz)
{
	if (datensatz == 0) {
		return 0;
	}
	if (datensatz->index < 0 || datensatz->index >= 3) {
		return 0;
	}
	((struct DATENSATZ_KOPIE*) g_77dda0)[datensatz->index] = *datensatz;
	g_774a1c = 1;
	return 1;
}
