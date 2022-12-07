from Domain.entity import Entity
from Domain.operation_undoredo import OperationUndoRedo
from Repository.repository import Repository


class OperationUpdate(OperationUndoRedo):
    def __init__(self, repository: Repository, entity: Entity,
                 updated_entity: Entity):
        self.repository = repository
        self.entity = entity
        self.updated_entity = updated_entity

    def undo(self):
        self.repository.update(self.entity)

    def redo(self):
        self.repository.update(self.updated_entity)
