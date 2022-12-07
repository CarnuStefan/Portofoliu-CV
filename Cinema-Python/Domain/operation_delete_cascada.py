from Domain.entity import Entity
from Domain.operation_undoredo import OperationUndoRedo
from typing import List
from Domain.rezervare import Rezervare
from Repository.repository import Repository


class OperationDeleteCascada(OperationUndoRedo):
    def __init__(self, repository: Repository,
                 rezervare_repository: Repository, lista: List[Rezervare],
                 entity: Entity):
        self.repository = repository
        self.rezervare_repository = rezervare_repository
        self.lista = lista
        self.entity = entity

    def undo(self):
        for rezervare in self.lista:
            self.rezervare_repository.create(rezervare)
        self.repository.create(self.entity)

    def redo(self):
        for rezervare in self.lista:
            self.rezervare_repository.delete(rezervare.id_entity)
        self.repository.delete(self.entity.id_entity)
