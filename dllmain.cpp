/*#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <iostream>

#include "gms.h"
#include "discord-files/discord_rpc.h"



static const char* APPLICATION_ID = "345229890980937739";
static int SendPresence = 1;
static stringToDLL P_state = "";
static stringToDLL P_details = "";
static stringToDLL P_largeKey = "";
static stringToDLL P_smallKey = "";


static void handleDiscordReady(const DiscordUser* connectedUser)
{
    printf("\nDiscord: connected to user %s#%s - %s\n",
           connectedUser->username,
           connectedUser->discriminator,
           connectedUser->userId);
}

static void handleDiscordDisconnected(int errcode, const char* message)
{
    printf("\nDiscord: disconnected (%d: %s)\n", errcode, message);
}

static void handleDiscordError(int errcode, const char* message)
{
    printf("\nDiscord: error (%d: %s)\n", errcode, message);
}

static void handleDiscordJoin(const char* secret)
{
    printf("\nDiscord: join (%s)\n", secret);
}

static void handleDiscordSpectate(const char* secret)
{
    printf("\nDiscord: spectate (%s)\n", secret);
}

static void handleDiscordJoinRequest(const DiscordUser* request)
{
    int response = -1;
    printf("\nDiscord: join request from %s#%s - %s\n",
           request->username,
           request->discriminator,
           request->userId);
}



static void updateDiscordPresence()
{
    if (SendPresence) {
        DiscordRichPresence discordPresence;
        memset(&discordPresence, 0, sizeof(discordPresence));
        discordPresence.state = P_state;
        discordPresence.details = P_details;
        //discordPresence.startTimestamp = StartTime;
        //discordPresence.endTimestamp = time(0) + 5 * 60;
        discordPresence.largeImageKey = P_largeKey;
        discordPresence.smallImageKey = P_smallKey;
        //discordPresence.partyId = "party1234";
        //discordPresence.partySize = 1;
        //discordPresence.partyMax = 6;
        //discordPresence.matchSecret = "xyzzy";
        //discordPresence.joinSecret = "join";
        //discordPresence.spectateSecret = "look";
        discordPresence.instance = 0;
        Discord_UpdatePresence(&discordPresence);
    }
    else {
        Discord_ClearPresence();
    }
}

static void discordInit()
{
    DiscordEventHandlers handlers;
    memset(&handlers, 0, sizeof(handlers));
    handlers.ready = handleDiscordReady;
    handlers.disconnected = handleDiscordDisconnected;
    handlers.errored = handleDiscordError;
    handlers.joinGame = handleDiscordJoin;
    handlers.spectateGame = handleDiscordSpectate;
    handlers.joinRequest = handleDiscordJoinRequest;
    Discord_Initialize(APPLICATION_ID, &handlers, 1, NULL);
}


gmx GMBOOL gmrpc_init(double appid)
{
    APPLICATION_ID = gmu::string_to_constcharptr(std::to_string(appid));
    discordInit();
    std::cout << "Set APPID to "<< APPLICATION_ID << "."<< std::endl;
    return GMTRUE;
}

gmx GMBOOL gmrpc_setText(stringToDLL state, stringToDLL details)
{
    P_state = state;
    P_details = details;
    return GMTRUE;
}

gmx GMBOOL gmrpc_setImages(stringToDLL large, stringToDLL small)
{
    P_smallKey = small;
    P_largeKey = large;
    return GMTRUE;
}

gmx GMBOOL gmrpc_update(GMINT appid)
{
    std::cout << "Updating GMRPC with APPID "<<appid <<std::endl;
    updateDiscordPresence();
    Discord_RunCallbacks();
    return GMTRUE;
}

gmx GMBOOL gmrpc_exit(GMINT appid)
{
    std::cout << "Exiting GMRPC with APPID "<<appid <<std::endl;
    Discord_Shutdown();
    return GMTRUE;
}

gmx GMBOOL gmrpc_toggleActive(GMINT on)
{
    SendPresence = (int)on;
    updateDiscordPresence();
}


*/
