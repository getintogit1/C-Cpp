
#include "cache.h"
#include "endprodukt.h"
#include "schritt.h"
#include "teil.h"

double berechne_kosten(const char *name, StuecklisteDict *stueckliste,
                       PreisDict *preise, CacheEintrag *cache, int cache_size) {

  double cached_value;
  if (cache_lookup(name, cache, cache_size, &cached_value))
    return cached_value;

  StuecklisteEintrag *eintrag = get_stueckliste(name, stueckliste);

  if (!eintrag) {
    // Basis-Teil
    double kosten = get_preis(name, preise);
    cache_store(name, kosten, cache, cache_size);
    return kosten;
  }

  double gesamt = 0.0;
  for (int i = 0; i < eintrag->komponenten.count; i++) {
    KomponentenEintrag *k = &eintrag->komponenten.data[i];
    double teil_kosten =
        berechne_kosten(k->name, stueckliste, preise, cache, cache_size);
    gesamt += teil_kosten * k->menge;
  }

  cache_store(name, gesamt, cache, cache_size);
  return gesamt;
}
