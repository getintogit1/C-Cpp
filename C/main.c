#include "cache.h"
#include "endprodukt.h"
#include "schritt.h"
#include "teil.h"
#include "utils.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {

  if (argc < 3) {
    fprintf(stderr, "Usage: %s <teil.dat> <schritt.dat>\n", argv[0]);
    return EXIT_FAILURE;
  }
  // Datei einlese
  const char *teileFile = argv[1];
  TeilListe teile = lade_teile_aus_file(teileFile);
  PreisDict preise = baue_preis_dict(&teile);

  const char *schritteFile = argv[2];
  SchrittListe schritte = lade_schritte_aus_file(schritteFile);

  // Namen der Endprodukte herausfinden
  int namen_count = 0;
  char **namen =
      ermittle_endproukt_namen_aus_schritten(&schritte, &namen_count);
  SchritteProEndProduktDict dict =
      ermittle_schritte_pro_name(&schritte, namen, namen_count);

  // Endprodukte erzeugen
  EndProdukt *produkte = malloc(sizeof(EndProdukt) * namen_count);

  for (int i = 0; i < namen_count; i++) {
    // Name
    snprintf(produkte[i].name, sizeof(produkte[i].name), "%s", dict.data[i].name);
    produkte[i].name[sizeof(produkte[i].name) - 1] = '\0';

    // Schritte
    produkte[i].schritte = dict.data[i].schrittListe.data;
    produkte[i].schritt_count = dict.data[i].schrittListe.count;

    // Komponenten initialisieren
    produkte[i].komponenten.data = malloc(100 * sizeof(KomponentenEintrag));
    produkte[i].komponenten.count = 0;
  }

  // Anzahl pro Buateil pro endproukt herausfinden
  ermittle_anzahl_pro_komponente_pro_namen(produkte, namen_count);
  StuecklisteDict stueckliste;
  stueckliste.count = namen_count;
  stueckliste.data = malloc(sizeof(StuecklisteEintrag) * namen_count);

  for (int i = 0; i < namen_count; i++) {
    snprintf(stueckliste.data[i].name, sizeof(stueckliste.data[i].name), "%s", produkte[i].name);
    stueckliste.data[i].komponenten.data = produkte[i].komponenten.data;
    stueckliste.data[i].komponenten.count = produkte[i].komponenten.count;
  }

  // Kosten Berechnen
  CacheEintrag cache[100] = {0};

  for (int i = 0; i < namen_count; i++) {
    double kosten = berechne_kosten(namen[i], &stueckliste, &preise, cache, 100);
    printf("Kosten %s: %f\n", namen[i], kosten);
  }
  return EXIT_SUCCESS;
}
