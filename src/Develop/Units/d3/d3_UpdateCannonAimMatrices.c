extern float d3_UnitAxisVectors[3];



void __cdecl d3_TransformDirection(int, void*, void*);

/* ADDRESS: GOLDDE 0x0056dc00 */
void __cdecl d3_UpdateCannonAimMatrices(char* obj)
{
	d3_TransformDirection(*(int*) (obj + 0x8c), (void*) d3_UnitAxisVectors, obj + 0x24);
	d3_TransformDirection(*(int*) (obj + 0x8c), (void*) (d3_UnitAxisVectors + 8), obj + 0x44);
	d3_TransformDirection(*(int*) (obj + 0x8c), (void*) (d3_UnitAxisVectors + 4), obj + 0x34);
}
