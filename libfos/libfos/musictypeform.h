/*	libfos
	Copyright 2015 Jonathan Wilson

	This file is part of libfos
	libfos is free software; you can redistribute it and/or modify it under
	the terms of the GNU General Public License as published by the Free
	Software Foundation; either version 3, or (at your option) any later
	version. See the file COPYING for more details.
*/
#pragma once
#include "form.h"
class MusicTypeForm : public Form, public SoundFile
{
public:
	MusicTypeForm(FormHeader h,ModFile *f) : Form(h,f)
	{
	}
protected:
	virtual void Load(FileRead *f)
	{
		while (readSize < uncompsize)
		{
			SubrecordHeader h = ReadSubrecord(f);
			switch(h.type)
			{
			FormLoad();
			SoundFileLoad();
			default:
				printf("Unknown subrecord found");
				__debugbreak();
				break;
			}
		}
	}
	virtual void Save(FileWrite *f)
	{
		FormSave();
		SoundFileSave();
	}
	virtual int GetSaveSize()
	{
		int size = 0;
		FormGetSaveSize();
		SoundFileGetSaveSize();
		return size;
	}
};
