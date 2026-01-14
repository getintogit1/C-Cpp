#include "endprodukt.h"
#include "schritt.h"
#include "teil.h"
#include <algorithm>
#include <iostream>
#include <map>
#include <set>
#include <string>
#include <vector>

#include <iomanip>

// Rekursive Kostenberechnung
double berechne_kosten(
    const std::string &name,
    const std::map<std::string, std::map<std::string, double>> &stueckliste,
    const std::map<std::string, double> &preise,
    std::map<std::string, double> &cache) {
  if (cache.find(name) != cache.end()) {
    return cache[name];
  }

  // Basis-Teil
  if (stueckliste.find(name) == stueckliste.end()) {
    double kosten = preise.at(name);
    cache[name] = kosten;
    return kosten;
  }

  // Endprodukt → rekursiv berechnen
  double gesamt = 0.0;
  for (const auto &[teil, menge] : stueckliste.at(name)) {
    double teil_kosten = berechne_kosten(teil, stueckliste, preise, cache);
    gesamt += teil_kosten * menge;
  }

  cache[name] = gesamt;
  return gesamt;
}

int main() {
  std::vector<Teil> teile = lade_teile_aus_file("teil.dat");
  std::unordered_map<std::string, double> temp_preise = baue_preis_dict(teile);

  std::map<std::string, double> preise(temp_preise.begin(), temp_preise.end());

  std::vector<Schritt> schritte = lade_schritte_aus_file("schritt.dat");

  std::set<std::string> namen = ermittle_produkt_namen_aus_schritten(schritte);

  // Schritte pro Name
  auto schritteProNamen = ermittle_schritte_pro_name(schritte, namen);

  // Endprodukte ermitteln
  std::vector<std::string> echte_endprodukte;
  for (const auto &name : namen) {
    if (ist_endprodukt(name, schritte)) {
      echte_endprodukte.push_back(name);
    }
  }

  // Stückliste ermitteln
  auto stueckliste = ermittle_anzahl_pro_komponente_pro_namen(schritteProNamen);

  // Kosten berechnen
  std::map<std::string, double> cache;
  double summe = 0.0;
  int anzahl = 0;
  for (const auto &name : echte_endprodukte) {
    double kosten = berechne_kosten(name, stueckliste, preise, cache);
    std::cout << std::fixed << std::setprecision(12);
    std::cout << "Kosten für " << name << " sind: " << kosten << "\n";
    summe += kosten;
    anzahl++;
  }

  if (anzahl > 0) {
    double durchschnitt = summe / anzahl;
    std::cout << "Durchschnittspreis: " << durchschnitt << "\n";
  }
  return 0;
}
