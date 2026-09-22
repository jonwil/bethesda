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
struct EffectShaderData
{
	ulong flags;
	ulong memSBlend;
	ulong memBlendOp;
	ulong memZFunc;
	Color fill;
	float fillAIn;
	float fillAFull;
	float fillAOut;
	float fillAPRatio;
	float fillAAmp;
	float fillAFreq;
	float fillAnimSpdU;
	float fillAnimSpdV;
	float edgeOff;
	Color edge;
	float edgeAIn;
	float edgeAFull;
	float edgeAOut;
	float edgeAPRatio;
	float edgeAAmp;
	float edgeAFreq;
	float fillAFRatio;
	float edgeAFRatio;
	ulong memDBlend;
	ulong partSBlend;
	ulong partBlendOp;
	ulong partZFunc;
	ulong partDBlend;
	float partBUp;
	float partBFull;
	float partBDown;
	float partBFRatio;
	float partBPRatio;
	float partLTime;
	float partLDelta;
	float partNSpd;
	float partNAcc;
	float partVel1;
	float partVel2;
	float partVel3;
	float partAcc1;
	float partAcc2;
	float partAcc3;
	float partKey1;
	float partKey2;
	float partKey1Time;
	float partKey2Time;
	Color key1;
	Color key2;
	Color key3;
	float key1A;
	float key2A;
	float key3A;
	float key1Time;
	float key2Time;
	float key3Time;
};
struct EffectShaderData2
{
	ulong flags;
	ulong memSBlend;
	ulong memBlendOp;
	ulong memZFunc;
	Color fill;
	float fillAIn;
	float fillAFull;
	float fillAOut;
	float fillAPRatio;
	float fillAAmp;
	float fillAFreq;
	float fillAnimSpdU;
	float fillAnimSpdV;
	float edgeOff;
	Color edge;
	float edgeAIn;
	float edgeAFull;
	float edgeAOut;
	float edgeAPRatio;
	float edgeAAmp;
	float edgeAFreq;
	float fillAFRatio;
	float edgeAFRatio;
	ulong memDBlend;
};
class EffectShaderForm : public Form
{
protected:
	char *editorID;
	EffectShaderData data;
	EffectShaderData2 data2;
	char *fillTexture;
	char *particleTexture;
	bool data2s;
public:
	EffectShaderForm(FormHeader h,ModFile *f) : Form(h,f), editorID(0), fillTexture(0), particleTexture(0), data2s(false)
	{
	}
	virtual ~EffectShaderForm()
	{
		if (editorID)
		{
			delete[] editorID;
		}
		if (fillTexture)
		{
			delete[] fillTexture;
		}
		if (particleTexture)
		{
			delete[] particleTexture;
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
			case 'ICON':
				fillTexture = f->readzstring(h.size);
				readSize += h.size;
				break;
			case 'ICO2':
				particleTexture = f->readzstring(h.size);
				readSize += h.size;
				break;
			case 'DATA':
				if (h.size == sizeof(EffectShaderData))
				{
					data = f->read<EffectShaderData>();
					readSize += sizeof(EffectShaderData);
				}
				else
				{
					data2s = true;
					data2 = f->read<EffectShaderData2>();
					readSize += sizeof(EffectShaderData2);
				}
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
		WriteZStringSubrecord('ICON',fillTexture,f);
		WriteZStringSubrecord('ICO2',particleTexture,f);
		if (data2s)
		{
			WriteSubrecord('DATA',sizeof(EffectShaderData2),f);
			f->write<EffectShaderData2>(data2);
		}
		else
		{
			WriteSubrecord('DATA',sizeof(EffectShaderData),f);
			f->write<EffectShaderData>(data);
		}
	}
	virtual int GetSaveSize()
	{
		int size = 0;
		size += ZStringSubrecordSize(editorID);
		size += ZStringSubrecordSize(fillTexture);
		size += ZStringSubrecordSize(particleTexture);
		if (data2s)
		{
			size += ComputeSubrecordSize(sizeof(EffectShaderData2));
		}
		else
		{
			size += ComputeSubrecordSize(sizeof(EffectShaderData));
		}
		return size;
	}
};
