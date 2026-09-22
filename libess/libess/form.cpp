/*	libess
	Copyright 2013 Jonathan Wilson

	This file is part of libess
	libess is free software; you can redistribute it and/or modify it under
	the terms of the GNU General Public License as published by the Free
	Software Foundation; either version 2, or (at your option) any later
	version. See the file COPYING for more details.
*/
#include "zlib.h"
#include "miscform.h"
#include "bookform.h"
#include "cellform.h"
#include "refrform.h"
#include "landform.h"
#include "roadform.h"
#include "pathgridform.h"
#include "worldspaceform.h"
#include "staticform.h"
#include "alchemyform.h"
#include "sigilstoneform.h"
#include "enchantmentform.h"
#include "spellform.h"
#include "activatorform.h"
#include "ammoform.h"
#include "animatedobjectform.h"
#include "apparatusform.h"
#include "armorform.h"
#include "clothingform.h"
#include "lightform.h"
#include "soulgemform.h"
#include "weaponform.h"
#include "floraform.h"
#include "gamesettingform.h"
#include "containerform.h"
#include "creatureform.h"
#include "scriptform.h"
#include "questform.h"
#include "leveleditemform.h"
#include "doorform.h"
#include "magiceffectform.h"
#include "effectshaderform.h"
#include "globalform.h"
#include "leveledcreatureform.h"
#include "npcform.h"
#include "aipackageform.h"
#include "regionform.h"
#include "dialogform.h"
#include "dialogresponseform.h"
#include "soundform.h"
#include "climateform.h"
#include "factionform.h"
#include "leveledspellform.h"
#include "waterform.h"
#include "furnitureform.h"
#include "classform.h"
#include "weatherform.h"
#include "idleform.h"
#include "combatstyleform.h"
#include "loadscreenform.h"
#include "hairform.h"
#include "eyesform.h"
#include "landscapetextureform.h"
#include "birthsignform.h"
#include "subspaceform.h"
#include "treeform.h"
#include "grassform.h"
#include "skillform.h"
#include "raceform.h"
void Form::LoadCompressed(FileRead *f)
{
	ubyte *outbuf = 0;
	if (header.flags & 0x00040000)
	{
		ulong len = f->read<ulong>();
		uncompsize = len;
		ubyte *buffer = f->readarray<ubyte>(header.dataSize-4);
		outbuf = new ubyte[len];
		z_stream s;
		s.total_out = 0;
		s.zalloc = (alloc_func)0;
		s.zfree = (free_func)0;
		s.opaque = (voidpf)0;
		s.next_in = (Bytef*)buffer;
		s.avail_in = (uInt)(header.dataSize - 4);
		s.next_out = (Bytef*)outbuf;
		s.avail_out = (uInt)(len);
		inflateInit(&s);
		inflate(&s,0);
		inflateEnd(&s);
		delete[] buffer;
		f->SetCompressed(outbuf);
	}
	Load(f);
	if (header.flags & 0x00040000)
	{
		f->ClearCompressed();
		delete[] outbuf;
	}
}
void Form::SaveCompressed(FileWrite *f)
{
	int size = GetSaveSize();
	ubyte *outbuf = new ubyte[size];
	f->SetCompressed(outbuf);
	Save(f);
	f->ClearCompressed();
	if (header.flags & 0x00040000)
	{
		ubyte *compbuf = new ubyte[size * 2];
		z_stream s;
		s.total_out = 0;
		s.zalloc = (alloc_func)0;
		s.zfree = (free_func)0;
		s.opaque = (voidpf)0;
		s.next_in = (Bytef*)outbuf;
		s.avail_in = (uInt)(size);
		s.next_out = (Bytef*)compbuf;
		s.avail_out = (uInt)(size * 2);
		deflateInit(&s,-1);
		deflate(&s,4);
		deflateEnd(&s);
		header.dataSize = ((size * 2) - s.avail_out) + 4;
		f->write<FormHeader>(header);
		f->write<ulong>(size);
		f->writearray<ubyte>((size * 2) - s.avail_out,compbuf);
		delete[] compbuf;
	}
	else
	{
		f->write<FormHeader>(header);
		f->writearray<ubyte>(size,outbuf);
	}
	delete[] outbuf;
}
Form *CreateForm(FormHeader header,ModFile *f)
{
	switch(SwapBytes(header.type))
	{
	case 'MISC':
	case 'KEYM':
		return new MiscForm(header,f);
		break;
	case 'BOOK':
		return new BookForm(header,f);
		break;
	case 'CELL':
		return new CellForm(header,f);
		break;
	case 'REFR':
	case 'ACRE':
	case 'ACHR':
		return new RefrForm(header,f);
		break;
	case 'SBSP':
		return new SubSpaceForm(header,f);
		break;
	case 'WRLD':
		return new WorldspaceForm(header,f);
		break;
	case 'PGRD':
		return new PathGridForm(header,f);
		break;
	case 'ROAD':
		return new RoadForm(header,f);
		break;
	case 'LAND':
		return new LandForm(header,f);
		break;
	case 'STAT':
		return new StaticForm(header,f);
		break;
	case 'ALCH':
	case 'INGR':
		return new AlchemyForm(header,f);
		break;
	case 'SGST':
		return new SigilStoneForm(header,f);
		break;
	case 'ENCH':
		return new EnchantmentForm(header,f);
		break;
	case 'SPEL':
 		return new SpellForm(header,f);
		break;
	case 'ACTI':
		return new ActivatorForm(header,f);
		break;
	case 'AMMO':
		return new AmmoForm(header,f);
		break;
	case 'ANIO':
		return new AnimatedObjectForm(header,f);
		break;
	case 'APPA':
		return new ApparatusForm(header,f);
		break;
	case 'ARMO':
		return new ArmorForm(header,f);
		break;
	case 'CLOT':
		return new ClothingForm(header,f);
		break;
	case 'LIGH':
		return new LightForm(header,f);
		break;
	case 'SLGM':
		return new SoulGemForm(header,f);
		break;
	case 'WEAP':
		return new WeaponForm(header,f);
		break;
	case 'FLOR':
		return new FloraForm(header,f);
		break;
	case 'GMST':
		return new GameSettingForm(header,f);
		break;
	case 'CONT':
		return new ContainerForm(header,f);
		break;
	case 'CREA':
		return new CreatureForm(header,f);
		break;
	case 'SCPT':
		return new ScriptForm(header,f);
		break;
	case 'QUST':
		return new QuestForm(header,f);
		break;
	case 'LVLI':
		return new LeveledItemForm(header,f);
		break;
	case 'DOOR':
		return new DoorForm(header,f);
		break;
	case 'MGEF':
		return new MagicEffectForm(header,f);
		break;
	case 'EFSH':
		return new EffectShaderForm(header,f);
		break;
	case 'GLOB':
		return new GlobalForm(header,f);
		break;
	case 'LVLC':
		return new LeveledCreatureForm(header,f);
		break;
	case 'NPC_':
		return new NPCForm(header,f);
		break;
	case 'PACK':
		return new AIPackageForm(header,f);
		break;
	case 'REGN':
		return new RegionForm(header,f);
		break;
	case 'DIAL':
		return new DialogForm(header,f);
		break;
	case 'INFO':
		return new DialogResponseForm(header,f);
		break;
	case 'SOUN':
		return new SoundForm(header,f);
	case 'CLMT':
		return new ClimateForm(header,f);
		break;
	case 'FACT':
		return new FactionForm(header,f);
		break;
	case 'LVSP':
		return new LeveledSpellForm(header,f);
		break;
	case 'WATR':
		return new WaterForm(header,f);
		break;
	case 'FURN':
		return new FurnitureForm(header,f);
		break;
	case 'CLAS':
		return new ClassForm(header,f);
		break;
	case 'WTHR':
		return new WeatherForm(header,f);
		break;
	case 'IDLE':
		return new IdleForm(header,f);
		break;
	case 'CSTY':
		return new CombatStyleForm(header,f);
		break;
	case 'LSCR':
		return new LoadScreenForm(header,f);
		break;
	case 'HAIR':
		return new HairForm(header,f);
		break;
	case 'EYES':
		return new EyesForm(header,f);
		break;
	case 'LTEX':
		return new LandscapeTextureForm(header,f);
		break;
	case 'BSGN':
		return new BirthSignForm(header,f);
		break;
	case 'RACE':
		return new RaceForm(header,f);
		break;
	case 'TREE':
		return new TreeForm(header,f);
		break;
	case 'GRAS':
		return new GrassForm(header,f);
		break;
	case 'SKIL':
		return new SkillForm(header,f);
		break;
	default:
		printf("Unknown form type found");
		__debugbreak();
		return 0;
		break;
	}
}
