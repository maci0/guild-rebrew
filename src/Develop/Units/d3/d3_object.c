#include "d3_object.h"

#ifdef REBREW_GOLD
int __cdecl fcn_0043c7a0(int);
#else
void __cdecl fcn_004398d0(char*);
#endif

void __cdecl d3_UnlinkObject(D3_OBJECT* object)
{
	if (object->naechstes != 0) {
		object->naechstes->voriges = object->voriges;
		if (object->voriges != 0) {
			object->voriges->naechstes = object->naechstes;
		} else if (object->eltern->kinder == object) {
			object->eltern->kinder = object->naechstes;
		}
	} else {
		if (object->voriges != 0) {
			object->voriges->naechstes = 0;
		} else if (object->eltern->kinder == object) {
			object->eltern->kinder = 0;
		}
	}
	object->eltern = 0;
	object->voriges = 0;
	object->naechstes = 0;
	object->flags0 &= ~2;
}

char __cdecl d3_DestroyObject(D3_OBJECT* object)
{
	if (object != 0) {
		d3_UnlinkObject(object);
#ifdef REBREW_GOLD
		fcn_0043c7a0((int) object);
#else
		fcn_004398d0((char*) object);
#endif
		return 1;
	}
	return 0;
}
