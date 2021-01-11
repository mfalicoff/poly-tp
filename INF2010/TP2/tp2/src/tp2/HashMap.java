package tp2;

import java.util.Arrays;
import java.util.Iterator;

public class HashMap<KeyType, DataType> implements Iterable<KeyType> {

    private static final int DEFAULT_CAPACITY = 20;
    private static final float DEFAULT_LOAD_FACTOR = 0.5f;
    private static final int CAPACITY_INCREASE_FACTOR = 2;

    private Node<KeyType, DataType>[] map;
    private int size = 0;
    private int capacity;
    private final float loadFactor; // Compression factor

    public HashMap() {
        this(DEFAULT_CAPACITY, DEFAULT_LOAD_FACTOR);
    }

    public HashMap(int initialCapacity) {
        this(initialCapacity > 0 ? initialCapacity : DEFAULT_CAPACITY,
                DEFAULT_LOAD_FACTOR);
    }

    public HashMap(int initialCapacity, float loadFactor) {
        capacity = initialCapacity;
        this.loadFactor = 1 / loadFactor;
        map = new Node[capacity];
    }

    /**
     * Finds the index attached to a particular key
     * This is the hashing function ("Fonction de dispersement")
     *
     * @param key Value used to access to a particular instance of a DataType within map
     * @return Index value where this key should be placed in attribute map
     */
    private int hash(KeyType key) {
        int keyHash = key.hashCode() % capacity;
        return Math.abs(keyHash);
    }

    /**
     * @return if map should be rehashed
     */
    private boolean needRehash() {
        return size * loadFactor > capacity;
    }

    /**
     * @return Number of elements currently in the map
     */
    public int size() {
        return size;
    }

    /**
     * @return Current reserved space for the map
     */
    public int capacity() {
        return capacity;
    }

    /**
     * @return if map does not contain any element
     */
    public boolean isEmpty() {
        return size == 0;
    }

    /**
     * TODO Average Case : O(1)
     * Find the next prime after increasing the capacity by CAPACITY_INCREASE_FACTOR (multiplication)
     */
    private void increaseCapacity() {
        capacity = findNextPrime(capacity * CAPACITY_INCREASE_FACTOR);
    }

    private int findNextPrime(int base) {
        int multipleCounter;
        base++;
        while (true) {
            multipleCounter = 0;
            for (int i = 2; i <= (int) Math.sqrt(base); i++) {
                if (base % i == 0) multipleCounter++;
            }
            if (multipleCounter == 0)
                return base;
            else {
                base++;
            }
        }
    }

    /**
     * TODO Average Case : O(n)
     * Increases capacity by CAPACITY_INCREASE_FACTOR (multiplication) and
     * reassigns all contained values within the new map
     */
    private void rehash() {
        increaseCapacity();
        Node<KeyType, DataType>[] clone = map.clone();

        clear();
        map = new Node[capacity];
        for (Node<KeyType, DataType> node : clone) {
            if (node != null) {
                put(node.key, node.data);
            }

        }
    }

    /**
     * TODO Average Case : O(1)
     * Finds if map contains a key
     *
     * @param key Key which we want to know if exists within map
     * @return if key is already used in map
     */
    public boolean containsKey(KeyType key) {
        int hashed = hash(key);
        if (map[hashed] != null) {
            if (map[hashed].key.equals(key)) {
                return true;
            } else {
                Node<KeyType, DataType> current = new Node<KeyType, DataType>(null, null);
                current = map[hashed];
                while (true) {
                    if (current.key.equals(key)) {
                        return true;
                    } else {
                        current = current.next;

                    }
                }

            }

        }
        return false;
    }

    /**
     * TODO Average Case : O(1)
     * Finds the value attached to a key
     *
     * @param key Key which we want to have its value
     * @return DataType instance attached to key (null if not found)
     */
    public DataType get(KeyType key) {
        int hashed = hash(key);
        if (map[hashed] != null) {
            if (map[hashed].next == null) {
                return map[hashed].data;
            } else {
                Node<KeyType, DataType> current = new Node<>(null, null);
                current.next = map[hashed];
                while (current.next != null) {
                    if (current.next.key.equals(key)) {
                        return current.next.data;
                    }
                    current = current.next;
                }
            }
        }
        return null;
    }

    /**
     * TODO Average Case : O(1) , Worst case : O(n)
     * Assigns a value to a key
     *
     * @param key Key which will have its value assigned or reassigned
     * @return Old DataType instance at key (null if none existed)
     */
    public DataType put(KeyType key, DataType value) {
        int hashed = hash(key);
        if (map[hashed] != null) {
            if (map[hashed].key.equals(key)) {
                DataType oldValue = map[hashed].data;
                map[hashed].data = value;
                return oldValue;
            } else {
                Node<KeyType, DataType> coll = new Node<KeyType, DataType>(key, value);
                Node<KeyType, DataType> current = map[hashed];
                while (current.next != null) {
                    current = current.next;
                }
                current.next = coll;
                return null;
            }

        } else {
            map[hashed] = new Node<>(key, value);
            size++;
            if (needRehash()) {
                rehash();
            }
            return null;
        }
    }

    /**
     * TODO Average Case : O(1)
     * Removes the node attached to a key
     *
     * @param key Key which is contained in the node to remove
     * @return Old DataType instance at key (null if none existed)
     */
    public DataType remove(KeyType key) {
        int hashed = hash(key);
        if (map[hashed] != null) {
            if (map[hashed].key.equals(key)) {
                DataType deletedValue = map[hashed].data;
                map[hashed] = map[hashed].next;
                if (this.map[hashed] == null) {
                    size--;
                }
                return deletedValue;
            } else {
                Node<KeyType, DataType> current = map[hashed];
                while (current.next != null) {
                    Node<KeyType, DataType> nextOfPrevious = current;
                    current = current.next;
                    if (current.key.equals(key)) {
                        DataType data = current.data;
                        current = current.next;
                        nextOfPrevious.next = current;
                        return data;
                    }

                }
            }

        }
        return null;
    }

    /**
     * TODO Worst Case : O(1)
     * Removes all nodes contained within the map
     */
    public void clear() {
        for (int i = 0; i < map.length; i++) {
            map[i] = null;
        }
        this.size = 0;


    }

    static class Node<KeyType, DataType> {
        final KeyType key;
        DataType data;
        Node<KeyType, DataType> next; // Pointer to the next node within a Linked List

        Node(KeyType key, DataType data) {
            this.key = key;
            this.data = data;
            next = null;
        }
    }

    @Override
    public Iterator<KeyType> iterator() {
        return new HashMapIterator();
    }

    // Iterators are used to iterate over collections like so:
    // for (Key key : map) { doSomethingWith(key); }
    private class HashMapIterator implements Iterator<KeyType> {
        // TODO: Add any relevant data structures to remember where we are in the list.
        private Node<KeyType, DataType> current;

        public HashMapIterator() {
            Node<KeyType, DataType> ok = new Node<KeyType, DataType>(null, null);
            ok.next = map[0];
            this.current = ok;
        }
//
//        public HashMapIterator(KeyType key){
//            Node<KeyType, DataType> ok = new Node<KeyType, DataType>(null, null);
//            ok.next = map[0];
//            this.current = ok;
//        }

        /**
         * TODO Worst Case : O(n)
         * Determine if there is a new element remaining in the hashmap.
         */
        public boolean hasNext() {
            return (current.next != null || hash(current.key) < size() - 1);
        }

        /**
         * TODO Worst Case : O(n)
         * Return the next new key in the hashmap.
         */
        public KeyType next(int test) {
            if (current.next != null) {
                Node<KeyType, DataType> next = current.next;
                this.current = next;
                return current.key;
            }
            return null;
        }

        public KeyType next() {
            if (current.next != null) {
                Node<KeyType, DataType> next = current.next;
                this.current = next;
                return current.key;
            } else {
                while (true) {
                    int decal = 1;
                    if (map[hash(current.key) + 1] != null) {
                        this.current = map[hash(current.key) + 1];
                        return current.key;
                    } else {
                        decal = decal + 1;
                    }
                }

            }
        }
    }
}
