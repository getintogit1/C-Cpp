from typing import List


def lade_schritte_aus_tsv_file(tsv_file: str) -> List["Schritt"]:
    schritte: List["Schritt"] = []
    with open(tsv_file, "r", encoding="utf-8") as f:
        for line in f:
            line = line.strip()
            words = line.split()

            if line:  # leere Zeilen überspringen
                schritt = Schritt(
                    words[0],
                    words[1],
                    words[2],
                    words[3],
                    words[4],
                    words[5],
                    words[6],
                    words[7],
                )
                schritte.append(schritt)
    return schritte


class Schritt:
    def __init__(
        self,
        ziel_typ,
        ziel_bez,
        schritt_nr,
        quell_typ,
        quell_bez,
        menge,
        taetigkeit,
        zeit,
    ) -> None:
        self.ziel_typ = ziel_typ
        self.ziel_bez = ziel_bez
        self.schritt_nr = schritt_nr
        self.quell_typ = quell_typ
        self.quell_bez = quell_bez
        self.menge = menge
        self.taetigkeit = taetigkeit
        self.zeit = zeit
        self.benoetigtes_teil = self.erstelle_benoetigtes_teil()

    def erstelle_benoetigtes_teil(self) -> List[str]:
        benoetigtes_teil: List[str] = [self.quell_typ, self.quell_bez]
        return benoetigtes_teil

    def __repr__(self):
        return f""" 
    ziel_typ: {self.ziel_typ}
    ziel_bez: {self.ziel_bez} 
    schritt_nr: {self.schritt_nr}
    quell_typ: {self.quell_typ}
    quell_bez: {self.quell_bez} 
    menge: {self.menge}
    taetigkeit: {self.taetigkeit}
    zeit: {self.zeit}
    """


def main():
    schritte = lade_schritte_aus_tsv_file("schritt.dat")
    for schritt in schritte:
        print(schritt)


if __name__ == "__main__":
    main()
