import numpy as np
import os


if __name__ == "__main__":
    try:
        os.mkdir('samples')

    except OSError as e:
        pass

    count = 0
    # Change the list of sizes to your will
    sizes = [250, 500, 750, 1000, 2500, 5000, 7500, 10000, 25000, 50000, 75000]
    # Change the number of samples per size aswell
    nb_exemplaires = 10
    for size in sizes:
        for i in range(1, nb_exemplaires + 1):
            f = open(f'samples/sample_{size}_{i}.txt', 'w')
            for n in range(size):
                h, l, p = np.random.randint(1, int(np.cbrt(size))+2, 3)
                f.write(f'{h} {l} {p}\n')
            f.close()
            count += 1
            print(
                f"Generating : {round(100*count/(len(sizes)*nb_exemplaires),2)}%           ", end='\r')
    print('Generation finished')
