package tp2;

import java.util.*;

public final class Interview {
    private static final ArrayList<Integer> singleNumbers = new ArrayList<Integer>() {{
        add(0);
        add(1);
        add(2);
        add(5);
        add(8);
    }};
    private static final HashMap<Integer, Integer> flippedValues = new HashMap<>() {{
        put(0, 0);
        put(1, 1);
        put(2, 2);
        put(3, null);
        put(4, null);
        put(5, 5);
        put(6, 9);
        put(7, null);
        put(8, 8);
        put(9, 6);

    }};


    /**
     * TODO Worst Case : O(n)
     * Is valid if you flip the number upside down.
     */
    public static boolean isValidFlipped(String listOfNumbers) {
        if (listOfNumbers.equals("")) {
            return true;
        } else {
            char[] listofNUmbersCharArray = listOfNumbers.toCharArray();
            String flipped = Flip(listofNUmbersCharArray);
            if (flipped == null) return false;
            else if (flipped.equals(listOfNumbers)) {
                return true;
            }

        }
        return false;
    }

    public static String Flip(char[] listofNumbers) {
        StringBuilder flippedNumbers = new StringBuilder("");
        for (char number : listofNumbers) {
            Integer pairedNumber = flippedValues.get(Character.getNumericValue(number));
            if (pairedNumber == null) {
                return null;
            } else {
                flippedNumbers.insert(0, String.valueOf(pairedNumber));
            }
        }
        return flippedNumbers.toString();
    }

    /**
     * TODO Worst Case : O(n)
     * Could be valid if you try to flip the number upside down with one of the combinations.
     */
    public static boolean isValidFlippedWithPermutation(String listOfNumbers) {

        if (listOfNumbers.equals("")) {
            return true;
        } else if (listOfNumbers.length() == 1) {
            if (singleNumbers.contains(Integer.valueOf(listOfNumbers))) {
                return true;
            }
        } else {
            // en vrai ici le principe c'est que il faut conpter touts les chiffres flippable
            // car le moyen le plus facile de trouver l'inverse du nombre est de prendre
            // deux nombres flippables entre eux et de les mettres a l'index n et k-n ou k le size de la liste
            // il faut alors compter touts les nombres flippables et s'aasurer qu'ils sont multiples de deux
            // sauf au maximum un qui peut se siteur au centre si k impair.


            java.util.HashMap<Integer, Integer> letterCount = new java.util.HashMap<>();
            char[] charArray = listOfNumbers.toCharArray();
            int counter = 0;
            for (char number : charArray) {
                if (letterCount.containsKey(Character.getNumericValue(number))) {
                    int count = letterCount.get(Character.getNumericValue(number));
                    count = count + 1;
                    letterCount.put(Character.getNumericValue(number), count);

                } else {
                    int num = Character.getNumericValue(number);
                    if (flippedValues.containsKey(num)) {
                        letterCount.put(Character.getNumericValue(number), 1);
                    } else {
                        return false;
                    }

                }

            }
            Iterator it = letterCount.entrySet().iterator();
            int count = 0;
            while (it.hasNext()) {
                Map.Entry ok = (Map.Entry) it.next();
                int test = (Integer) ok.getValue() % 2;
                if (test != 0) {
                    count++;
                }
            }
            if (count > 1) {
                return false;
            } else {
                return true;
            }
        }
        return false;
    }
}
