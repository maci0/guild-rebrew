// SIZE 0x20
typedef struct {
	int p0;
	int x4;
	char p8[0xc];
	unsigned char bpp;
	char p15[7];
	int x1c;
} Surf;

// SIZE 0xe
typedef struct {
	char p0[0xc];
	char kind;
	char mode;
} Img;

Img* __cdecl shp_GrabBit24(int, int, int, int, int, int, int);
char* __cdecl shp_EncodeSpriteBlock(int a1, int a2, int a3, int a4, int a5, unsigned char a8, int a7);
Img* __cdecl d2_GrabBit8(int, int, int, int, int, int, int);
Img* __cdecl shp_GrabBit24NoRS(int, int, int, int, int, int, int);
Img* __cdecl shp_GrabBit16(int, int, int, int, int, int, int);


/* ADDRESS: GOLDTL 0x004788b0 */
Img* __cdecl shp_CreateSpriteFromSurface(int a1, int a2, int a3, int a4, Surf* surface, int mode, char alpha)
{
	Img* imageResult;
	int kind;

	imageResult = 0;
	if (alpha) {
		switch (surface->bpp) {
		case 0x18:
			imageResult = shp_GrabBit24(a1, a2, a3, a4, surface->x1c, mode, surface->x4);
			kind = 2;
			break;
		case 0x10:
			imageResult = shp_EncodeSpriteBlock(a1, a2, a3, a4, surface->x1c, mode, surface->x4);
			kind = 1;
			break;
		case 8:
			imageResult = d2_GrabBit8(a1, a2, a3, a4, surface->x1c, mode, surface->x4);
			kind = 0;
			break;
		default:
			break;
		}
	} else {
		switch (surface->bpp) {
		case 0x18:
			imageResult = shp_GrabBit24NoRS(a1, a2, a3, a4, surface->x1c, mode, surface->x4);
			kind = 2;
			break;
		case 0x10:
			imageResult = shp_GrabBit16(a1, a2, a3, a4, surface->x1c, mode, surface->x4);
			kind = 1;
			break;
		default:
			break;
		}
	}
	if (imageResult != 0) {
		imageResult->kind = (char) kind;
		imageResult->mode = (char) mode;
	}
	return imageResult;
}
