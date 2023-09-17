
#pragma once
#include "utils/offsets.h"
#include "utils/math.h"
#include <iostream>
#include <vector>

#define	FL_ONGROUND				(1<<0)	// At rest / on the ground
#define FL_DUCKING				(1<<1)	// Player flag -- Player is fully crouched

class CWeapon {
public:
	int ID();
	int Ammo();
	int PaintKit();

	uintptr_t GetOwner();

	void SetPaint(int paint);
	void SetID(int id);
	void SetWear(float wear);
	void SetOwner(uintptr_t owner);
	void SetKills(int kills);
	void SetSeed(int seed);

};


class GlobalVars
{
public:
	float realTime;
	std::int32_t frameCount;
	float absFrameTime;
	float absFrameStartTime;
	float currentTime;
	float frameTime;
	std::int32_t maxClients;
	std::int32_t tickCount;
	float intervalPerTick;
	float interpolationAmount;
	std::int32_t frameSimulationTicks;
	std::int32_t networkProtocol;
	void* saveData;
	bool client;
	bool remoteClient;
	std::int32_t timestampNetworkingBase;
	std::int32_t timestampRandomizeWindow;
};


class CBomb {
public:
	int BombSite();
	float DefuseTime();
	float ExplodeTime();
	float DefuseLenght();
	bool Defused();
};

class Entity {
public:

	int ClassID();

	int Health();
	int Armor();
	int Team();
	int Ammo();
	int Flags();
	int CrossHairID();
	int ObserverTargetID();
	int ShotsFired();

	int TickBase();

	bool IsAlive();
	bool IsDormant();
	bool IsDefusing();
	bool IsBlind();
	bool IsScoped();
	bool HasGunGameImmunity();
	bool HasDefuseKit();
	bool IsWeapon();
	bool Spoted();

	Vector3 ViewOffset();
	Vector3 Origin();
	Vector3 Bone(int index);
	Vector3 Angles();
	Vector3 AimPunch();

	
	
	CWeapon* ActiveWeapon();

	
};




class Hack {
public:

	//uintptr_t client;
	//uintptr_t engine;
	//CEntity* localEnt;
	//EntList* entList;
	//
	//
	//float viewMatrix[16];

	uintptr_t client;
	uintptr_t engine;
	uintptr_t EntityList;


	Entity* LocalPlayer;;
	float ViewMatrix[16];

	Vector3 GetViewAngles();

	int bombID;

	void Init();
	void Update();
	void MainLoop();
	
	Entity* GetEntity(int index);
	int GetBombOwnerID();
	std::string GetEntityName(int index);
	const char* GetWeaponName(int ID);
	int GetWeaponType(int ID);
	int MaxWeaponAmmo(int ID);

	bool IsValid(Entity* ent);
	bool WorldToScreen(Vector3 pos, Vector2 &screen);

	std::vector<int> BODY = { 8,7,6,5,3 };
	std::vector<int> CTRARM = { 11 ,12,13 };
	std::vector<int> CTLARM = { 40 ,41,43 };
	std::vector<int> CTRLEG = { 77 ,73,74 };
	std::vector<int> CTLLEG = { 86 ,82,83 };


	std::vector<int> TRARM = { 11 ,12,13 };
	std::vector<int> TLARM = { 39 ,40,41 };
	std::vector<int> TRLEG = { 71 ,67,68 };
	std::vector<int> TLLEG = { 78 ,74,75 };
	
	Vector3 TransformVector(Vector3 src, Vector3 angle, float magnitude);

	void MoveMouse(int x, int y);
	void LeftClick();
	void RightClick();

	bool IsBombBeingDefused();
	
	GlobalVars globalvars;

	std::vector<int> DrawListEntities;
	//bool IsValidEnt(CEntity* ent);
	//bool WorldToScreen(Vector3 pos, Vector2& screen);
	//
	//bool WorldToScreenC(Vector3 pos, Vector2& screen);
	//int ClampInt(int value, int max, int min);
	//float ClampFloat(float value, float max, float min);
	//
	//// hacks
	//
	//void RunAimbot();
	//
	////clientdll + dwradarbase + radarOffset + nameoff + 0x174 entity number
	//short GetMyWeaponId();
	//short GetWeaponId(int entIndex);
	//
	//const char* GetWeaponName(short wpId);
	//char* GetEntName(int index);
	//Vector3 GetBonePos(CEntity* ent, int bone);
	//Vector3 TransformVec(Vector3 src, Vector3 angle, float magnitude);
	//
	//Vector3 TransformCVector(Vector3 src, Vector3 angle, float magnitude);
	//float Dist2Points2d(Vector2 point1, Vector2 point2);
	//
	//float Dist2Points3d(Vector3 p1, Vector3 p2);
	//
	//
	////Skin GetNewSkin(short wpId);
	//using is_c4_owner_fn = bool(__thiscall*)(CEntity*);
	//is_c4_owner_fn is_c4_owner = nullptr;
	//
	//
	//
	//using LoadSkyFn = void(__thiscall*)(const char* skyname);
	//LoadSkyFn LoadSky = nullptr;


};


/*

	8
 67 7 38
41	6  12
95	5  95
	3
  82 73
83     74

*/

enum EClassID : std::int32_t
{
	CAI_BaseNPC = 0,
	CAK47,
	CBaseAnimating,
	CBaseAnimatingOverlay,
	CBaseAttributableItem,
	CBaseButton,
	CBaseCombatCharacter,
	CBaseCombatWeapon,
	CBaseCSGrenade,
	CBaseCSGrenadeProjectile,
	CBaseDoor,
	CBaseEntity,
	CBaseFlex,
	CBaseGrenade,
	CBaseParticleEntity,
	CBasePlayer,
	CBasePropDoor,
	CBaseTeamObjectiveResource,
	CBaseTempEntity,
	CBaseToggle,
	CBaseTrigger,
	CBaseViewModel,
	CBaseVPhysicsTrigger,
	CBaseWeaponWorldModel,
	CBeam,
	CBeamSpotlight,
	CBoneFollower,
	CBRC4Target,
	CBreachCharge,
	CBreachChargeProjectile,
	CBreakableProp,
	CBreakableSurface,
	CBumpMine,
	CBumpMineProjectile,
	CC4,
	CCascadeLight,
	CChicken,
	CColorCorrection,
	CColorCorrectionVolume,
	CCSGameRulesProxy,
	CCSPlayer,
	CCSPlayerResource,
	CCSRagdoll,
	CCSTeam,
	CDangerZone,
	CDangerZoneController,
	CDEagle,
	CDecoyGrenade,
	CDecoyProjectile,
	CDrone,
	CDronegun,
	CDynamicLight,
	CDynamicProp,
	CEconEntity,
	CEconWearable,
	CEmbers,
	CEntityDissolve,
	CEntityFlame,
	CEntityFreezing,
	CEntityParticleTrail,
	CEnvAmbientLight,
	CEnvDetailController,
	CEnvDOFController,
	CEnvGasCanister,
	CEnvParticleScript,
	CEnvProjectedTexture,
	CEnvQuadraticBeam,
	CEnvScreenEffect,
	CEnvScreenOverlay,
	CEnvTonemapController,
	CEnvWind,
	CFEPlayerDecal,
	CFireCrackerBlast,
	CFireSmoke,
	CFireTrail,
	CFish,
	CFists,
	CFlashbang,
	CFogController,
	CFootstepControl,
	CFunc_Dust,
	CFunc_LOD,
	CFuncAreaPortalWindow,
	CFuncBrush,
	CFuncConveyor,
	CFuncLadder,
	CFuncMonitor,
	CFuncMoveLinear,
	CFuncOccluder,
	CFuncReflectiveGlass,
	CFuncRotating,
	CFuncSmokeVolume,
	CFuncTrackTrain,
	CGameRulesProxy,
	CGrassBurn,
	CHandleTest,
	CHEGrenade,
	CHostage,
	CHostageCarriableProp,
	CIncendiaryGrenade,
	CInferno,
	CInfoLadderDismount,
	CInfoMapRegion,
	CInfoOverlayAccessor,
	CItem_Healthshot,
	CItemCash,
	CItemDogtags,
	CKnife,
	CKnifeGG,
	CLightGlow,
	CMapVetoPickController,
	CMaterialModifyControl,
	CMelee,
	CMolotovGrenade,
	CMolotovProjectile,
	CMovieDisplay,
	CParadropChopper,
	CParticleFire,
	CParticlePerformanceMonitor,
	CParticleSystem,
	CPhysBox,
	CPhysBoxMultiplayer,
	CPhysicsProp,
	CPhysicsPropMultiplayer,
	CPhysMagnet,
	CPhysPropAmmoBox,
	CPhysPropLootCrate,
	CPhysPropRadarJammer,
	CPhysPropWeaponUpgrade,
	CPlantedC4,
	CPlasma,
	CPlayerPing,
	CPlayerResource,
	CPointCamera,
	CPointCommentaryNode,
	CPointWorldText,
	CPoseController,
	CPostProcessController,
	CPrecipitation,
	CPrecipitationBlocker,
	CPredictedViewModel,
	CProp_Hallucination,
	CPropCounter,
	CPropDoorRotating,
	CPropJeep,
	CPropVehicleDriveable,
	CRagdollManager,
	CRagdollProp,
	CRagdollPropAttached,
	CRopeKeyframe,
	CSCAR17,
	CSceneEntity,
	CSensorGrenade,
	CSensorGrenadeProjectile,
	CShadowControl,
	CSlideshowDisplay,
	CSmokeGrenade,
	CSmokeGrenadeProjectile,
	CSmokeStack,
	CSnowball,
	CSnowballPile,
	CSnowballProjectile,
	CSpatialEntity,
	CSpotlightEnd,
	CSprite,
	CSpriteOriented,
	CSpriteTrail,
	CStatueProp,
	CSteamJet,
	CSun,
	CSunlightShadowControl,
	CSurvivalSpawnChopper,
	CTablet,
	CTeam,
	CTeamplayRoundBasedRulesProxy,
	CTEArmorRicochet,
	CTEBaseBeam,
	CTEBeamEntPoint,
	CTEBeamEnts,
	CTEBeamFollow,
	CTEBeamLaser,
	CTEBeamPoints,
	CTEBeamRing,
	CTEBeamRingPoint,
	CTEBeamSpline,
	CTEBloodSprite,
	CTEBloodStream,
	CTEBreakModel,
	CTEBSPDecal,
	CTEBubbles,
	CTEBubbleTrail,
	CTEClientProjectile,
	CTEDecal,
	CTEDust,
	CTEDynamicLight,
	CTEEffectDispatch,
	CTEEnergySplash,
	CTEExplosion,
	CTEFireBullets,
	CTEFizz,
	CTEFootprintDecal,
	CTEFoundryHelpers,
	CTEGaussExplosion,
	CTEGlowSprite,
	CTEImpact,
	CTEKillPlayerAttachments,
	CTELargeFunnel,
	CTEMetalSparks,
	CTEMuzzleFlash,
	CTEParticleSystem,
	CTEPhysicsProp,
	CTEPlantBomb,
	CTEPlayerAnimEvent,
	CTEPlayerDecal,
	CTEProjectedDecal,
	CTERadioIcon,
	CTEShatterSurface,
	CTEShowLine,
	CTesla,
	CTESmoke,
	CTESparks,
	CTESprite,
	CTESpriteSpray,
	CTest_ProxyToggle_Networkable,
	CTestTraceline,
	CTEWorldDecal,
	CTriggerPlayerMovement,
	CTriggerSoundOperator,
	CVGuiScreen,
	CVoteController,
	CWaterBullet,
	CWaterLODControl,
	CWeaponAug,
	CWeaponAWP,
	CWeaponBaseItem,
	CWeaponBizon,
	CWeaponCSBase,
	CWeaponCSBaseGun,
	CWeaponCycler,
	CWeaponElite,
	CWeaponFamas,
	CWeaponFiveSeven,
	CWeaponG3SG1,
	CWeaponGalil,
	CWeaponGalilAR,
	CWeaponGlock,
	CWeaponHKP2000,
	CWeaponM249,
	CWeaponM3,
	CWeaponM4A1,
	CWeaponMAC10,
	CWeaponMag7,
	CWeaponMP5Navy,
	CWeaponMP7,
	CWeaponMP9,
	CWeaponNegev,
	CWeaponNOVA,
	CWeaponP228,
	CWeaponP250,
	CWeaponP90,
	CWeaponSawedoff,
	CWeaponSCAR20,
	CWeaponScout,
	CWeaponSG550,
	CWeaponSG552,
	CWeaponSG556,
	CWeaponShield,
	CWeaponSSG08,
	CWeaponTaser,
	CWeaponTec9,
	CWeaponTMP,
	CWeaponUMP45,
	CWeaponUSP,
	CWeaponXM1014,
	CWeaponZoneRepulsor,
	CWorld,
	CWorldVguiText,
	DustTrail,
	MovieExplosion,
	ParticleSmokeGrenade,
	RocketTrail,
	SmokeTrail,
	SporeExplosion,
	SporeTrail,
};