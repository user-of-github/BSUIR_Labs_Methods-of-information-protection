from ec import ECPoint
from gost3410 import Gost3410
from data import message, a, b, x, y, p, q


def main() -> None:
    gost = Gost3410(p, a, b, q, x, y)
    key = gost.generate_keys()
    d = key[0]
    q_x = key[1].x
    q_y = key[1].y

    r, s = gost.encrypt(message, d)
    print(f'r = {r}\nq = {q}')

    public_key = ECPoint(q_x, q_y, a, b, p)
    is_verified = gost.verify_signature(message, (r, s), public_key)

    if is_verified:
        print('ЭЦП подтверждена')
    else:
        print('ЭЦП не подтверждена')


if __name__ == '__main__':
    main()