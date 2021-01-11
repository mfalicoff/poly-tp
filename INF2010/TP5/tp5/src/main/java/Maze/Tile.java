package Maze;

public enum Tile {
    Floor,
    Wall,
    Exit;

    @Override
    public String toString() {
        return switch (this) {
            case Exit -> "*";
            case Floor -> "_";
            case Wall -> "#";
        };
    }


}
