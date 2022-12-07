from Domain.film import Film
from Repository.repository import Repository


class FilmValidator:
    def __init__(self, film_repository: Repository):
        self.film_repository = film_repository

    def validate(self, film: Film):
        erori = []

        if film.pret_bilet_film < 0:
            erori.append("Pret invalid: "
                         "pretul trebuie sa fie pozitiv")
        if erori:
            raise ValueError(erori)
