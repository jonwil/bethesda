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
struct WeatherColor
{
	Color rise;
	Color day;
	Color set;
	Color night;
};
struct WeatherColors
{
	WeatherColor upperSky;
	WeatherColor fog;
	WeatherColor lowerClouds;
	WeatherColor ambient;
	WeatherColor sunlight;
	WeatherColor sun;
	WeatherColor stars;
	WeatherColor lowerSky;
	WeatherColor horizon;
	WeatherColor upperClouds;
};
struct WeatherFog
{
	float fogDayNear;
	float fogDayFar;
	float fogNightNear;
	float fogNightFar;
};
struct WeatherHDR
{
	float eyeAdaptSpeed;
	float blurRadius;
	float blurPasses;
	float emissiveMult;
	float targetLum;
	float upperLumClamp;
	float brightScale;
	float brightClamp;
	float lumRampNoTex;
	float lumRampMin;
	float lumRampMax;
	float sunLightDimmer;
	float grassDimmer;
	float treeDimmer;
};
struct WeatherData
{
	ubyte windSpeed;
	ubyte lowerCloudSpeed;
	ubyte upperCloudSpeed;
	ubyte transDelta;
	ubyte sunGlare;
	ubyte sunDamage;
	ubyte rainFadeIn;
	ubyte rainFadeOut;
	ubyte boltFadeIn;
	ubyte boltFadeOut;
	ubyte boltFrequency;
	ubyte weatherType;
	ubyte boltRed;
	ubyte boltGreen;
	ubyte boltBlue;
};
struct WeatherSound
{
	formid sound;
	ulong type;
};
class WeatherForm : public Form
{
protected:
	char *editorID;
	char *upperTexture;
	char *lowerTexture;
	char *model;
	float boundRadius;
	ulong textureHashesCount;
	TextureHash *textureHashes;
	WeatherColors colors;
	WeatherFog fog;
	WeatherHDR hdr;
	WeatherData data;
	SimpleDynVecClass<WeatherSound> sounds;
public:
	WeatherForm(FormHeader h,ModFile *f) : Form(h,f), editorID(0), upperTexture(0), lowerTexture(0), model(0), boundRadius(0), textureHashesCount(0), textureHashes(0), sounds(0)
	{
	}
	virtual ~WeatherForm()
	{
		if (editorID)
		{
			delete[] editorID;
		}
		if (model)
		{
			delete[] model;
		}
		if (textureHashes)
		{
			delete[] textureHashes;
		}
		if (upperTexture)
		{
			delete[] upperTexture;
		}
		if (lowerTexture)
		{
			delete[] lowerTexture;
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
			case 'CNAM':
				upperTexture = f->readzstring(h.size);
				readSize += h.size;
				break;
			case 'DNAM':
				lowerTexture = f->readzstring(h.size);
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
			case 'NAM0':
				colors = f->read<WeatherColors>();
				readSize += sizeof(WeatherColors);
				break;
			case 'FNAM':
				fog = f->read<WeatherFog>();
				readSize += sizeof(WeatherFog);
				break;
			case 'HNAM':
				hdr = f->read<WeatherHDR>();
				readSize += sizeof(WeatherHDR);
				break;
			case 'DATA':
				data = f->read<WeatherData>();
				readSize += sizeof(WeatherData);
				break;
			case 'SNAM':
				sounds.Add(f->read<WeatherSound>());
				readSize += sizeof(WeatherSound);
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
		WriteZStringSubrecord('CNAM',upperTexture,f);
		WriteZStringSubrecord('DNAM',lowerTexture,f);
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
		WriteSubrecord('NAM0',sizeof(WeatherColors),f);
		f->write<WeatherColors>(colors);
		WriteSubrecord('FNAM',sizeof(WeatherFog),f);
		f->write<WeatherFog>(fog);
		WriteSubrecord('HNAM',sizeof(WeatherHDR),f);
		f->write<WeatherHDR>(hdr);
		WriteSubrecord('DATA',sizeof(WeatherData),f);
		f->write<WeatherData>(data);
		for (int i = 0;i < sounds.Count();i++)
		{
			WriteSubrecord('SNAM',sizeof(WeatherSound),f);
			f->write<WeatherSound>(sounds[i]);
		}
	}
	virtual int GetSaveSize()
	{
		int size = 0;
		size += ZStringSubrecordSize(editorID);
		size += ZStringSubrecordSize(model);
		size += ZStringSubrecordSize(upperTexture);
		size += ZStringSubrecordSize(lowerTexture);
		if (model)
		{
			size += ComputeSubrecordSize(4);
		}
		if (textureHashes)
		{
			size += ComputeSubrecordSize(textureHashesCount * sizeof(TextureHash));
		}
		size += ComputeSubrecordSize(sizeof(WeatherColors));
		size += ComputeSubrecordSize(sizeof(WeatherFog));
		size += ComputeSubrecordSize(sizeof(WeatherHDR));
		size += ComputeSubrecordSize(sizeof(WeatherData));
		for (int i = 0;i < sounds.Count();i++)
		{
			size += ComputeSubrecordSize(sizeof(WeatherSound));
		}
		return size;
	}
};
