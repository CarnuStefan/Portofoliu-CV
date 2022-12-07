
from dataclasses import dataclass
from datetime import datetime

from Domain.entity import Entity


@dataclass
class Rezervare(Entity):
    id_film: str
    data_si_ora: datetime
    id_card_client: str = None
