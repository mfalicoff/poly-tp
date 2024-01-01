import sys
import traceback


def fitness(block, max_height, max_depth, maxWidth):
    return (block.depth / max_depth) * (block.width / maxWidth) * (block.height / max_height)


def return_keys(blocks):
    return list(dict.fromkeys(blocks))


def greedy(the_list, max_height, max_depth, max_width):
    try:
        sorted_blocks = sorted(list(the_list), key=lambda x: fitness(x, max_height, max_depth, max_width), reverse=True)

        used_blocks = []
        height = 0

        while len(sorted_blocks) != 0:
            if len(used_blocks) == 0:
                block = sorted_blocks.pop(0)
                used_blocks.append(block)
                height += block.height
                continue
            block = sorted_blocks.pop(0)
            if block.fits_on_other_block(used_blocks[-1]):
                used_blocks.append(block)
                height += block.height

        return used_blocks, height

    except Exception:
        print(traceback.format_exc())
        # or
        print(sys.exc_info()[2])
