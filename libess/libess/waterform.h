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
#pragma pack(push,1)
struct WaterData
{
	float windVelocity;
	float windDirection;
	float waveAmp;
	float waveFreq;
	float sunPower;
	float reflectAmt;
	float fresnelAmt;
	float xSpeed;
	float ySpeed;
	float fogNear;
	float fogFar;
	Color shallow;
	Color deep;
	Color refl;
	ulong blend;
	float rainForce;
	float rainVelocity;
	float rainFalloff;
	float rainDampner;
	float rainSize;
	float dispForce;
	float dispVelocity;
	float dispFalloff;
	float dispDampner;
	float dispSize;
	ushort damage;
};
struct WaterData2
{
	float windVelocity;
	float windDirection;
	float waveAmp;
	float waveFreq;
	float sunPower;
	float reflectAmt;
	float fresnelAmt;
	float xSpeed;
	float ySpeed;
	float fogNear;
	float fogFar;
	Color shallow;
	Color deep;
	Color refl;
	ulong blend;
	float rainForce;
	float rainVelocity;
	float rainFalloff;
	float rainDampner;
	float rainSize;
	float dispForce;
	ubyte pad[2];
};
struct WaterData3
{
	float windVelocity;
	float windDirection;
	float waveAmp;
	float waveFreq;
	float sunPower;
	float reflectAmt;
	float fresnelAmt;
	float xSpeed;
	float ySpeed;
	float fogNear;
	float fogFar;
	Color shallow;
	Color deep;
	Color refl;
	ulong blend;
	ubyte pad[2];
};
struct WaterData4
{
	float windVelocity;
	float windDirection;
	float waveAmp;
	float waveFreq;
	float sunPower;
	float reflectAmt;
	float fresnelAmt;
	float xSpeed;
	float ySpeed;
	float fogNear;
	ubyte pad[2];
};
struct WaterData5
{
	ubyte pad[2];
};
#pragma pack(pop)
class WaterForm : public Form
{
protected:
	char *editorID;
	char *texture;
	ubyte opacity;
	ubyte flags;
	char *material;
	formid sound;
	bool dataSeen;
	WaterData data;
	WaterData2 data2;
	WaterData3 data3;
	WaterData4 data4;
	WaterData5 data5;
	bool gnamSeen;
	formid dayWater;
	formid nightWater;
	formid underWater;
	bool data2s;
	bool data3s;
	bool data4s;
	bool data5s;
public:
	WaterForm(FormHeader h,ModFile *f) : Form(h,f), editorID(0), texture(0), opacity(0), flags(0), material(0), sound(0), dataSeen(false), gnamSeen(false), dayWater(0), nightWater(0), underWater(0), data2s(0), data3s(0), data4s(0), data5s(0)
	{
	}
	virtual ~WaterForm()
	{
		if (editorID)
		{
			delete[] editorID;
		}
		if (texture)
		{
			delete[] texture;
		}
		if (material)
		{
			delete[] material;
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
			case 'TNAM':
				texture = f->readzstring(h.size);
				readSize += h.size;
				break;
			case 'ANAM':
				opacity = f->read<ubyte>();
				readSize += 1;
				break;
			case 'FNAM':
				flags = f->read<ubyte>();
				readSize += 1;
				break;
			case 'MNAM':
				material = f->readzstring(h.size);
				readSize += h.size;
				break;
			case 'SNAM':
				sound = f->read<formid>();
				readSize += 4;
				break;
			case 'DATA':
				dataSeen = true;
				if (h.size == sizeof(WaterData))
				{
					data = f->read<WaterData>();
					readSize += sizeof(WaterData);
				}
				else if (h.size == sizeof(WaterData2))
				{
					data2s = true;
					data2 = f->read<WaterData2>();
					readSize += sizeof(WaterData2);
				}
				else if (h.size == sizeof(WaterData3))
				{
					data3s = true;
					data3 = f->read<WaterData3>();
					readSize += sizeof(WaterData3);
				}
				else if (h.size == sizeof(WaterData4))
				{
					data4s = true;
					data4 = f->read<WaterData4>();
					readSize += sizeof(WaterData4);
				}
				else
				{
					data5s = true;
					data5 = f->read<WaterData5>();
					readSize += sizeof(WaterData5);
				}
				break;
			case 'GNAM':
				gnamSeen = true;
				dayWater = f->read<formid>();
				readSize += 4;
				nightWater = f->read<formid>();
				readSize += 4;
				underWater = f->read<formid>();
				readSize += 4;
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
		WriteZStringSubrecord('TNAM',texture,f);
		WriteSubrecord('ANAM',1,f);
		f->write<ubyte>(opacity);
		WriteSubrecord('FNAM',1,f);
		f->write<ubyte>(flags);
		WriteZStringSubrecord('MNAM',material,f);
		if (sound)
		{
			WriteSubrecord('SNAM',4,f);
			f->write<formid>(sound);
		}
		if (dataSeen)
		{
			if (data2s)
			{
				WriteSubrecord('DATA',sizeof(WaterData2),f);
				f->write<WaterData2>(data2);
			}
			else if (data3s)
			{
				WriteSubrecord('DATA',sizeof(WaterData3),f);
				f->write<WaterData3>(data3);
			}
			else if (data4s)
			{
				WriteSubrecord('DATA',sizeof(WaterData4),f);
				f->write<WaterData4>(data4);
			}
			else if (data5s)
			{
				WriteSubrecord('DATA',sizeof(WaterData5),f);
				f->write<WaterData5>(data5);
			}
			else
			{
				WriteSubrecord('DATA',sizeof(WaterData),f);
				f->write<WaterData>(data);
			}
		}
		if (gnamSeen)
		{
			WriteSubrecord('GNAM',12,f);
			f->write<formid>(dayWater);
			f->write<formid>(nightWater);
			f->write<formid>(underWater);
		}
	}
	virtual int GetSaveSize()
	{
		int size = 0;
		size += ZStringSubrecordSize(editorID);
		size += ZStringSubrecordSize(texture);
		size += ComputeSubrecordSize(1);
		size += ComputeSubrecordSize(1);
		size += ZStringSubrecordSize(material);
		if (sound)
		{
			size += ComputeSubrecordSize(4);
		}
		if (dataSeen)
		{
			if (data2s)
			{
				size += ComputeSubrecordSize(sizeof(WaterData2));
			}
			else if (data3s)
			{
				size += ComputeSubrecordSize(sizeof(WaterData3));
			}
			else if (data4s)
			{
				size += ComputeSubrecordSize(sizeof(WaterData4));
			}
			else if (data5s)
			{
				size += ComputeSubrecordSize(sizeof(WaterData5));
			}
			else
			{
				size += ComputeSubrecordSize(sizeof(WaterData));
			}
		}
		if (gnamSeen)
		{
			size += ComputeSubrecordSize(12);
		}
		return size;
	}
};
