#pragma once
#include "platform.h"
#include "stdint.h"
#include "utils/module.h"
#include "utlstring.h"


struct Signature {
	const char *data = nullptr;
	size_t length = 0;

	template<size_t N>
	Signature(const char(&str)[N]) {
		data = str;
		length = N - 1;
	}
};
#define DECLARE_SIG(name, sig) inline const Signature name = Signature(sig);

namespace modules
{
	inline CModule *engine;
	inline CModule *tier0;
	inline CModule *server;
	inline CModule *schemasystem;
	inline CModule *steamnetworkingsockets;
	void Initialize();
}

class CBasePlayerController;

namespace addresses
{
	inline void(FASTCALL* UTIL_ClientPrintAll)(int msg_dest, const char* msg_name, const char* param1, const char* param2, const char* param3, const char* param4);
	inline void(FASTCALL* ClientPrint)(CBasePlayerController* player, int msg_dest, const char* msg_name, const char* param1, const char* param2, const char* param3, const char* param4);
}

namespace offsets
{
#ifdef _WIN32
	inline constexpr int GameEntitySystem = 0x58;
	inline constexpr int IsEntityPawn = 152;
	inline constexpr int IsEntityController = 153;
	inline constexpr int SetMoveType = 77;
	inline constexpr int CollisionRulesChanged = 173;
	// 5 functions after one with "Physics_SimulateEntity" "Server Game"
	inline constexpr int Teleport = 148;
	inline constexpr int SetTransmit = 86;
	inline constexpr int GetEventManager = 91;
#else
	inline constexpr int GameEntitySystem = 0x50;
	inline constexpr int IsEntityPawn = 151;
	inline constexpr int IsEntityController = 152;
	inline constexpr int SetMoveType = 76;
	inline constexpr int CollisionRulesChanged = 172;
	inline constexpr int Teleport = 147;
	inline constexpr int SetTransmit = 85;
	inline constexpr int GetEventManager = 91;
#endif
}

namespace sigs
{
#ifdef _WIN32
	/* Miscellaneous */
	
	// search for "WARNING: Ignoring invalid gameinfo MaxNetworkableEntities %d\n", go to the only xref.
	DECLARE_SIG(CEntitySystem_ctor, "\x48\x89\x5C\x24\x10\x48\x89\x74\x24\x18\x57\x48\x83\xEC\x20\x48\x8B\xD9\xE8\x2A\x2A\x2A\x2A\x33\xFF\xC7");
	
	// "Cannot create an entity because entity class is NULL %d\n"
	DECLARE_SIG(CEntitySystem_CreateEntity, "\x48\x89\x5C\x24\x08\x48\x89\x6C\x24\x10\x56\x57\x41\x56\x48\x83\xEC\x40\x4D");
	
	// search for "In level transition: %s %s\n", go to only xref, the first function called in that is this.
	DECLARE_SIG(CBaseTrigger_StartTouch, "\x41\x56\x41\x57\x48\x83\xEC\x58\x48\x8B\x01");
	
	// search for "kevlar(%d) ", go to only xref, the first function called in that is this.
	DECLARE_SIG(CBaseTrigger_EndTouch, "\x40\x53\x57\x41\x55\x48\x83\xEC\x40");

	DECLARE_SIG(NetworkStateChanged, "\x4C\x8B\xC9\x48\x8B\x09\x48\x85\xC9\x74\x2A\x48\x8B\x41\x10");

	DECLARE_SIG(StateChanged, "\x48\x89\x54\x24\x10\x55\x53\x57\x41\x55");

	// TODO linux no forgot!
	DECLARE_SIG(UTIL_ClientPrintAll, "\x48\x89\x5C\x24\x08\x48\x89\x6C\x24\x10\x48\x89\x74\x24\x18\x57\x48\x81\xEC\x70\x01\x2A\x2A\x8B\xE9")
	DECLARE_SIG(ClientPrint, "\x48\x85\xC9\x0F\x84\x2A\x2A\x2A\x2A\x48\x8B\xC4\x48\x89\x58\x18")

	DECLARE_SIG(UTIL_ClientPrintFilter, "\x48\x89\x5C\x24\x08\x48\x89\x6C\x24\x18\x56\x57\x41\x56\x48\x81\xEC\x90\x00\x00\x00\x49\x8B\xF0");
	
	// search for the string "\"Console<0>\" say_team \"%s\"\n"
	DECLARE_SIG(Host_Say, "\x44\x89\x4C\x24\x20\x44\x88");

	// "Cannot create an entity because entity class is NULL %d\n"
	DECLARE_SIG(CreateEntity, "\x48\x89\x5C\x24\x08\x48\x89\x6C\x24\x10\x56\x57\x41\x56\x48\x83\xEC\x40\x4D");
	
	// "Radial using: %s\n"
	DECLARE_SIG(FindUseEntity, "\x48\x89\x5C\x24\x10\x55\x56\x57\x41\x54\x41\x55\x41\x56\x41\x57\x48\x8D\xAC\x24\x00\xEB\xFF\xFF");
	
	// search for "exec maps/%s.cfg\n"
	//DECLARE_SIG(CCSGameRules_ctor, "\x48\x8B\xC4\x48\x89\x58\x20\x48\x89\x48\x08\x55\x56\x57\x41\x54\x41\x55\x41\x56\x41\x57\x48\x8D\xA8\x78\xFD\xFF\xFF");
	DECLARE_SIG(CCSGameRules_ctor, "\x40\x53\x48\x83\xEC\x20\x48\x8D\x05\x2A\x2A\x2A\x2A\x48\x8B\xD9\x48\x89\x01\x48\x89\x0D");

	// CSource2GameClients::StartHLTVServer: game event %s not found.
	// Function right before the first virtual function call
	DECLARE_SIG(GetLegacyGameEventListener, "\x48\x8B\x15\x2A\x2A\x2A\x2A\x48\x85\xD2\x74\x2A\x85\xC9\x74");
	
	// RecvServerBrowserPacketTask vtable reference
	DECLARE_SIG(RecvServerBrowserPacket, "\x48\x89\x6C\x24\x18\x56\x48\x83\xEC\x20\x48\x8B\xF1\x48\x8B\xEA");
	
	// Find handler for setang console command
	DECLARE_SIG(SnapViewAngles, "\x48\x89\x5C\x24\x20\x55\x56\x57\x41\x56\x41\x57\x48\x8D\x6C\x24\xC9\x48\x81\xEC\xD0\x00\x00\x00\xBF\xFF\xFF\xFF\xFF");
	
	
	/* Trace related stuff */
	
	// TODO
	DECLARE_SIG(InitPlayerMovementTraceFilter, "\x48\x89\x5C\x24\x08\x48\x89\x74\x24\x10\x57\x48\x83\xEC\x20\x0F\xB6\x41\x37\x48\x8B\xD9");

	// TODO
	DECLARE_SIG(TracePlayerBBoxForGround, "\x48\x8B\xC4\x48\x89\x58\x10\x48\x89\x70\x18\x48\x89\x78\x20\x48\x89\x48\x08\x55\x41\x54");

	// search for "CCSBot::BendLineOfSight". should find 1 function, CGameTrace::Init is called in there right after this string is referenced with an 80 byte parameter.
	DECLARE_SIG(InitGameTrace, "\x48\x89\x5C\x24\x08\x57\x48\x83\xEC\x20\x48\x8B\xD9\x33\xFF\x48\x8B\x0D\x2A\x2A\x2A\x2A\x48\x85\xC9");

	// "pa start %f"
	DECLARE_SIG(ProcessMovement, "\x40\x56\x57\x48\x81\xEC\xA8\x00\x00\x00\x4C\x8B\x49\x30");

	/* Movement related functions */
	
	//*(a2 + 200) = sub_7FFE4786BD30(a1->pawn); <- this function
	//   v23 = a1->pawn;
	//   a1->m_bInStuckTest = 0;
	//   v24 = v23->m_pCameraServices;
	//   v25 = sub_7FFE47482320(v23);
	//   v26 = v25;
	//   if ( v25 )
	//   {
	//     EntIndex(v25, &v35);
	//     sub_7FFE4799A200(a1, "following entity %d", v35);
	//   }
	// also contains the string "weapon_shield"
	/*
	DECLARE_SIG(GetMaxSpeed, "\x48\x89\x5C\x24\x18\x57\x48\x83\xEC\x30\x80\xB9\xC2\x02\x00\x00\x00");


	
	// called in ProcessMovement in between the strings "pa start %f" and "pa end %f", contains the string "Can't move"
	DECLARE_SIG(PlayerMoveNew, "\x48\x89\x5C\x24\x10\x48\x89\x74\x24\x18\x57\x48\x83\xEC\x2A\x48\x8B\xF9\x48\x8B\xDA");

	// Second thing called during PlayerMoveNew
	DECLARE_SIG(CheckParameters, "\x48\x8B\xC4\x48\x89\x58\x10\x48\x89\x70\x18\x55\x57\x41\x54\x41\x56\x41\x57\x48\x8D\x68\xA1\x48\x81\xEC\xD0\x00\x00\x00");

	// dev_cs_force_disable_move
	DECLARE_SIG(CanMove, "\x40\x53\x48\x83\xEC\x30\x48\x8B\xD9\xBA\xFF\xFF\xFF\xFF\x48\x8D\x0D\x2A\x2A\x2A\x2A\xE8\x2A\x2A\x2A\x2A\x48\x85\xC0\x75\x2A\x48\x8B\x05\x2A\x2A\x2A\x2A\x48\x8B\x40\x08\x80\x38\x00\x0F\x85");
	
	// "FullWalkMovePreMove"
	DECLARE_SIG(FullWalkMove, "\x40\x53\x57\x48\x83\xEC\x68\x48\x8B\xFA\x48\x8B\xD9\x45");

	// "[%s] Bogus pmove player movetype in ShouldApplyGravity %i\n"
	DECLARE_SIG(MoveInit, "\x40\x53\x57\x41\x56\x48\x83\xEC\x50\x48\x8B\xD9");

	// somewhere in MoveInit. GLHF!
	DECLARE_SIG(CheckWater, "\x48\x8B\xC4\x48\x89\x58\x08\x48\x89\x78\x10\x55\x48\x8D\xA8\x68\xFF\xFF\xFF");

	// "CCSPlayer_MovementServices(%s):  %d/%s Got a NaN velocity on %s\n"
	DECLARE_SIG(CheckVelocity, "\x48\x8B\xC4\x4C\x89\x40\x18\x48\x89\x50\x10\x55\x53\x56\x57\x41\x54\x41\x55\x41\x56\x41\x57\x48\x8D\x68\xA1");

	// called after MoveInit in PlayerMoveNew in switch statement with movetype 5
	DECLARE_SIG(Duck, "\x48\x8B\xC4\x48\x89\x58\x20\x55\x56\x57\x41\x56\x41\x57\x48\x8D\xA8\xD8\xFE\xFF\xFF");

	// sv_ladder_dampen
	DECLARE_SIG(LadderMove, "\x40\x55\x56\x57\x41\x54\x41\x55\x48\x8D\xAC\x24\xE0\xFC\xFF\xFF");

	// Look for sv_jump_spam_penalty_time
	DECLARE_SIG(CheckJumpButton, "\x48\x89\x5C\x24\x18\x56\x48\x83\xEC\x40\x48\x8B\xF2");

	// "player_jump"
	DECLARE_SIG(OnJump, "\x40\x53\x57\x48\x81\xEC\x98\x00\x00\x00\x48\x8B\xD9\x48\x8B\xFA");

	// Look for sv_air_max_wishspeed
	DECLARE_SIG(AirAccelerate, "\x48\x89\x5C\x24\x08\x48\x89\x74\x24\x10\x48\x89\x7C\x24\x18\x55\x48\x8D\x6C\x24\xB1");

	// sub_7FFE47869020(a1, a2); <- this function
	// sub_7FFE47863820(a1, a2, "FullWalkMovePreMove"); 
	// sub_7FFE4787B4C0(a1, a2); <- the walkmove function
	DECLARE_SIG(Friction, "\x48\x89\x74\x24\x18\x57\x48\x83\xEC\x60\x48\x8B\x41\x30");

	// sub_7FFE47863820(a1, a2, "FullWalkMovePreMove");
	// sub_7FFE4787B4C0(a1, a2); <- this function
	DECLARE_SIG(WalkMove, "\x48\x8B\xC4\x48\x89\x58\x18\x48\x89\x70\x20\x55\x57\x41\x54\x48\x8D");

	// "CCSPlayer_MovementServices::TryPlayerMove() Trace ended stuck"
	DECLARE_SIG(TryPlayerMove, "\x48\x8B\xC4\x4C\x89\x48\x20\x4C\x89\x40\x18\x48\x89\x50\x10\x55\x53\x56\x57\x41\x54\x41\x55");

	// sub_18061AF90(a1, a2, *(*(a1 + 48) + 864i64) & 1); <- this one
	// sub_18061D5B0(a1, a2, "PlayerMove_PostMove");
	DECLARE_SIG(CategorizePosition, "\x40\x55\x56\x57\x41\x57\x48\x8D\xAC\x24\x28\xFE\xFF\xFF");

	// called before the "player_jump" string in OnJump
	DECLARE_SIG(FinishGravity, "\x48\x89\x74\x24\x10\x57\x48\x83\xEC\x40\x4C\x8B\x41\x30");

	// sv_staminalandcost only ref. not inlined in linux, check calling functions.
	DECLARE_SIG(CheckFalling, "\x48\x89\x5C\x24\x10\x57\x48\x83\xEC\x60\xF3\x0F\x10\x81\x20\x02\x00\x00");

	// TODO
	DECLARE_SIG(PlayerMovePost, "\x40\x53\x56\x48\x83\xEC\x58\x48\x8B\x59\x30");

	// "[%.0f %.0f %.0f] relocated from [%.0f %.0f %.0f] in %0.1f sec (v2d = %.0f u/s)\n" "health=%d, armor=%d, helmet=%d"
	DECLARE_SIG(PostThink, "\x48\x8B\xC4\x48\x89\x48\x08\x55\x53\x56\x57\x41\x56\x48\x8D\xA8\xD8\xFE\xFF\xFF");*/
#else
	DECLARE_SIG(TEST, "\x55\x48\x89\xE5\x41\x57\x41\x56\x41\x55\x41\x54\x53\x48\x83\xEC\x68");
	DECLARE_SIG(CEntitySystem_ctor, "\x55\x48\x89\xE5\x41\x54\x49\x89\xFC\x53\x48\x8D\x1D\x2A\x2A\x2A\x2A\xE8\x2A\x2A\x2A\x2A\x48\x8D\x05\x2A\x2A\x2A\x2A");
	DECLARE_SIG(CEntitySystem_CreateEntity, "\x55\x48\x89\xE5\x41\x57\x41\x56\x49\x89\xD6\x41\x55\x45");
	DECLARE_SIG(CBaseTrigger_StartTouch, "\x55\x48\x89\xE5\x41\x56\x49\x89\xF6\x41\x55\x49\x89\xFD\x41\x54\x53\xBB");
	DECLARE_SIG(CBaseTrigger_EndTouch, "\x55\xBA\xFF\xFF\xFF\xFF\x48\x89\xE5\x41\x57\x41\x56\x41\x55\x49");
	DECLARE_SIG(NetworkStateChanged, "\x4C\x8B\x07\x4D\x85\xC0\x74\x2A\x49\x8B\x40\x10");
	DECLARE_SIG(StateChanged, "\x55\x48\x89\xE5\x41\x57\x41\x56\x41\x55\x41\x54\x53\x89\xD3");
	DECLARE_SIG(UTIL_ClientPrintAll, "\x55\x48\x89\xE5\x41\x57\x49\x89\xD7\x41\x56\x49\x89\xF6\x41\x55\x41\x89\xFD")
	DECLARE_SIG(ClientPrint, "\x55\x48\x89\xE5\x41\x57\x49\x89\xCF\x41\x56\x49\x89\xD6\x41\x55\x41\x89\xF5\x41\x54\x4C\x8D\xA5\xA0\xFE\xFF\xFF")
	DECLARE_SIG(UTIL_ClientPrintFilter, "\x55\x48\x89\xE5\x41\x57\x49\x89\xCF\x41\x56\x4D\x89\xC6\x41\x55\x49\x89\xD5\x31\xD2\x41\x54\x4C\x8D\x65\x88");
	DECLARE_SIG(Host_Say, "\x55\x48\x89\xE5\x41\x57\x49\x89\xFF\x41\x56\x41\x55\x41\x54\x4D");
	DECLARE_SIG(CBaseAnimGraph__Teleport, "\x55\x48\x89\xE5\x41\x56\x49\x89\xCE\x41\x55\x49\x89\xD5\x41\x54\x49\x89\xF4\x53");
	DECLARE_SIG(CreateEntity, "\x55\x48\x89\xE5\x41\x57\x41\x56\x49\x89\xD6\x41\x55\x45");
	DECLARE_SIG(FindUseEntity, "\x55\xBE\xFF\xFF\xFF\xFF\x48\x89\xE5\x41\x57\x41\x56\x41\x55\x49\x89\xFD\x41\x54\x48\x8D\x3D\x2A\x2A\x2A\x2A\x53\x48\x81");
	DECLARE_SIG(CCSGameRules_ctor, "\x55\x48\x8D\x05\x2A\x2A\x2A\x2A\x48\x89\xE5\x53\x48\x89\xFB\x48\x83\xEC\x08\x48\x89\x07\x48\x89\x3D");
	DECLARE_SIG(GetLegacyGameEventListener, "\x48\x8B\x05\x2A\x2A\x2A\x2A\x48\x85\xC0\x74\x2A\x83\xFF\x3F\x76\x2A\x31\xC0");
	DECLARE_SIG(RecvServerBrowserPacket, "\x41\x54\x55\x48\x89\xF5\x53\x48\x89\xFB\x48\x63\x47\x08");
	DECLARE_SIG(SnapViewAngles, "\x55\x48\x89\xE5\x41\x57\x41\x56\x41\x55\x41\x54\x53\x48\x89\xFB\x48\x89\xF7\x4C\x8D\xA3\x28\x0D\x00\x00");
	DECLARE_SIG(InitPlayerMovementTraceFilter, "\x55\xB8\x07\x00\x00\x00\x48\x89\xE5\x41\x55\x41\x54\x49\x89\xF4\x53\x48\x89\xFB\x48\x83\xEC\x08\x66\x89\x47\x34\x48\x8D\x05\x2A\x2A\x2A\x2A\x88\x4F\x36\x48\x89\x07\x0F\xB7\x47\x37\x48\x89\x57\x08\x48\xC7\x47\x10\x00\x00\x00\x00\x48\xC7\x47\x18\x00\x00\x00\x00\x66\x25\x80\x00\x48\xC7\x47\x20\xFF\xFF\xFF\xFF\x83\xC8\x49\x48\xC7\x47\x28\xFF\xFF\xFF\xFF\xC7\x47\x30\x00\x00\x00\x00\x66\x89\x47\x37\x48\x89\xF7\xE8\x2A\x2A\x2A\x2A\x31\xFF");
	DECLARE_SIG(TracePlayerBBoxForGround, "\x55\x48\x89\xE5\x41\x57\x4D\x89\xC7\x41\x56\x49\x89\xD6\x41\x55\x41\x54");
	DECLARE_SIG(InitGameTrace, "\x55\x48\x89\xE5\x41\x57\x41\x56\x41\x55\x41\x54\x53\x48\x89\xFB\x48\x81\xEC\xA8\x00\x00\x00\x4C\x8B\x25\x2A\x2A\x2A\x2A\x4D\x85\xE4");
	DECLARE_SIG(GetMaxSpeed, "\x55\x48\x89\xE5\x41\x55\x41\x54\x53\x48\x89\xFB\x48\x83\xEC\x2A\x4C\x8D\x25\x2A\x2A\x2A\x2A\x49\x8B\x3C\x24\xE8");
	DECLARE_SIG(ProcessMovement, "\x55\x48\x89\xE5\x41\x57\x41\x56\x41\x55\x41\x54\x49\x89\xFC\x53\x48\x83\xEC\x2A\x48\x8B\x7F\x2A\x8B");
	DECLARE_SIG(PlayerMoveNew, "\x55\x48\x89\xE5\x41\x55\x49\x89\xF5\x41\x54\x49\x89\xFC\x48\x8B\x7F\x2A");
	DECLARE_SIG(CheckParameters, "\x55\x48\x89\xE5\x41\x57\x41\x56\x41\x55\x41\x54\x49\x89\xFC\x53\x48\x89\xF3\x48\x83\xEC\x2A\xE8\x2A\x2A\x2A\x2A\x49\x8B");
	DECLARE_SIG(CanMove, "\x55\xBE\xFF\xFF\xFF\xFF\x48\x89\xE5\x53\x48\x89\xFB\x48\x8D\x3D\x2A\x2A\x2A\x2A\x48\x83\xEC\x2A\xE8\x2A\x2A\x2A\x2A\x48\x85\xC0\x74\x1E");
	DECLARE_SIG(FullWalkMove, "\x55\x48\x89\xE5\x41\x57\x41\x56\x41\x55\x49\x89\xF5\x41\x54\x49\x89\xFC\x53\x48\x83\xEC\x2A\x84");
	DECLARE_SIG(MoveInit, "\x55\x48\x89\xE5\x41\x55\x49\x89\xF5\x41\x54\x49\x89\xFC\x48\x89\xF7\x53\x48\x83\xEC\x2A\x48");
	DECLARE_SIG(CheckWater, "\x55\x48\x89\xE5\x41\x54\x49\x89\xF4\x53\x48\x89\xFB\x48\x81\xEC\x2A\x2A\x2A\x2A\x48");
	DECLARE_SIG(CheckVelocity, "\x55\x48\x89\xE5\x41\x57\x41\x56\x41\x55\x49\x89\xFD\x41\x54\x53\x48\x89\xF3\x48\x83\xEC\x2A\x48\x8B\x7F");
	DECLARE_SIG(Duck, "\x55\x48\x89\xE5\x41\x57\x41\x56\x49\x89\xFE\x41\x55\x45\x31\xED\x41\x54\x49\x89\xF4\x53\x48\x81");
	DECLARE_SIG(LadderMove, "\x48\xB8\x00\x00\x00\x00\xFF\xFF\xFF\xFF\x55\x48\x89\xE5\x41\x57\x49\x89\xFF\x41\x56\x41\x55\x41\x54\x4C");
	DECLARE_SIG(CheckJumpButton, "\x55\x48\x89\xE5\x41\x56\x41\x55\x41\x54\x49\x89\xF4\xBE\x2A\x2A\x2A\x2A\x53\x48\x89\xFB\x48\x83\xEC\x2A\xE8");
	DECLARE_SIG(OnJump, "\x55\x48\x89\xE5\x41\x57\x41\x56\x41\x55\x41\x54\x49\x89\xFC\x53\x48\x89\xF3\x48\x83\xEC\x2A\x48\x8B\x7F");
	DECLARE_SIG(AirAccelerate, "\x55\x66\x0F\xEF\xED\x48\x89\xE5\x41\x55");
	DECLARE_SIG(Friction, "\x55\x48\x89\xE5\x41\x56\x41\x55\x41\x54\x49\x89\xFC\x53\x48\x89\xF3\x48\x83\xEC\x2A\x48\x8B\x47\x2A\x48\x8B");
	DECLARE_SIG(WalkMove, "\x48\xB8\x00\x00\x00\x00\xFF\xFF\xFF\xFF\x55\x48\x89\xE5\x41\x57\x41\x56\x4C\x8D\xBD\xDC");
	DECLARE_SIG(TryPlayerMove, "\x48\xB8\x00\x00\x00\x00\xFF\xFF\xFF\xFF\x55\x66\x0F\xEF\xC0");
	DECLARE_SIG(CategorizePosition, "\x48\xB8\x00\x00\x00\x00\xFF\xFF\xFF\xFF\x55\x48\x89\xE5\x41\x57\x41\x89\xD7");
	DECLARE_SIG(FinishGravity, "\x55\x48\x89\xE5\x41\x56\x41\x55\x41\x54\x49\x89\xF4\x53\x48\x89\xFB\x48\x83\xEC\x2A\x48\x8B\x57");
	DECLARE_SIG(CheckFalling, "\x55\x48\x89\xE5\x41\x57\x41\x56\x41\x55\x41\x54\x49\x89\xF4\x53\x48\x89\xFB\x48\x83\xEC\x2A\x48\x8B\x7F\x2A\xE8");
	// Function at the end of the function containing PlayerMove_PostMove string (which is inlined in windows)
	DECLARE_SIG(PlayerMovePost, "\x55\x48\x89\xE5\x41\x56\x49\x89\xF6\x41\x55\x41\x54\x53\x48\x89\xFB\x48\x83\xEC\x10");
	DECLARE_SIG(PostThink, "\x55\x48\x89\xE5\x41\x57\x49\x89\xFF\x41\x56\x41\x55\x41\x54\x53\x48\x81\xEC\x2A\x2A\x2A\x2A\xE8\x2A\x2A\x2A\x2A\x4C");
#endif
}