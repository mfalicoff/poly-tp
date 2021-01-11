package tp1;

import java.util.ArrayList;

public final class LetterFactory {
    final static Double maxHeight = 200.0;
    final static Double maxWidth = maxHeight / 2.5;
    final static Double halfMaxHeight = maxHeight / 2;
    final static Double halfMaxWidth = maxWidth / 2;
    final static Double stripeThickness = maxHeight / 8;
    final static Double halfStripeThickness = stripeThickness / 2;

    // TODO
    public static BaseShape create_e() {
        Ellipse mainBody = new Ellipse(maxWidth, maxHeight);
        Ellipse middleToRemove = new Ellipse(maxWidth - stripeThickness,
                maxHeight - stripeThickness);

        Rectangle middleStripe = new Rectangle(maxWidth, halfMaxHeight/5);
        Rectangle middleStripeToRemove = new Rectangle(halfMaxWidth-10, halfMaxHeight/3.5).translate(new Point2d(30.0, 20.0));

        mainBody.remove(middleToRemove);
        mainBody.remove(middleStripeToRemove);
        mainBody.add(middleStripe);
        return mainBody;

    }

    // TODO
    public static BaseShape create_a() {
        Ellipse mainBody = new Ellipse(maxWidth, maxHeight);
        Ellipse middleToRemove = new Ellipse(maxWidth - stripeThickness,
                maxHeight - stripeThickness);
        mainBody.remove(middleToRemove);
        Rectangle rightSide = new Rectangle(halfStripeThickness, maxHeight).translate(new Point2d(halfMaxWidth, 0.0));
        mainBody.add(rightSide);
        return mainBody;
    }

    public static BaseShape create_C() {
        Ellipse mainBody = new Ellipse(maxWidth, maxHeight);
        Ellipse middleToRemove = new Ellipse(maxWidth - stripeThickness,
                maxHeight - stripeThickness);
        BaseShape rightToRemove = new Rectangle(halfMaxWidth, maxHeight/1.5).translate(new Point2d(halfMaxWidth/2, 0.0));

        mainBody.remove(middleToRemove);
        mainBody.remove(rightToRemove);
        return mainBody;
    }

    // TODO
    public static BaseShape create_l() {
        return new Rectangle(halfStripeThickness, maxHeight);
    }

    // TODO
    public static BaseShape create_i() {
        Rectangle stripe = new Rectangle(halfStripeThickness, maxHeight);
        Rectangle topRemove = new Rectangle(halfStripeThickness, halfMaxHeight/3).translate(new Point2d(0.0, -65.0));

        Circle topDot = new Circle(halfMaxWidth/2);
        topDot.translate(new Point2d(0.0, -91.0));
        stripe.remove(topRemove);
        stripe.add(topDot);
        return stripe;
    }

    // TODO
    public static BaseShape create_A() {
        BaseShape vBase = create_V();
        vBase.rotate(Math.toRadians(180.0));

        Rectangle middle = new Rectangle(maxWidth/4, halfMaxHeight/10);
        middle.translate(new Point2d(-10.0, 5.0));
        vBase.add(middle);



        return vBase;
    }

    // TODO
    public static BaseShape create_V() {
        Rectangle stripeLeft = new Rectangle(halfStripeThickness, maxHeight);
        Rectangle stripeRight = new Rectangle(halfStripeThickness, maxHeight).translate(new Point2d(maxWidth, 0.0));

        stripeLeft.rotate(Math.toRadians(-8));
        stripeRight.rotate(Math.toRadians(8));
        stripeRight.translate(new Point2d(-47.0, -11.0));
        stripeLeft.add(stripeRight);

        return stripeLeft;

    }

    // TODO
    public static BaseShape create_n() {
        Rectangle stripeLeft = new Rectangle(halfStripeThickness, maxHeight);
        Rectangle stripeRight = new Rectangle(halfStripeThickness, maxHeight*0.8).translate(new Point2d(halfMaxWidth+20, 20.0));

        Circle arc = new Circle(halfMaxWidth+35);
        arc.rotate(80.0);
        arc.translate(new Point2d((maxWidth/2)-10, -50.0));


        Circle arcRemove = new Circle((halfMaxWidth-(halfStripeThickness))+20);
        arcRemove.translate(new Point2d((maxWidth/2)-10, -50.0));
        arc.remove(arcRemove);

        ArrayList<Point2d> test = (ArrayList<Point2d>) arc.getCoords();
        for(int i = 0; i < test.size()/2; i++){
            arc.remove(test.get(i));
        }

        stripeLeft.add(stripeRight);
        stripeLeft.add(arc);

        return stripeLeft;
    }

    // TODO
    public static BaseShape create_r() {
        Rectangle stripeLeft = new Rectangle(halfStripeThickness, maxHeight);

        Circle arc = new Circle(maxWidth+10);
        arc.rotate(Math.toRadians(-90.0));
        arc.translate(new Point2d((maxWidth/2), -50.0));


        Circle arcRemove = new Circle(maxWidth-(halfStripeThickness));
        arcRemove.translate(new Point2d((maxWidth/2), -50.0));
        arc.remove(arcRemove);

        ArrayList<Point2d> test = (ArrayList<Point2d>) arc.getCoords();
        for(int i = 0; i < test.size()/2; i++){
            arc.remove(test.get(i));
        }

        stripeLeft.add(arc);

        return stripeLeft;

    }

    // TODO
    public static BaseShape create_B() {
        Rectangle stripeLeft = new Rectangle(halfStripeThickness, maxHeight);
        Circle topCircle = new Circle(halfMaxHeight);
        Circle bottomCircle = new Circle(halfMaxHeight);

        topCircle.translate(new Point2d(0.0, -50.0));
        bottomCircle.translate(new Point2d(0.0, 50.0));

        Circle centerToRemoveTop = new Circle((halfMaxHeight - halfStripeThickness)-5);
        Circle centerToRemoveBottom = new Circle((halfMaxHeight - halfStripeThickness)-5);
        centerToRemoveTop.translate(new Point2d(0.0, -50.0));
        centerToRemoveBottom.translate(new Point2d(0.0, 50.0));

        topCircle.remove(centerToRemoveTop);
        bottomCircle.remove(centerToRemoveBottom);

        ArrayList<Point2d> test = (ArrayList<Point2d>) topCircle.getCoords();
        for(int i = 0; i < test.size()/2; i++){
            topCircle.remove(test.get(i));
        }
        ArrayList<Point2d> test1 = (ArrayList<Point2d>) bottomCircle.getCoords();
        for(int i = 0; i < test1.size()/2; i++){
            bottomCircle.remove(test1.get(i));
        }

        stripeLeft.add(bottomCircle);
        stripeLeft.add(topCircle);

        return stripeLeft;

    }
}
