from Domain.film import Film
from Repository.jsonrepository import JsonRepository
from utils import clearfile


def testfilmrepository():
    filename = 'test_film_repository.json'
    clearfile(filename)
    added = Film('1', 'Filmul test', 2021, 123, True)
    film_repository = JsonRepository(filename)
    film_repository.create(added)
    assert film_repository.read(added.id_entity) == added
    film_repository.delete(added.id_entity)
    assert film_repository.read(added.id_entity) != added
    assert not film_repository.read()
    film_repository.create(added)
    updated = Film('1', 'Filmul test updated', 1, 123.123, False)
    film_repository.update(updated)
    assert film_repository.read(added.id_entity) == updated
    assert film_repository.read(added.id_entity) != added
