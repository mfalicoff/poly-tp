package tp4;

import java.util.*;

public class Heap<ValueType extends Comparable<? super ValueType>> implements Iterable<ValueType> {
    private ArrayList<ValueType> data;
    private boolean isMin;

    // O(1)
    public Heap() {
        this(true);
    }

    // O(1): construction sans donnees initiales
    public Heap(boolean isMin) {
        this.isMin = isMin;
        this.data = new ArrayList<>(2);
        this.data.add(0, null);
    }

    // O(n)
    public Heap(Collection<ValueType> data) {
        this(true, data);
    }

    // O(n): construction avec donnees initiales, allez voir le lien dans la description pour vous aider
    public Heap(boolean isMin, Collection<ValueType> data) {
        this.isMin = isMin;
        this.data = new ArrayList<>(1);
        this.data.add(0, null);
        this.data.addAll(data);
        build();
    }

    // O(1): on retourne le nombre d'elements dans la liste
    public int size() {
        return data.size()-1;
    }

    // O(1): on compare deux elements en fonction du type de monceau
    private boolean compare(ValueType first, ValueType second) {
        if(this.isMin)
            return first.compareTo(second) < 0;
        else
            return  first.compareTo(second) > 0;
    }

    // O(1): on donne l'indice du parent
    private int parentIdx(int idx) {
        return idx/2;
    }

    // O(1): on donne l'indice de l'enfant de gauche
    private int leftChildIdx(int idx) {
        return idx*2+1;
    }

    // O(1): on donne l'indice de l'enfant de droite
    private int rightChildIdx(int idx) {
        return idx*2;
    }

    // O(1): on echange deux elements dans le tableau
    private void swap(int firstIdx, int secondIdx) {
        ValueType temp = data.get(firstIdx);
        data.set(firstIdx, data.get(secondIdx));
        data.set(secondIdx, temp);
    }

    // O(log(n)): l'index courant represente le parent, on s'assure que le parent soit le min/max avec ses enfants
    // De facon visuelle, ceci ammene un noeud le plus haut possible dans l'arbre
    // Par exemple: si le min/max est une feuille, on appelera resursivement log(n) fois la methode pour monter le noeud
    private void heapify(int idx) {

        if(idx == 1){
            int child;
            ValueType tmp = data.get(idx);
            for(; rightChildIdx(idx) < data.size(); idx = child){
                child = rightChildIdx(idx);
                if(child < data.size()-1 && compare(data.get(child+1), data.get(child)))  //data.get(child + 1).compareTo(data.get(child)) < 0
                    child++;
                if(child <= size() && compare(data.get(child), tmp)) //data.get(child).compareTo(tmp) < 0
                    data.set(idx, data.get(child));
                else
                    break;
            }
            data.set(idx, tmp);
            return;
        }
        while(data.get(parentIdx(idx)) != null && compare(data.get(idx), data.get(parentIdx(idx)) )  ){  //data.get(idx).compareTo(data.get(parentIdx(idx))) < 0
            swap(idx, parentIdx(idx));
            idx = parentIdx(idx);
        }
    }

    // O(log(n)): on ajoute un element et on preserve les proprietes du monceau
    public void insert(ValueType element) {
        data.add(element);
        heapify(data.size()-1);
    }

    // O(n): on s'assure que tous les elements sont bien places dans le tableau,
    // allez voir le lien dans la description pour vous aider
    public void build() {
        for(int i = 0; i < size(); i++)
            heapify(i);
    }

    // O(log(n)): on retire le min ou le max et on preserve les proprietes du monceau
    public ValueType pop() {
        ValueType returnValue = data.get(1);
        swap(1, size());
        data.remove(data.size()-1);
        if(data.size() == 1)
            return returnValue;
        heapify(1);
        return returnValue;
    }

    // O(1): on retourne sans retirer le plus petit ou plus grand element.
    public ValueType peek() {
        return data.get(1);
    }

    // O(nlog(n)): On applique l'algorithme Heap Sort, on s'attend a ce que le monceau soit vide a la fin.
    public List<ValueType> sort() {
        int totalElements = size();
        LinkedList<ValueType> sortedList = new LinkedList<>();
        int counter = size();

        while(data.size() > 1){
            ValueType deletedItem = pop();
            sortedList.addLast(deletedItem);
            counter--;
        }
        return sortedList;
    }

    // Creation d'un iterateur seulement utilise dans les tests, permet de faire des boucles "for-each"
    @Override
    public Iterator<ValueType> iterator() {
        return new Iterator<ValueType>() {
            int currentIndex = 1;
            @Override
            public boolean hasNext() {
                return ++currentIndex < data.size();
            }

            @Override
            public ValueType next() {
                return data.get(currentIndex);
            }
        };
    }
}
