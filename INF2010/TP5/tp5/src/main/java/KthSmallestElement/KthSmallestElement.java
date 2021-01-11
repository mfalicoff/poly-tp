package KthSmallestElement;

import java.util.ArrayList;
import java.util.Comparator;
import java.util.List;
import java.util.PriorityQueue;

public class KthSmallestElement {
    /**
     * Explication de votre complexité temporelle
     *  On construit un heap a partir d'une table en donc O(largeur)
     *  Puis on ajoute k fois au heap donc O(klog(largeur)) car on doit faire un heapify pour chaque insertion.
     *
     * Explication de votre complexité spatiale
     * On tient en memoire au maximum une ligne a la fois.
     * On creer un prority queue contenant la premiere ligne
     * On poll le premier element puis on ajoute si possible l'element se situant au rang y+1, x (y=ligne)(x=colonne)
     * Donc on enleve puis on rajoute un element dans le meme loop.
     * On garde alors au maximum une ligne a la fois.
     *
     */
    /** TODO Worst case
     *      Time complexity : O ( k log max(m,n) )
     *      Space complexity : O (max(m,n) )
     *
     * Returns the `k`th smallest element in `matrix`
     * @param matrix 2D table of shape M x N respecting the following rules
     *               matrix[i][j] <= matrix[i+1][j]
     *               matrix[i][j] <= matrix[i][j + 1]
     * @param k Index of the smallest element we want
     * @return `K`th smallest element in `matrix`, null if non-existent
     */
    static public <T extends Comparable<T>> T findKthSmallestElement(final T[][] matrix, final int k) {

        if(matrix == null || k < 0 || k >= matrix.length * matrix[0].length)
            return null;

        //priority queue sorted by T value
        PriorityQueue<MatrixElement> q = new PriorityQueue<>(matrix[0].length, (Comparator<MatrixElement>) (o1, o2) -> {
            return o1.compareTo(o2);
        });

        List<MatrixElement> initList = new ArrayList<>();
        for(int i = 0; i < matrix[0].length; i++){
            initList.add(new MatrixElement(matrix[0][i], 0, i));
        }
        q.addAll(initList);

        for(int i = 0; i < k; i++){

            MatrixElement cur = q.poll();

            if(cur.getyPos() + 1 < matrix.length){
                MatrixElement nextVal = new MatrixElement(matrix[cur.getyPos()+1][cur.getxPos()], cur.getyPos()+1,cur.getxPos());
                q.add(nextVal);
            }
        }
        return (T) q.peek().getValue();
    }
}
