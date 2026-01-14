
#pragma once

#include "schritt.h"
#include <map>
#include <set>
#include <string>
#include <vector>

class Endprodukt {
public:
  std::string name;
  std::vector<Schritt> schritte;
  std::map<std::string, double> komponenten;
  double preis;

  Endprodukt(const std::string &name_, const std::vector<Schritt> &schritte_,
             const std::map<std::string, double> &komponenten_);

  void berechne_preis();
};

std::set<std::string>
ermittle_produkt_namen_aus_schritten(const std::vector<Schritt> &schritte);

std::map<std::string, std::vector<Schritt>>
ermittle_schritte_pro_name(const std::vector<Schritt> &schritte,
                           const std::set<std::string> &namen);

std::map<std::string, std::map<std::string, double>>
ermittle_anzahl_pro_komponente_pro_namen(
    const std::map<std::string, std::vector<Schritt>> &schritte_pro_namen);

bool ist_endprodukt(const std::string &name,
                    const std::vector<Schritt> &schritte);
