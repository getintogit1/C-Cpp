from typing import List


def lade_teile_aus_tsv_file(tsv_file: str) -> List["Teil"]:
    teile = []
    with open(tsv_file, "r", encoding="utf-8") as f:
        for line in f:
            line = line.strip()
            words = line.split()

            if line:  # leere Zeilen überspringen
                teil = Teil(
                    words[0], words[1], words[2], float(words[3]), float(words[4])
                )
                teile.append(teil)
    return teile


def baue_preis_dict(teile: List["Teil"]) -> dict:
    preise = {}
    for teil in teile:
        name = f"{teil.typ} {teil.bezeichnung}"
        preise[name] = teil.preis  # float
    return preise


class Teil:
    def __init__(
        self, typ, bezeichnung, einheit, gewicht, preis, komponenten=None
    ) -> None:
        self.typ = typ
        self.bezeichnung = bezeichnung
        self.einheit = einheit
        self.gewicht = gewicht
        self.preis = preis
        self.komponenten: List[Teil] = []

        if komponenten is None:
            komponenten = []
        self.komponenten = komponenten

    def __repr__(self):
        return f""" 
    Typ: {self.typ}
    Bez: {self.bezeichnung}
    Einheit: {self.einheit}
    Gewicht: {self.gewicht}
    Preis: {self.preis}
    Komponenten: {self.komponenten}
    """


def main():
    teile = lade_teile_aus_tsv_file("teil.dat")
    for teil in teile:
        print(teil)


if __name__ == "__main__":
    main()
