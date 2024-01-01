import numpy as np
import os
import argparse


def gen(size, magnitude, nb, nearly_sorted):
    try:    
        os.mkdir('samples')

    except OSError as e:
        pass

    for i in range(1, nb+1):
        if nearly_sorted:
            array = np.linspace(0, magnitude, num=size, dtype=int)
            for j in range(max(1, array.size//10)):
                a, b = np.random.randint(0, array.size-1), np.random.randint(0, array.size-1)
                array[a], array[b] = array[b], array[a]

        else:
            array = np.random.randint(0, magnitude, size)
        
        f = open(f'samples/sample_{size}_{magnitude}_{i}.txt', 'w')
        np.savetxt(f, array, fmt="%.1d", newline=' ')
        f.close()

    
if __name__ == "__main__":
    # Parse arguments
    parser = argparse.ArgumentParser()
    parser.add_argument("-s", "--array_size", required=True, type=int,
                        help="Represente le nombre d'éléments du tableau")
    parser.add_argument("-n", "--nb_samples", required=False, default=1, type=int,
                        help="Represente le nombre d'exemplaires de tableaux de même taille générés")
    parser.add_argument("-m", "--magnitude", required=True, default=1000, type=int,
                        help="Represente la valeur maximale des éléments du tableau")
    parser.add_argument("-r", "--random_seed", required=False, default=1, type=int,
                        help="Represente le germe du generateur de nombres aléatoires")
    parser.add_argument("-p", "--nearly_sorted", required=False, default=False, type=str,
                        help="Indique si le tableau généré est presque trié ou non")
    
    args = parser.parse_args()

    np.random.seed(args.random_seed)
    gen(args.array_size, args.magnitude, args.nb_samples, args.nearly_sorted == 'True' or args.nearly_sorted == '1')



