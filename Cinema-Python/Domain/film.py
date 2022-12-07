from dataclasses import dataclass

from Domain.entity import Entity


@dataclass
class Film(Entity):
    titlu_film: str
    an_aparitie: int
    pret_bilet_film: float
    film_in_program: bool
