
from dataclasses import dataclass
from datetime import date

from Domain.entity import Entity


@dataclass
class Cardclient(Entity):
    nume: str
    prenume: str
    cnp: str
    data_nasterii: date
    data_inregistrarii: date
    puncte_acumulate: int = 0
