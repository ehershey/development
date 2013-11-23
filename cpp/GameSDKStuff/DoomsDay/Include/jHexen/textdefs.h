
//**************************************************************************
//**
//** textdefs.h : Heretic 2 : Raven Software, Corp.
//**
//** $RCSfile: textdefs.h,v $
//** $Revision: 1.3 $
//** $Date: 2004/05/29 09:53:12 $
//** $Author: skyjake $
//**
//**************************************************************************

#define GET_TXT(x)		((*gi.text)[x].text)

// MN_menu.c ---------------------------------------------------------------

#define PRESSKEY GET_TXT(TXT_PRESSKEY)
#define PRESSYN GET_TXT(TXT_PRESSYN)
#define TXT_PAUSED GET_TXT(TXT_TXT_PAUSED)
#define QUITMSG GET_TXT(TXT_QUITMSG)
#define LOADNET GET_TXT(TXT_LOADNET)
#define QLOADNET GET_TXT(TXT_QLOADNET)
#define QSAVESPOT GET_TXT(TXT_QSAVESPOT)
#define SAVEDEAD GET_TXT(TXT_SAVEDEAD)
#define QSPROMPT GET_TXT(TXT_QSPROMPT)
#define QLPROMPT GET_TXT(TXT_QLPROMPT)
#define NEWGAME GET_TXT(TXT_NEWGAME)
#define MSGOFF GET_TXT(TXT_MSGOFF)
#define MSGON GET_TXT(TXT_MSGON)
#define NETEND GET_TXT(TXT_NETEND)
#define ENDGAME GET_TXT(TXT_ENDGAME)
#define DOSY GET_TXT(TXT_DOSY)
#define TXT_GAMMA_LEVEL_OFF GET_TXT(TXT_TXT_GAMMA_LEVEL_OFF)
#define TXT_GAMMA_LEVEL_1 GET_TXT(TXT_TXT_GAMMA_LEVEL_1)
#define TXT_GAMMA_LEVEL_2 GET_TXT(TXT_TXT_GAMMA_LEVEL_2)
#define TXT_GAMMA_LEVEL_3 GET_TXT(TXT_TXT_GAMMA_LEVEL_3)
#define TXT_GAMMA_LEVEL_4 GET_TXT(TXT_TXT_GAMMA_LEVEL_4)
#define	EMPTYSTRING	GET_TXT(TXT_EMPTYSTRING)

// P_inter.c ---------------------------------------------------------------

// Mana

#define TXT_MANA_1 GET_TXT(TXT_TXT_MANA_1)
#define TXT_MANA_2 GET_TXT(TXT_TXT_MANA_2)
#define TXT_MANA_BOTH GET_TXT(TXT_TXT_MANA_BOTH)

// Keys

#define	TXT_KEY_STEEL GET_TXT(TXT_TXT_KEY_STEEL)
#define	TXT_KEY_CAVE GET_TXT(TXT_TXT_KEY_CAVE)
#define	TXT_KEY_AXE	GET_TXT(TXT_TXT_KEY_AXE)
#define	TXT_KEY_FIRE GET_TXT(TXT_TXT_KEY_FIRE)
#define	TXT_KEY_EMERALD GET_TXT(TXT_TXT_KEY_EMERALD)
#define	TXT_KEY_DUNGEON	GET_TXT(TXT_TXT_KEY_DUNGEON)
#define	TXT_KEY_SILVER GET_TXT(TXT_TXT_KEY_SILVER)
#define	TXT_KEY_RUSTED GET_TXT(TXT_TXT_KEY_RUSTED)
#define	TXT_KEY_HORN GET_TXT(TXT_TXT_KEY_HORN)
#define	TXT_KEY_SWAMP GET_TXT(TXT_TXT_KEY_SWAMP)
#define TXT_KEY_CASTLE GET_TXT(TXT_TXT_KEY_CASTLE)

// Artifacts

#define TXT_ARTIINVULNERABILITY GET_TXT(TXT_TXT_ARTIINVULNERABILITY)
#define TXT_ARTIHEALTH GET_TXT(TXT_TXT_ARTIHEALTH)
#define TXT_ARTISUPERHEALTH GET_TXT(TXT_TXT_ARTISUPERHEALTH)
#define TXT_ARTISUMMON GET_TXT(TXT_TXT_ARTISUMMON)
#define TXT_ARTITORCH GET_TXT(TXT_TXT_ARTITORCH)
#define TXT_ARTIEGG GET_TXT(TXT_TXT_ARTIEGG)
#define TXT_ARTIFLY GET_TXT(TXT_TXT_ARTIFLY)
#define TXT_ARTITELEPORT GET_TXT(TXT_TXT_ARTITELEPORT)
#define TXT_ARTIPOISONBAG GET_TXT(TXT_TXT_ARTIPOISONBAG)
#define TXT_ARTITELEPORTOTHER GET_TXT(TXT_TXT_ARTITELEPORTOTHER)
#define TXT_ARTISPEED GET_TXT(TXT_TXT_ARTISPEED)
#define TXT_ARTIBOOSTMANA GET_TXT(TXT_TXT_ARTIBOOSTMANA)
#define TXT_ARTIBOOSTARMOR GET_TXT(TXT_TXT_ARTIBOOSTARMOR)
#define TXT_ARTIBLASTRADIUS GET_TXT(TXT_TXT_ARTIBLASTRADIUS)
#define TXT_ARTIHEALINGRADIUS GET_TXT(TXT_TXT_ARTIHEALINGRADIUS)

// Puzzle artifacts

#define TXT_ARTIPUZZSKULL GET_TXT(TXT_TXT_ARTIPUZZSKULL)
#define TXT_ARTIPUZZGEMBIG GET_TXT(TXT_TXT_ARTIPUZZGEMBIG)
#define TXT_ARTIPUZZGEMRED GET_TXT(TXT_TXT_ARTIPUZZGEMRED)
#define TXT_ARTIPUZZGEMGREEN1 GET_TXT(TXT_TXT_ARTIPUZZGEMGREEN1)
#define TXT_ARTIPUZZGEMGREEN2 GET_TXT(TXT_TXT_ARTIPUZZGEMGREEN2)
#define TXT_ARTIPUZZGEMBLUE1 GET_TXT(TXT_TXT_ARTIPUZZGEMBLUE1)
#define TXT_ARTIPUZZGEMBLUE2 GET_TXT(TXT_TXT_ARTIPUZZGEMBLUE2)
#define TXT_ARTIPUZZBOOK1 GET_TXT(TXT_TXT_ARTIPUZZBOOK1)
#define TXT_ARTIPUZZBOOK2 GET_TXT(TXT_TXT_ARTIPUZZBOOK2)
#define TXT_ARTIPUZZSKULL2 GET_TXT(TXT_TXT_ARTIPUZZSKULL2)
#define TXT_ARTIPUZZFWEAPON GET_TXT(TXT_TXT_ARTIPUZZFWEAPON)
#define TXT_ARTIPUZZCWEAPON GET_TXT(TXT_TXT_ARTIPUZZCWEAPON)
#define TXT_ARTIPUZZMWEAPON GET_TXT(TXT_TXT_ARTIPUZZMWEAPON)
#define TXT_ARTIPUZZGEAR GET_TXT(TXT_TXT_ARTIPUZZGEAR)
#define TXT_USEPUZZLEFAILED GET_TXT(TXT_TXT_USEPUZZLEFAILED)

// Items

#define TXT_ITEMHEALTH GET_TXT(TXT_TXT_ITEMHEALTH)
#define TXT_ITEMBAGOFHOLDING GET_TXT(TXT_TXT_ITEMBAGOFHOLDING)
#define TXT_ITEMSHIELD1 GET_TXT(TXT_TXT_ITEMSHIELD1)
#define TXT_ITEMSHIELD2 GET_TXT(TXT_TXT_ITEMSHIELD2)
#define TXT_ITEMSUPERMAP GET_TXT(TXT_TXT_ITEMSUPERMAP)
#define TXT_ARMOR1 GET_TXT(TXT_TXT_ARMOR1)
#define TXT_ARMOR2 GET_TXT(TXT_TXT_ARMOR2)
#define TXT_ARMOR3 GET_TXT(TXT_TXT_ARMOR3)
#define TXT_ARMOR4 GET_TXT(TXT_TXT_ARMOR4)

// Weapons

#define TXT_WEAPON_F2 GET_TXT(TXT_TXT_WEAPON_F2)
#define TXT_WEAPON_F3 GET_TXT(TXT_TXT_WEAPON_F3)
#define TXT_WEAPON_F4 GET_TXT(TXT_TXT_WEAPON_F4)
#define TXT_WEAPON_C2 GET_TXT(TXT_TXT_WEAPON_C2)
#define TXT_WEAPON_C3 GET_TXT(TXT_TXT_WEAPON_C3)
#define TXT_WEAPON_C4 GET_TXT(TXT_TXT_WEAPON_C4)
#define TXT_WEAPON_M2 GET_TXT(TXT_TXT_WEAPON_M2)
#define TXT_WEAPON_M3 GET_TXT(TXT_TXT_WEAPON_M3)
#define TXT_WEAPON_M4 GET_TXT(TXT_TXT_WEAPON_M4)
#define TXT_QUIETUS_PIECE GET_TXT(TXT_TXT_QUIETUS_PIECE)
#define TXT_WRAITHVERGE_PIECE GET_TXT(TXT_TXT_WRAITHVERGE_PIECE)
#define TXT_BLOODSCOURGE_PIECE GET_TXT(TXT_TXT_BLOODSCOURGE_PIECE)

// SB_bar.c ----------------------------------------------------------------

#define TXT_CHEATGODON GET_TXT(TXT_TXT_CHEATGODON)
#define TXT_CHEATGODOFF GET_TXT(TXT_TXT_CHEATGODOFF)
#define TXT_CHEATNOCLIPON GET_TXT(TXT_TXT_CHEATNOCLIPON)
#define TXT_CHEATNOCLIPOFF GET_TXT(TXT_TXT_CHEATNOCLIPOFF)
#define TXT_CHEATWEAPONS GET_TXT(TXT_TXT_CHEATWEAPONS)
#define TXT_CHEATHEALTH GET_TXT(TXT_TXT_CHEATHEALTH)
#define TXT_CHEATKEYS GET_TXT(TXT_TXT_CHEATKEYS)
#define TXT_CHEATSOUNDON GET_TXT(TXT_TXT_CHEATSOUNDON)
#define TXT_CHEATSOUNDOFF GET_TXT(TXT_TXT_CHEATSOUNDOFF)
#define TXT_CHEATTICKERON GET_TXT(TXT_TXT_CHEATTICKERON)
#define TXT_CHEATTICKEROFF GET_TXT(TXT_TXT_CHEATTICKEROFF)
#define TXT_CHEATARTIFACTS3 GET_TXT(TXT_TXT_CHEATARTIFACTS3)
#define TXT_CHEATARTIFACTSFAIL GET_TXT(TXT_TXT_CHEATARTIFACTSFAIL)
#define TXT_CHEATWARP GET_TXT(TXT_TXT_CHEATWARP)
#define TXT_CHEATSCREENSHOT GET_TXT(TXT_TXT_CHEATSCREENSHOT)
#define TXT_CHEATIDDQD GET_TXT(TXT_TXT_CHEATIDDQD)
#define TXT_CHEATIDKFA GET_TXT(TXT_TXT_CHEATIDKFA)
#define TXT_CHEATBADINPUT GET_TXT(TXT_TXT_CHEATBADINPUT)
#define TXT_CHEATNOMAP GET_TXT(TXT_TXT_CHEATNOMAP)

// G_game.c ----------------------------------------------------------------

#define TXT_GAMESAVED GET_TXT(TXT_TXT_GAMESAVED)

// M_misc.c ----------------------------------------------------------------

#define HUSTR_CHATMACRO1 GET_TXT(TXT_HUSTR_CHATMACRO1)
#define HUSTR_CHATMACRO2 GET_TXT(TXT_HUSTR_CHATMACRO2)
#define HUSTR_CHATMACRO3 GET_TXT(TXT_HUSTR_CHATMACRO3)
#define HUSTR_CHATMACRO4 GET_TXT(TXT_HUSTR_CHATMACRO4)
#define HUSTR_CHATMACRO5 GET_TXT(TXT_HUSTR_CHATMACRO5)
#define HUSTR_CHATMACRO6 GET_TXT(TXT_HUSTR_CHATMACRO6)
#define HUSTR_CHATMACRO7 GET_TXT(TXT_HUSTR_CHATMACRO7)
#define HUSTR_CHATMACRO8 GET_TXT(TXT_HUSTR_CHATMACRO8)
#define HUSTR_CHATMACRO9 GET_TXT(TXT_HUSTR_CHATMACRO9)
#define HUSTR_CHATMACRO0 GET_TXT(TXT_HUSTR_CHATMACRO0)

// AM_map.c ----------------------------------------------------------------

#define AMSTR_FOLLOWON GET_TXT(TXT_AMSTR_FOLLOWON)
#define AMSTR_FOLLOWOFF GET_TXT(TXT_AMSTR_FOLLOWOFF)