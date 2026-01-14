#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

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

  Schritt(const std::string &ziel_typ_, const std::string &ziel_bez_,
          const std::string &schritt_nr_, const std::string &quell_typ_,
          const std::string &quell_bez_, const std::string &menge_,
          const std::string &taetigkeit_, const std::string &zeit_)
      : ziel_typ(ziel_typ_), ziel_bez(ziel_bez_), schritt_nr(schritt_nr_),
        quell_typ(quell_typ_), quell_bez(quell_bez_), menge(menge_),
        taetigkeit(taetigkeit_), zeit(zeit_) {
    benoetigtes_teil.push_back(quell_typ);
    benoetigtes_teil.push_back(quell_bez);
  }

  void print() const {
    std::cout << "ziel_typ: " << ziel_typ << "\n"
              << "ziel_bez: " << ziel_bez << "\n"
              << "schritt_nr: " << schritt_nr << "\n"
              << "quell_typ: " << quell_typ << "\n"
              << "quell_bez: " << quell_bez << "\n"
              << "menge: " << menge << "\n"
              << "taetigkeit: " << taetigkeit << "\n"
              << "zeit: " << zeit << "\n\n";
  }
};

std::vector<Schritt> lade_schritte_aus_file(const std::string &filename) {
  std::vector<Schritt> schritte;
  std::ifstream file(filename);
  std::string line;

  while (std::getline(file, line)) {
    if (line.empty())
      continue;

    std::istringstream iss(line);
    std::vector<std::string> words;
    std::string word;
    while (iss >> word) {
      words.push_back(word);
    }

    if (words.size() >= 8) {
      Schritt schritt(words[0], words[1], words[2], words[3], words[4],
                      words[5], words[6], words[7]);
      schritte.push_back(schritt);
    }
  }

  return schritte;
}

int main_schritt() {
  std::vector<Schritt> schritte = lade_schritte_aus_file("schritt.dat");

  for (const auto &schritt : schritte) {
    schritt.print();
  }

  return 0;
}
