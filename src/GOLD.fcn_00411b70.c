typedef struct {
	char pad0[0x68];
	char *name;
	char pad6c[0x10];
} Page;

typedef struct {
	char pad0[0xf4];
	char sounds[0x1c];
	Page pages[3];
} Pages;

typedef struct {
	char pad0[0x1ec];
	Pages *pages;
} Model;

void __cdecl fcn_00435740(char *sounds, char *name);

/* ADDRESS: GOLD 0x00411b70 */
int __cdecl fcn_00411b70(Model *model)
{
	int i;
	Pages *pages;

	for (i = 0; i < 3; i++) {
		pages = model->pages;
		if (pages != 0 && pages->pages[i].name != 0) {
			fcn_00435740(pages->sounds, pages->pages[i].name);
		}
	}
	return 1;
}
