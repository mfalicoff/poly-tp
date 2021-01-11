package KthSmallestElement;

public class MatrixElement <T extends Comparable<T>>{

    //Class representing a matrix element, used for storing coordinates
    private int xPos;
    private int yPos;
    private T value;

    public MatrixElement(T value, int y, int x) {
        this.value = value;
        this.xPos = x;
        this.yPos = y;
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

    public T getValue() {
        return value;
    }

    public void setValue(T value) {
        this.value = value;
    }


    public int compareTo(MatrixElement<T> ele){
        return value.compareTo(ele.value);
    }

}
