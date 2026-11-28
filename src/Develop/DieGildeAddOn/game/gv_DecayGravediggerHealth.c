


extern char* gm_CityEntity;
extern float g_662914;
extern float flt_0_0;

float __cdecl gv_CalcDecayReduction(char* o);
void __cdecl cm_RequestChangeFloat(int id, int kind, float v);

/* ADDRESS: GOLDDE 0x004df830 */
int __cdecl gm_DecayServantHealth(char* entity)
{
	char* graveyard;
	float decay;
	float remaining;

	if (entity == 0 || entity[2] != 0x14 || entity[8] == 0) {
		return 0;
	}
	graveyard = *(char**) (entity + 0x16c);
	if (graveyard != 0 && *(unsigned short*) (graveyard + 0x27) != 0xffff && *(unsigned short*) (graveyard + 0x27) != *((unsigned short*)gm_CityEntity)) {
		decay = *(float*) (entity + 0x14) - gv_CalcDecayReduction(graveyard) * g_662914;
		remaining = *(float*) (entity + 0x1c) - decay;
		cm_RequestChangeFloat(*(int*) (entity + 4), 0x1c, -decay);
		if (!(remaining <= flt_0_0)) {
			return 0;
		}
	} else {
		cm_RequestChangeFloat(*(int*) (entity + 4), 0x1c, -1000.0f);
	}
	return 1;
}
