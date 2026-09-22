/*	libess
	Copyright 2013 Jonathan Wilson

	This file is part of libess
	libess is free software; you can redistribute it and/or modify it under
	the terms of the GNU General Public License as published by the Free
	Software Foundation; either version 2, or (at your option) any later
	version. See the file COPYING for more details.
*/
#include "essfile.h"
int main()
{
	ESSFile *file = new ESSFile();
	if (!file->Open("autosave.ess"))
	{
		return 1;
	}
	file->Save("test.ess");
	return 0;
}

