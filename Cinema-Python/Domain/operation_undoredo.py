from abc import ABC, abstractmethod


class OperationUndoRedo(ABC):
    @abstractmethod
    def undo(self):
        ...

    @abstractmethod
    def redo(self):
        ...
