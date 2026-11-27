

int __cdecl d2_CreateGuiElement(short, short, int);

int __cdecl d2_CreateElementAt(short x, short y, int type)
{
	return d2_CreateGuiElement(x, y, type);
}
