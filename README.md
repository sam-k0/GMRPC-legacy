# GMRPC-legacy
Make your GameMaker game stand out with Rich Presence!

# Setup

  ## Get the Thing
 Download the latest [release](https://github.com/sam-k0/GMRPC-legacy/releases/tag/default) here.
	
 ## Import the gmz in GameMaker
Extensions -> Import (Drag and Drop onto the GMS window *may* work too)
 ## Use it in code
		

 - The first function you want to call is **gmrpc_init**(*AppID*).
	 - The AppID is obtained on the [discord developer](https://discord.com/developers/applications) page.
	 - I assume you already have your Game / App set up on Discord's side.
- After that, you can set the presence with gmrpc_setPresence(...)
	- Snytax: **gmrpc_setPresence**(*state, details, largeImage, smallImage*)
			Where:
			 
|parameter| description  |
|--|--|
|  State|is the state text displayed on the user's profile  |
|Details| are the details displayed on the user's profile|
|largeImage|is the large image displayed on the user's profile|
|smallImage|is the small image in the bottom right corner of the large image|

## Free the DLL
Make sure to exit Discord if you don't need it anymore.
		 This will unload the "discord-rpc.dll" from memory.

 
				
			
		 

