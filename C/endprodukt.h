#ifndef ENDPRODUKT_H
#define ENDPRODUKT_H

#include "schritt.h"

typedef struct {
  char name[100];
  double menge;
} KomponentenEintrag;

typedef struct {
  KomponentenEintrag *data;
  int count;
} KomponentenDict;

typedef struct {
  char name[100];
  Schritt *schritte;
  int schritt_count;
  KomponentenDict komponenten;
} EndProdukt;

typedef struct {
  char name[50];
  SchrittListe schrittListe;

} SchritteProEndProduktEintrag;

typedef struct {
  SchritteProEndProduktEintrag *data;
  int count;
} SchritteProEndProduktDict;

typedef struct {
  char name[100];
  KomponentenDict komponenten; // name + menge
} StuecklisteEintrag;

typedef struct {
  StuecklisteEintrag *data;
  int count;
} StuecklisteDict;

char **ermittle_endproukt_namen_aus_schritten(SchrittListe *liste, int *anzahl);

SchritteProEndProduktDict
ermittle_schritte_pro_name(SchrittListe *liste, char **namen, int namen_count);
StuecklisteEintrag *get_stueckliste(const char *name, StuecklisteDict *stueckliste);

void ermittle_anzahl_pro_komponente_pro_namen(EndProdukt *produkte, int count);

#endif // !ENDPRODUKT_H
