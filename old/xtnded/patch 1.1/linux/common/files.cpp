#include "../game/shared.hpp"

typedef struct {
	char pakFilename[256];               // c:\program files\call of duty\main\pak6.pk3
	char pakBasename[256];               // pak6
	char pakGamename[256];               // main
	void* handle;
	int checksum;
	int checksum_pure;
	int numfiles;
	int referenced;
	int hashSize;
	//rest idc
} pack_t;

typedef struct searchpath_s {
	struct searchpath_s *next;
	pack_t      *pak;
	void* dir; //cba to check and don't need it
} searchpath_t;

static searchpath_t    *fs_searchpaths = (searchpath_t*)0x80DD590;

int pak_num = 0;

bool FS_IsServerFile(char* basename) {
	bool flag = false;
	if(strstr(basename, "svr") != NULL)
		flag=1;
	if(strstr(basename, "server") != NULL)
		flag=1;
	if(strstr(basename, "localized") != NULL)
		flag=1;
	if(strstr(basename, "pak") != NULL)
		flag=1;
	return flag;
}

bool FS_IsExtendedFile(char* file) {
	bool flag = false;
	if(strstr(file, "xtnded") != NULL)
		flag=1;
	if(strstr(file, "codextended") != NULL)
		flag=1;
	return flag;
}

static bool count_flag = 1;

const char *__cdecl FS_LoadedPakPureChecksums( void ) {
	static char info[8192];
	info[0] = 0;
	searchpath_t *search;
	char fs_game[256];
	char* check = Cvar_VariableString("fs_game");
	if(check[0] == '\0')
		sprintf(fs_game, "main");
	else
		sprintf(fs_game, check);
	for(search = fs_searchpaths->next; search; search = search->next) {
		if(search->pak) {
			if(FS_IsServerFile(search->pak->pakBasename))
				continue;
			if ( *info ) {
				sprintf(info, "%s%s", info, " " );
			}
			//if(search->pak->referenced || !strcmp(fs_game, search->pak->pakGamename)) {
			if(search->pak->referenced || FS_IsExtendedFile(search->pak->pakBasename)) {
				sprintf(info, "%s%i", info, search->pak->checksum_pure);
				if(count_flag)
				pak_num++;
			}
		}
	}
	if(count_flag)
		count_flag=0;
	return info;
}

const char *__cdecl FS_ReferencedPakChecksums() {
	static char info[8192];
	info[0] = 0;
	searchpath_t *search;
	char fs_game[256];
	char* check = Cvar_VariableString("fs_game");
	if(check[0] == '\0')
		sprintf(fs_game, "main");
	else
		sprintf(fs_game, check);
	for(search = fs_searchpaths->next; search; search = search->next) {
		if(search->pak) {
			if(FS_IsServerFile(search->pak->pakBasename))
				continue;
			if ( *info ) {
				sprintf(info, "%s%s", info, " " );
			}
			//if(search->pak->referenced || !strcmp(fs_game, search->pak->pakGamename)) {
			if(search->pak->referenced || FS_IsExtendedFile(search->pak->pakBasename)) {
				sprintf(info, "%s%i", info, search->pak->checksum);
			}
		}
	}
	return info;
}

const char *__cdecl FS_ReferencedPakNames() {
	static char info[8192];
	info[0] = 0;
	searchpath_t *search;
	char fs_game[256];
	char* check = Cvar_VariableString("fs_game");
	if(check[0] == '\0')
		sprintf(fs_game, "main");
	else
		sprintf(fs_game, check);
	for(search = fs_searchpaths->next; search; search = search->next) {
		if(search->pak) {
			if(FS_IsServerFile(search->pak->pakBasename))
				continue;
			if ( *info ) {
				sprintf(info, "%s%s", info, " " );
			}
			//if(search->pak->referenced || !strcmp(fs_game, search->pak->pakGamename)) {
			if(search->pak->referenced || FS_IsExtendedFile(search->pak->pakBasename)) {
				//printf("PAK: %s with checksum %d and PURE = %d GAMENAME = %s\n", search->pak->pakBasename, search->pak->checksum, search->pak->checksum_pure, search->pak->pakGamename);
				sprintf(info, "%s%s", info, search->pak->pakGamename );
				sprintf(info, "%s%s", info, "/" );
				sprintf(info, "%s%s", info, search->pak->pakBasename );
			}
		}
	}
	return info;
}
