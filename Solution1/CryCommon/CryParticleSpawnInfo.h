
//////////////////////////////////////////////////////////////////////////
//
//	Crytek Source code 
//	Copyright (c) Crytek 2001-2004
//
//	File: CryParticleSpawnInfo.h
//	Description: declaration of struct CryParticleSpawnInfo.
//    3D Engine and Character Animation subsystems (as well as perhaps
//    some others) transfer data about the particles that need to be spawned
//    via this structure. This is to avoid passing many parameters through
//    each function call, and to save on copying these parameters when just
//    simply passing the structure from one function to another.
//
//	History:
//	- Sep 23, 2002: Created by Sergiy Migdalskiy
//	- February 2005: Modified by Marco Corbetta for SDK release
//
//////////////////////////////////////////////////////////////////////

#ifndef __CRY_COMMON_PARTICLE_SPAWN_INFO_HDR__
#define __CRY_COMMON_PARTICLE_SPAWN_INFO_HDR__

//////////////////////////////////////////////////////////////////////
//! Structure containing common parameters describing particle spawning
//! This is in addition to the ParticleParams defined in the 3D Engine
struct CryParticleSpawnInfo
{
public:
	// Particle spawn rate: the number of particles to be spawned
	// PER SECOND. The number of particles to spawn per Frame is:
	//   fSpawnRate * fFrameDurationSeconds
	float fSpawnRate;

	enum FlagEnum
	{
		// in this mode, only up-looking normals will be taken into account
		FLAGS_RAIN_MODE      = 1,
		// with this flag, the spawn will occur only on one frame
		FLAGS_ONE_TIME_SPAWN = 1 << 1,
		// with this flag, nBoneId will determine the bone from which the particle will be spawned,
		// vBonePos will be the position in bone coordinates at which the particles will be spawned
		FLAGS_SPAWN_FROM_BONE = 1 << 2
	};

	// flags - combination of FlagEnum flags
	unsigned nFlags;
	// valid only with FLAGS_SPAWN_FROM_BONE:
	// the bone number, can be determined with the ICryCharModel::GetBoneByName(), should be non-negative
	unsigned nBone;
	// valid only with FLAGS_SPAWN_FROM_BONE:
	// the position of the particle in local bone coordinates
	Vec3 vBonePos;

	CryParticleSpawnInfo():
		fSpawnRate (0),
		nFlags (0),
		nBone (0),
		vBonePos(0,0,0)
	{
	}
	
	CryParticleSpawnInfo (float _fSpawnRate, unsigned _nFlags = 0):
		fSpawnRate(_fSpawnRate),
		nFlags (_nFlags)
	{
	}
};

#endif