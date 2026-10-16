#include "d3_object.h"
#include "../m_alloc/m_alloc.h"
#include "d3_camera.h"

#ifdef REBREW_GOLD
void __cdecl fcn_0043cc90(char*);
#else
void __cdecl fcn_00439c90(char*);
#endif

#ifdef REBREW_GOLD
int __cdecl fcn_0043c7a0(int);
#else
void __cdecl d3_DisposeObject(char*);
#endif

/* Inferred name and placement; this removes a list node, not its hierarchy. */
void __cdecl d3_RemoveObjectFromList(D3_OBJECT* object)
{
    switch (object->art) {
    case 3:
        if (g_6b8014 == (char*) object) {
            g_6b8014 = 0;
        }
    case 1:
    case 2:
    case 4:
    case 5:
    case 6:
    case 7:
    case 8:
        object->naechstes->voriges = object->voriges;
        object->voriges->naechstes = object->naechstes;
        break;
    }
    object->flags0 &= ~2;
}

/* Inferred name and placement; native draw-part providers remain separate. */
void __cdecl d3_CleanupObjectDrawData(D3_OBJECT* object)
{
	int i;

	if (object->zeichendaten != 0) {
		for (i = 0; i < object->zeichendaten->teile_anzahl; i++) {
#ifdef REBREW_GOLD
			fcn_0043cc90((char*) &object->zeichendaten->teile[i]);
#else
			fcn_00439c90((char*) &object->zeichendaten->teile[i]);
#endif
		}
#ifdef REBREW_GOLD
		fcn_0043cc90((char*) &object->zeichendaten->teile[3]);
#else
		fcn_00439c90((char*) &object->zeichendaten->teile[3]);
#endif
		object->zeichendaten->teile_anzahl = 0;
		m_FreeTracked(object->zeichendaten);
		object->zeichendaten = 0;
	}
	object->kontext = 0;
}

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
		d3_DisposeObject((char*) object);
#endif
		return 1;
	}
	return 0;
}

/* Inferred auxiliary cleanup; per-record providers retain their native identities. */
#ifdef REBREW_GOLD
void __cdecl fcn_0045cc80(char*);
#else
void __cdecl fcn_00456b10(char*);
#endif
void __cdecl d3_CleanupObjectAuxSlots(D3_OBJECT* object)
{
    int i;
    if (object->zusatz_flag && object->zeichendaten != 0) {
        for (i = 0; i < 4; i++) {
            if (object->zeichendaten->zusatz[i].unbekannt_000 != 0) {
#ifdef REBREW_GOLD
                fcn_0045cc80((char*) &object->zeichendaten->zusatz[i]);
#else
                fcn_00456b10((char*) &object->zeichendaten->zusatz[i]);
#endif
                object->zeichendaten->zusatz[i].objekt = 0;
                object->zeichendaten->zusatz[i].unbekannt_a = 0;
                object->zeichendaten->zusatz[i].unbekannt_b = 0;
                object->zeichendaten->zusatz[i].unbekannt_c = 0;
            }
        }
    }
}
