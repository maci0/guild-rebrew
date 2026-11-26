float __cdecl fcn_0050f980(unsigned int a0, unsigned int a1, unsigned int a2);
int __cdecl amt_GetOfficeRank(int);
int __cdecl fcn_004e6f10(int);
float __cdecl amt_GetOfficeAffinityScore(unsigned char*, int);


/* ADDRESS: GOLDTL 0x004ad500 */
float __cdecl fcn_004ad500(unsigned char* subjectEntity, unsigned short* otherEntity, int a3, int a4)
{
	float d;
	float w;
	float r1;
	float r2;
	float s1;
	float s2;

	d = fcn_0050f980(*(unsigned short*) subjectEntity, *otherEntity, 1) * 0.01f;
	if (a4 != 0)
		d = d + d;
	w = (subjectEntity[0xd] + 1) * 0.1f;
	w = w + w;
	r1 = (float) amt_GetOfficeRank(subjectEntity[0x166]) / amt_GetOfficeRank(0x1b);
	r2 = (float) amt_GetOfficeRank(subjectEntity[0x167]) / amt_GetOfficeRank(0x1b);
	s1 = 0.0f;
	if (subjectEntity[0x166] != 0)
		s1 = amt_GetOfficeAffinityScore(subjectEntity, fcn_004e6f10(subjectEntity[0x166]));
	s2 = 0.0f;
	if (subjectEntity[0x167] != 0)
		s2 = amt_GetOfficeAffinityScore(subjectEntity, fcn_004e6f10(subjectEntity[0x167]));
	return s1 * r1 + s2 * r2 + w + d;
}
