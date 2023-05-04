#pragma once

#include "structs.hpp"
#include "launcher/launcher.hpp"

#define SELECT_VALUE(sp, mp) (game::is_sp() ? (sp) : (mp))

#define SERVER_CD_KEY "Open-IW5-CD-Key"

namespace game
{
	namespace native
	{
		typedef void (*Cmd_AddCommandInternal_t)(const char* cmdName, void (*function)(), cmd_function_s* allocedCmd);
		extern Cmd_AddCommandInternal_t Cmd_AddCommandInternal;

		typedef void (*Cmd_RemoveCommand_t)(const char* cmdName);
		extern Cmd_RemoveCommand_t Cmd_RemoveCommand;

		typedef void (*Cbuf_AddText_t)(LocalClientNum_t localClientNum, const char* text);
		extern Cbuf_AddText_t Cbuf_AddText;

		typedef void (*Conbuf_AppendText_t)(const char* message);
		extern Conbuf_AppendText_t Conbuf_AppendText;

		typedef void (*Com_Error_t)(errorParm_t code, const char* fmt, ...);
		extern Com_Error_t Com_Error;

		typedef bool (*Com_Filter_t)(const char* filter, const char* name, int casesensitive);
		extern Com_Filter_t Com_Filter;

		typedef void (*DB_LoadXAssets_t)(XZoneInfo* zoneInfo, unsigned int zoneCount, int sync);
		extern DB_LoadXAssets_t DB_LoadXAssets;

		typedef XAssetHeader (*DB_FindXAssetHeader_t)(XAssetType type, const char* name, int allowCreateDefault);
		extern DB_FindXAssetHeader_t DB_FindXAssetHeader;

		typedef int (*DB_IsXAssetDefault_t)(XAssetType type, const char* name);
		extern DB_IsXAssetDefault_t DB_IsXAssetDefault;

		typedef void (*DB_EnumXAssets_t)(int type, void(*func)(XAssetHeader, void*), const void* inData, bool includeOverride);
		extern DB_EnumXAssets_t DB_EnumXAssets;

		typedef const char* (*DB_GetXAssetName_t)(const XAsset* asset);
		extern DB_GetXAssetName_t DB_GetXAssetName;

		typedef const dvar_t* (*Dvar_RegisterBool_t)(const char* dvarName, bool value, unsigned __int16 flags, const char* description);
		extern Dvar_RegisterBool_t Dvar_RegisterBool;

		typedef const dvar_t* (*Dvar_RegisterFloat_t)(const char* dvarName, float value, float min, float max, unsigned __int16 flags, const char* description);
		extern Dvar_RegisterFloat_t Dvar_RegisterFloat;

		typedef const dvar_t* (*Dvar_RegisterInt_t)(const char* dvarName, int value, int min, int max, unsigned __int16 flags, const char* description);
		extern Dvar_RegisterInt_t Dvar_RegisterInt;

		typedef const dvar_t* (*Dvar_RegisterString_t)(const char* dvarName, const char* value, unsigned __int16 flags, const char* description);
		extern Dvar_RegisterString_t Dvar_RegisterString;

		typedef void (*Dvar_SetIntByName_t)(const char* dvarName, int value);
		extern Dvar_SetIntByName_t Dvar_SetIntByName;

		typedef void (*Dvar_SetFromStringByName_t)(const char* dvarName, const char* string);
		extern Dvar_SetFromStringByName_t Dvar_SetFromStringByName;

		typedef void (*Dvar_SetString_t)(const dvar_t* dvar, const char* value);
		extern Dvar_SetString_t Dvar_SetString;

		typedef void (*Dvar_ForEach_t)(void (*callback)(const dvar_t*, void*), void* userData);
		extern Dvar_ForEach_t Dvar_ForEach;

		typedef const char* (*Dvar_DisplayableValue_t)(const dvar_t* dvar);
		extern Dvar_DisplayableValue_t Dvar_DisplayableValue;

		typedef const char* (*Dvar_DisplayableLatchedValue_t)(const dvar_t* dvar);
		extern Dvar_DisplayableLatchedValue_t Dvar_DisplayableLatchedValue;

		typedef int (*G_RunFrame_t)(int, int);
		extern G_RunFrame_t G_RunFrame;

		typedef Weapon (*G_GetWeaponForName_t)(const char* name);
		extern G_GetWeaponForName_t G_GetWeaponForName;

		typedef void (*MSG_ReadData_t)(msg_t* msg, void* data, int len);
		extern MSG_ReadData_t MSG_ReadData;

		typedef void* (*MT_AllocIndex_t)(int numBytes, int type);
		extern MT_AllocIndex_t MT_AllocIndex;

		typedef unsigned int (*FindVariable_t)(unsigned int parentId, unsigned int name);
		extern FindVariable_t FindVariable;

		typedef void (*RemoveRefToValue_t)(int type, VariableUnion u);
		extern RemoveRefToValue_t RemoveRefToValue;

		typedef VariableValue (*GetEntityFieldValue_t)(unsigned int classnum, int entnum, int offset);
		extern GetEntityFieldValue_t GetEntityFieldValue;

		typedef unsigned int (*SL_GetStringOfSize_t)(const char* str, unsigned int user, unsigned int len, int type);
		extern SL_GetStringOfSize_t SL_GetStringOfSize;

		typedef void (*Scr_AddEntityNum_t)(int entnum, unsigned int classnum);
		extern Scr_AddEntityNum_t Scr_AddEntityNum;

		typedef void (*Scr_AddString_t)(const char* value);
		extern Scr_AddString_t Scr_AddString;

		typedef void (*Scr_AddInt_t)(int value);
		extern Scr_AddInt_t Scr_AddInt;

		typedef void (*Scr_AddFloat_t)(float value);
		extern Scr_AddFloat_t Scr_AddFloat;

		typedef void (*Scr_Notify_t)(gentity_s* ent, scr_string_t, unsigned int paramcount);
		extern Scr_Notify_t Scr_Notify;

		typedef void (*Scr_NotifyLevel_t)(unsigned int stringValue, unsigned int paramcount);
		extern Scr_NotifyLevel_t Scr_NotifyLevel;

		typedef unsigned int (*Scr_GetNumParam_t)();
		extern Scr_GetNumParam_t Scr_GetNumParam;

		typedef const char* (*Scr_GetString_t)(unsigned int index);
		extern Scr_GetString_t Scr_GetString;

		typedef bool (*Scr_CastString_t)(VariableValue* value);
		extern Scr_CastString_t Scr_CastString;

		typedef void (*Scr_ErrorInternal_t)();
		extern Scr_ErrorInternal_t Scr_ErrorInternal;

		typedef unsigned int (*Scr_LoadScript_t)(const char* filename);
		extern Scr_LoadScript_t Scr_LoadScript;

		typedef int (*Scr_GetFunctionHandle_t)(const char* filename, unsigned short name);
		extern Scr_GetFunctionHandle_t Scr_GetFunctionHandle;

		typedef int (*Scr_ExecThread_t)(int handle, unsigned int paramcount);
		extern Scr_ExecThread_t Scr_ExecThread;

		typedef void (*Scr_FreeThread_t)(unsigned short handle);
		extern Scr_FreeThread_t Scr_FreeThread;

		typedef void (*Scr_RegisterFunction_t)(void* func, int type, unsigned int name);
		extern Scr_RegisterFunction_t Scr_RegisterFunction;

		typedef unsigned int(*GetObjectType_t)(unsigned int id);
		extern GetObjectType_t GetObjectType;

		typedef void (*Sys_ShowConsole_t)();
		extern Sys_ShowConsole_t Sys_ShowConsole;

		typedef void (*Sys_Error_t)(const char* error, ...);
		extern Sys_Error_t Sys_Error;

		typedef int (*Sys_Milliseconds_t)();
		extern Sys_Milliseconds_t Sys_Milliseconds;

		typedef void (*Sys_Sleep_t)(int msec);
		extern Sys_Sleep_t Sys_Sleep;

		typedef void (*Sys_FreeFileList_t)(char** list);
		extern Sys_FreeFileList_t Sys_FreeFileList;

		typedef int (*Sys_MessageBox_t)(const char* lpText, const char* lpCaption, unsigned int uType, int defaultValue);
		extern Sys_MessageBox_t Sys_MessageBox;

		typedef void (*Sys_LockWrite_t)(FastCriticalSection* critSect);
		extern Sys_LockWrite_t Sys_LockWrite;

		typedef void (*Sys_TempPriorityEnd_t)(TempPriority*);
		extern Sys_TempPriorityEnd_t Sys_TempPriorityEnd;

		typedef void* (*PMem_AllocFromSource_NoDebug_t)(unsigned int size, unsigned int alignment, unsigned int type, int source);
		extern PMem_AllocFromSource_NoDebug_t PMem_AllocFromSource_NoDebug;

		typedef void* (*Hunk_AllocateTempMemoryHighInternal_t)(unsigned int size);
		extern Hunk_AllocateTempMemoryHighInternal_t Hunk_AllocateTempMemoryHighInternal;

		typedef void (*Hunk_FreeTempMemory_t)(void* buf);
		extern Hunk_FreeTempMemory_t Hunk_FreeTempMemory;

		typedef void (*Hunk_UserDestroy_t)(HunkUser* user);
		extern Hunk_UserDestroy_t Hunk_UserDestroy;

		typedef void (*VM_Notify_t)(unsigned int notifyListOwnerId, unsigned int stringValue, VariableValue* top);
		extern VM_Notify_t VM_Notify;

		typedef unsigned int (*BG_NetDataChecksum_t)();
		extern BG_NetDataChecksum_t BG_NetDataChecksum;

		typedef int (*BG_GetMaxSprintTime_t)(void* ps);
		extern BG_GetMaxSprintTime_t BG_GetMaxSprintTime;

		typedef int (*LiveStorage_GetPersistentDataDefVersion_t)();
		extern LiveStorage_GetPersistentDataDefVersion_t LiveStorage_GetPersistentDataDefVersion;

		typedef unsigned int (*LiveStorage_GetPersistentDataDefFormatChecksum_t)();
		extern LiveStorage_GetPersistentDataDefFormatChecksum_t LiveStorage_GetPersistentDataDefFormatChecksum;

		typedef void (*SV_DirectConnect_t)(netadr_s from);
		extern SV_DirectConnect_t SV_DirectConnect;

		typedef void (*SV_ClientEnterWorld_t)(mp::client_t* client, usercmd_s* cmd);
		extern SV_ClientEnterWorld_t SV_ClientEnterWorld;

		typedef void (*SV_Cmd_TokenizeString_t)(const char* text_in);
		extern SV_Cmd_TokenizeString_t SV_Cmd_TokenizeString;

		typedef void (*SV_Cmd_EndTokenizedString_t)();
		extern SV_Cmd_EndTokenizedString_t SV_Cmd_EndTokenizedString;

		typedef void (*SV_SpawnServer_t)(const char* server, int mapIsPreloaded, int savegame);
		extern SV_SpawnServer_t SV_SpawnServer;

		typedef void (*SV_GetConfigstring_t)(int index, char* buffer, int bufferSize);
		extern SV_GetConfigstring_t SV_GetConfigstring;

		typedef void (*XUIDToString_t)(const unsigned __int64* xuid, char* str);
		extern XUIDToString_t XUIDToString;

		typedef char* (*SEH_LocalizeTextMessage_t)(const char* pszInputBuffer, const char* pszMessageType, msgLocErrType_t errType);
		extern SEH_LocalizeTextMessage_t SEH_LocalizeTextMessage;

		typedef const char* (*SEH_GetLanguageName_t)(int iLanguage);
		extern SEH_GetLanguageName_t SEH_GetLanguageName;

		typedef void (*CM_TransformedCapsuleTrace_t)(trace_t* results, const float* start, const float* end,
			const Bounds* bounds, const Bounds* capsule, int contents,
			const float* origin, const float* angles);
		extern CM_TransformedCapsuleTrace_t CM_TransformedCapsuleTrace;

		typedef void (*PM_WeaponUseAmmo_t)(playerState_s* ps, const Weapon weapon, bool isAlternate, int amount, PlayerHandIndex hand);
		extern PM_WeaponUseAmmo_t PM_WeaponUseAmmo;

		typedef void (*PM_playerTrace_t)(pmove_t* pm, trace_t* results, const float* start, const float* end,
			const Bounds* bounds, int passEntityNum, int contentMask);
		extern PM_playerTrace_t PM_playerTrace;

		typedef void (*PM_trace_t)(const pmove_t* pm, trace_t* results, const float* start, const float* end,
			const Bounds* bounds, int passEntityNum, int contentMask);
		extern PM_trace_t PM_trace;

		typedef void (*Jump_ClearState_t)(playerState_s* ps);
		extern Jump_ClearState_t Jump_ClearState;

		typedef void (*Vec3Normalize_t)(float* v);
		extern Vec3Normalize_t Vec3Normalize;

		typedef void (*Cmd_ExecuteSingleCommand_t)(LocalClientNum_t localClientNum, int controllerIndex, const char* text);
		extern Cmd_ExecuteSingleCommand_t Cmd_ExecuteSingleCommand;

		typedef void (*Com_Quit_f_t)();
		extern Com_Quit_f_t Com_Quit_f;

		typedef void (*FS_Printf_t)(int h, const char* fmt, ...);
		extern FS_Printf_t FS_Printf;

		typedef int (*FS_ReadFile_t)(const char* qpath, char** buffer);
		extern FS_ReadFile_t FS_ReadFile;

		typedef int (*FS_CreatePath_t)(char* OSPath);
		extern FS_CreatePath_t FS_CreatePath;

		typedef int (*FS_HandleForFile_t)(FsThread thread);
		extern FS_HandleForFile_t FS_HandleForFile;

		typedef void (*FS_FCloseFile_t)(int h);
		extern FS_FCloseFile_t FS_FCloseFile;

		typedef char** (*FS_ListFilteredFiles_t)(searchpath_s* searchPath, const char* path, const char* extension, const char* filter, FsListBehavior_e behavior, int* numfiles, int allocTrackType);
		extern FS_ListFilteredFiles_t FS_ListFilteredFiles;

		typedef void (*player_die_t)(gentity_s* self, const gentity_s* inflictor, gentity_s* attacker, int damage, int meansOfDeath, const Weapon* iWeapon, bool isAlternate, const float* vDir, const hitLocation_t hitLoc, int psTimeOffset);
		extern player_die_t player_die;

		typedef void (*LargeLocalResetToMark_t)(int markPos);
		extern LargeLocalResetToMark_t LargeLocalResetToMark;

		typedef const char* (*Win_LocalizeRef_t)(const char* ref);
		extern Win_LocalizeRef_t Win_LocalizeRef;

		typedef const char* (*Key_KeynumToString_t)(int keynum, int translate);
		extern Key_KeynumToString_t Key_KeynumToString;

		extern decltype(longjmp)* _longjmp;

		constexpr auto CMD_MAX_NESTING = 8;
		extern CmdArgs* sv_cmd_args;
		extern CmdArgs* cmd_args;

		extern short* scrVarGlob;
		extern char** scrMemTreePub;
		extern char* scrMemTreeGlob;

		extern function_stack_t* scr_function_stack;
		extern scrVarPub_t* scr_VarPub;
		extern scrVmPub_t* scr_VmPub;

		extern unsigned int* levelEntityId;

		extern int* g_script_error_level;
		extern jmp_buf* g_script_error;

		extern scr_classStruct_t* g_classMap;

		constexpr auto MAX_CLIENTS = 18;
		extern int* svs_clientCount;

		constexpr auto MAX_GENTITIES = 2048u;
		constexpr auto ENTITYNUM_NONE = MAX_GENTITIES - 1u;
		extern gentity_s* g_entities;

		extern DeferredQueue* deferredQueue;

		extern float* com_codeTimeScale;

		extern int* com_frameTime;

		extern RTL_CRITICAL_SECTION* s_criticalSection;

		extern int* logfile;

		extern searchpath_s** fs_searchpaths;
		extern char* fs_gamedir;
		extern fileHandleData_t* fsh;
		extern int* fs_numServerIwds;
		extern int* fs_serverIwds;
		extern int* fs_iwdFileCount;
		extern int* com_fileAccessed;

		extern unsigned int(*threadId)[THREAD_CONTEXT_COUNT];

		extern int* initialized_0;
		extern int* sys_timeBase;
		extern unsigned __int64* sys_counterBase;

		extern int* dvarCount;
		extern dvar_t** sortedDvars;

		extern FastCriticalSection* db_hashCritSect;

		extern const char** g_assetNames;

		extern const char** command_whitelist;

		// Global Definitions & Functions
		constexpr auto JUMP_LAND_SLOWDOWN_TIME = 1800;

		constexpr auto MAX_QPATH = 64;
		constexpr auto MAX_OSPATH = 256;

		// Angle indexes
		constexpr auto PITCH = 0; // up / down
		constexpr auto YAW = 1; // left / right
		constexpr auto ROLL = 2; // fall over

		// From Quake III, to match game's assembly
		template <typename T, typename R>
		constexpr auto VectorScale(T v, R s, T out) { out[0] = v[0] * s; out[1] = v[1] * s; out[2] = v[2] * s; }

		int Vec4Compare(const float* a, const float* b);

		namespace mp
		{
			typedef char* (*SV_GetGuid_t)(int clientNum);
			extern SV_GetGuid_t SV_GetGuid;

			typedef void (*SV_GameSendServerCommand_t)(int clientNum, svscmd_type type, const char* text);
			extern SV_GameSendServerCommand_t SV_GameSendServerCommand;

			extern client_t* svs_clients;

			extern level_locals_t* level;
		}

		namespace sp
		{
			typedef bool (*IsServerRunning_t)();
			extern IsServerRunning_t IsServerRunning;

			typedef void (*SV_GameSendServerCommand_t)(int clientNum, const char* text);
			extern SV_GameSendServerCommand_t SV_GameSendServerCommand;

			typedef void (*TeleportPlayer_t)(gentity_s* player, float* origin, float* angles);
			extern TeleportPlayer_t TeleportPlayer;

			extern gentity_s* g_entities;

			extern gclient_s* g_clients;
		}

		int Cmd_Argc();
		const char* Cmd_Argv(int argIndex);

		void AddRefToValue(VariableValue* value);

		void* MT_Alloc(int numBytes, int type);

		dvar_t* Dvar_FindVar(const char* dvarName);

		const float* Scr_AllocVector(const float* v);
		void Scr_ClearOutParams();
		scr_entref_t Scr_GetEntityIdRef(unsigned int id);
		void Scr_NotifyId(unsigned int id, unsigned int stringValue, unsigned int paramcount);
		int Scr_SetObjectField(unsigned int classnum, int entnum, int offset);

		const char* SL_ConvertToString(unsigned int stringValue);
		unsigned int SL_GetString(const char* str, unsigned int user);
		unsigned int SL_GetCanonicalString(const char* str);

		void SV_SendClientGameState(mp::client_t* client);
		int SV_IsTestClient(int clientNum);
		void SV_DropClient(mp::client_t* drop, const char* reason, bool tellThem);
		void SV_DropAllBots();

		void ClientCommand(int clientNum);

		int GetProtocolVersion();

		void NetAdr_SetType(netadr_s* addr, netadrtype_t type);

		void TeleportPlayer(gentity_s* player, float* origin, float* angles);

		void CG_GameMessage(LocalClientNum_t localClientNum, const char* msg, int flags = 0);

		void Sys_EnterCriticalSection(CriticalSection critSect);
		void Sys_LeaveCriticalSection(CriticalSection critSect);
		bool Sys_TryEnterCriticalSection(CriticalSection critSect);
		bool Sys_IsMainThread();
		bool Sys_IsDatabaseThread();
		bool Sys_IsStreamThread();
		bool Sys_IsRenderThread();
		bool Sys_IsServerThread();
		void Sys_LockRead(FastCriticalSection* critSect);
		void Sys_UnlockRead(FastCriticalSection* critSect);
		void Sys_UnlockWrite(FastCriticalSection* critSect);
		[[noreturn]] void Sys_OutOfMemErrorInternal(const char* filename, int line);

		bool FS_Initialized();
		int FS_FOpenFileReadForThread(const char* filename, int* file, FsThread thread);
		void FS_CheckFileSystemStarted();

		XAssetEntry* DB_FindXAssetEntry(XAssetType type, const char* name);
		int DB_XAssetExists(XAssetType type, const char* name);

		int SEH_GetCurrentLanguage();

		void* Z_Malloc(std::size_t size);

		bool I_islower(int c);
		bool I_isupper(int c);
	}

	bool is_mp();
	bool is_sp();

	void initialize(launcher::mode mode);
}

#define Sys_OutOfMemError() game::native::Sys_OutOfMemErrorInternal(__FILE__, __LINE__)
