package MySource;

import java.util.NoSuchElementException;

  /**
     * This inner iterator class is utilized for iterating over elements within the JavaSet and JavaVector classes.
     * It takes object element as consructor.
     * @param <E> generic type of interface class
     * It encompasses two methods:
     * - {@code hasNext()}: Returns a boolean value, true if there are still elements available for iteration, false if it is end.
     * - {@code  next()}: Returns the subsequent element in the JavaSet and JavaVector  class. Note that typecasting is significant.
     */


public class Myiterator<E> {
    private int curr_index;
    private Object[] elements;
    public Myiterator(Object[] _elements){
        elements = _elements;
        curr_index = 0;
    }
     /**
    * -{@code hasNext()}: checks if it is the last element of the container or still there are some other elements.
     * @return Returns a boolean value, true if there are still elements available for iteration, false if it is end.
     */

    public boolean hasNext(){
        return (curr_index < elements.length && elements[curr_index] !=null);
    }
    /**
     * 
     * @throws NoSuchElementException if there are no other element , the element is the last of the container.
     * @return Returns the subsequent element in the JavaSet and JavaVector  class. Note that typecasting is significant.
     */
    public E next(){
        if(!hasNext()){
            throw new NoSuchElementException("No such an element");
        }
        @SuppressWarnings("unchecked")
        E result = (E) elements[curr_index++];
        return result;
    }
}
