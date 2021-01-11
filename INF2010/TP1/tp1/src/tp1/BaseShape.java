package tp1;

import java.util.*;

public class BaseShape implements Cloneable {
    private final Collection<Point2d> coords;

    // TODO Initialiser la liste de points.
    public BaseShape() {
        this.coords = new ArrayList<>(0);
    }

    // TODO prendre une liste de points et creer une nouvelle forme.
    public BaseShape(Collection<Point2d> coords) {
        this.coords = new ArrayList<>(coords);
    }

    // TODO ajouter ou retirer des coordonnees a la liste de points.
    public BaseShape add(Point2d coord) {
        this.coords.add(coord);
        return this;
    }
    public BaseShape add(BaseShape shape) {
        coords.addAll(shape.coords);
        return this;
    }
    public BaseShape addAll(Collection<Point2d> coords) {
        this.coords.addAll(coords);
        return this;
    }
    public BaseShape remove(Point2d coord) {
        this.coords.remove(coord);
        return this;
    }
    public BaseShape remove(BaseShape shape) {
        this.removeAll(shape.coords);
        return this;
    }
    public BaseShape removeAll(Collection<Point2d> coords) {
        this.coords.removeAll(coords);
        return this;
    }

    // TODO retourner les coordonnees de la liste.
    public Collection<Point2d> getCoords() {
        return new ArrayList<>(this.coords);
    }

    // TODO retourner une nouvelle liste ou tous les points sont des copy
    public Collection<Point2d> getCoordsDeepCopy() {
        ArrayList<Point2d> returnCopy = new ArrayList<>(this.getCoords().size());
        Iterator<Point2d> itr = coords.iterator();

        while(itr.hasNext()){
            returnCopy.add(itr.next().clone());
        }
        return returnCopy;
    }

    // TODO appliquer la translation sur la forme.
    public BaseShape translate(Point2d point) {
        Iterator<Point2d> itr = coords.iterator();

        while(itr.hasNext()){
            itr.next().translate(point);
        }
        return this;
    }

    // TODO appliquer la rotation sur la forme.
    public BaseShape rotate(Double angle) {
        Iterator<Point2d> itr = coords.iterator();

        while(itr.hasNext()){
            itr.next().rotate(angle);
        }
        return this;
    }

    // TODO donner la plus grande valeur en X
    public Double getMaxX() {
        Double max = Double.MIN_VALUE;
        Iterator<Point2d> itr = coords.iterator();

        while (itr.hasNext()){
            Double value = itr.next().vector[0];
            if(value > max){
                max = value;
            }
        }
        return max;
    }

    // TODO donner la plus grande valeur en Y
    public Double getMaxY() {
        Double max = Double.MIN_VALUE;
        Iterator<Point2d> itr = coords.iterator();

        while (itr.hasNext()){
            Double value = itr.next().vector[1];
            if(value > max){
                max = value;
            }
        }
        return max;
    }

    // TODO donner les plus grandes valeurs en X et Y
    public Point2d getMaxCoord() {
        double maxX = Double.MIN_VALUE;
        double maxY = Double.MIN_VALUE;
        Point2d maxVal = new Point2d(new Double[]{maxX, maxY});

        maxVal.vector[0] = getMaxX();
        maxVal.vector[1] = getMaxY();

        return maxVal;
    }

    // TODO donner la plus petite valeur en X
    public Double getMinX() {
        Double min = Double.MAX_VALUE;
        Iterator<Point2d> itr = coords.iterator();

        while(itr.hasNext()){
            Double value = itr.next().vector[0];
            if(value < min){
                min = value;
            }
        }
        return min;
    }

    // TODO donner la plus petite valeur en Y
    public Double getMinY() {
        Double min = Double.MAX_VALUE;
        Iterator<Point2d> itr = coords.iterator();

        while(itr.hasNext()){
            Double value = itr.next().vector[1];
            if(value < min){
                min = value;
            }
        }
        return min;
    }

    // TODO donner les plus petites valeurs en X et Y
    public Point2d getMinCoord() {
        double minX = Double.MAX_VALUE;
        double minY = Double.MAX_VALUE;
        Point2d minVal = new Point2d(new Double[]{minX, minY});

        minVal.vector[0] = getMinX();
        minVal.vector[1] = getMinY();
        return minVal;
    }

    // TODO retourner une nouvelle forme.
    public BaseShape clone() {
        return new BaseShape(getCoordsDeepCopy());
    }
}