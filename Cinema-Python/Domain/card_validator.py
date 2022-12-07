from Domain.card_client import Cardclient
from Repository.repository import Repository


class CardValidator:
    def __init__(self, card_repository: Repository):
        self.card_repository = card_repository

    def validate(self, cardnou: Cardclient):
        erori = []

        if len(cardnou.cnp) != 13:
            erori.append('CNP invalid: '
                         'codul numeric personal este format din 13 cifre')
        if not cardnou.cnp.isnumeric():
            erori.append('CNP invalid: '
                         'codul numeric personal poate contine doar cifre')
        for card in self.card_repository.read():
            if self.card_repository.read(cardnou.id_entity):
                if (card.cnp == cardnou.cnp) & (
                        cardnou.cnp != self.card_repository.read(
                        cardnou.id_entity).cnp):
                    erori.append('CNP invalid: '
                                 'exista un card '
                                 'cu acest cod numeric personal')
            elif card.cnp == cardnou.cnp:
                erori.append('CNP invalid: '
                             'exista un card '
                             'cu acest cod numeric personal')

        if erori:
            raise ValueError(erori)
