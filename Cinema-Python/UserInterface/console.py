from datetime import date, datetime

from Service.card_service import CardService
from Service.film_service import FilmService
from Service.rezervare_service import RezervareService
from Service.undoredo_service import UndoRedoService
from ViewModels.cardclient_str import CardClientString
from ViewModels.film_str import FilmString
from utils import check_date_str, check_time_str


def handle_showall(entities):
    for entitiy in entities:
        print(entitiy)


def show_menu():
    print('1.Submeniu filme')
    print('2.Submeniu carduri')
    print('3.Submeniu rezervari')
    print('u.Undo')
    print('r.Redo')
    print('a.Afisare filme,carduri si rezervari')
    print('x.Exit')


class Console:
    def __init__(self,
                 card_service: CardService,
                 film_service: FilmService,
                 rezervare_service: RezervareService,
                 undoredo_service: UndoRedoService):
        self.undoredo_service = undoredo_service
        self.card_service = card_service
        self.film_service = film_service
        self.rezervare_service = rezervare_service

    def run_console(self):
        while True:
            show_menu()
            op = input("Alegeti optiunea: ")

            if op == '1':
                self.film_submenu()
            elif op == '2':
                self.card_submenu()
            elif op == '3':
                self.rezervari_submenu()
            elif op == 'u':
                self.undoredo_service.do_undo()
            elif op == 'r':
                self.undoredo_service.do_redo()
            elif op == 'a':
                handle_showall(self.film_service.get_all())
                handle_showall(self.card_service.get_all())
                handle_showall(self.rezervare_service.get_all())
            elif op == 'x':
                break

    def film_submenu(self):
        while True:
            print("1.Adaugare film")
            print("2.Modificare film")
            print("3.Stergere film")
            print("4.Afișarea filmelor ordonate descrescător"
                  " după numărul de rezervări.")
            print("5.Delete cascada")
            print('u.Undo')
            print('r.Redo')
            print("a.Afisare filme")
            print("s.Search")

            print("x.Exit")
            opf = input("Alegeti optiunea: ")
            if opf == '1':
                self.handle_add_film()
            elif opf == '2':
                self.handle_update_film()
            elif opf == '3':
                self.handle_delete_film()
            elif opf == '4':
                handle_showall(
                    self.film_service.descending_by_rezervation(
                        self.rezervare_service.rezervare_repository))
            elif opf == '5':
                self.handle_delete_cascada_film()
            elif opf == 'u':
                self.undoredo_service.do_undo()
            elif opf == 'r':
                self.undoredo_service.do_redo()
            elif opf == 'a':
                handle_showall(self.film_service.get_all())
            elif opf == 's':
                self.handle_search_film()
            elif opf == 'x':
                break

    def card_submenu(self):
        while True:
            print("1.Adaugare card")
            print("2.Modificare card")
            print("3.Stergere card")
            print("4.Generare n carduri random")
            print("5.Afișarea cardurilor client ordonate descrescător după "
                  "numărul de puncte de pe card. ")
            print("6.Incrementarea cu o valoare dată "
                  "a punctelor de pe toate cardurile "
                  "a căror zi de naștere se află într-un interval dat.")
            print("7.Delete cascada")
            print('u.Undo')
            print('r.Redo')
            print("a.Afisare carduri")
            print("s.Search")

            print("x.Exit")
            opc = input("Alegeti optiunea: ")
            if opc == '1':
                self.handle_add_card()
            elif opc == '2':
                self.handle_update_card()
            elif opc == '3':
                self.handle_delete_card()
            elif opc == '4':
                self.handle_random_cards()
            elif opc == '5':
                self.handle_descending_by_points()
            elif opc == '6':
                self.handle_increment_between()
            elif opc == '7':
                self.handle_delete_cascada_card()
            elif opc == 'u':
                self.undoredo_service.do_undo()
            elif opc == 'r':
                self.undoredo_service.do_redo()
            elif opc == 'a':
                handle_showall(self.card_service.get_all())
            elif opc == 's':
                self.handle_search_carduri()
            elif opc == 'x':
                break

    def rezervari_submenu(self):
        while True:
            print("1.Adaugare rezervare")
            print("2.Modificare rezervare")
            print("3.Stergere rezervare")
            print("4.Afișarea tuturor rezervărilor"
                  " dintr-un interval de ore dat,"
                  " indiferent de zi.")
            print("5.Ștergerea tuturor rezervărilor"
                  " dintr-un anumit interval de zile.")
            print('u.Undo')
            print('r.Redo')
            print("a.Afisare rezervare")

            print("x.Exit")
            opr = input("Alegeti optiunea: ")
            if opr == '1':
                self.handle_add_rezervare()
            elif opr == '2':
                self.handle_update_rezervare()
            elif opr == '3':
                self.handle_delete_rezervare()
            elif opr == '4':
                self.handle_showall_between()
            elif opr == '5':
                self.handle_delete_all_between()
            elif opr == 'u':
                self.undoredo_service.do_undo()
            elif opr == 'r':
                self.undoredo_service.do_redo()
            elif opr == 'a':
                handle_showall(self.rezervare_service.get_all())
            elif opr == 'x':
                break

    def handle_add_film(self):
        try:
            id_film = input('Introduceti id-ul filmului: ')
            titlu_film = input('Introduceti tilul filmului: ')
            an_aparitie = input('Introduceti anul de aparitie al filmului: ')
            pret_bilet_film = input('Introduceti pretul unui bilet:')
            film_in_program = input(
                'introduceti "da" daca filmul este in program: ')
            while True:
                if an_aparitie.isdecimal():
                    an_aparitie = int(an_aparitie)
                    if (an_aparitie > 1) and (an_aparitie < 9999):
                        break
                    else:
                        print('anul de aparitie trebuie '
                              'sa fie cuprins intre 1 si 9999')
                        an_aparitie = input(
                            'Introduceti anul de aparitie al filmului:')
                else:
                    print('Anul trebuie sa contina doar cifre')
                    an_aparitie = input(
                        'Introduceti anul de aparitie al filmului:')

            while True:
                try:
                    pret_bilet_film = float(pret_bilet_film)
                except ValueError:
                    print("Pretul trebuie sa fie numar real")
                    pret_bilet_film = None
                if pret_bilet_film:
                    if pret_bilet_film > 0:
                        break
                    else:
                        print('Pretul trebuie sa fie pozitiv')
                pret_bilet_film = input('Introduceti pretul unui bilet:')
            self.film_service.add_film(id_film, titlu_film, an_aparitie,
                                       pret_bilet_film, film_in_program)
        except KeyError as ke:
            print('Eroare ID: ', ke)
        except ValueError as ve:
            print('Eroare Validare: ', ve)
        except Exception as ee:
            print('Eroare:', ee)

    def handle_update_film(self):
        try:
            id_film = input('Introduceti id-ul filmului ce trebuie updatat: ')
            titlu_film = input('Introduceti noul tilul filmului: ')
            an_aparitie = input(
                'introduceti noul anul de aparitie al filmului: ')
            pret_bilet_film = input('Introduceti noul pret pentru un bilet: ')
            film_in_program = input(
                'introduceti "da" daca filmul este in program: ')
            while True:
                if an_aparitie.isdecimal():
                    an_aparitie = int(an_aparitie)
                    if (an_aparitie > 1) and (an_aparitie < 9999):
                        break
                    else:
                        print('anul de aparitie trebuie'
                              ' sa fie cuprins intre 1 si 9999')
                        an_aparitie = input('Introduceti '
                                            'anul de aparitie al filmului:')
                else:
                    print('Anul trebuie sa contina doar cifre')
                    an_aparitie = input(
                        'Introduceti anul de aparitie al filmului:')

            while True:
                try:
                    pret_bilet_film = float(pret_bilet_film)
                except ValueError:
                    print("Pretul trebuie sa fie numar real")
                    pret_bilet_film = None
                if pret_bilet_film:
                    if pret_bilet_film > 0:
                        break
                    else:
                        print('Pretul trebuie sa fie pozitiv')
                pret_bilet_film = input('Introduceti pretul unui bilet:')
            self.film_service.update_film(id_film, titlu_film, an_aparitie,
                                          pret_bilet_film, film_in_program)
        except KeyError as ke:
            print('Eroare ID: ', ke)
        except ValueError as ve:
            print('Eroare Validare', ve)
        except Exception as ee:
            print('Eroare:', ee)

    def handle_delete_film(self):
        try:
            id_delete = input('Introduceti '
                              'id-ul filmului care trebuie sters: ')
            self.film_service.delete_film(id_delete)
        except KeyError as ke:
            print('Eroare ID: ', ke)
        except ValueError as ve:
            print('Eroare Validare:', ve)
        except Exception as ee:
            print('Eroare:', ee)

    def handle_add_card(self):
        try:
            id_card = input('Introduceti id-ul cardului:')
            nume = input('Introduceti numele: ')
            prenume = input('Introduceti prenumele: ')
            cnp = input('Introduceti cnp-ul: ')
            data_nasterii_str = input('Introduceti data nasterii'
                                      ' in format "dd.mm.yyyy": ')
            check_date_str(data_nasterii_str)
            data_nasterii_str_split = data_nasterii_str.split('.')
            data_nasterii = date(int(data_nasterii_str_split[2]),
                                 int(data_nasterii_str_split[1]),
                                 int(data_nasterii_str_split[0]))
            data_inregistrarii_str = input('Introduceti data inregistrarii'
                                           ' in format "dd.mm.yyyy": ')
            check_date_str(data_inregistrarii_str)
            data_inregistrarii_str_split = data_inregistrarii_str.split('.')
            data_inregistrarii = date(int(data_inregistrarii_str_split[2]),
                                      int(data_inregistrarii_str_split[1]),
                                      int(data_inregistrarii_str_split[0]))
            puncte = int(input('Introduceti punctele de pe card: '))
            self.card_service.add_card(id_card,
                                       nume,
                                       prenume,
                                       cnp,
                                       data_nasterii,
                                       data_inregistrarii,
                                       puncte)

        except KeyError as ke:
            print('Eroare ID: ', ke)
        except ValueError as ve:
            print('Eroare Validare: ', ve)
        except Exception as ee:
            print('Eroare: ', ee)

    def handle_update_card(self):
        try:
            id_card = input('Introduceti id-ul cardului care trebuie updatat:')
            nume = input('Introduceti noul nume: ')
            prenume = input('Introduceti noul prenume: ')
            cnp = input('Introduceti noul cnp: ')
            data_nasterii_str = input('Introduceti noua data a nasterii'
                                      ' in format "dd.mm.yyyy":')
            check_date_str(data_nasterii_str)
            data_nasterii_str_split = data_nasterii_str.split('.')
            data_nasterii = date(int(data_nasterii_str_split[2]),
                                 int(data_nasterii_str_split[1]),
                                 int(data_nasterii_str_split[0]))
            data_inregistrarii_str = input('Introduceti noua '
                                           'data a inregistrarii'
                                           ' in format "dd.mm.yyyy":')
            check_date_str(data_inregistrarii_str)
            data_inregistrarii_str_split = data_inregistrarii_str.split('.')
            data_inregistrarii = date(int(data_inregistrarii_str_split[2]),
                                      int(data_inregistrarii_str_split[1]),
                                      int(data_inregistrarii_str_split[0]))
            self.card_service.update_card(id_card,
                                          nume,
                                          prenume,
                                          cnp,
                                          data_nasterii,
                                          data_inregistrarii, )
        except KeyError as ke:
            print('Eroare ID: ', ke)
        except ValueError as ve:
            print('Eroare Validare:', ve)
        except Exception as ee:
            print('Eroare:', ee)

    def handle_delete_card(self):
        try:
            id_delete = input('Introduceti id-ul cardului '
                              'care trebuie sters: ')
            self.card_service.delete_card(id_delete)
        except KeyError as ke:
            print('Eroare ID: ', ke)
        except ValueError as ve:
            print('Eroare Validare:', ve)
        except Exception as ee:
            print('Eroare:', ee)

    def handle_add_rezervare(self):
        try:
            id_rezervare = input('Introduceti id-ul rezervarii: ')
            id_film = input('Introduceti id-ul filmului: ')
            id_card_client = input('Introduceti id-ul cardului de client: ')
            data_str = input(
                'Introduceti noua data rezervarii in format"dd.mm.yyy": ')
            check_date_str(data_str)
            ora_str = input(
                'Introduceti noua ora rezervarii in format "hh:mm": ')
            check_time_str(ora_str)
            data = data_str.split('.')
            ora = ora_str.split(':')
            data_si_ora = datetime(int(data[2]), int(data[1]), int(data[0]),
                                   int(ora[0]), int(ora[1]))

            self.rezervare_service.add_rezervare(id_rezervare,
                                                 id_film,
                                                 data_si_ora,
                                                 id_card_client, )

        except KeyError as ke:
            print('Eroare ID: ', ke)
        except ValueError as ve:
            print('Eroare Validare: ', ve)
        except Exception as ee:
            print('Eroare:', ee)

    def handle_update_rezervare(self):

        try:
            id_rezervare = input('Introduceti id-ul rezervarii '
                                 'care trebuie updatate: ')
            id_film = input('Introduceti noul id al filmului: ')
            id_card_client = input(
                'Introduceti noul id al cardului de client: ')
            data_str = input(
                'Introduceti data rezervarii in format"dd.mm.yyy": ')
            check_date_str(data_str)
            ora_str = input('Introduceti ora rezervarii in format "hh:mm": ')
            data = data_str.split('.')
            ora = ora_str.split(':')
            data_si_ora = datetime(int(data[2]), int(data[1]), int(data[0]),
                                   int(ora[0]), int(ora[1]))
            self.rezervare_service.add_rezervare(id_rezervare,
                                                 id_film,
                                                 data_si_ora,
                                                 id_card_client, )
        except KeyError as ke:
            print('Eroare ID: ', ke)
        except ValueError as ve:
            print('Eroare Validare: ', ve)
        except Exception as ee:
            print('Eroare:', ee)

    def handle_delete_rezervare(self):
        try:
            id_rezervare = input('Introduceti id-ul rezervarii '
                                 'care trebuie sterse:')
            self.rezervare_service.delete_rezervare(id_rezervare)
        except KeyError as ke:
            print('Eroare ID: ', ke)
        except ValueError as ve:
            print('Eroare Validare: ', ve)
        except Exception as ee:
            print('Eroare:', ee)

    def handle_search_carduri(self):
        carduri = self.card_service.get_all()
        search = input('Search: ')
        cardstr_list = map(lambda x: CardClientString(x), carduri)
        searchlist = [print(cardstr.get_values()) for cardstr in cardstr_list
                      if search in cardstr.get_string()]
        print('Numarul returnarilor: ', len(searchlist))

    def handle_search_film(self):
        filme = self.film_service.get_all()
        search = input('Search: ')
        filmstr_list = map(lambda x: FilmString(x), filme)
        searchlist = [print(filmstr.get_values()) for filmstr in filmstr_list
                      if search in filmstr.get_string()]
        print('Numarul returnarilor: ', len(searchlist))

    def handle_random_cards(self):
        try:
            n = int(input('Dati numarul de carduri ce trebuie generate: '))
            self.card_service.gen_rand_n_cards(n)
        except KeyError as ke:
            print('Eroare ID: ', ke)
        except ValueError as ve:
            print('Eroare Validare: ', ve)
        except Exception as ee:
            print('Eroare:', ee)

    def handle_showall_between(self):
        try:
            ora_inceput = input('Intoduceti '
                                'ora de inceput in format "hh:mm": ')
            ora_final = input('Introduceti '
                              'ora de final in format "hh:mm": ')
            handle_showall(self.rezervare_service.get_all_between(ora_inceput,
                                                                  ora_final))
        except KeyError as ke:
            print('Eroare ID: ', ke)
        except ValueError as ve:
            print('Eroare Validare: ', ve)
        except Exception as ee:
            print('Eroare:', ee)

    def handle_descending_by_points(self):
        try:
            handle_showall(self.card_service.get_card_descending())
        except KeyError as ke:
            print('Eroare ID: ', ke)
        except ValueError as ve:
            print('Eroare Validare: ', ve)
        except Exception as ee:
            print('Eroare:', ee)

    def handle_delete_all_between(self):
        try:
            date_inceput_str = input('Introduceti data inceperii'
                                     ' in format "dd.mm.yyyy": ')
            check_date_str(date_inceput_str)
            data_inceput_str_split = date_inceput_str.split('.')
            data_inceput = datetime(int(data_inceput_str_split[2]),
                                    int(data_inceput_str_split[1]),
                                    int(data_inceput_str_split[0]))
            data_final_str = input('Introduceti data finalului'
                                   ' in format "dd.mm.yyyy": ')
            check_date_str(date_inceput_str)
            data_final_str_split = data_final_str.split('.')
            data_final = datetime(int(data_final_str_split[2]),
                                  int(data_final_str_split[1]),
                                  int(data_final_str_split[0]))
            self.rezervare_service.delete_all_between(data_inceput, data_final)
        except KeyError as ke:
            print('Eroare ID: ', ke)
        except ValueError as ve:
            print('Eroare Validare: ', ve)
        except Exception as ee:
            print('Eroare:', ee)

    def handle_increment_between(self):
        try:
            date_inceput_str = input('Introduceti data inceperii'
                                     ' in format "dd.mm.yyyy": ')
            check_date_str(date_inceput_str)
            data_inceput_str_split = date_inceput_str.split('.')
            data_inceput = date(int(data_inceput_str_split[2]),
                                int(data_inceput_str_split[1]),
                                int(data_inceput_str_split[0]))
            data_final_str = input('Introduceti data finalului'
                                   ' in format "dd.mm.yyyy": ')
            check_date_str(date_inceput_str)
            data_final_str_split = data_final_str.split('.')
            data_final = date(int(data_final_str_split[2]),
                              int(data_final_str_split[1]),
                              int(data_final_str_split[0]))
            puncte = input('Introduceti increment: ')
            if not puncte.isdigit():
                raise ValueError('Punctele trebuie sa fie numar intreg')

            self.card_service.increment_between(data_inceput,
                                                data_final,
                                                int(puncte))
        except KeyError as ke:
            print('Eroare ID: ', ke)
        except ValueError as ve:
            print('Eroare Validare: ', ve)
        except Exception as ee:
            print('Eroare:', ee)

    def handle_delete_cascada_film(self):
        try:
            id_film = input('Introduceti id-ul filmului care trebuie sters: ')
            repository = self.rezervare_service.rezervare_repository
            self.film_service.delete_cascada_film(id_film, repository)
        except KeyError as ke:
            print('Eroare ID: ', ke)
        except ValueError as ve:
            print('Eroare Validare: ', ve)
        except Exception as ee:
            print('Eroare:', ee)

    def handle_delete_cascada_card(self):
        try:
            id_card = input(
                'Introduceti id-ul cardului care trebuie sters: ')
            repository = self.rezervare_service.rezervare_repository
            self.card_service.delete_cascada_card(id_card, repository)
        except KeyError as ke:
            print('Eroare ID: ', ke)
        except ValueError as ve:
            print('Eroare Validare: ', ve)
        except Exception as ee:
            print('Eroare:', ee)
