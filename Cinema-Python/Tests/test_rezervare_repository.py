from datetime import datetime
from Domain.rezervare import Rezervare
from Repository.jsonrepository import JsonRepository
from utils import clearfile


def testrezervarerepository():
    filename = 'test_rezervare_repository.json'
    clearfile(filename)
    added = Rezervare('12', '1', datetime(1234, 12, 12, 14, 23))
    rezervare_repository = JsonRepository(filename)
    rezervare_repository.create(added)
    assert rezervare_repository.read(added.id_entity) == added
    rezervare_repository.delete(added.id_entity)
    assert rezervare_repository.read(added.id_entity) != added
    assert not rezervare_repository.read()
    rezervare_repository.create(added)
    updated = Rezervare('12', '1', datetime(1245, 1, 19, 16, 47), '1')
    rezervare_repository.update(updated)
    assert rezervare_repository.read(added.id_entity) == updated
    assert rezervare_repository.read(added.id_entity) != added
