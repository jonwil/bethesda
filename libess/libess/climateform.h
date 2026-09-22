/*	libess
	Copyright 2013 Jonathan Wilson

	This file is part of libess
	libess is free software; you can redistribute it and/or modify it under
	the terms of the GNU General Public License as published by the Free
	Software Foundation; either version 2, or (at your option) any later
	version. See the file COPYING for more details.
*/
#pragma once
#include "form.h"
struct ClimateWeather
{
	formid weather;
	ulong chance;
};
class ClimateForm : public Form
{
protected:
	char *editorID;
	ulong weatherCount;
	ClimateWeather *weatherTypes;
	char *sunTexture;
	char *sunGlareTexture;
	char *model;
	float boundRadius;
	ulong textureHashesCount;
	TextureHash *textureHashes;
	ubyte sunriseBegin;
	ubyte sunriseEnd;
	ubyte sunsetBegin;
	ubyte sunsetEnd;
	ubyte volatility;
	ubyte phaseLength;
public:
	ClimateForm(FormHeader h,ModFile *f) : Form(h,f), editorID(0), weatherCount(0), weatherTypes(0), sunTexture(0), sunGlareTexture(0), model(0), boundRadius(0), textureHashesCount(0), textureHashes(0), sunriseBegin(0), sunriseEnd(0), sunsetBegin(0), sunsetEnd(0), volatility(0), phaseLength(0)
	{
	}
	virtual ~ClimateForm()
	{
		if (editorID)
		{
			delete[] editorID;
		}
		if (weatherTypes)
		{
			delete[] weatherTypes;
		}
		if (model)
		{
			delete[] model;
		}
		if (textureHashes)
		{
			delete[] textureHashes;
		}
	}
protected:
	virtual void Load(FileRead *f)
	{
		while (readSize < uncompsize)
		{
			SubrecordHeader h = ReadSubrecord(f);
			switch(h.type)
			{
			case 'EDID':
				editorID = f->readzstring(h.size);
				readSize += h.size;
				break;
			case 'WLST':
				weatherCount = h.size / sizeof(ClimateWeather);
				weatherTypes = f->readarray<ClimateWeather>(weatherCount);
				readSize += h.size;
				break;
			case 'FNAM':
				sunTexture = f->readzstring(h.size);
				readSize += h.size;
				break;
			case 'GNAM':
				sunGlareTexture = f->readzstring(h.size);
				readSize += h.size;
				break;
			case 'MODL':
				model = f->readzstring(h.size);
				readSize += h.size;
				break;
			case 'MODB':
				boundRadius = f->read<float>();
				readSize += 4;
				break;
			case 'MODT':
				textureHashesCount = h.size / sizeof(TextureHash);
				textureHashes = f->readarray<TextureHash>(h.size / sizeof(TextureHash));
				readSize += h.size;
				break;
			case 'TNAM':
				sunriseBegin = f->read<ubyte>();
				readSize += 1;
				sunriseEnd = f->read<ubyte>();
				readSize += 1;
				sunsetBegin = f->read<ubyte>();
				readSize += 1;
				sunsetEnd = f->read<ubyte>();
				readSize += 1;
				volatility = f->read<ubyte>();
				readSize += 1;
				phaseLength = f->read<ubyte>();
				readSize += 1;
				break;
			default:
				printf("Unknown subrecord found");
				__debugbreak();
				break;
			}
		}
	}
	virtual void Save(FileWrite *f)
	{
		WriteZStringSubrecord('EDID',editorID,f);
		if (weatherTypes)
		{
			WriteSubrecord('WLST',weatherCount * sizeof(ClimateWeather),f);
			f->writearray<ClimateWeather>(weatherCount,weatherTypes);
		}
		WriteZStringSubrecord('FNAM',sunTexture,f);
		WriteZStringSubrecord('GNAM',sunGlareTexture,f);
		WriteZStringSubrecord('MODL',model,f);
		if (model)
		{
			WriteSubrecord('MODB',4,f);
			f->write<float>(boundRadius);
		}
		if (textureHashes)
		{
			WriteSubrecord('MODT',textureHashesCount * sizeof(TextureHash),f);
			f->writearray<TextureHash>(textureHashesCount,textureHashes);
		}
		WriteSubrecord('TNAM',6,f);
		f->write<ubyte>(sunriseBegin);
		f->write<ubyte>(sunriseEnd);
		f->write<ubyte>(sunsetBegin);
		f->write<ubyte>(sunsetEnd);
		f->write<ubyte>(volatility);
		f->write<ubyte>(phaseLength);
	}
	virtual int GetSaveSize()
	{
		int size = 0;
		size += ZStringSubrecordSize(editorID);
		if (weatherTypes)
		{
			size += ComputeSubrecordSize(weatherCount * sizeof(ClimateWeather));
		}
		size += ZStringSubrecordSize(sunTexture);
		size += ZStringSubrecordSize(sunGlareTexture);
		size += ZStringSubrecordSize(model);
		if (model)
		{
			size += ComputeSubrecordSize(4);
		}
		if (textureHashes)
		{
			size += ComputeSubrecordSize(textureHashesCount * sizeof(TextureHash));
		}
		size += ComputeSubrecordSize(6);
		return size;
	}
};
