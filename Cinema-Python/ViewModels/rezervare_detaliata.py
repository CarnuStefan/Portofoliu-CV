from dataclasses import dataclass

from Domain.film import Film
from ViewModels.card_with_formated_dates import CardWithFormatedDates


@dataclass
class RezervareDetaliata:
    id_rezervare: str
    id_film: Film
    data_si_ora: str
    id_card_client: CardWithFormatedDates
