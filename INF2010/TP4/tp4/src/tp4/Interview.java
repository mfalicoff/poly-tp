package tp4;

import java.util.*;


public final class Interview {
    /**
     * @param circleSize le nombre d'amis que l'on doit inclure dans le cercle
     * @param centers les indices des centres dans "points"
     * @param points la liste des individus
     * @return les indices dans "points" qui creent l'intersection de deux cercles d'amis.
     *
     * On veut que vous indiquiez la complexite sur chaque ligne en fonction de:
     *  - circleSize -> O(a) a est pour le nombre d' "amis" communs
     *  - centers -> O(c) c est pour le nombre de "centres"
     *  - points -> O(n) n est simplement le nombre de d'individus dans la population
     * Vous n'avez pas besoin d'indiquer la complexite des lignes etant en O(1)
     * Lorsque vous avez des boucles, indiquez clairement la complexite de la boucle, par exemple:
     *   for (Integer p1 : points) { // O(n) * O(n^2*log(n)) -> O(n^3*log(n))
     *     for (Integer p2 : points) { // O(n) * O(n*log(n) -> O(n^2*log(n))
     *       Collections.sort(points); // O(n*log(n)
     *     }
     *   }
     * Ceci est un exemple, on voit clairement que la boucle sur "p2" est en O(n) et puisque son interieur est
     * en O(n*log(n), la complexite totale sera la multiplication, O(n^2*log(n)).
     *
     * O(n^2 * log(n)): ceci est la complexite en "worst case" ou 'a' et 'c' tendent vers 'n'
     * Il est peut etre possible d'avoir une meilleure complexite, soyez clair dans vos explications si vous croyez
     * avoir trouve :)
     */
    public static List<Integer> getFriendsToRemove(Integer circleSize, List<Integer> centers, List<Point> points) {

        for(int i = 0; i < points.size(); i++){
            points.get(i).setKey(i); //O(n)
        }

        ArrayList< ArrayList<Integer>> listOfCircles = new ArrayList<>();
        HashMap<Integer, Integer> allFriends = new HashMap<>();
        HashMap<Integer, Integer> problematic = new HashMap<>();

        for(Integer centerCircle: centers){ // O(c) * O(anlogn) -> O(canlogn)
            Point currentCenter = points.get(centerCircle);
            ArrayList<Integer> circle = new ArrayList<>();

            List<Point> sortedPoints = new ArrayList<>(points);
            sortedPoints.sort(new Comparator<Point>() {
                @Override
                public int compare(Point o1, Point o2) {
                    Integer distance1 = Math.abs(o1.X() - points.get(centerCircle).X()) + Math.abs(o1.Y() - points.get(centerCircle).Y());
                    Integer distance2 = Math.abs(o2.X() - points.get(centerCircle).X()) + Math.abs(o2.Y() - points.get(centerCircle).Y());
                    return distance1.compareTo(distance2);
                }
            }); // O(a) * O(n*logn) -> O(anlogn)

            for(int i = 0; i < sortedPoints.size(); i++){ //O(a) car on utlise des hashmaps assez petits, donc collisions sont peu probable

                Point currentPoint = sortedPoints.get(i);
                int currentPointKey = currentPoint.Key();

                if(currentCenter == currentPoint)
                    continue;
                if(i <= circleSize){
                    if(allFriends.containsKey(currentPointKey)){
                        if (allFriends.get(currentPointKey).equals(currentPointKey) && !problematic.containsKey(currentPointKey))
                            problematic.put(currentPointKey, currentPointKey);
                    }
                    else
                        allFriends.put(currentPointKey, currentPointKey);
                }
            }
        }

        List<Integer> problematicFriends = new ArrayList<>(problematic.values());
        Collections.sort(problematicFriends); //O(nlog(n))
        return problematicFriends;
    }
}
