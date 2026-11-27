typedef struct View {
	int x0;
	char pad4[0x18];
	int x1c;
	int x20;
	unsigned char x24;
	char pad25[0x67];
} View;

typedef struct Elem {
	int kind;
	char pad[0x10];
} Elem;

void* __cdecl FindSlotEntryFiltered(int a, unsigned char* rec, void* prev,
	void* filter, int mask);
int __cdecl gm_GetEntitySlotIndex(char* a, Elem* e);
int __cdecl gv_FindEntityGraveSlot(int a, unsigned char** out1, void** out2);
void __cdecl io_FormatTextBuffer(void* dest, int id, ...);
int __cdecl d2_CreateRentAGraveDialog(View* view, char* text);
void __cdecl d2_RunRentAGraveMenu(unsigned char* a1, View* view);
void __cdecl d2_DestroyForm(int a);
void __cdecl d2_OpenRentAGraveDialog(unsigned char* a1);
int __cdecl fcn_00526120(int a, int b);
void __cdecl d3_EndCameraAndUiMode(void);

/* ADDRESS: GOLDTL 0x0058fa40 */
void __cdecl d2_RunGraveyardDialog(unsigned char* input)
{
	unsigned char text[0x100];
	View view;
	unsigned char* rec;
	void* obj;

	obj = FindSlotEntryFiltered(
		(int) (0x7f4ca0 + (*(unsigned short*) 0x774970) * 0x21c), input, 0,
		(void*) 0x4f1820, 0xff);
	if (obj != 0) {
		view.x20 = *(int*) obj;
		view.x1c = (int) obj;
		view.x24 = (unsigned char) gm_GetEntitySlotIndex((char*) *(int*) (input + 0x65),
			(Elem*) obj);
		io_FormatTextBuffer(text, 0x4107, ((char**) 0x665f78)[*(int*) obj]);
		if (d2_CreateRentAGraveDialog(&view, (char*) text) != 0) {
			d2_RunRentAGraveMenu(input, &view);
			d2_DestroyForm(view.x0);
			d3_EndCameraAndUiMode();
			return;
		}
		return;
	}
	if (gv_FindEntityGraveSlot((int) (0x7f4ca0 + (*(unsigned short*) 0x774970) * 0x21c),
			&rec, &obj) == 0) {
		d2_OpenRentAGraveDialog(input);
		d3_EndCameraAndUiMode();
		return;
	}
	fcn_00526120(*(int*) 0x14b5f00, 0);
}
