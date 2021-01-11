package tp1;

import java.util.*;

public final class PointOperator {

    // TODO appliquer la translation sur le vecteur d'entree.
    public static void translate(Double[] vector, Double[] translateVector) {
        for(int i = 0; i < vector.length; i++){
            vector[i] = vector[i]+translateVector[i];
        }
    }

    // TODO appliquer la translation sur le vecteur d'entree.
    public static void rotate(Double[] vector, Double[][] rotationMatrix) {
        Double[] originalV = new Double[vector.length];
        System.arraycopy(vector, 0, originalV, 0, vector.length);
        for(int i = 0; i < rotationMatrix.length; i++)  {

            double add =0.0;

            for(int j = 0; j < rotationMatrix[i].length; j++) {
                add += rotationMatrix[i][j] * originalV[j];
            }
            vector[i] = add;
        }

    }

    // TODO division sur le vecteur d'entree
    public static void divide(Double[] vector, Double divider) {
        for(int i = 0; i < vector.length; i++){
            vector[i] = vector[i]/divider;
        }

    }

    // TODO multiplication sur le vecteur d'entree
    public static void multiply(Double[] vector, Double multiplier) {
        for(int i = 0; i < vector.length; i++){
            vector[i] = vector[i]*multiplier;
        }
    }

    // TODO addition sur le vecteur d'entree
    public static void add(Double[] vector, Double adder) {
        for(int i = 0; i < vector.length; i++){
            vector[i] = vector[i] + adder;
        }
    }
}
