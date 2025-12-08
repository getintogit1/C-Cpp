#include "teil.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

TeilListe lade_teile_aus_file(const char *filename) {
  TeilListe liste;
  liste.data = NULL;
  liste.count = 0;

  FILE *f = fopen(filename, "r");
  if (!f) {
    perror("Fehler beim Öffnen der Datei");
    return liste;
  }

  char line[256]; // gg
  while (fgets(line, sizeof(line), f)) {
    line[strcspn(line, "\r\n")] = 0; // Whitespace entfernen (wie strip())

    if (strlen(line) == 0) // leere Zeile überspringen
      continue;

    char *words[5]; // Wörter splitten
    int i = 0;
    char *token = strtok(line, " ");
    while (token && i < 5) {
      words[i++] = token;
      token = strtok(NULL, " ");
    }

    if (i < 5)
      continue; // fehlerhafte Zeile

    liste.data =
        realloc(liste.data,
                (liste.count + 1) * sizeof(Teil)); // Liste mit Teilen befuellen
    Teil *t = &liste.data[liste.count];
    snprintf(t->typ, sizeof(t->typ), "%s", words[0]);
    snprintf(t->bezeichnung, sizeof(t->bezeichnung), "%s", words[1]);
    snprintf(t->einheit, sizeof(t->einheit), "%s", words[2]);
    t->gewicht = atof(words[3]);
    t->preis = atof(words[4]);

    liste.count++;
  }

  fclose(f);
  return liste;
}

PreisDict baue_preis_dict(const TeilListe *liste) {
  PreisDict dict;
  dict.data = NULL;
  dict.count = 0;

  for (int i = 0; i < liste->count; i++) {
    const Teil *t = &liste->data[i];

    dict.data = realloc(dict.data, (dict.count + 1) * sizeof(PreisEintrag));
    PreisEintrag *e = &dict.data[dict.count];

    snprintf(e->name, sizeof(e->name), "%s %s", t->typ,
             t->bezeichnung); // name = "typ bezeichnung"
    e->preis = t->preis;

    dict.count++;
  }
  return dict;
}

double get_preis(const char *name, PreisDict *preise) {
  for (int i = 0; i < preise->count; i++) {
    if (strcmp(preise->data[i].name, name) == 0)
      return preise->data[i].preis;
  }
  return 0.0;
}

int main_teil(int argc, char *argv[]) {
  const char *filename = "teil.dat";
  TeilListe teile = lade_teile_aus_file(filename);

  for (int i = 0; i < teile.count; i++) {
    printf(
        "typ: %s\nbezeichnung: %s\neinheit: %s\ngewicht: %.2f\npreis: %.2f\n\n",
        teile.data[i].typ, teile.data[i].bezeichnung, teile.data[i].einheit,
        teile.data[i].gewicht, teile.data[i].preis);
  }

  free(teile.data);

  PreisDict p = baue_preis_dict(&teile);

  for (int i = 0; i < p.count; i++) {
    printf("%s -> %.2f\n", p.data[i].name, p.data[i].preis);
  }

  free(p.data);
  return EXIT_SUCCESS;
}
