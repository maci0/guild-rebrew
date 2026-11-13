#include "gold_gui.h"
extern GuiEnt* g_00f8f080;
int __cdecl fcn_0046c9e0(void);
void __cdecl fcn_00469170(int, void**, int*);
void __cdecl d2_AddRefcount(int);
int __cdecl fcn_0047cd10(int, int, void*, int);
char* __cdecl fcn_0047cb60(void*, unsigned short);

/* ADDRESS: GOLD 0x0046cb10 */
int __cdecl fcn_0046cb10(int x, int y, int type)
{
	void* data;
	GuiEnt* s;
	char* resource;
	char* shape;
	int id;
	int handle;

	data = 0;
	if (type > *(int*) 0x6ed91c)
		return -1;
	id = fcn_0046c9e0();
	s = &g_00f8f080[id];
	if (id >= 0x300)
		return -1;
	fcn_00469170(type, &data, &type);
	s->data = data;
	s->f08 = type;
	s->kind = *(int*) (*(char**) 0x6ed918 + type * 0x54 + 0x3c);
	s->x = (short) x;
	s->y = (short) y;
	s->f1e = *(short*) 0x6f0458;
	s->f20 = *(short*) 0x5fed5c;
	s->f22 = *(short*) 0x6f045c;
	s->f24 = *(short*) 0x5fed60;
	s->f1c = 2;
	d2_AddRefcount(type);
	if (s->kind == 8)
		s->f4c = 1;
	*(int*) ((char*) s + 0x1d4) = -1;
	*(int*) ((char*) s + 0x1d8) = 0;
	*(int*) ((char*) s + 0x1dc) = 0;
	switch (s->kind) {
	case 1:
		resource = g_00f8f080[id].data;
		s->w = *(short*) (resource + 0x2c);
		s->f16 = *(short*) (resource + 0x2e);
		break;
	case 4:
		handle = fcn_0047cd10(x, y, g_00f8f080[id].data, 0);
		g_00f8f080[id].bild_offset = handle;
		resource = g_00f8f080[id].data;
		g_00f8f080[id].w = *(short*) (resource + 0x2c);
		g_00f8f080[id].f16 = *(short*) (resource + 0x2e);
		break;
	case 5:
	case 8:
		s->bild_offset = *(int*) 0x6ed98c;
		resource = g_00f8f080[id].data;
		shape = fcn_0047cb60(resource, (unsigned short) g_00f8f080[id].bild_offset);
		s->w = *(short*) (shape + 6);
		s->f16 = *(short*) (shape + 10);
		*(int*) ((char*) s + 0x1cc) = -1;
		*(int*) ((char*) s + 0x1d0) = -1;
		*(int*) ((char*) s + 0x1c4) = *(unsigned short*) (resource + 0x2c);
		*(int*) ((char*) s + 0x1c8) = *(unsigned short*) (resource + 0x2e);
		*((char*) &g_00f8f080[id] + 0x6c) = 8;
		*((char*) &g_00f8f080[id] + 0x6d) = 8;
		break;
	case 17:
		resource = g_00f8f080[id].data;
		g_00f8f080[id].w = *(short*) (resource + 0xc);
		g_00f8f080[id].f16 = *(short*) (resource + 0xe);
		g_00f8f080[id].bild_offset = 2;
		break;
	}
	return id;
}
