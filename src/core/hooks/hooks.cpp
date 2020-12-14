#include "../../includes.hpp"
#include "hooks.hpp"
#include "vmt.hpp"
#include <unistd.h>

/* Create hooks */
bool Hooks::init() {
    Log::log("Initialising hooks...");
    if (!initSDL()) {
        Log::err("Failed to initialise SDL hooks!");
        return false;
    }

    Log::log(" Hooking CreateMove...");
    CreateMove::original = (CreateMove::func)VMT::hook(Interfaces::clientMode, (void*)CreateMove::hook, 25);

    Log::log(" Hooking PaintTraverse...");
    PaintTraverse::original = (PaintTraverse::func)VMT::hook(Interfaces::panel, (void*)PaintTraverse::hook, 42);

    Log::log("Initialised hooks!");
    return true;
}

/* Unload hooks */
bool Hooks::unload() {
    Log::log("Unloading hooks...");

    if (!unloadSDL()) {
        Log::err("Failed to unload SDL hooks!");
        return false;
    }

    /* hook with original to do bigrain unhooking */
    Log::log(" Unhooking CreateMove...");
    VMT::hook(Interfaces::clientMode, (void*)CreateMove::original, 25);

    Log::log(" Unhooking PaintTraverse...");
    VMT::hook(Interfaces::panel, (void*)PaintTraverse::original, 42);
    
    /* Wait 2 secs so you dont uninject while a hook is still running */
    usleep(2000000);

    Log::log("Unloaded hooks!");
    return true;
}