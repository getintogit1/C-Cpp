#ifndef CACHE_H
#define CACHE_H

typedef struct {
  char name[100];
  double kosten;
  int valid; // 1 = gültig, 0 = leer
} CacheEintrag;

int cache_lookup(const char *name, CacheEintrag *cache, int cache_size, double *value);
void cache_store(const char *name, double value, CacheEintrag *cache, int cache_size);

#endif // !CACHE_H
