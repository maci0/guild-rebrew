


typedef struct
{
	char pad[0x188];
	char active;
	char tail[0x93];
} Ent21c;
// SIZE 0x21c

extern int g_9b4a40[];

void __cdecl fcn_004cfa80(void);
void __cdecl d2_OpenEntityStatusPopup(int, Ent21c*);

void __cdecl d2_UpdateEntityOverlays(int context)
{
	Ent21c* entity;

	fcn_004cfa80();
	for (entity = (Ent21c*) g_9b4a40; (int) entity < (int) ((Ent21c*) g_9b4a40 + 32); entity++) {
		if (entity->active != 0) {
			d2_OpenEntityStatusPopup(context, entity);
		}
	}
}
