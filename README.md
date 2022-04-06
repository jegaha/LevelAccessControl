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
