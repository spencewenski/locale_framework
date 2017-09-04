#pragma once
#include "hash.h"

#define LOCALIZE(str) locale_str(HASH_DJB2(str))

void locale_init(void);

char *locale_str(int hashval);

