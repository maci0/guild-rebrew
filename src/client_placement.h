#ifndef CLIENT_PLACEMENT_H
#define CLIENT_PLACEMENT_H

/* Inferred local views; native clears and accesses establish these extents. */
typedef struct LC_GEBAEUDE_BAUPLATZ {
	char name[0x40];
	float position[3];
	char unbekannt_4c[4];
	char* node;
} LC_GEBAEUDE_BAUPLATZ;

typedef struct LC_OBJECT_LIST {
	char* objects[32];
	int count;
} LC_OBJECT_LIST;

int __cdecl fcn_00597ff0(int key, char* out);
int __cdecl lc_GetGebaeudeBauplatz(LC_GEBAEUDE_BAUPLATZ* out, unsigned char* obj);
char __cdecl fcn_00598550(char* object, void* context);
char __cdecl fcn_005982d0(char* object, void* context);
char __cdecl fcn_0058fa00(char* object, void* context);
void __cdecl fcn_00598330(char* node, int flag);

#endif
