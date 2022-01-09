import random
import json

quantities = [100, 200, 300, 400, 500]


def generate_prices(m: int):
    l = []
    for i in range(m):
        l.append(random.randint(5, 29))
    return f'"prices": {json.dumps(l)},'


def generate_quantities(m: int):
    l = []
    for i in range(m):
        l.append(quantities[random.randint(0, 3)])
    return f'"quantities": {json.dumps(l)},'


def generate_exp_dates(m: int):
    l = []
    for i in range(m):
        l.append(random.randint(1, 6))
    return f'"dates": {json.dumps(l)},'


def generate_recipes(n: int, m: int):
    l = []
    for i in range(n):
        nl = []
        for j in range(m):
            nl.append(random.randint(100, 199))
        l.append(nl)
    return f'"recipes": {json.dumps(l)},'


def generate_times(n: int):
    l = []
    for i in range(n):
        l.append(random.randint(5, 31))
    return f'"times": {json.dumps(l)}'


if __name__ == "__main__":
    random.seed(420)
    n = 20
    m = 150
    money = 1000

    json_object = '{' \
                  + f'"n": {n},' \
                  + f'"m": {m},' \
                  + f'"money": {money},' \
                  + generate_prices(m) \
                  + generate_quantities(m) \
                  + generate_exp_dates(m) \
                  + generate_recipes(n, m) \
                  + generate_times(n) \
                  + '}'
    with open('generated_data.json', 'w') as file:
        file.write(json_object)
