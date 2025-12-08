

#include "cache.h"
#include <string.h>

int cache_lookup(const char *name, CacheEintrag *cache, int cache_size,
                 double *value) {
  for (int i = 0; i < cache_size; i++) {
    if (cache[i].valid && strcmp(cache[i].name, name) == 0) {
      *value = cache[i].kosten;
      return 1;
    }
  }
  return 0;
}

void cache_store(const char *name, double value, CacheEintrag *cache,
                 int cache_size) {
  for (int i = 0; i < cache_size; i++) {
    if (!cache[i].valid) {
      strncpy(cache[i].name, name, sizeof(cache[i].name) - 1);
      cache[i].name[sizeof(cache[i].name) - 1] = '\0';
      cache[i].kosten = value;
      cache[i].valid = 1;
      return;
    }
  }
}
