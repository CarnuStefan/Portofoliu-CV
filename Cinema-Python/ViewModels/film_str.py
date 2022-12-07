from Domain.film import Film


class FilmString:
    def __init__(self, film: Film):
        self.id_film = film.id_entity
        self.titlu_film = film.titlu_film
        self.an_aparitie = str(film.an_aparitie)
        self.pret_bilet_film = str(film.pret_bilet_film)
        if film.film_in_program:
            self.film_in_program = 'da'
        else:
            self.film_in_program = 'nu'

    def get_string(self):
        return self.id_film \
               + self.titlu_film \
               + self.an_aparitie \
               + self.pret_bilet_film \
               + self.film_in_program

    def get_values(self):
        return {"id_film": self.id_film,
                "titlu": self.titlu_film,
                "an aparitie": self.an_aparitie,
                "pret": self.pret_bilet_film,
                "in program": self.film_in_program,
                }
