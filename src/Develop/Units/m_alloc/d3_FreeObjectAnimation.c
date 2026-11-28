


void __cdecl m_FreeTracked(int);

/* ADDRESS: GOLDDE 0x0042cd40 */
void __cdecl d3_FreeObjectAnimation(void* object)
{
	if (*(int*) ((char*) object + 0x1d0) != 0) {
		m_FreeTracked(*(int*) ((char*) *(int*) ((char*) object + 0x1d0) + 0x40));
		*(int*) ((char*) *(int*) ((char*) object + 0x1d0) + 0x40) = 0;
		m_FreeTracked(*(int*) ((char*) object + 0x1d0));
		*(int*) ((char*) object + 0x1d0) = 0;
	}
}
