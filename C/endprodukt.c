#include "endprodukt.h"
#include "schritt.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char **ermittle_endproukt_namen_aus_schritten(SchrittListe *liste,
                                              int *anzahl) {
  char **namen =
      malloc(liste->count * sizeof(char *)); // worst case: alle verschieden
  int count = 0;

  for (int i = 0; i < liste->count; i++) {
    char name[100];
    snprintf(name, sizeof(name), "%s %s", liste->data[i].ziel_typ,
             liste->data[i].ziel_bezeichnung);

    // Prüfen ob Name schon existiert
    int exists = 0;
    for (int j = 0; j < count; j++) {
      if (strcmp(namen[j], name) == 0) {
        exists = 1;
        break;
      }
    }

    if (!exists) {
      namen[count] = malloc(strlen(name) + 1);
      strcpy(namen[count], name);
      count++;
    }
  }

  *anzahl = count;
  return namen;
}

SchritteProEndProduktDict
ermittle_schritte_pro_name(SchrittListe *liste, char **namen, int namen_count) {

  SchritteProEndProduktDict dict;
  dict.data = malloc(namen_count * sizeof(SchritteProEndProduktEintrag));
  dict.count = namen_count;

  // Initialisieren
  for (int i = 0; i < namen_count; i++) {
    strcpy(dict.data[i].name, namen[i]);
    dict.data[i].schrittListe.data = malloc(liste->count * sizeof(Schritt));
    dict.data[i].schrittListe.count = 0;
  }

  // Schritte sortieren nach schritt_nr (Bubble sort für Einfachheit)
  for (int a = 0; a < liste->count; a++) {
    for (int b = a + 1; b < liste->count; b++) {
      if (liste->data[b].schritt_nr < liste->data[a].schritt_nr) {
        Schritt tmp = liste->data[a];
        liste->data[a] = liste->data[b];
        liste->data[b] = tmp;
      }
    }
  }

  // Schritte zuordnen
  for (int i = 0; i < liste->count; i++) {
    char name[100];
    snprintf(name, sizeof(name), "%s %s", liste->data[i].ziel_typ,
             liste->data[i].ziel_bezeichnung);

    for (int j = 0; j < namen_count; j++) {
      if (strcmp(dict.data[j].name, name) == 0) {
        int k = dict.data[j].schrittListe.count;
        dict.data[j].schrittListe.data[k] = liste->data[i];
        dict.data[j].schrittListe.count++;
      }
    }
  }

  return dict;
}

void ermittle_anzahl_pro_komponente_pro_namen(EndProdukt *produkte, int count) {
  for (int i = 0; i < count; i++) {
    EndProdukt *p = &produkte[i];

    // Speicher vorbereiten
    p->komponenten.data = malloc(100 * sizeof(KomponentenEintrag));
    p->komponenten.count = 0;

    for (int s = 0; s < p->schritt_count; s++) {
      Schritt *sch = &p->schritte[s];

      char kompname[100];
      snprintf(kompname, sizeof(kompname), "%s %s", sch->quell_typ,
               sch->quell_bezeichnung);

      double menge = (double)sch->menge;

      // prüfen ob existiert
      int found = 0;
      for (int k = 0; k < p->komponenten.count; k++) {
        if (strcmp(p->komponenten.data[k].name, kompname) == 0) {
          p->komponenten.data[k].menge += menge;
          found = 1;
          break;
        }
      }

      if (!found) {
        int idx = p->komponenten.count;
        strcpy(p->komponenten.data[idx].name, kompname);
        p->komponenten.data[idx].menge = menge;
        p->komponenten.count++;
      }
    }
  }
}

StuecklisteEintrag *get_stueckliste(const char *name,
                                    StuecklisteDict *stueckliste) {
  for (int i = 0; i < stueckliste->count; i++) {
    if (strcmp(stueckliste->data[i].name, name) == 0)
      return &stueckliste->data[i];
  }
  return NULL;
}

int main_endprodukt() {
  // 1) Schritte laden
  SchrittListe liste = lade_schritte_aus_file("schritt.dat");

  // 2) Endprodukt-Namen bestimmen
  int namen_count = 0;
  char **namen = ermittle_endproukt_namen_aus_schritten(&liste, &namen_count);

  printf("Gefundene Endprodukte:\n");
  for (int i = 0; i < namen_count; i++) {
    printf(" - %s\n", namen[i]);
  }

  // 3) Schritte pro Namen ermitteln
  SchritteProEndProduktDict dict =
      ermittle_schritte_pro_name(&liste, namen, namen_count);

  printf("\nSchritte pro Endprodukt:\n");
  for (int i = 0; i < dict.count; i++) {
    SchritteProEndProduktEintrag *e = &dict.data[i];
    printf("Endprodukt: %s (%d Schritte)\n", e->name, e->schrittListe.count);
  }

  // 4) Komponenten berechnen
  EndProdukt *produkte = malloc(sizeof(EndProdukt) * namen_count);

  for (int i = 0; i < namen_count; i++) {
    snprintf(produkte[i].name, sizeof(produkte[i].name), "%s", namen[i]);
    produkte[i].schritte = dict.data[i].schrittListe.data;
    produkte[i].schritt_count = dict.data[i].schrittListe.count;
    produkte[i].komponenten.data = NULL;
    produkte[i].komponenten.count = 0;
  }

  ermittle_anzahl_pro_komponente_pro_namen(produkte, namen_count);

  printf("\nKomponenten pro Endprodukt:\n");
  for (int i = 0; i < namen_count; i++) {
    printf("Endprodukt: %s\n", produkte[i].name);
    for (int j = 0; j < produkte[i].komponenten.count; j++) {
      KomponentenEintrag *e = &produkte[i].komponenten.data[j];
      printf("   %s  ->  %.2f\n", e->name, e->menge);
    }
  }

  // 5) Speicher freigeben
  for (int i = 0; i < namen_count; i++) {
    free(namen[i]);
  }
  free(namen);
  free(produkte);
  free(liste.data);

  return 0;
}
