testArr = ["2 3 4", "5 6 3", "4 4 4"]


class Block:
    def __init__(self, height, length, depth) -> None:
        self.height = height
        self.length = length
        self.depth = depth


def convertIntoBlock(arr, index):
    if (index < len(arr)):
        values = arr[index].split(" ")
        return Block(int(values[0]), int(values[1]), int(values[2]))
    return "error"


def getBlockArea(block):
    return block.length * block.depth


def getBlockDensity(block):
    return float(block.height / block.length * block.depth)


newBlock = convertIntoBlock(testArr, 0)
blockAir = getBlockArea(newBlock)
blockDensity = getBlockDensity(newBlock)
print(convertIntoBlock(testArr, 0).height)
print(blockAir)
print(blockDensity)
