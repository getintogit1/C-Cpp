from schritt import Schritt, lade_schritte_aus_tsv_file
from teil import Teil, lade_teile_aus_tsv_file, baue_preis_dict
from endprodukt import (
    Endprodukt,
    ermittle_anzahl_pro_komponente_pro_namen,
    ermittle_schritte_pro_name,
    ermittle_endproukt_namen_aus_schritten,
)
# from utils import


def berechne_kosten(name, stueckliste, preise, cache=None):
    if cache is None:
        cache = {}

    # Falls schon berechnet → direkt zurückgeben
    if name in cache:
        return cache[name]

    # Fall 1: Basis-Teil (kein Eintrag in stueckliste)
    if name not in stueckliste:
        kosten = preise[name]
        cache[name] = kosten
        return kosten

    # Fall 2: Endprodukt → rekursiv berechnen
    gesamt = 0
    for teil, menge in stueckliste[name].items():
        teil_kosten = berechne_kosten(teil, stueckliste, preise, cache)
        gesamt += teil_kosten * menge

    cache[name] = gesamt
    return gesamt


def main():
    teile = lade_teile_aus_tsv_file("teil.dat")
    preise = baue_preis_dict(teile)
    schritte = lade_schritte_aus_tsv_file("schritt.dat")
    namen = ermittle_endproukt_namen_aus_schritten(schritte)
    for name in namen:
        print(name)

    schritteProNamen = ermittle_schritte_pro_name(schritte, namen)
    print(schritteProNamen)

    stueckliste = ermittle_anzahl_pro_komponente_pro_namen(schritteProNamen)
    print("Stueckliste:", stueckliste)
    kosten_ww3 = berechne_kosten("Warpkern W3", stueckliste, preise)
    print("ww3", kosten_ww3)
    kosten_ww4 = berechne_kosten("Warpkern W4", stueckliste, preise)
    print("ww4", kosten_ww4)
    kosten_Gehaeuse_Lager_100 = berechne_kosten(
        "Gehäuse Lager-100", stueckliste, preise
    )
    print("Gehäuse Lager-100", kosten_Gehaeuse_Lager_100)


if __name__ == "__main__":
    main()
