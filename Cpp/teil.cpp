#include <fstream>
#include <iostream>
#include <sstream>
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

  Teil(std::string typ, std::string bezeichnung, std::string einheit,
       double gewicht, double preis, std::vector<Teil> komponenten = {})
      : typ(std::move(typ)), bezeichnung(std::move(bezeichnung)),
        einheit(std::move(einheit)), gewicht(gewicht), preis(preis),
        komponenten(std::move(komponenten)) {}

  friend std::ostream &operator<<(std::ostream &os, const Teil &teil) {
    os << "Typ: " << teil.typ << "\n"
       << "Bez: " << teil.bezeichnung << "\n"
       << "Einheit: " << teil.einheit << "\n"
       << "Gewicht: " << teil.gewicht << "\n"
       << "Preis: " << teil.preis << "\n"
       << "Komponenten: " << teil.komponenten.size() << "\n";
    return os;
  }
};

std::vector<Teil> lade_teile_aus_file(const std::string &filePrm) {
  std::vector<Teil> teile;
  std::ifstream file(filePrm);

  if (!file) {
    std::cerr << "Fehler beim Öffnen der Datei: " << filePrm << "\n";
    return teile;
  }

  std::string line;
  while (std::getline(file, line)) {
    if (line.empty())
      continue;

    std::istringstream iss(line);
    std::string typ, bezeichnung, einheit;
    double gewicht, preis;

    iss >> typ >> bezeichnung >> einheit >> gewicht >> preis;

    teile.emplace_back(typ, bezeichnung, einheit, gewicht, preis);
  }

  return teile;
}

std::unordered_map<std::string, double>
baue_preis_dict(const std::vector<Teil> &teile) {
  std::unordered_map<std::string, double> preise;

  for (const auto &teil : teile) {
    std::string name = teil.typ + " " + teil.bezeichnung;
    preise[name] = teil.preis;
  }

  return preise;
}

int main_teil() {
  auto teile = lade_teile_aus_file("teil.dat");

  for (const auto &teil : teile) {
    std::cout << teil << "\n";
  }

  return 0;
}
