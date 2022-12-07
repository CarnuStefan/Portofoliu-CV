from typing import List, Tuple

from Domain.film import Film
from Domain.film_validator import FilmValidator
from Domain.operation_add import OperationAdd
from Domain.operation_delete import OperationDelete
from Domain.operation_delete_cascada import OperationDeleteCascada
from Domain.operation_update import OperationUpdate
from Repository.repository import Repository
from Service.undoredo_service import UndoRedoService
from utils import my_sort


class FilmService:
    def __init__(self,
                 film_repository: Repository,
                 film_validator: FilmValidator,
                 undoredo_service: UndoRedoService):
        self.film_repository = film_repository
        self.film_validator = film_validator
        self.undoredo_service = undoredo_service

    def add_film(self, id_film: str, titlu_film: str, an_aparitie: int,
                 pret_bilet_film: float, film_in_program: str):
        """
        Adauga un film in repository
        :param id_film: id-ul filmului
        :param titlu_film: titlul filmului
        :param an_aparitie: anul de aparitie al filmului
        :param pret_bilet_film: pretul unui bilet la film
        :param film_in_program: daca filmul este sau nu in program (status)
        :return:
        """
        if film_in_program == 'da':
            film_in_program = True
        else:
            film_in_program = False

        film = Film(id_film, titlu_film, an_aparitie, pret_bilet_film,
                    film_in_program)
        self.film_validator.validate(film)
        self.film_repository.create(film)
        addop = OperationAdd(self.film_repository, film)
        self.undoredo_service.clear_redo()
        self.undoredo_service.add_to_undo(addop)

    def update_film(self, id_film: str, titlu_film: str, an_aparitie: int,
                    pret_bilet_film: float,
                    film_in_program: str):
        """
        Modifica un film din repository
       :param id_film: id-ul filmului ce trebuie modificat
       :param titlu_film: un nou titlu
       :param an_aparitie: un nou an de aparitie
       :param pret_bilet_film: un nou pret
       :param film_in_program: un nou status de program
       :return:
       """

        if film_in_program == 'da':
            film_in_program = True
        else:
            film_in_program = False
        old_film = self.film_repository.read(id_film)
        film = Film(id_film, titlu_film, an_aparitie, pret_bilet_film,
                    film_in_program)
        self.film_validator.validate(film)
        self.film_repository.update(film)
        updateop = OperationUpdate(self.film_repository, old_film, film)
        self.undoredo_service.clear_redo()
        self.undoredo_service.add_to_undo(updateop)

    def delete_film(self, id_film: str):
        """
        Sterge un film din repository
        :param self:
        :param id_film: id-ul filmului care trebuie sters
        :return:
        """
        deleteop = OperationDelete(self.film_repository,
                                   self.film_repository.read(id_film))
        self.film_repository.delete(id_film)
        self.undoredo_service.clear_redo()
        self.undoredo_service.add_to_undo(deleteop)

    def get_all(self) -> List[Film]:
        """
        :param self:
        :return: Lista cu toate filmele din repository
        """
        return self.film_repository.read()

    def descending_by_rezervation(self, rezervari_repository: Repository) \
            -> List[Tuple[Film, int]]:
        def inner(filme):
            if not filme:
                return []
            nr_rezervari = 0
            for rezervare in rezervari_repository.read():
                if filme[0].id_entity == rezervare.id_film:
                    nr_rezervari = nr_rezervari + 1
            return [(filme[0], nr_rezervari)] + inner(filme[1:])

        lst_filme_nr_rezervari = inner(self.get_all())
        return my_sort(lst_filme_nr_rezervari, key=lambda x: x[1],
                       reverse=True)

    def delete_cascada_film(self, id_film: str,
                            rezervare_repository: Repository) -> None:
        if self.film_repository.read(id_film) is None:
            raise KeyError("filmul nu exista")
        else:
            lst_undo = []
            for rezervare in rezervare_repository.read():
                if rezervare.id_film == id_film:
                    lst_undo.append(rezervare)
                    rezervare_repository.delete(rezervare.id_entity)
            self.undoredo_service.clear_redo()
            deletecascadaop = OperationDeleteCascada(self.film_repository,
                                                     rezervare_repository,
                                                     lst_undo,
                                                     self.film_repository.read(
                                                         id_film))
            self.delete_film(id_film)
            self.undoredo_service.add_to_undo(deletecascadaop)
