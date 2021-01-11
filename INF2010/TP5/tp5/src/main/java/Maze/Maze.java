package Maze;

import java.sql.Array;
import java.util.*;
import java.util.stream.Collectors;

public class Maze {
    /**
     * TODO
     * Returns the distance of the shortest path within the maze
     *
     * @param maze 2D table representing the maze
     * @return Distance of the shortest path within the maze, null if not solvable
     */

    private static MazeTile start;
    private static MazeTile end;
    private static int width;
    private static int height;
    private static ArrayList<Boolean> visited;
    private static int count = 0;

    static int rowNum[] = {-1, 0, 0, 1};
    static int colNum[] = {0, -1, 1, 0};

    public static Integer findShortestPath(ArrayList<ArrayList<Tile>> maze) {

        setup(maze);
        int ret = BFS(maze, Maze.start, Maze.end);
        return ret == -1 ? null : ret;
    }

    private static void setup(ArrayList<ArrayList<Tile>> maze){
        try {
            Maze.height = maze.size();
            Maze.width = maze.get(0).size();
            findStart(maze);
            findEnd(maze);
            
        } catch (Exception e){
            System.out.println(e.toString());
        }

    }

    static boolean isIsMaze(int row, int col) {
        return (row >= 0) && (row < Maze.width) && (col >= 0) && (col < Maze.height);
    }

    public static void findStart(ArrayList<ArrayList<Tile>> maze) {
        for(int i = 0; i < maze.size(); i++){
            for(int j = 0; j < maze.get(0).size(); j++){
                Tile cur = maze.get(i).get(j);
                if((cur.toString() == "*")){
                    Maze.start = new MazeTile(cur, j, i);
                    return;
                }
            }
        }
    }

    public static void findEnd(ArrayList<ArrayList<Tile>> maze){
        for(int i = 0; i < maze.size(); i++){
            for(int j = 0; j < maze.get(0).size(); j++){
                Tile cur = maze.get(i).get(j);
                if((cur.toString() == "*" && i != start.getyPos() && j != start.getxPos())){
                    Maze.end = new MazeTile(cur, j, i);
                    return;
                }
            }
        }
    }

    public static int BFS(ArrayList<ArrayList<Tile>> maze, MazeTile src, MazeTile dest) {
        // cas sans src ou dest
        if (src == null || dest == null)
            return -1;

        boolean[][] vis = new boolean[height][width];
        vis[src.getyPos()][src.getxPos()] = true;

        Queue<MazeTileNode> q = new LinkedList<>();

        MazeTileNode s = new MazeTileNode(src, 0);
        q.add(s);

        while (!q.isEmpty()) {

            MazeTileNode curr = q.peek();
            MazeTile pt = curr.pt;

            if (pt.getxPos() == dest.getxPos() && pt.getyPos() == dest.getyPos()) // est dest
                return curr.dist;

            q.remove();

            for (int i = 0; i < 4; i++) { // voisins: top left right bottom

                int nextRow = pt.getyPos() + rowNum[i];
                int newCol = pt.getxPos() + colNum[i];

                if (isIsMaze(nextRow, newCol) && !vis[nextRow][newCol]) {

                    if(maze.get(nextRow).get(newCol).toString() == "_" || maze.get(nextRow).get(newCol).toString() == "*") {

                        vis[nextRow][newCol] = true;
                        MazeTileNode voisin = new MazeTileNode(new MazeTile(maze.get(nextRow).get(newCol), newCol, nextRow), curr.dist + 1 );
                        q.add(voisin);
                    }
                }
            }
        }
        return -1;
    }

    public static void printMaze(ArrayList<ArrayList<Tile>> maze) {
        for (ArrayList<Tile> row : maze) {
            System.out.println(row.stream().map(String::valueOf).collect(Collectors.joining("")));
        }
    }

static class MazeTileNode {

    MazeTile pt;
    int dist;

    public MazeTileNode(MazeTile pt, int dist) {
        this.pt = pt;
        this.dist = dist;
    }
}}

