# SciFi-Fabrik – Teile- und Arbeitsschrittverarbeitung

Dieses Repository enthält eine Implementierung eines Uni-Projekts zur Verarbeitung von Bauteilen und Arbeitsschritten einer fiktiven SciFi-Fabrik.  
Das Projekt wurde zunächst in **Python** prototypisch umgesetzt und anschließend nach **C** und **C++** übertragen.

Die Programme lesen strukturierte Textdateien ein, verarbeiten die enthaltenen Daten und erzeugen – je nach Aufgabenstellung – Ausgaben auf der Konsole oder in Dateien.

---

## 📁 Projektstruktur

.
├── python/
│ └── main.py
├── c/
│ └── main.c
├── cpp/
│ └── main.cpp
└── README.md

yaml
Code kopieren

Jeder Ordner enthält eine eigenständige Implementierung derselben Logik in der jeweiligen Programmiersprache.

---

## 📄 Eingabedateien

Die Programme arbeiten mit **zwei Eingabedateien**, deren **Dateinamen über die Kommandozeile übergeben** werden.

⚠️ Die Dateien sind **nicht im Repository enthalten** und müssen separat bereitgestellt werden.

### 1️⃣ `teil.dat`

Enthält Bauteile der Fabrik.  
Jede Zeile beschreibt **ein Teil**, eindeutig identifiziert durch **Typ** und **Bezeichnung**.

**Format:**
Typ Bezeichnung Einheit Gewicht Preis

makefile
Code kopieren

**Beispiel:**
Motor XJ9 kg 12.5 199.99

yaml
Code kopieren

---

### 2️⃣ `schritt.dat`

Beschreibt die Arbeitsschritte zum Zusammenbauen von Teilen.

**Format:**
Ziel-Typ Ziel-Bez Nr Quell-Typ Quell-Bez Menge Taetigkeit Zeit

markdown
Code kopieren

**Bedeutung:**
- Beim Zusammenbau des Ziel-Teils
- wird im `Nr`-ten Schritt
- eine bestimmte `Menge` eines Quell-Teils
- durch Ausführen der angegebenen `Taetigkeit`
- in `Zeit` Sekunden verbaut

**Beispiel:**
Robot R2D2 1 Motor XJ9 2 montieren 120

yaml
Code kopieren

---

## 🔑 Wichtige Eigenschaften

- 🔹 Teile werden **immer über (Typ, Bezeichnung)** identifiziert
- 🔹 Die Programme **setzen keine Sortierung** der Eingabedateien voraus
- 🔹 Funktionieren auch mit **randomisierter Reihenfolge**
- 🔹 Robuste Verarbeitung durch explizite Suche statt Positionsannahmen
- 🔹 Ausgabe optional in **Datei oder Konsole**

---

## ▶️ Ausführung

### Python
```bash
python3 main.py teil.dat schritt.dat
C
bash
Code kopieren
gcc main.c -o fabrikanalyse
./fabrikanalyse teil.dat schritt.dat
C++
bash
Code kopieren
g++ main.cpp -o fabrikanalyse
./fabrikanalyse teil.dat schritt.dat
Optionale Ausgabedateien können (je nach Implementierung) ebenfalls über die Kommandozeile übergeben werden.

🧠 Implementierungsdetails
Einlesen der Dateien zeilenweise

Speicherung der Daten in geeigneten Datenstrukturen

Python: Dictionaries / Listen

C: Structs + Arrays

C++: Structs + STL-Container

Explizite Verknüpfung zwischen Teilen und Arbeitsschritten

Keine Annahmen über Dateireihenfolge oder Vollständigkeit

🎓 Kontext
Dieses Projekt wurde im Rahmen eines Universitätskurses erstellt und dient dem Vergleich von Implementierungen derselben Logik in verschiedenen Programmiersprache
