#ifndef DAEDALUS_TOUCHSYNC_H
#define DAEDALUS_TOUCHSYNC_H

// Included for the DateTime struct, cba to rip it out and it would prolly breach some kind of licence and I can't be bothered with that
#include <RTClib.h>

/**
 * @brief Handles all time synchronization functions, should be called every loop
 * @param now Pointer to where the new date should we saved
 * @return Whether or not a time synchronization happened
*/
bool daelus_tsync_tick(DateTime* now);

#endif