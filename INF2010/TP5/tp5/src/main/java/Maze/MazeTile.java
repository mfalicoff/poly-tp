package Maze;

import java.util.Objects;

public class MazeTile {

    // Class representing a mazileTile element, used for coordinates and to compare Tiles
    private String type;
    private int xPos;
    private int yPos;

    public MazeTile(Tile tile, int x, int y) {
        this.type = new String(tile.toString());
        this.xPos = x;
        this.yPos = y;
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;
        MazeTile point = (MazeTile) o;
        return xPos == point.xPos &&
                yPos == point.yPos &&
                Objects.equals(type, point.type);
    }

    public String getType() {
        return type;
    }

    public void setType(String type) {
        this.type = type;
    }

    public int getxPos() {
        return xPos;
    }

    public void setxPos(int xPos) {
        this.xPos = xPos;
    }

    public int getyPos() {
        return yPos;
    }

    public void setyPos(int yPos) {
        this.yPos = yPos;
    }
}
