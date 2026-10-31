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
int __cdecl fcn_004f1790(char* a, Elem* e);
int __cdecl fcn_004f46e0(int a, unsigned char** out1, void** out2);
void __cdecl io_FormatTextBuffer(void* dest, int id, ...);
int __cdecl fcn_0058c410(View* view, char* text);
void __cdecl fcn_0058cc90(unsigned char* a1, View* view);
void __cdecl fcn_00471e30(int a);
void __cdecl fcn_0058d020(unsigned char* a1);
int __cdecl fcn_00526120(int a, int b);
void __cdecl fcn_00532ef0(void);

/* ADDRESS: GOLDTL 0x0058fa40 */
void __cdecl fcn_0058fa40(unsigned char* a1)
{
	unsigned char text[0x100];
	View view;
	unsigned char* rec;
	void* obj;

	obj = FindSlotEntryFiltered(
		(int) (0x7f4ca0 + (*(unsigned short*) 0x774970) * 0x21c), a1, 0,
		(void*) 0x4f1820, 0xff);
	if (obj != 0) {
		view.x20 = *(int*) obj;
		view.x1c = (int) obj;
		view.x24 = (unsigned char) fcn_004f1790((char*) *(int*) (a1 + 0x65),
			(Elem*) obj);
		io_FormatTextBuffer(text, 0x4107, ((char**) 0x665f78)[*(int*) obj]);
		if (fcn_0058c410(&view, (char*) text) != 0) {
			fcn_0058cc90(a1, &view);
			fcn_00471e30(view.x0);
			fcn_00532ef0();
			return;
		}
		return;
	}
	if (fcn_004f46e0((int) (0x7f4ca0 + (*(unsigned short*) 0x774970) * 0x21c),
			&rec, &obj) == 0) {
		fcn_0058d020(a1);
		fcn_00532ef0();
		return;
	}
	fcn_00526120(*(int*) 0x14b5f00, 0);
}
