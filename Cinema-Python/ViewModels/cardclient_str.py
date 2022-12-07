from Domain.card_client import Cardclient


class CardClientString:
    def __init__(self, card: Cardclient):
        self.id_card = card.id_entity
        self.nume = card.nume
        self.prenume = card.prenume
        self.cnp = card.cnp
        self.data_nasterii = card.data_nasterii.strftime('%d.%m.%Y')
        self.data_inregistrarii = card.data_inregistrarii.strftime('%d.%m.%Y')
        self.puncte_acumulate = str(card.puncte_acumulate)

    def get_string(self):
        return self.id_card \
               + self.nume \
               + self.prenume \
               + self.cnp \
               + self.data_nasterii \
               + self.data_inregistrarii \
               + self.puncte_acumulate

    def get_values(self):
        return {"id_card": self.id_card,
                "nume": self.nume,
                "prenume": self.prenume,
                "cnp": self.cnp,
                "data_nasterii": self.data_nasterii,
                "data_inregistrarii": self.data_inregistrarii,
                "puncte": self.puncte_acumulate}
