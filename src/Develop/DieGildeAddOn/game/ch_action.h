#ifndef CH_ACTION_H
#define CH_ACTION_H

/* Inferred action record; field meanings and names remain provisional. */
typedef struct CH_ACTION CH_ACTION;

struct CH_ACTION {
	void (__cdecl* ausfuehren)(CH_ACTION* t);
	void (__cdecl* abschluss)(CH_ACTION* t);
	unsigned char stufe;
	char art;
	char pad0a[2];
	int zustand;
	unsigned char merkmale;
	char pad11[3];
	char* besitzer;
	char pad18[0x24 - 0x18];
	CH_ACTION* vorherige;
	CH_ACTION* naechste;
	char pad2c[4];
	int parameter;
	int unbekannt_034;
	int unbekannt_038;
	char pad3c[0xf0 - 0x3c];
	char name[0x40];
	char name_2[0x40];
	int unbekannt_170;
	int unbekannt_174;
	float unbekannt_178;
	char pad17c[0x190 - 0x17c];
	unsigned char unbekannt_190;
	char pad191[3];
};

int __cdecl ch_ExecuteAction(char* object);
void __cdecl ch_ClearSitting(unsigned char* object);

#endif
