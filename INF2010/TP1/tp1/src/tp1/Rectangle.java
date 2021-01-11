package tp1;

import java.util.ArrayList;
import java.util.Collection;

public class Rectangle extends BaseShape {
    // TODO creer un rectangle avec une largeur et une longueur.
    public Rectangle(Double width, Double height) {
        super(new ArrayList<>());
        double minX = -1*(width/2);
        double minY = -1*(height/2);

        if(width != 0.0 || height != 0.0){
            for(; minX <= width/2; minX++){
                for(; minY <= height/2; minY++){
                    Point2d point = new Point2d(new Double[]{minX, minY});
                    super.add(point);
                }
                minY = -1*(height/2);
            }
        }

    }

    // TODO creer un rectangle avec les dimensions contenu dans un Point.
    public Rectangle(Point2d dimensions) {
        super();
        double minX = -1*(dimensions.vector[0]/2);
        double minY = -1*(dimensions.vector[1]/2);

        for(; minX <= dimensions.vector[0]/2; minX++){
            for(; minY <= dimensions.vector[1]/2; minY++){
                Point2d point = new Point2d(new Double[]{minX, minY});
                super.add(point);
            }
            minY = -1*(dimensions.vector[1]/2);
        }
    }

    // TODO initialiser le parent.
    private Rectangle(Collection<Point2d> coords) {
        super(coords);
    }

    // TODO appliquer la translation sur la forme.
    @Override
    public Rectangle translate(Point2d point) {
        super.translate(point);
        return this;
    }

    // TODO appliquer la rotation sur la forme.
    @Override
    public Rectangle rotate(Double angle) {
        super.rotate(angle);
        return this;
    }

    // TODO retourner une nouvelle forme.
    @Override
    public Rectangle clone() {
        return (Rectangle) super.clone();
    }
}
