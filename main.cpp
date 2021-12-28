#define _CRT_SECURE_NO_WARNINGS /* thanks Microsoft */
#include <windows.h>
#include <stdio.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <iostream>

#include <string>
#include <locale>
#include <codecvt>


#include "gmrpc.h"
#include "gms.h"
#include "discord-files/discord_rpc.h"

using namespace std;

/* DLL global variables */
static const char* APPLICATION_ID = "345229890980937739";
bool initialized = false;
int64_t endTime = -1; // Since epoch
int64_t startTime = -1; // Since epoch

/***
 Discord Callbacks
***/

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
    printf("\nDiscord: join request from %s#%s - %s\n",
           request->username,
           request->discriminator,
           request->userId);
}


/* Discord Functions */

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

    // Set initialized to true
    initialized = true;
}

/** DLL Exposed functions */

/**
* @param appid The app id of the app
* @brief This is the first function to be called. Initializes the rpc dll
*/
gmx gmbool gmrpc_init(const char* appid)
{
    APPLICATION_ID = appid;
    discordInit();
    std::cout << "Initialized presence to App "<< appid <<endl;
    return gmtrue;
}

/**
* @brief Sets the start timestamp (Time since epoch)
* @param passedTime The timestamp
*/
gmx gmbool gmrpc_setStarttime(gmint passedTime)
{
    startTime = int64_t(passedTime);
    return gmtrue;
}

/**
* @brief Sets the end timestamp (Time since epoch)
* @param passedTime The timestamp
*/
gmx gmbool gmrpc_setEndtime(gmint passedTime)
{
    endTime = int64_t(passedTime);
    return gmtrue;
}

/**
* @param state The state to display
* @param details The details to display
* @param largeKey The image to show (large)
* @param smallKey The image to show (small)
* @brief This changes the presence of displayed info
*/
gmx gmbool gmrpc_setPresence(stringToDLL state, stringToDLL details, stringToDLL largeKey, stringToDLL smallKey)
{
    if(!initialized) // Check if initialized rpc
    {
        gmu::debugmessage("GMRPC is not initialized! Please call gmrpc_init(...) first");
        return gmfalse;
    }

    char statebuf[256];
    char detbuf[256];
    char smallBuf[256];
    char largeBuf[256];
    // Get RPC
    DiscordRichPresence discordPresence;
    memset(&discordPresence, 0, sizeof(discordPresence));
    /// Set state
    string tempState = gmu::constcharptr_to_string(state);
    sprintf(statebuf, "%s", gmu::string_to_charptr(tempState));
    discordPresence.state = statebuf;

    /// Set Details
    string tempDetails = gmu::constcharptr_to_string(details);
    sprintf(detbuf, "%s", gmu::string_to_charptr(tempDetails));
    discordPresence.details = detbuf;

    /// Set small image
    string tempSmall = gmu::constcharptr_to_string(smallKey);
    sprintf(smallBuf, "%s", gmu::string_to_charptr(tempSmall));
    discordPresence.smallImageKey = smallBuf;

    /// Set large image
    string tempLarge = gmu::constcharptr_to_string(largeKey);
    sprintf(largeBuf, "%s", gmu::string_to_charptr(tempLarge));
    discordPresence.largeImageKey = largeBuf;

    /// Add timestamps if set
    if(startTime != -1)
    {
        discordPresence.startTimestamp = startTime;
    }
    else if(endTime  != -1)
    {
        discordPresence.endTimestamp = endTime;
    }
    // Reset timestamps
    startTime = -1;
    endTime = -1;

    /// Finish and call update
    discordPresence.instance = 0;
    Discord_UpdatePresence(&discordPresence);
    Discord_RunCallbacks();

    cout << "Updated Presence to "<<tempState << " / "<< tempDetails<<endl;
    return gmtrue;
}

/**
* @brief Exits and frees the dll
*/
gmx gmbool gmrpc_exit()
{
    if(!initialized) // Check if initialized rpc
    {
        gmu::debugmessage("GMRPC is not initialized! Please call gmrpc_init(...) first");
        return gmfalse;
    }
    std::cout << "Exiting GMRPC"<<endl;
    Discord_Shutdown();
    return gmtrue;
}

/**
* @brief Reset presence
*/
gmx gmbool gmrpc_clear()
{
    if(!initialized) // Check if initialized rpc
    {
        gmu::debugmessage("GMRPC is not initialized! Please call gmrpc_init(...) first");
        return gmfalse;
    }
    Discord_ClearPresence();
    std::cout << "Clearing Presence"<<endl;
    return gmtrue;
}



/// User management
/*
gmx stringFromDLL gmrpc_user_getUsername()
{
    if(!initialized) // Check if initialized rpc
    {
        gmu::debugmessage("GMRPC is not initialized! Please call gmrpc_init(...) first");
        return "";
    }

    // try converting
    try{
        cout << localUser->username << endl;
       //return gmu::string_to_charptr(localUser->username);
       return "Amogus";
    }
    catch(std::logic_error &e)
    {

        cout << "Could not fetch username! "<< e.what()<< endl;
        return "GMRPC_ERR_USERNAME";
    }

}*/


/**
* @brief This is to check the connection to the dll. Does nothing really.
*/
gmx gmint gmrpc_checkConnection(gmint n)
{
    return n*2;
}
/*<!--- Unused ----> */
/*
static void updateDiscordPresence()
{

    if (SendPresence) {
        /// Alloc buffers
        char statebuf[256];
        char detbuf[256];
        char smallBuf[256];
        char largeBuf[256];

        /// Get a presence
        DiscordRichPresence discordPresence;
        memset(&discordPresence, 0, sizeof(discordPresence));

        /// Write to buffer

        // Set state
        string tempState = gmu::constcharptr_to_string(P_state);
        sprintf(statebuf, "%s", gmu::string_to_charptr(tempState));
        discordPresence.state = statebuf;

        // Set Details
        string tempDetails = gmu::constcharptr_to_string(P_details);
        sprintf(detbuf, "%s", gmu::string_to_charptr(tempDetails));
        discordPresence.details = detbuf;

         // Set small image
        string tempSmall = gmu::constcharptr_to_string(P_smallKey);
        sprintf(smallBuf, "%s", gmu::string_to_charptr(tempSmall));
        discordPresence.state = smallBuf;

        // Set large image
        string tempLarge = gmu::constcharptr_to_string(P_largeKey);
        sprintf(largeBuf, "%s", gmu::string_to_charptr(tempLarge));
        discordPresence.details = largeBuf;

        /// Do some other stuff...

        discordPresence.startTimestamp = StartTime;
        discordPresence.endTimestamp = time(0) + 5 * 60;

        discordPresence.instance = 0;
        Discord_UpdatePresence(&discordPresence);
    }
    else {
        Discord_ClearPresence();
    }
}
*/


/** Example from official discord repo **/

/*
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include "gms.h"

#include "discord-files/discord_rpc.h"

static const char* APPLICATION_ID = "345229890980937739";
static int FrustrationLevel = 0;
static int64_t StartTime;
static int SendPresence = 1;

static int prompt(char* line, size_t size)
{
    int res;
    char* nl;
    printf("\n> ");
    fflush(stdout);
    res = fgets(line, (int)size, stdin) ? 1 : 0;
    line[size - 1] = 0;
    nl = strchr(line, '\n');
    if (nl) {
        *nl = 0;
    }
    return res;
}

static void updateDiscordPresence()
{
    if (SendPresence) {
        char buffer[256];
        DiscordRichPresence discordPresence;
        memset(&discordPresence, 0, sizeof(discordPresence));
        discordPresence.state = "West of House";
        sprintf(buffer, "Frustration level: %d", FrustrationLevel);
        discordPresence.details = buffer;
        discordPresence.startTimestamp = StartTime;
        discordPresence.endTimestamp = time(0) + 5 * 60;
        discordPresence.largeImageKey = "canary-large";
        discordPresence.smallImageKey = "ptb-small";
        discordPresence.partyId = "party1234";
        discordPresence.partySize = 1;
        discordPresence.partyMax = 6;
        //discordPresence.partyPrivacy = DISCORD_PARTY_PUBLIC;
        discordPresence.matchSecret = "xyzzy";
        discordPresence.joinSecret = "join";
        discordPresence.spectateSecret = "look";
        discordPresence.instance = 0;
        Discord_UpdatePresence(&discordPresence);
    }
    else {
        Discord_ClearPresence();
    }
}

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
    char yn[4];
    printf("\nDiscord: join request from %s#%s - %s\n",
           request->username,
           request->discriminator,
           request->userId);
    do {
        printf("Accept? (y/n)");
        if (!prompt(yn, sizeof(yn))) {
            break;
        }

        if (!yn[0]) {
            continue;
        }

        if (yn[0] == 'y') {
            response = DISCORD_REPLY_YES;
            break;
        }

        if (yn[0] == 'n') {
            response = DISCORD_REPLY_NO;
            break;
        }
    } while (1);
    if (response != -1) {
        Discord_Respond(request->userId, response);
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

static void gameLoop()
{
    char line[512];
    char* space;

    StartTime = time(0);

    printf("You are standing in an open field west of a white house.\n");
    while (prompt(line, sizeof(line))) {
        if (line[0]) {
            if (line[0] == 'q') {
                break;
            }

            if (line[0] == 't') {
                printf("Shutting off Discord.\n");
                Discord_Shutdown();
                continue;
            }

            if (line[0] == 'c') {
                if (SendPresence) {
                    printf("Clearing presence information.\n");
                    SendPresence = 0;
                }
                else {
                    printf("Restoring presence information.\n");
                    SendPresence = 1;
                }
                updateDiscordPresence();
                continue;
            }

            if (line[0] == 'y') {
                printf("Reinit Discord.\n");
                discordInit();
                continue;
            }

            if (time(NULL) & 1) {
                printf("I don't understand that.\n");
            }
            else {
                space = strchr(line, ' ');
                if (space) {
                    *space = 0;
                }
                printf("I don't know the word \"%s\".\n", line);
            }

            ++FrustrationLevel;

            updateDiscordPresence();
            printf("Amogus");
        }

#ifdef DISCORD_DISABLE_IO_THREAD
        Discord_UpdateConnection();
#endif
        Discord_RunCallbacks();
    }
}

int main(int argc, char* argv[])
{
    discordInit();

    gameLoop();

    Discord_Shutdown();
    return 0;
}*/
