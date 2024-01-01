import numpy as np
import os
import argparse
import itertools


def gen(n_students, n_pairs):  
    try:    
        os.mkdir('samples')
    except OSError as e:
        pass
    
    all_combinations = np.array(list(itertools.combinations(np.arange(n_students), 2)))
    print('Maximum pairs for this sample :', len(all_combinations))
    if n_pairs > len(all_combinations) :
        print('ERREUR : Vous demandez plus de paires que de combinaisons possibles')
        return
    
    f = open(f'samples/sample_{n_students}_{n_pairs}_1.txt', 'w')
    f.write(f'{n_students}\n{n_pairs}\n')
    sizes = np.random.randint(10000, 20000, n_students)  # in micro meters
    for i in range(n_students):
        f.write(f'{sizes[i]}\n')
    
    indexes = np.random.choice(len(all_combinations), n_pairs, replace=False)
    pairs = all_combinations[indexes]
    for s1, s2 in pairs:
        f.write(f'{s1} {s2}\n')
    f.close()
    
if __name__ == "__main__":
    # Parse arguments
    parser = argparse.ArgumentParser()
    parser.add_argument("-n", "--nb_students", required=True, type=int,
                        help="Represente le nombre d'étudiants à mettre en rang")
    parser.add_argument("-p", "--nb_pairs", required=True, type=int,
                        help="Represente le nombre de paires d'étudiants ne s'entendant pas bien.")
    args = parser.parse_args()

    gen(args.nb_students, args.nb_pairs)



