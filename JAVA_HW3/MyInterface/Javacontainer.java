

package MyInterface;
import MySource.Myiterator;

/**
 * The Javacontainer interface defines common methods shared by both set and vector implementations in Java. *
 * I have implement extra methods to make an improved and better  homework , I hope it is not a problem. King regards.
 * 
 * @param <E> the type of elements in the container
 * @author Yusuf Emre Kilicer / 210104004017
 * @version 1.0
 * @since January 18, 2024
 */
public interface Javacontainer<E> {

    /**
     * The initial capacity for containers 
     */
    public static final int initial_capacity = 10;

    /**
     * Adds the specified element to the container.
     *
     * @param element the element to be added to the container
     */
    public void add(E element);

    /**
     * Removes the specified element from the container.
     *
     * @param element the element which will be removed from container.
     */
    public void remove(E element);

     /**
     * Returns the current size (number of elements) of the container / Getter.
     *
     * @return the size of the container
     */
    public int size();
    
 /**
    * Returns an iterator for sequential access to the elements in the container. The iterator follows the Iterator
    * design pattern, patterns were explained before the implementation which are  : ({@code hasNext()}) and  ({@code next()}). 
    *
    * @return an iterator for the elements in the container
    */

    public Myiterator<E> getIterator();

        /**
     * Checks if the container is equal to another object.
     *
     * @param obj the object to compare
     * @return true if the containers are equal, false otherwise
     */
    public boolean equals(Object obj);


     /**
     * Returns a string representation of the container.
     *
     * @return a string representation of the container
     */
    public String toString();


    /**
     * Removes the element at the specified index from the container.
     *
     * @param index the index of the element to be removed
     */
    public void removeElementAt(int index);

    /**
     * Clears the container by removing all elements.
     */
    public void clear();


    /**
     * Returns the current capacity of the container // Getter.
     *
     * @return the capacity of the container
     */
    public int capacity();

    /**
     * Returns the index of the specified element in the container.
     *
     * @param element the element to find the index of
     * @return the index of the element, or -1 if not found
     */
    public int index_of(E element);

    /**
     * Checks if the specified element is present in the container.
     *
     * @param element the element to search for
     * @return true if the element is found, false otherwise
     */
    public boolean is_find(E element);

    /**
     * Checks if the container is empty.
     *
     * @return true if the container is empty, false otherwise
     */
    public boolean isEmpty();

    /**
     * Returns the first element in the container.
     *
     * @return the first element
     */
    public E firstElement();

    /**
     * Returns the last element in the container.
     *
     * @return the last element
     */
    public E lastElement();

    /**
     * Returns the element at the specified index in the container.
     *
     * @param index the index of the element to be retrieved
     * @return the element at the specified index
     */
    public E get(int index);


    /**
     * Loads the container from a file with the specified file name.
     *
     * @param fileName the name of the file to load the container from
     */
    public void load_file(String fileName);

    /**
     * Saves the current container to a file.
     */
    public void save_file();
    
    /**
     * Setter for capacity
     * @param _capacity the specified capacity that is determined by user.
     */
    public void set_capacity(int _capacity);

}