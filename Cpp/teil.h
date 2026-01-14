

#pragma once

#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

class Teil {
public:
  std::string typ;
  std::string bezeichnung;
  std::string einheit;
  double gewicht;
  double preis;
  std::vector<Teil> komponenten;

  Teil(const std::string &typ, const std::string &bezeichnung,
       const std::string &einheit, double gewicht, double preis,
       const std::vector<Teil> &komponenten = {});

  friend std::ostream &operator<<(std::ostream &os, const Teil &teil);
};

std::vector<Teil> lade_teile_aus_file(const std::string &file);

std::unordered_map<std::string, double>
baue_preis_dict(const std::vector<Teil> &teile);
