from typing import List

from Domain.card_client import Cardclient
from Domain.operation_undoredo import OperationUndoRedo
from Repository.repository import Repository


class OperationMultiUpdate(OperationUndoRedo):
    def __init__(self, repository: Repository, listaundo: List[Cardclient],
                 listaredo: List[Cardclient]):
        self.repository = repository
        self.listaundo = listaundo
        self.listaredo = listaredo

    def undo(self):
        for card in self.listaundo:
            self.repository.update(card)

    def redo(self):
        for card in self.listaredo:
            self.repository.update(card)
