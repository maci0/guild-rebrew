


#include <stdio.h>
#include <string.h>

int __cdecl fcn_004a4200(char* name)
{
	char buf[0x80];

	if (_strcmpi(name, "APS") == 0) {
		return 0;
	}
	if (_strcmpi(name, "UNVERSEHRTHEIT") == 0) {
		return 1;
	}
	if (_strcmpi(name, "WOHNUNG") == 0) {
		return 2;
	}
	if (_strcmpi(name, "GELD") == 0) {
		return 3;
	}
	if (_strcmpi(name, "BERUF") == 0) {
		return 4;
	}
	if (_strcmpi(name, "VERGNUEGEN") == 0) {
		return 5;
	}
	if (_strcmpi(name, "ANSEHEN") == 0) {
		return 6;
	}
	if (_strcmpi(name, "AMT") == 0) {
		return 7;
	}
	if (_strcmpi(name, "BILDUNG") == 0) {
		return 8;
	}
	if (_strcmpi(name, "RECHTSCHAFFENHEIT") == 0) {
		return 9;
	}
	if (_strcmpi(name, "GEMEINHEIT") == 0) {
		return 10;
	}
	if (_strcmpi(name, "SICHERHEIT") == 0) {
		return 11;
	}
	if (_strcmpi(name, "FORTPFLANZUNG") == 0) {
		return 12;
	}
	if (_strcmpi(name, "TRAEGHEIT") == 0) {
		return 13;
	}
	sprintf(buf, "amt_GetDesireByName(): Unbekanntes Bed\xfcrfnis: %s", name);
	return -1;
}
