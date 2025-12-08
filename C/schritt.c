#include "schritt.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

SchrittListe lade_schritte_aus_file(const char *filename) {
  SchrittListe liste;
  liste.data = NULL;
  liste.count = 0;

  FILE *f = fopen(filename, "r");
  if (!f) {
    perror("Fehler beim Öffnen der Datei");
    return liste;
  }

  char line[256];
  while (fgets(line, sizeof(line), f)) {
    line[strcspn(line, "\r\n")] = 0; // Whitespace entfernen (wie strip())

    if (strlen(line) == 0) // leere Zeile überspringen
      continue;

    char *words[8]; // Wörter splitten
    int i = 0;
    char *token = strtok(line, " ");
    while (token && i < 8) {
      words[i++] = token;
      token = strtok(NULL, " ");
    }

    if (i < 8)
      continue; // fehlerhafte Zeile

    liste.data = realloc(liste.data, (liste.count + 1) * sizeof(Schritt));
    Schritt *s = &liste.data[liste.count];

    snprintf(s->ziel_typ, sizeof(s->ziel_typ), "%s", words[0]);
    snprintf(s->ziel_bezeichnung, sizeof(s->ziel_bezeichnung), "%s", words[1]);
    s->schritt_nr = atof(words[2]);
    snprintf(s->quell_typ, sizeof(s->quell_typ), "%s", words[3]);
    snprintf(s->quell_bezeichnung, sizeof(s->quell_bezeichnung), "%s", words[4]);
    s->menge = atof(words[5]);
    snprintf(s->taetigkeit, sizeof(s->taetigkeit), "%s", words[6]);
    s->zeit = atof(words[7]);
    liste.count++;
  }

  fclose(f);
  return liste;
}

int main_schritt(int argc, char *argv[]) {
  const char *filename = "schritt.dat";
  SchrittListe schritte = lade_schritte_aus_file(filename);

  for (int i = 0; i < schritte.count; i++) {
    printf(
        "ziel_typ: %s\nziel_bezeichnung: %s\nschritt_nr: %d\nquell_typ: "

        "%s\nquell_bezeichnung: %s\nmenge: %f\ntaetigkeit: %s\nzeit: %.2f\n\n",
        schritte.data[i].ziel_typ, schritte.data[i].ziel_bezeichnung,
        schritte.data[i].schritt_nr, schritte.data[i].quell_typ,
        schritte.data[i].quell_bezeichnung, schritte.data[i].menge,
        schritte.data[i].taetigkeit, schritte.data[i].zeit);
  }

  free(schritte.data);

  return EXIT_SUCCESS;
}
