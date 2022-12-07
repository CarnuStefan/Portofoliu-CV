from Domain.rezervare import Rezervare
from Repository.repository import Repository


class RezervareValidator:
    def __init__(self,
                 film_repository: Repository,
                 card_repository: Repository,
                 rezervare_repository: Repository):
        self.film_repository = film_repository
        self.card_repository = card_repository
        self.rezervare_repository = rezervare_repository

    def validare(self, rezervare: Rezervare, ):
        erori = []
        if self.card_repository.read(rezervare.id_card_client) is None:
            msg = f'Nu exista un card cu id-ul {rezervare.id_card_client} ' \
                  f'pe care sa se faca rezervarea'
            erori.append(msg)
        if self.film_repository.read(rezervare.id_film) is None:
            msg = f'Nu exista un film cu id-ul {rezervare.id_film}' \
                  f' pe care sa se faca rezervarea '
            erori.append(msg)
        else:
            film = self.film_repository.read(rezervare.id_film)
            if not film.film_in_program:
                msg = f'Filmul nu este in program'
                erori.append(msg)
        if erori:
            raise Exception(erori)
