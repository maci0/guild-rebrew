


int __cdecl ahm_LoadAlchemyDataIni(void);
void __cdecl ahm_ResetAlchemyState(int);
int __cdecl ahm_fio_SaveAlchemyData(void);
int __cdecl ahm_LoadAlchemyData(void);

/* ADDRESS: GOLDDE 0x004d9650 */
int __cdecl ahm_ReloadAlchemyPrototypes(int loadFromIni)
{
	if (loadFromIni != 0) {
		if (ahm_LoadAlchemyDataIni() != 0) {
			ahm_ResetAlchemyState(1);
			return ahm_fio_SaveAlchemyData();
		}
		return 0;
	}
	if (ahm_LoadAlchemyData() != 0) {
		ahm_ResetAlchemyState(1);
	}
	return 1;
}
