# LevelAccessControl

RFID based solution to prevent/gain access to some levels in a lift control panel.

# Prototyping

Das Prototyping findet auf einem Wemos D1 mini und einigen Shields statt.

## Aufgabenstellungen

1. Es wird ein Branch feature/blink_relais vom development Branch erstellt.
   In diesem Branch soll der technische Durchstich dokumentiert werden,
   wie mit der Beispiel Anwendung blink das Relais zum Schalten gebracht wird.
   Ziel soll es sein, zu klären welchen PIN das Relias-Shield verwendet und die einfache Ansteuerung (Initialisierung und Steuerung) zu zeigen
2. Es wird ein Branch feature/read_rfid vom development Branch erstellt.
   In diesem Branch soll der technisch Durchstich dokumentiert werden,
   wie mit der RFID-Hardware auf das Näherbringen/Auflegen einer RFID-Karte reagiert werden kann.
   Es soll bei Annäherung der Karte die eindeutige Kennung der Karte gelesen werden und über die Serielle Schnittstelle ausgegeben werden.
   Ziel soll es sein, zu klären welche PINs/IOs für das Steuern des RFID Moduls notwendig sind und wie gut sich auf die Ereignisse reagieren lässt.

# Branches

- feature/blink_relais: Einfaches Blink des Relays auf Pin D1 (GPIO 5)
- feature/read_rfid: RFID auslesen und ID in die serielle Konsole schreiben
- feature/read_ota: Einfaches OTA zum kontaklosem Update hinzufügen

# Pins:

## Relay-Modul:

| D1 Mini | GPIO | Modul |
| :-----: | :--: | :---: |
|   D1    |  5   |  D1   |

## RFID-Modul:

| D1 Mini | GPIO | Modul |
| :-----: | :--: | :---: |
|   D3    |  0   |  RST  |
|   D8    |  15  |  SDA  |
|   D7    |  13  | MOSI  |
|   D6    |  12  | MISO  |
|   D5    |  14  |  SCK  |
|   3v3   |      | 3.3v  |
|    G    |      |  GND  |

# Entwicklung Setup

## Konfiguration der Anwendung

Bestandteil des Repositories ist eine `settings.h.dist` Datei. 
Diese muss kopiert werden und als `settings.h` bereit gestellt werden.
Konfigurationen nur in der `settings.h` Datei vornehmen. 
Da diese Datei auch Passwöter enthält wird sie nicht mit in das Repository übertragen.
Bei Erweiterungen bitte diese unbedingt auch in der `settings.h.dist' für die weitere Entwicklung bereit stellen.
