
#ifndef SCHRITTE_H
#define SCHRITTE_H

typedef struct {
  char ziel_typ[50];
  char ziel_bezeichnung[50];
  int schritt_nr;
  char quell_typ[50];
  char quell_bezeichnung[50];
  double menge;
  char taetigkeit[50];
  double zeit;
} Schritt;

typedef struct {
  Schritt *data;
  int count;
} SchrittListe;

SchrittListe lade_schritte_aus_file(const char *filename);
#endif
