def clearfile(filename):
    with open(filename, 'w'):
        pass


def check_date_str(data: str):
    erori = []
    if len(data.split('.')) != 3:
        erori.append('Format invalid:'
                     'data trebuie sa fie in format "dd.mm.yyyy"')
    else:
        if not data.split('.')[0].isdigit():
            erori.append('Format invalid:'
                         'ziua trebuie sa contina doar cifre')
        if not data.split('.')[1].isdigit():
            erori.append('Format invalid:'
                         'luna trebuie sa contina doar cifre')
        if not data.split('.')[2].isdigit():
            erori.append('Format invalid:'
                         'anul trebuie sa contina doar cifre')
        if len(data.split('.')[0]) > 2:
            erori.append('Format invalid:'
                         'ziua nu trebuie sa contina mai mult de 2 cifre')
        if len(data.split('.')[1]) > 2:
            erori.append('Format invalid:'
                         'luna nu trebuie sa contina mai mult de 2 cifre')
        if len(data.split('.')[2]) > 4:
            erori.append('Format invalid:'
                         'anul nu trebuie sa contina mai mult de 4 cifre')
    if erori:
        raise ValueError(erori)


def check_time_str(time: str):
    erori = []
    if len(time.split(':')) != 2:
        erori.append('Format invalid:'
                     'formatul orei de inceput trebuie sa fie "ora:minut"')
    else:
        if not time.split(':')[0].isdigit():
            erori.append('Format invalid:'
                         'ora trebuie sa contina doar cifre')
        if not time.split(':')[1].isdigit():
            erori.append('Format invalid:'
                         'minutul trebuie sa contina doar cifre')
    if erori:
        raise ValueError(erori)


def my_sort(iterable, *, key=lambda x: x, reverse: bool = False):
    sorted_lst = iterable
    for i in range(len(sorted_lst)):
        min_idx = i
        for j in range(i + 1, len(sorted_lst)):
            if key(sorted_lst[min_idx]) > key(sorted_lst[j]):
                min_idx = j
        sorted_lst[i], sorted_lst[min_idx] = sorted_lst[min_idx], sorted_lst[i]
    if reverse:
        return sorted_lst[::-1]
    return sorted_lst


"""
print_templates:
#rezervari detaliate
    for rez in rezervare_repository.read():
        card=card_repository.read(rez.id_card_client)
        formatedcard = \
            CardWithFormatedDates(card.id_card,
                                  card.nume,
                                  card.prenume,
                                  card.cnp,
                                  card.data_nasterii.strftime("%d.%m.%Y"),
                                  card.data_inregistrarii.strftime("%d.%m.%Y"),
                                  card.puncte_acumulate)
        rezdetail = \
            RezervareDetaliata(rez.id_rezervare,
                               film_repository.read(rez.id_film),
                               rez.data_si_ora.strftime('%d.%m.%Y ; %H:%M'),
                               formatedcard)
        print(rezdetail)


#carduri
    for card in card_repository.read():
        formatedcard = \
            CardWithFormatedDates(card.id_card,
                                  card.nume,
                                  card.prenume,
                                  card.cnp,
                                  card.data_nasterii.strftime("%d.%m.%Y"),
                                  card.data_inregistrarii.strftime("%d.%m.%Y"),
                                  card.puncte_acumulate)
        print(formatedcard)

"""
