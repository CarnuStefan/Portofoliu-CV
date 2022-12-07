from datetime import date

from Domain.card_client import Cardclient
from Repository.jsonrepository import JsonRepository
from utils import clearfile


def testcardrepository():
    filename = 'test_card_repository.json'
    clearfile(filename)
    an = 1234
    luna = 1
    zi = 12
    data_nasterii = date(an, luna, zi)
    data_inregistrarii = date(4321, 1, 21)
    added = Cardclient('1', 'Test', 'testat', '012345678912345',
                       data_nasterii, data_inregistrarii, 0)
    card_repository = JsonRepository(filename)
    card_repository.create(added)
    assert card_repository.read(added.id_entity) == added
    card_repository.delete(added.id_entity)
    assert card_repository.read(added.id_entity) != added
    assert not card_repository.read()
    card_repository.create(added)
    data_nasterii_nou = date(2000, 2, 29)
    data_inregistrarii_nou = date(2020, 1, 21)
    updated = Cardclient('1', 'Test', 'Updatat', '012345678912345',
                         data_nasterii_nou, data_inregistrarii_nou, 0)
    card_repository.update(updated)
    assert card_repository.read(added.id_entity) == updated
    assert card_repository.read(added.id_entity) != added
    try:
        same_cnp = Cardclient('2', 'Test', 'testat', '012345678912345',
                              data_nasterii, data_inregistrarii, 0)
        card_repository.create(same_cnp)
    except KeyError:
        assert True
