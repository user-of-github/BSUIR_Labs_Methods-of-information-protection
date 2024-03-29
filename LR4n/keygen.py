import numpy as np


class HammingKeygen:

    def __init__(self, kgen):
        self.kgen = kgen
        self.k = 2 ** self.kgen - self.kgen - 1
        self.n = 2 ** self.kgen - 1
        self.G = self.get_hamming_matrix()
        self.S = self.get_invertible_matrix()
        self.P = self.generate_permute_matrix()
        self.Gcarat = np.matmul(np.matmul(self.S, self.G), self.P) % 2

    def get_hamming_matrix(self):
        identity = np.identity(self.kgen)
        identityk = np.identity(self.k)
        left = np.zeros((self.kgen, 2 ** self.kgen - 1 - self.kgen)).T
        rowcount = 0

        for i in range(2 ** self.kgen):
            if i + 1 != 1:
                if (i + 1) & i != 0:
                    binarystring = np.binary_repr(i + 1)
                    column = np.zeros((len(binarystring), 1))
                    for i in range(len(binarystring)):
                        column[-i - 1] = binarystring[i]
                    column = np.pad(column, (0, self.kgen - len(binarystring)), 'constant')
                    left[rowcount] = column.T[0]
                    rowcount += 1

        left = left.T
        self.paritycheck = np.block([left, identity])
        self.generator = np.block([identityk, np.transpose(left)])

        return self.generator

    def get_invertible_matrix(self):
        S = np.random.randint(0, 2, (self.k, self.k), dtype=np.uint)

        while np.linalg.det(S) == 0:
            S = np.random.randint(0, 2, (self.k, self.k), dtype=np.uint)

        return S

    def generate_permute_matrix(self):
        P = np.identity(self.n, dtype=np.uint)
        return P[np.random.permutation(self.n)]
