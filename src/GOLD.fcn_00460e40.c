#include "client_scene_resources.h"

extern void __cdecl m_FreeTracked(void *ptr);
extern char *__cdecl fcn_0045f9e0(char *name);
extern void __cdecl fcn_00437390(char *name, void *spec, void **slot60, void **slot64,
	unsigned int mask, unsigned int width, unsigned int width2, int extra);
extern void __cdecl fcn_00460dd0(SCENE_RESOURCE *resource);

/* ADDRESS: GOLD 0x00460e40 */
void __cdecl fcn_00460e40(SCENE_RESOURCE *resource, int selector)
{
	SCENE_RESOURCE *base;
	unsigned char saved;
	unsigned char mode;
	unsigned char flags;
	unsigned char name;
	void *com;
	void **slot60;
	void **slot64;
	char *built;
	unsigned int mask;
	unsigned int width;
	unsigned int count;
	unsigned int index;
	int piece;

	if (resource == 0)
		return;
	if (resource->level <= 0)
		return;
	if ((resource->flags & 2) != 0)
		resource = *(SCENE_RESOURCE **)0xfb9074 + resource->alias;
	saved = *(unsigned char *)0x63342c;
	if (*(unsigned char *)0x633450 != 0) {
		slot60 = &resource->com60;
		if (*slot60 != 0 && (char)selector == 0)
			goto tail;
		if (*slot60 != 0) {
			com = *slot60;
			*(int *)0x146356c = ((int (__stdcall *)(void*))(*(void ***)com)[2])(com);
			*slot60 = 0;
		}
		slot64 = &resource->com64;
		com = *slot64;
		if (com != 0) {
			*(int *)0x146356c = ((int (__stdcall *)(void*))(*(void ***)com)[2])(com);
			*slot64 = 0;
		}
		if ((char)selector != 0 && resource->tracked != 0) {
			m_FreeTracked(resource->tracked);
			resource->tracked = 0;
		}
		if (resource->alias == 0 || resource->name[0] == '*')
			goto tail;
		built = fcn_0045f9e0((char *)resource);
		if (built == 0)
			goto tail;
		flags = resource->flags;
		mask = (flags & 8) ? 0 : *(unsigned int *)0x5fd0b0;
		mode = (flags & 0x40) ? 0 : saved;
		*(unsigned char *)0x63342c = mode;
		width = resource->value;
		piece = resource->extra;
		if ((resource->flags & 4) != 0) {
			fcn_00437390(built, (void *)0xfe79ec, slot60, slot64, mask, width, width, piece);
			resource->result = *(unsigned char *)0xfe79e8;
		} else {
			fcn_00437390(built, (void *)0xfe79c8, slot60, slot64, mask, width, width, piece);
			resource->result = *(unsigned char *)0xfe79c0;
		}
		resource->shifted = resource->value >> *(unsigned char *)0x63342c;
		goto tail;
	}
	com = resource->com60;
	if (com == 0 && resource->com64 == 0 && resource->tracked != 0 && (char)selector == 0)
		goto tail;
	if (com != 0) {
		*(int *)0x146356c = ((int (__stdcall *)(void*))(*(void ***)com)[2])(com);
		resource->com60 = 0;
	}
	com = resource->com64;
	if (com != 0) {
		*(int *)0x146356c = ((int (__stdcall *)(void*))(*(void ***)com)[2])(com);
		resource->com64 = 0;
	}
	if ((char)selector == 0 && resource->tracked != 0)
		m_FreeTracked(resource->tracked);
	name = resource->name[0];
	resource->tracked = 0;
	if (name == '*') {
		fcn_0045fbb0(resource);
		goto tail;
	}
	if (resource->alias != 0) {
		fcn_00460210(fcn_0045f9e0((char *)resource), resource);
		resource->result = 8;
	}
tail:
	fcn_00460dd0(resource);
	*(unsigned char *)0x63342c = saved;
	if (resource->byte70 <= 1 || resource->byte71 != 0)
		return;
	count = *(unsigned int *)0xfb9084;
	base = *(SCENE_RESOURCE **)0xfb9074;
	index = 0;
	if (count > 0) {
		do {
			if (base->level > 0 && base->id == resource->id && base->byte71 > 0)
				fcn_00460e40(base, selector);
			count = *(unsigned int *)0xfb9084;
			index++;
			base++;
		} while (index < count);
	}
}
