public class Interview<ValueType extends Comparable<? super ValueType> > {
    // 2D array of any shape which contains elements sorted from left to right, top to bottom
    private final ValueType[][] matrix;

    public Interview(ValueType[][] matrix) {
        this.matrix = matrix.clone();
    }

    /** TODO Worst case : O ( max(log n, log m) )
     *
     * Verifies if the value is contained within the 2D array
     * @param value value to verify
     * @return if value is in matrix
     */
    public boolean contains(ValueType value) {
        int lignes = matrix.length;
        if (lignes == 0) return false;
        int colonnes = matrix[0].length;
        if (colonnes == 0) return false;

        int indexLigne = lignes - 1;
        int indexColonne = 0;
        while (indexLigne>=0 && indexColonne <= colonnes - 1) {
            //int mid = indexLigne + (indexColonne - indexLigne) / 2;
            ValueType element = matrix[indexLigne][indexColonne];
            if (value.compareTo(element) == 0) {
                return  true;
            }
            if (value.compareTo(element) > 0) {
                indexColonne += 1;
            } else {
                indexLigne -= 1;
            }
        }
        return false;
    }
}
