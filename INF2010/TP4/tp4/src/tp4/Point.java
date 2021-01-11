package tp4;

public class Point implements Comparable<Point> {
    // TODO vous pouvez modifier ce que vous voulez, tant que vous ne modifiez pas les tests

    private Integer x;
    private Integer y;
    private Integer key;

    public Point(String xy) {
        String[] xAndY = xy.split(" +");
        this.x = Integer.parseInt(xAndY[0]);
        this.y = Integer.parseInt(xAndY[1]);
    }

    public Point(Integer x, Integer y) {
        this.x = x;
        this.y = y;
    }

    public int X(){
        return this.x;
    }

    public int Y(){
        return this.y;
    }

    public void setKey(int key){ this.key = key;}
    public int Key(){return this.key;}

    @Override
    public String toString() {
        return String.format("{X: %d, Y: %d}", x, y);
    }

    @Override
    public boolean equals(Object obj) {
        if (!(obj instanceof Point)) {
            return false;
        }

        Point point = (Point)obj;
        return point.x.equals(x) && point.y.equals(y);
    }

    @Override
    public int compareTo(Point point) {
        // TODO ceci vous sera peut etre utile
        return 0;
    }
}
