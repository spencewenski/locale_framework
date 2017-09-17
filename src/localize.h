#pragma once
#include "hash.h"

/**
 * Macro used to mark a string a localizable. Source files are parsed and
 * strings wrapped in this macro are extracted into a string dictionary that
 * can then be localized.
 *
 * @param  str  String to mark as localizable.
 */
#define LOCALIZE(str) locale_str(HASH_DJB2(str))

/**
 * Initialize the locale dictionary.
 *
 * Should be called when the app is loading.
 */
void locale_init();

/**
 * Deinitialize the locale dictionary.
 *
 * Should be called when the app is closing to free memory used for the
 * locale dictionary.
 */
void local_deinit();

/**
 * Get the string for the given has value.
 *
 * @param  hashval Hash value to get the string for.
 * @return         The string associated with the given hash value.
 */
char *locale_str(int hashval);

