from Domain.entity import Entity
from Domain.operation_undoredo import OperationUndoRedo

from Repository.repository import Repository


class OperationAdd(OperationUndoRedo):
    def __init__(self, repository: Repository, entity: Entity):
        self.repository = repository
        self.entity = entity

    def undo(self):
        self.repository.delete(self.entity.id_entity)

    def redo(self):
        self.repository.create(self.entity)
