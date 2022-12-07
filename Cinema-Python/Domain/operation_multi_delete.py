from typing import List

from Domain.entity import Entity
from Domain.operation_undoredo import OperationUndoRedo
from Repository.repository import Repository


class OperationMultiDelete(OperationUndoRedo):
    def __init__(self, repository: Repository, lista: List[Entity]):
        self.repository = repository
        self.lista = lista

    def undo(self):
        for entity in self.lista:
            self.repository.create(entity)

    def redo(self):
        for entity in self.lista:
            self.repository.delete(entity.id_entity)
