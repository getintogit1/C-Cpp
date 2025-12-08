
#ifndef TEILE_H
#define TEILE_H

typedef struct {
  char typ[50];
  char bezeichnung[50];
  char einheit[10];
  double gewicht;
  double preis;
} Teil;

typedef struct {
  Teil *data;
  int count;
} TeilListe;

typedef struct {
  char name[120];
  double preis;
} PreisEintrag;

typedef struct {
  PreisEintrag *data;
  int count;
} PreisDict;

TeilListe lade_teile_aus_file(const char *filename);
PreisDict baue_preis_dict(const TeilListe *liste);
double get_preis(const char *name, PreisDict *preise);

#endif
