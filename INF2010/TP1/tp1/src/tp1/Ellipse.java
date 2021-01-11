package tp1;

import java.util.Collection;

public class Ellipse extends BaseShape {
    // TODO creer une ellipse avec une largeur et une longueur.
    public Ellipse(Double widthRadius, Double heightRadius) {
        super();
        widthRadius /= 2;
        heightRadius /= 2;
        for(double i = -widthRadius; i <= widthRadius; i++){
            for(double j = -heightRadius; j <= heightRadius; j ++){
                double ellipsePoint = (Math.pow(i, 2)/Math.pow(widthRadius, 2) ) + (Math.pow(j, 2)/Math.pow(heightRadius, 2));
                if(ellipsePoint <= 1){
                    super.add(new Point2d(i, j));
                }

            }
        }
    }

    // TODO creer une ellipse avec les dimensions contenu dans un Point.
    public Ellipse(Point2d dimensions) {
        super();
        double widthRadius = dimensions.vector[0];
        double heightRadius = dimensions.vector[1];
        for(double i = -widthRadius; i <= widthRadius; i++){
            for(double j = -heightRadius; j <= heightRadius; j += 0.1){
                double ellipsePoint = (Math.pow(i, 2)/Math.pow(widthRadius, 2) ) + (Math.pow(j, 2)/Math.pow(heightRadius, 2));
                if(ellipsePoint <= 1){
                    super.add(new Point2d(i, j));
                }

            }
        }
    }

    // TODO initialiser le parent.
    private Ellipse(Collection<Point2d> coords) {
        super(coords);
    }

    // TODO appliquer la translation sur la forme.
    @Override
    public Ellipse translate(Point2d point) {
        return (Ellipse) super.translate(point);
    }

    // TODO appliquer la rotation sur la forme.
    @Override
    public Ellipse rotate(Double angle) {
        return (Ellipse) super.rotate(angle);
    }

    // TODO retourner une nouvelle forme.
    @Override
    public Ellipse clone() {

        return (Ellipse) super.clone();
    }
}
