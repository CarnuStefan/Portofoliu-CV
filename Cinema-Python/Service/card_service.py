import string
import random
from datetime import date
from typing import List

from Domain.card_client import Cardclient
from Domain.card_validator import CardValidator
from Domain.operation_add import OperationAdd
from Domain.operation_delete import OperationDelete
from Domain.operation_delete_cascada import OperationDeleteCascada
from Domain.operation_multi_add import OperationMultiAdd
from Domain.operation_multi_update import OperationMultiUpdate
from Domain.operation_update import OperationUpdate
from Repository.repository import Repository
from Service.undoredo_service import UndoRedoService
from utils import my_sort


def gen_random_date() -> date:
    an = random.randint(1, 9999)
    bisect = False
    if (an % 4 == 0) & (an % 100 != 0):
        bisect = True
    elif an % 400 == 0:
        bisect = True
    luna = random.randint(1, 12)
    zi = 1
    if luna == 2:
        if bisect:
            zi = random.randint(1, 29)
        else:
            zi = random.randint(1, 28)
    if luna in [4, 6, 9, 11]:
        zi = random.randint(1, 30)
    elif luna in [1, 3, 5, 7, 8, 10, 12]:
        zi = random.randint(1, 31)

    return date(an, luna, zi)


class CardService:
    def __init__(self,
                 card_repository: Repository,
                 card_validator: CardValidator,
                 undoredo_service: UndoRedoService):
        self.card_repository = card_repository
        self.card_validator = card_validator
        self.undoredo_service = undoredo_service

    def add_card(self,
                 id_card: str,
                 nume: str,
                 prenume: str,
                 cnp: str,
                 data_nasterii: date,
                 data_inregistrarii: date,
                 puncte_acumulate: int = 0):
        """
        Valideaza si adauga un card in repository
        :param id_card:
        :param nume:
        :param prenume:
        :param cnp:
        :param data_nasterii:
        :param data_inregistrarii:
        :param puncte_acumulate:
        :return:
        """
        card = Cardclient(id_card, nume, prenume, cnp, data_nasterii,
                          data_inregistrarii, puncte_acumulate)

        self.card_validator.validate(card)
        self.card_repository.create(card)
        addop = OperationAdd(self.card_repository, card)
        self.undoredo_service.clear_redo()
        self.undoredo_service.add_to_undo(addop)

    def update_card(self,
                    id_card: str,
                    nume: str,
                    prenume: str,
                    cnp: str,
                    data_nasterii: date,
                    data_inregistrarii: date,
                    puncte_acumulate: int = 0):
        """
        Valideaza si modifica cardul cu id_card din repository
        :param id_card:
        :param nume:
        :param prenume:
        :param cnp:
        :param data_nasterii:
        :param data_inregistrarii:
        :param puncte_acumulate:
        :return:
        """
        card = Cardclient(id_card, nume, prenume, cnp, data_nasterii,
                          data_inregistrarii, puncte_acumulate)
        self.card_validator.validate(card)
        old_card = self.card_repository.read(card.id_entity)
        self.card_repository.update(card)
        updateop = OperationUpdate(self.card_repository, old_card, card)
        self.undoredo_service.clear_redo()
        self.undoredo_service.add_to_undo(updateop)

    def delete_card(self, id_card):
        """
        Sterge cardul cu id_card din repository
        :param id_card:
        :return:
        """
        deleteop = OperationDelete(self.card_repository,
                                   self.card_repository.read(id_card))
        self.undoredo_service.clear_redo()
        self.undoredo_service.add_to_undo(deleteop)
        self.card_repository.delete(id_card)

    def gen_rand_n_cards(self, n: int) -> None:
        """
        Genereaza si adauga random n carduri in repository
        :param n: numarul de carduri care trebuie generate
        :return:
        """
        lista = []
        for i in range(n):
            while True:
                lenid = random.randint(1, 10)
                id_card = ''.join((random.choice(string.ascii_lowercase)
                                   for _ in range(lenid)))
                if self.card_repository.read(id_card) is None:
                    break
            lennume = random.randint(1, 10)
            nume = ''.join((random.choice(string.ascii_lowercase)
                            for _ in range(lennume)))
            lenprenume = random.randint(1, 10)
            prenume = ''.join((random.choice(string.ascii_lowercase)
                               for _ in range(lenprenume)))
            while True:
                ok = True
                cnp = ''.join((random.choice(string.digits)
                               for _ in range(13)))
                for card in self.card_repository.read():
                    if card.cnp == cnp:
                        ok = False
                if ok:
                    break
            data_nasterii = gen_random_date()
            data_inregistrarii = gen_random_date()
            puncte = random.randint(0, 50)

            card = Cardclient(id_card,
                              nume,
                              prenume,
                              cnp,
                              data_nasterii,
                              data_inregistrarii,
                              puncte)
            self.card_repository.create(card)
            lista = lista + [card]
            self.undoredo_service.clear_redo()
            multiaddop = OperationMultiAdd(self.card_repository, lista)
            self.undoredo_service.add_to_undo(multiaddop)

    def get_all(self):
        return self.card_repository.read()

    def get_card_descending(self) \
            -> List[Cardclient]:

        return my_sort(self.get_all(),
                       key=lambda x: x.puncte_acumulate,
                       reverse=True)

    def increment_between(self, data_inceput: date, data_final: date,
                          puncte: int) -> None:
        lst_undo = []
        lst_redo = []
        for card in self.get_all():
            if card.data_nasterii >= data_inceput:
                if card.data_nasterii <= data_final:
                    lst_undo.append(card)
                    lst_redo.append(Cardclient(card.id_entity,
                                               card.nume,
                                               card.prenume,
                                               card.cnp,
                                               card.data_nasterii,
                                               card.data_inregistrarii,
                                               card.puncte_acumulate + puncte))
                    self.update_card(card.id_entity,
                                     card.nume,
                                     card.prenume,
                                     card.cnp,
                                     card.data_nasterii,
                                     card.data_inregistrarii,
                                     card.puncte_acumulate + puncte)
        self.undoredo_service.clear_redo()
        multiupdateop = OperationMultiUpdate(self.card_repository,
                                             lst_undo, lst_redo)
        self.undoredo_service.add_to_undo(multiupdateop)

    def delete_cascada_card(self, id_card: str,
                            rezervare_repository: Repository) -> None:
        if self.card_repository.read(id_card) is None:
            raise KeyError("cardul nu exista")
        else:
            lst_undo = []
            for rezervare in rezervare_repository.read():
                if rezervare.id_card_client == id_card:
                    lst_undo.append(rezervare)
                    rezervare_repository.delete(rezervare.id_entity)
            self.undoredo_service.clear_redo()
            deletecascadaop = OperationDeleteCascada(self.card_repository,
                                                     rezervare_repository,
                                                     lst_undo,
                                                     self.card_repository.read(
                                                         id_card))
            self.delete_card(id_card)
            self.undoredo_service.add_to_undo(deletecascadaop)
