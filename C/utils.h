#ifndef UTILS_H
#define UTILS_H

#include "cache.h"
#include "endprodukt.h"
#include "schritt.h"
#include "teil.h"

double berechne_kosten(const char *name, StuecklisteDict *stueckliste, PreisDict *preise, CacheEintrag *cache, int cache_size);
#endif
