#include <stdio.h>
#include <string.h>
#include "Develop/DieGildeAddOn/game/game_data.h"

/* SIZE 0x7c */
typedef struct {
	char pad0[0x68];
	char* name;
	char pad6c;
	unsigned char flags;
	char pad6e[0xe];
} Page;

/* SIZE 0x284 (GOLD) / 0x590 (GOLDTL) */
typedef struct {
	char pad0[0xf4];
#if defined(REBREW_GOLD)
	char sounds[0x1c];
#else
	char sounds[0x328];
#endif
	Page pages[3];
} Pages;

/* SIZE 0x1f0 */
typedef struct {
	char pad0[0x1ec];
	Pages* pages;
} Model;

/* SIZE 0x272 */
typedef struct {
	Model* model;
	char pad4[0x224];
	int widgets[18];
	signed char page;
	signed char count;
} Book;

extern char g_631090[];
extern char* g_6f240c;
extern char g_6b5c60[];

char* __cdecl StripPathAndExt(char*);
void __cdecl d3_RemoveObjectAnimation(char*, char*);
void __cdecl d2_UpdateFormPageTextures(int, char*, char*);
void __cdecl d2_SetFormVisible(int, int);
void __cdecl d3_AttachObjectAnim(Model*, char*, int);
void __cdecl d2_SetFormTextures(int, char*, char*);
void __cdecl d2_SetGroupVisibility(int, int);
void __cdecl d3_ApplyObjectAnimation(Model*, char*, int);
void __cdecl d2_HandleBookPageButton(Book*);
void* __cdecl fcn_00426fa0(char*, const char*, int, int, int, int, int);
void* __cdecl sb_PlayVoice(char*, const char*, int, int, int, int, int);

#if defined(REBREW_GOLD)
/* ADDRESS: GOLD 0x0052f740 */
int __cdecl d2_TurnBookPages(Book* book, signed char dir)
{
	char top[0x40];
	char bottom[0x40];
	char name[0x200];
	Page* pg;
	char* r;
	int i;

	if (book == 0) {
		return 0;
	}
	if (dir >= 0) {
		if (book->page + 2 >= book->count) {
			return 0;
		}
	} else if (book->page - 2 < 0) {
		return 0;
	}
	for (i = 0; i < 3; i++) {
		strcpy(name, "buch\\Buch_vorblaettern.baf");
		r = StripPathAndExt(name);
		pg = &book->model->pages->pages[i];
		if (pg->name != 0 && _strcmpi(pg->name, r) == 0 && dir > 0) {
			if (!(pg->flags & 0x20)) {
				return 0;
			}
			d3_RemoveObjectAnimation(book->model->pages->sounds, book->model->pages->pages[i].name);
		}
		strcpy(name, "buch\\Buch_zurueckblaettern.baf");
		r = StripPathAndExt(name);
		if (pg->name != 0 && _strcmpi(pg->name, r) == 0) {
			if (!(pg->flags & 0x20) && dir > 0) {
				return 0;
			}
			d3_RemoveObjectAnimation(book->model->pages->sounds, book->model->pages->pages[i].name);
		}
	}
	for (i = 0; i < 3; i++) {
		if (book->model->pages->pages[i].name != 0 && !(book->model->pages->pages[i].flags & 0x20)) {
			return 0;
		}
	}
	for (i = 0; i < book->count; i++) {
		if (i >= (dir > 0 ? book->page : book->page - 2) && i <= (dir > 0 ? book->page + 4 : book->page + 2)) {
			sprintf(top, "Buch_Seite%i_oben_ns_nm", (i & 3) + 1);
			sprintf(bottom, "Buch_Seite%i_unten_ns_nm", (i & 3) + 1);
			d2_UpdateFormPageTextures(book->widgets[i], top, bottom);
			d2_SetFormVisible(book->widgets[i], 1);
		} else {
			d2_UpdateFormPageTextures(book->widgets[i], &(*(char*)g_631090), &(*(char*)g_631090));
			d2_SetFormVisible(book->widgets[i], 0);
		}
	}
	if (dir > 0) {
		d3_AttachObjectAnim(book->model, "buch\\Buch_vorblaettern.baf", 0x12);
	} else {
		d3_AttachObjectAnim(book->model, "buch\\Buch_zurueckblaettern.baf", 0x12);
	}
	book->page += dir;
	d2_HandleBookPageButton(book);
	fcn_00426fa0(g_6f240c, "Umblaettern_s", 1, 0x3f, 0x7f, 0, 0);
	return 1;
}
#else
/* ADDRESS: GOLDTL 0x00535270 */
int __cdecl d2_TurnBookPages(Book* b, signed char dir)
{
	char top[0x40];
	char bottom[0x40];
	char name[0x200];
	Page* pg;
	char* r;
	int i;

	if (b == 0) {
		return 0;
	}
	if (dir >= 0) {
		if (b->page + 2 >= b->count) {
			return 0;
		}
	} else if (b->page - 2 < 0) {
		return 0;
	}
	for (i = 0; i < 3; i++) {
		strcpy(name, "buch\\Buch_vorblaettern.baf");
		r = StripPathAndExt(name);
		pg = &b->model->pages->pages[i];
		if (pg->name != 0 && _strcmpi(pg->name, r) == 0 && dir > 0) {
			if (!(pg->flags & 0x20)) {
				return 0;
			}
			d3_RemoveObjectAnimation(b->model->pages->sounds, b->model->pages->pages[i].name);
		}
		strcpy(name, "buch\\Buch_zurueckblaettern.baf");
		r = StripPathAndExt(name);
		if (pg->name != 0 && _strcmpi(pg->name, r) == 0) {
			if (!(pg->flags & 0x20) && dir > 0) {
				return 0;
			}
			d3_RemoveObjectAnimation(b->model->pages->sounds, b->model->pages->pages[i].name);
		}
	}
	for (i = 0; i < 3; i++) {
		if (b->model->pages->pages[i].name != 0 && !(b->model->pages->pages[i].flags & 0x20)) {
			return 0;
		}
	}
	for (i = 0; i < b->count; i++) {
		if (i >= (dir > 0 ? b->page : b->page - 2) && i <= (dir > 0 ? b->page + 4 : b->page + 2)) {
			sprintf(top, "Buch_Seite%i_oben_ns_nm", (i & 3) + 1);
			sprintf(bottom, "Buch_Seite%i_unten_ns_nm", (i & 3) + 1);
			d2_SetFormTextures(b->widgets[i], top, bottom);
			d2_SetGroupVisibility(b->widgets[i], 1);
		} else {
			d2_SetFormTextures(b->widgets[i], &(*(char*)g_6b5c60), &(*(char*)g_6b5c60));
			d2_SetGroupVisibility(b->widgets[i], 0);
		}
	}
	if (dir > 0) {
		d3_ApplyObjectAnimation(b->model, "buch\\Buch_vorblaettern.baf", 0x12);
	} else {
		d3_ApplyObjectAnimation(b->model, "buch\\Buch_zurueckblaettern.baf", 0x12);
	}
	b->page += dir;
	d2_HandleBookPageButton(b);
	sb_PlayVoice(((char*)g_7747c4), "Umblaettern_s", 1, 0x3f, 0x7f, 0, 0);
	return 1;
}
#endif
