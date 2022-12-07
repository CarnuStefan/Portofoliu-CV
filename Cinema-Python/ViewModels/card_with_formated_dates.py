from dataclasses import dataclass


@dataclass
class CardWithFormatedDates:
    id_card: str
    nume: str
    prenume: str
    cnp: str
    data_nasterii: str
    data_inregistrarii: str
    puncte_acumulate: int = 0
