from schritt import Schritt, lade_schritte_aus_tsv_file


def ermittle_endproukt_namen_aus_schritten(schritte) -> set[str]:
    namen = set()
    for schritt in schritte:
        name = f"{schritt.ziel_typ} {schritt.ziel_bez}"
        namen.add(name)
    return namen


def ermittle_schritte_pro_name(schritte, namen):
    schritteProNamen = {name: [] for name in namen}

    schritte.sort(key=lambda s: s.schritt_nr)
    for schritt in schritte:
        name = f"{schritt.ziel_typ} {schritt.ziel_bez}"
        if name in namen:
            schritteProNamen[name].append(schritt)

    return schritteProNamen


def ermittle_anzahl_pro_komponente_pro_namen(schritte_pro_namen):
    result = {}

    for name, schritte in schritte_pro_namen.items():
        komponenten = {}

        for schritt in schritte:
            komponente = f"{schritt.quell_typ} {schritt.quell_bez}"

            # Menge sicher als float casten
            menge = float(schritt.menge)

            komponenten[komponente] = komponenten.get(komponente, 0) + menge

        result[name] = komponenten

    return result


class Endprodukt:
    def __init__(self, name, schritte, komponenten) -> None:
        self.name = name
        self.schritte = schritte
        self.komponenten = komponenten
        self.preis = None

    def berechne_preis(self): ...


def main():
    schritte = lade_schritte_aus_tsv_file("schritt.dat")
    namen = ermittle_endproukt_namen_aus_schritten(schritte)
    for name in namen:
        print(name)

    schritteProNamen = ermittle_schritte_pro_name(schritte, namen)
    print(schritteProNamen)

    komponentenAnzahlProName = ermittle_anzahl_pro_komponente_pro_namen(
        schritteProNamen
    )
    print(komponentenAnzahlProName)


if __name__ == "__main__":
    main()
