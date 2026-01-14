#include "schritt.h"
#include <algorithm>
#include <fstream>
#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <string>
#include <vector>

#include "endprodukt.h"
Endprodukt::Endprodukt(const std::string &name_,
                       const std::vector<Schritt> &schritte_,
                       const std::map<std::string, double> &komponenten_)
    : name(name_), schritte(schritte_), komponenten(komponenten_), preis(0.0) {}

void Endprodukt::berechne_preis() {
  // Logik hier einfügen
}

// Ermittle Produktnamen aus Schritten
std::set<std::string>
ermittle_produkt_namen_aus_schritten(const std::vector<Schritt> &schritte) {
  std::set<std::string> namen;
  for (const auto &schritt : schritte) {
    std::string name = schritt.ziel_typ + " " + schritt.ziel_bez;
    namen.insert(name);
  }
  return namen;
}

// Ermittle Schritte pro Produktname

std::map<std::string, std::vector<Schritt>>
ermittle_schritte_pro_name(const std::vector<Schritt> &schritte,
                           const std::set<std::string> &namen) {
  std::map<std::string, std::vector<Schritt>> schritteProNamen;
  for (const auto &name : namen) {
    schritteProNamen[name] = std::vector<Schritt>{};
  }

  std::vector<Schritt> sorted_schritte = schritte;
  std::sort(sorted_schritte.begin(), sorted_schritte.end(),
            [](const Schritt &a, const Schritt &b) {
              return a.schritt_nr < b.schritt_nr;
            });

  for (const auto &schritt : sorted_schritte) {
    std::string name = schritt.ziel_typ + " " + schritt.ziel_bez;
    if (namen.find(name) != namen.end()) {
      schritteProNamen[name].push_back(schritt);
    }
  }

  return schritteProNamen;
}

// Ermittle Anzahl pro Komponente pro Name
std::map<std::string, std::map<std::string, double>>
ermittle_anzahl_pro_komponente_pro_namen(
    const std::map<std::string, std::vector<Schritt>> &schritte_pro_namen) {
  std::map<std::string, std::map<std::string, double>> result;

  for (const auto &[name, schritte] : schritte_pro_namen) {
    std::map<std::string, double> komponenten;

    for (const auto &schritt : schritte) {
      std::string komponente = schritt.quell_typ + " " + schritt.quell_bez;
      double menge = std::stod(schritt.menge);
      komponenten[komponente] += menge;
    }

    result[name] = komponenten;
  }

  return result;
}

// Prüfen ob Name ein Endprodukt ist
bool ist_endprodukt(const std::string &name,
                    const std::vector<Schritt> &schritte) {
  for (const auto &schritt : schritte) {
    std::string schritt_name = schritt.quell_typ + " " + schritt.quell_bez;
    if (name == schritt_name)
      return false;
  }
  return true;
}

int main_endprodukt() {
  std::vector<Schritt> schritte = lade_schritte_aus_file("schritt.dat");

  std::set<std::string> namen = ermittle_produkt_namen_aus_schritten(schritte);
  for (const auto &name : namen) {
    std::cout << name << "\n";
  }

  auto schritteProNamen = ermittle_schritte_pro_name(schritte, namen);

  auto komponentenAnzahlProName =
      ermittle_anzahl_pro_komponente_pro_namen(schritteProNamen);

  std::cout << "------------------------------\n";

  std::vector<std::string> echte_endprodukte;
  for (const auto &name : namen) {
    if (ist_endprodukt(name, schritte)) {
      echte_endprodukte.push_back(name);
    }
  }

  for (const auto &name : echte_endprodukte) {
    std::cout << name << "\n";
  }

  return 0;
}
