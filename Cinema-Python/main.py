from Domain.card_validator import CardValidator
from Domain.film_validator import FilmValidator
from Domain.rezervare_validator import RezervareValidator
from Repository.jsonrepository import JsonRepository
from Service.card_service import CardService
from Service.film_service import FilmService
from Service.rezervare_service import RezervareService
from Service.undoredo_service import UndoRedoService
from Tests.test_card_repository import testcardrepository
from Tests.test_film_repository import testfilmrepository
from Tests.test_rezervare_repository import testrezervarerepository
from Tests.test_services import testservices

from UserInterface.console import Console
from utils import clearfile


def main():
    file_filme = 'filme.json'
    file_carduri = 'carduri.json'
    file_rezervari = 'rezervari.json'

    filme_repository = JsonRepository(file_filme)
    carduri_repository = JsonRepository(file_carduri)
    rezervari_repository = JsonRepository(file_rezervari)

    film_validator = FilmValidator(filme_repository)
    card_validator = CardValidator(carduri_repository)
    rezervare_validator = RezervareValidator(filme_repository,
                                             carduri_repository,
                                             rezervari_repository)

    undoredo_service = UndoRedoService()
    film_service = FilmService(filme_repository, film_validator,
                               undoredo_service)
    card_service = CardService(carduri_repository, card_validator,
                               undoredo_service)
    rezervare_service = RezervareService(rezervari_repository,
                                         carduri_repository, filme_repository,
                                         rezervare_validator, undoredo_service)
    console = Console(card_service, film_service, rezervare_service,
                      undoredo_service)

    while True:
        print('1.Start')
        print('2.Empty files')
        print('x.Exit')
        op = input('Alegeti optiunea: ')
        if op == '1':
            console.run_console()
        elif op == '2':
            print('Sigur vreti sa stergeti toate datele din fisiere?')
            sure = input('Alegeti "da" sau "nu": ')
            if sure == "da":
                clearfile(file_carduri)
                clearfile(file_filme)
                clearfile(file_rezervari)
        elif op == 'x':
            break


if __name__ == '__main__':
    testfilmrepository()
    testcardrepository()
    testrezervarerepository()
    testservices()
    main()
