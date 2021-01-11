package DetailMyWorld;

import java.util.*;
import java.util.stream.Collectors;

public class DetailMyWorld {
    /**
     * TODO
     * Returns a list of all continents with their respective countries within `world`
     *
     * @param world 2D table of shape M x N representing the world
     * 0 : Water Region
     * Positive non-null value : Country region for country of that specific value
     * @param isBreadthFirstSearch
     * If true, algorithm used should be Breadth-First Search
     * If false, algorithm used should be Depth-First Search
     * @return List of all continents with their respective countries
     * Continents should be in order from left to right, top to bottom
     * Each continent should have its countries in order
     */

    private static int height;
    private static int width;
    private static boolean[][] visited;

    static int rowNum[] = {-1, 0, 1, 0};
    static int colNum[] = {0, 1, 0, -1};

    public static List<Set<Integer>> findContinents(ArrayList<ArrayList<Integer>> world, boolean isBreadthFirstSearch) {

        setup(world);

        LinkedList<WorldTile> q = new LinkedList<>();
        List<Set<Integer>> returnedList = new LinkedList<>();

        for (int i = 0; i < height; i++) {

            for (int j = 0; j < width; j++) {

                if (!visited[i][j] && world.get(i).get(j) != 0) {

                    HashSet<Integer> currentContinent = new HashSet<>();
                    q.add(new WorldTile(j, i, world.get(i).get(j)));

                    getCountriesFromContinent(q, world, visited, currentContinent, isBreadthFirstSearch);
                    returnedList.add(currentContinent);

                }
            }
        }


        return returnedList;


    }

    // setup, set height, width and visted array
    private static void setup(ArrayList<ArrayList<Integer>> world) {
        height = world.size();
        width = world.get(0).size();
        visited = new boolean[height][width];

        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++) {
                visited[i][j] = false;
            }
        }
    }


    private static void getCountriesFromContinent(LinkedList<WorldTile> queue, ArrayList<ArrayList<Integer>> world, boolean[][] visited, Set<Integer> currentContinent, boolean isBreadthFirstSearch) {

        HashMap<Integer, WorldTile> currentContinentWithTiles = new HashMap<Integer, WorldTile>();

        while (!queue.isEmpty()) {

            WorldTile cur = queue.poll();

            // put value in the current continent and keep the highest and leftest value
            if (!currentContinent.contains(cur.value)) {

                currentContinent.add(cur.value);
                currentContinentWithTiles.put(cur.value, cur);

            } else {

                WorldTile inserted = currentContinentWithTiles.get(cur.value);

                if (inserted.getyPos() > cur.getyPos() || inserted.getXPos() > cur.getXPos())
                    currentContinentWithTiles.put(cur.value, cur);
            }

            // add depending on traversal method
            for (int i = 0; i < 4; i++) {

                int nextRow = cur.getyPos() + rowNum[i];
                int newCol = cur.getXPos() + colNum[i];

                if (isInWorldAndNotVisited(nextRow, newCol, world, visited)) {

                    visited[nextRow][newCol] = true;
                    WorldTile voi = new WorldTile(newCol, nextRow, world.get(nextRow).get(newCol));

                    if (isBreadthFirstSearch)
                        queue.addLast(voi);
                    else
                        queue.addFirst(voi);

                }
            }

        }

        SortedSet<WorldTile> values = new TreeSet<WorldTile>(new Comparator<WorldTile>() {
            @Override
            public int compare(WorldTile o1, WorldTile o2) {
                int result = o1.getyPos().compareTo(o2.getyPos());
                if (result == 0) {
                    result = o1.getXPos().compareTo(o2.getXPos());
                }
                return result;
            }
        });

        // sort by position
        values.addAll(currentContinentWithTiles.values());
        currentContinent.clear();

        // add in sorted position
        for (WorldTile tile : values)
            if (!currentContinent.contains(tile.value))
                currentContinent.add(tile.value);

    }

    static boolean isInWorldAndNotVisited(int row, int col, ArrayList<ArrayList<Integer>> world, boolean visited[][]) {
        return (row >= 0) && (row < height) && (col >= 0) && (col < width) && (world.get(row).get(col) != 0 && !visited[row][col]);
    }

    public static void printWorld(ArrayList<ArrayList<Integer>> world) {
        for (ArrayList<Integer> row : world) {
            System.out.println(row.stream().map(String::valueOf).collect(Collectors.joining(" ")));
        }
    }
}