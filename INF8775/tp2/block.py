class Block:
    def __init__(self, height, width, depth, fitness=-1):
        self.width = width
        self.height = height
        self.depth = depth
        if fitness == -1:
            self.fitness = self.height / self.depth * self.width * self.height
        else:
            self.fitness = fitness

    def __str__(self):
        return (f"height: {self.height}, width: {self.width}, depth: {self.depth}, "
                f"density: {self.height * self.width * self.depth}, "
                f"fitness: {self.fitness}")

    def __eq__(self, other):
        return self.width == other.width and self.depth == other.depth and self.height == other.height

    def __hash__(self):
        return hash((self.height, self.width, self.depth))

    def fits_on_other_block(self, previous_block):
        return self.width < previous_block.width and self.depth < previous_block.depth
