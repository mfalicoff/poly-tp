import numpy
from scipy.special import softmax


def fitness(block):
    block.fitness = (block.width * block.depth) + block.height
    return block.fitness


def probability(blocks):
    try:
        for block in blocks:
            fitness(block)

        used_blocks = set()
        height = 0

        while len(blocks) > 0:
            fitness_values = [obj.fitness for obj in blocks]
            probabilities = softmax(fitness_values)
            chosen_index = numpy.random.choice(len(blocks), p=probabilities)
            chosen_block = list(blocks)[chosen_index]
            blocks.remove(chosen_block)
            chosen_block.fitness = 0

            if len(used_blocks) == 0:
                used_blocks.add(chosen_block)
                height += chosen_block.height
                continue

            for used_block in used_blocks:
                if not chosen_block.fits_on_other_block(used_block):
                    break
            else:
                used_blocks.add(chosen_block)
                height += chosen_block.height

        return sorted(used_blocks, key=lambda block_lambda: (block_lambda.width, block_lambda.depth), reverse=True), height
    except Exception as e:
        print(traceback.format_exc())
        # or
        print(sys.exc_info()[2])
