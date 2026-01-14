
#pragma once

#include <string>
#include <vector>

// Klasse Schritt
class Schritt {
public:
  std::string ziel_typ;
  std::string ziel_bez;
  std::string schritt_nr;
  std::string quell_typ;
  std::string quell_bez;
  std::string menge;
  std::string taetigkeit;
  std::string zeit;
  std::vector<std::string> benoetigtes_teil;

  // Konstruktor
  Schritt(const std::string &ziel_typ_, const std::string &ziel_bez_,
          const std::string &schritt_nr_, const std::string &quell_typ_,
          const std::string &quell_bez_, const std::string &menge_,
          const std::string &taetigkeit_, const std::string &zeit_);

  void print() const;

private:
  std::vector<std::string> erstelle_benoetigtes_teil() const;
};

std::vector<Schritt> lade_schritte_aus_file(const std::string &filename);
