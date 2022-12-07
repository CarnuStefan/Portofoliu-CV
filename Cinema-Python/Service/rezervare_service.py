from datetime import datetime, time
from typing import List

from Domain.operation_add import OperationAdd
from Domain.operation_delete import OperationDelete
from Domain.operation_multi_delete import OperationMultiDelete
from Domain.operation_update import OperationUpdate
from Domain.rezervare import Rezervare
from Domain.rezervare_validator import RezervareValidator
from Repository.repository import Repository
from Service.undoredo_service import UndoRedoService
from utils import check_time_str


class RezervareService:
    def __init__(self,
                 rezervare_repository: Repository,
                 card_repository: Repository,
                 film_repository: Repository,
                 rezervare_validator: RezervareValidator,
                 undoredo_service: UndoRedoService):
        self.card_repository = card_repository
        self.film_repository = film_repository
        self.rezervare_repository = rezervare_repository
        self.rezervare_validator = rezervare_validator
        self.undoredo_service = undoredo_service

    def add_rezervare(self,
                      id_rezervare: str,
                      id_film: str,
                      data_si_ora: datetime,
                      id_card_client: str = None):
        rezervare = Rezervare(id_rezervare,
                              id_film,
                              data_si_ora,
                              id_card_client)
        self.rezervare_validator.validare(rezervare)
        if rezervare.id_card_client:
            card = self.card_repository.read(rezervare.id_card_client)
            film = self.film_repository.read(rezervare.id_film)
            card.puncte_acumulate = \
                card.puncte_acumulate + int(10 / 100 * film.pret_bilet_film)
            self.card_repository.update(card)
            print(f"Totalul punctelor acumulate pe card: "
                  f"{card.puncte_acumulate}")
        self.rezervare_repository.create(rezervare)
        addop = OperationAdd(self.rezervare_repository, rezervare)
        self.undoredo_service.clear_redo()
        self.undoredo_service.add_to_undo(addop)

    def update_rezervare(self,
                         id_rezervare: str,
                         id_film: str,
                         data_si_ora: datetime,
                         id_card_client: str = None):
        old_rezervare = self.rezervare_repository.read(id_rezervare)
        rezervare = Rezervare(id_rezervare,
                              id_film,
                              data_si_ora,
                              id_card_client)
        self.rezervare_validator.validare(rezervare)
        self.rezervare_repository.update(rezervare)
        updateop = OperationUpdate(self.rezervare_repository,
                                   old_rezervare,
                                   rezervare)
        self.undoredo_service.clear_redo()
        self.undoredo_service.add_to_undo(updateop)

    def delete_rezervare(self, id_rezervare):
        deleteop = OperationDelete(self.rezervare_repository,
                                   self.rezervare_repository.read(
                                       id_rezervare))
        self.rezervare_repository.delete(id_rezervare)
        self.undoredo_service.clear_redo()
        self.undoredo_service.add_to_undo(deleteop)

    def get_all_between(self, ora_inceput: str, ora_final: str) \
            -> List[Rezervare]:
        check_time_str(ora_inceput)
        check_time_str(ora_final)

        def inner(rezervari: List[Rezervare], lst_rezervari_ok: list):
            if not rezervari:
                return []
            start = time(int(ora_inceput.split(":")[0]),
                         int(ora_inceput.split(":")[1]))
            end = time(int(ora_final.split(":")[0]),
                       int(ora_final.split(":")[1]))
            ora = time(int(rezervari[0].data_si_ora.time().hour),
                       int(rezervari[0].data_si_ora.time().minute))
            if ora >= start:
                if ora <= end:
                    return lst_rezervari_ok + [rezervari[0]] + \
                           inner(rezervari[1:], lst_rezervari_ok)
            return lst_rezervari_ok + inner(rezervari[1:], lst_rezervari_ok)

        return inner(self.get_all(), [])

    def delete_all_between(self,
                           data_inceput: datetime,
                           data_final: datetime) -> None:
        lst_undo = []
        for rezervare in self.get_all():
            if (rezervare.data_si_ora.date() >= data_inceput.date()) & \
                    (rezervare.data_si_ora.date() <= data_final.date()):
                lst_undo.append(rezervare)
                self.delete_rezervare(rezervare.id_entity)

        self.undoredo_service.clear_redo()
        multideleteop = OperationMultiDelete(self.rezervare_repository,
                                             lst_undo)
        self.undoredo_service.add_to_undo(multideleteop)

    def get_all(self):
        return self.rezervare_repository.read()
