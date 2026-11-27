


typedef struct
{
	int a;
	int b;
	int c;
} V12;
// SIZE 0xc

typedef struct
{
	int h0;
	int h4;
	int x8;
	V12 v;
	int x18;
	int x1c;
	int x20;
} Msg24;
// SIZE 0x24

int __cdecl ahm_FindRecipePrototypeByKey(int id);
int __cdecl cm_SendAllocAlchemist(Msg24* m);

int __cdecl ahm_DispatchAlchemistCommand(char* building, char* order)
{
	Msg24 m;
	char* recipe;

	recipe = (char*) ahm_FindRecipePrototypeByKey(*(int*) (order + 0xc));
	if (recipe == 0) {
		return -1;
	}
	m.x8 = *(int*) (building + 1);
	m.v = *(V12*) (order + 4);
	m.x18 = *(int*) (order + 0x10);
	m.x1c = *(int*) (order + 0x14);
	m.x20 = *(int*) (recipe + 8);
	return cm_SendAllocAlchemist(&m);
}
