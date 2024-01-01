import sys
import traceback
from operator import itemgetter


def fitness(block):
    return block.depth * block.width


def dyn(the_list):
    try:

        sorted_blocks = sorted(list(the_list), key=lambda x: fitness(x), reverse=True)

        stacks_table = [()] * len(sorted_blocks)

        for i in range(len(sorted_blocks)):
            stacks_table[i] = (sorted_blocks[i].height, [sorted_blocks[i]])

        for i in range(1, len(sorted_blocks)):
            for j in range(0, i):
                if (sorted_blocks[i].fits_on_other_block(sorted_blocks[j])
                        and stacks_table[i][0] < stacks_table[j][0] + sorted_blocks[i].height):
                    stacks_table[i] = (
                        stacks_table[j][0] + sorted_blocks[i].height, stacks_table[j][1] + [sorted_blocks[i]])

        return max(stacks_table, key=itemgetter(0))[1], max(stacks_table, key=itemgetter(0))[0]

    except Exception:
        print(traceback.format_exc())
        print(sys.exc_info()[2])
