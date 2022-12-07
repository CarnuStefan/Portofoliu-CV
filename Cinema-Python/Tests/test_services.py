import os
import random
import string
import sys
from datetime import date, datetime

from Domain.card_client import Cardclient
from Domain.card_validator import CardValidator
from Domain.film import Film
from Domain.film_validator import FilmValidator
from Domain.rezervare import Rezervare
from Domain.rezervare_validator import RezervareValidator
from Repository.jsonrepository import JsonRepository
from Service.card_service import CardService
from Service.film_service import FilmService
from Service.rezervare_service import RezervareService
from Service.undoredo_service import UndoRedoService
from utils import clearfile


def stop_print():
    sys.stdout = open(os.devnull, 'w')


def start_print():
    sys.stdout = sys.__stdout__


def testservices():
    films_file = 'test_service_film.json'
    cards_file = 'test_service_card.json'
    rezervari_file = 'test_service_rezervare.json'
    clearfile(films_file)
    clearfile(cards_file)
    clearfile(rezervari_file)
    film_repository = JsonRepository(films_file)
    card_repository = JsonRepository(cards_file)
    rezervare_repository = JsonRepository(rezervari_file)
    film_validator = FilmValidator(film_repository)
    card_validator = CardValidator(card_repository)
    rezervare_validator = RezervareValidator(film_repository,
                                             card_repository,
                                             rezervare_repository)
    undoredo_service = UndoRedoService()
    card_service = CardService(card_repository,
                               card_validator, undoredo_service)
    rezervare_service = RezervareService(rezervare_repository,
                                         card_repository,
                                         film_repository,
                                         rezervare_validator,
                                         undoredo_service)
    film_service = FilmService(film_repository,
                               film_validator,
                               undoredo_service)
    film_test = Film('1', 'test', 1234, 12.34, True)
    card_test = Cardclient('1', 'Test', 'Test', '1385931345634',
                           date(1234, 12, 3), date(1234, 11, 22), 0)
    rezervare_test = Rezervare('1', '1', datetime(1234, 12, 23, 12, 34, ), '1')
    film_service.add_film('1', 'test', 1234, 12.34, 'da')
    card_service.add_card('1', 'Test', 'Test', '1385931345634',
                          date(1234, 12, 3), date(1234, 11, 22), 0)
    stop_print()
    rezervare_service.add_rezervare('1', '1', datetime(1234, 12, 23, 12, 34),
                                    '1')
    start_print()
    assert film_test in film_service.get_all()
    for card in card_service.get_all():
        assert card_test.id_entity == card.id_entity
    assert rezervare_test in rezervare_service.get_all()
    film_test_modificat = Film('1', 'modificat', 1256, 43.23, True)
    card_test_modificat = Cardclient('1',
                                     'modificat',
                                     'modificat',
                                     '1385931345634',
                                     date(4353, 10, 25),
                                     date(4561, 8, 22),
                                     25)
    stop_print()
    rezervare_test_modificata = Rezervare('1',
                                          '1245',
                                          datetime(3274, 7, 22, 13, 48),
                                          '56578')
    start_print()
    film_service.update_film('1', 'modificat', 1256, 43.23, 'da')
    card_service.update_card('1',
                             'modificat',
                             'modificat',
                             '1385931345634',
                             date(4353, 10, 25),
                             date(4561, 8, 22),
                             25)
    film_service.add_film('1245', 'modificare ', 1970, 18.40, 'da')
    card_service.add_card('56578', 'Test', 'Test', '0123456789123',
                          date(3456, 12, 3), date(2134, 2, 12), )
    stop_print()
    rezervare_service.update_rezervare('1',
                                       '1245',
                                       datetime(3274, 7, 22, 13, 48),
                                       '56578')
    start_print()
    assert film_test not in film_service.get_all()
    assert card_test not in card_service.get_all()
    assert rezervare_test not in rezervare_service.get_all()
    assert film_test_modificat in film_service.get_all()
    assert card_test_modificat in card_service.get_all()
    assert rezervare_test_modificata in rezervare_service.get_all()
    film_service.delete_film('1')
    card_service.delete_card('1')
    rezervare_service.delete_rezervare('1')
    assert film_test not in film_service.get_all()
    assert card_test not in card_service.get_all()
    assert rezervare_test not in rezervare_service.get_all()
    assert film_test_modificat not in film_service.get_all()
    assert card_test_modificat not in card_service.get_all()
    assert rezervare_test_modificata not in rezervare_service.get_all()
    # Afișarea tuturor rezervărilor dintr-un interval de ore dat,
    # indiferent de zi.
    film_service.add_film('1', 'titlu', 1234, 12.50, 'da')
    film_service.add_film('2', 'titlu', 1234, 12.50, 'da')
    film_service.add_film('3', 'titlu', 1234, 12.50, 'da')
    film_service.add_film('4', 'titlu', 1234, 12.50, 'da')
    rezervare_service.add_rezervare('1', '1', datetime(1234, 6, 26, 8, 0), )
    rezervare_service.add_rezervare('2', '2', datetime(2345, 3, 2, 9, 0), )
    rezervare_service.add_rezervare('3', '2', datetime(1123, 12, 3, 10, 0), )
    rezervare_service.add_rezervare('4', '2', datetime(1532, 10, 28, 11, 0), )
    rezervare_service.add_rezervare('5', '2', datetime(2344, 9, 30, 12, 0), )
    rezervare_service.add_rezervare('6', '3', datetime(1112, 7, 21, 13, 0), )
    rezervare_service.add_rezervare('7', '3', datetime(1134, 2, 20, 14, 10), )
    rezervare_service.add_rezervare('8', '4', datetime(5321, 1, 23, 14, 20), )
    rezervare_service.add_rezervare('9', '3', datetime(3141, 11, 7, 14, 30), )
    rezervare_service.add_rezervare('10', '2',
                                    datetime(1234, 12, 23, 14, 35), )
    rezervare_service.add_rezervare('11', '1',
                                    datetime(1234, 12, 23, 14, 39), )
    lst_rezervari_between = rezervare_service.get_all_between('11:22', '14:34')
    assert rezervare_repository.read('1') not in lst_rezervari_between
    assert rezervare_repository.read('2') not in lst_rezervari_between
    assert rezervare_repository.read('3') not in lst_rezervari_between
    assert rezervare_repository.read('4') not in lst_rezervari_between
    assert rezervare_repository.read('5') in lst_rezervari_between
    assert rezervare_repository.read('6') in lst_rezervari_between
    assert rezervare_repository.read('7') in lst_rezervari_between
    assert rezervare_repository.read('8') in lst_rezervari_between
    assert rezervare_repository.read('9') in lst_rezervari_between
    assert rezervare_repository.read('10') not in lst_rezervari_between
    assert rezervare_repository.read('11') not in lst_rezervari_between
    # Afișarea filmelor ordonate descrescător după numărul de rezervări.
    lst_descending_film = film_service.descending_by_rezervation(
        rezervare_repository)
    assert film_repository.read('1') == lst_descending_film[2][0]
    assert film_repository.read('2') == lst_descending_film[0][0]
    assert film_repository.read('3') == lst_descending_film[1][0]
    assert film_repository.read('4') == lst_descending_film[3][0]
    # Afișarea cardurilor client ordonate descrescător
    # după numărul de puncte de pe card.
    card_service.add_card('1', 'Test', 'Test',
                          ''.join((random.choice(string.digits)
                                   for _ in range(13))),
                          date(3456, 12, 3),
                          date(2134, 2, 12),
                          24)
    card_service.add_card('2', 'Test', 'Test',
                          ''.join((random.choice(string.digits)
                                   for _ in range(13))),
                          date(3456, 12, 3),
                          date(2134, 2, 12), 1)
    card_service.add_card('3', 'Test', 'Test',
                          ''.join((random.choice(string.digits)
                                   for _ in range(13))),
                          date(3456, 12, 3),
                          date(2134, 2, 12), 22)
    lst_descending_card = card_service.get_card_descending()
    assert card_repository.read('1') == lst_descending_card[0]
    assert card_repository.read('2') == lst_descending_card[2]
    assert card_repository.read('3') == lst_descending_card[1]
    # Ștergerea tuturor rezervărilor dintr-un anumit interval de zile.
    rezervare_service.delete_all_between(datetime(1000, 1, 1),
                                         datetime(2000, 1, 1))
    assert rezervare_repository.read('1') not in rezervare_service.get_all()
    assert rezervare_repository.read('3') not in rezervare_service.get_all()
    assert rezervare_repository.read('4') not in rezervare_service.get_all()
    assert rezervare_repository.read('6') not in rezervare_service.get_all()
    assert rezervare_repository.read('7') not in rezervare_service.get_all()
    assert rezervare_repository.read('10') not in rezervare_service.get_all()
    assert rezervare_repository.read('11') not in rezervare_service.get_all()
    assert rezervare_repository.read('2') in rezervare_service.get_all()
    assert rezervare_repository.read('5') in rezervare_service.get_all()
    assert rezervare_repository.read('8') in rezervare_service.get_all()
    assert rezervare_repository.read('9') in rezervare_service.get_all()
    # Incrementarea cu o valoare dată a punctelor de pe toate cardurile
    # a căror zi de naștere se află într-un interval dat.
    card_service.increment_between(date(1000, 1, 1), date(4000, 1, 1), 20)
    assert card_repository.read('1').puncte_acumulate == 44
    assert card_repository.read('2').puncte_acumulate == 21
    assert card_repository.read('3').puncte_acumulate == 42
    assert card_repository.read('56578').puncte_acumulate == 20
