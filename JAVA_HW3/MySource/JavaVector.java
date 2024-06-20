    package MySource;
    import MyInterface.*;
    import java.io.BufferedWriter;
    import java.io.File;
    import java.io.FileNotFoundException;
    import java.io.FileWriter;
    import java.io.IOException;
    import java.util.InputMismatchException;
    import java.util.NoSuchElementException;
    import java.util.Objects;
    import java.util.Scanner;
    /**
     * My JavaVector generic class represents a vector collectionof Java with various helper methods.
     * Each method is documented with a Javadoc comment describing its functionality
     *  Please read the  javadoc comments for details of any function.
     *  * Generic type parameter:
     * @param <E> the type of elements in the set 
     *
     * @author Yusuf Emre Kilicer / 210104004017
     * @version 1.0
     * @since Java 10.0 , January 18, 2024
     */

    public class JavaVector<E> implements Javacontainer<E>, Cloneable {

        private int capacity;
        private int size;
        private Object[] my_vector;

        /**
         * Default constructor for JavaVector. Initializes an empty vector with the default capacity.
         */
        public JavaVector() {
            size = 0;
            capacity = initial_capacity;
            my_vector = new Object[initial_capacity];
        }

        /**
         * Constructor for JavaVector with a specified initial capacity.
         *
         * @param capacity_ the initial capacity of the vector
         * @throws IllegalArgumentException if the specified initial capacity is less than 1
         */
        public JavaVector(int capacity_) {
            if (capacity_ < 1) throw new IllegalArgumentException("Capacity cannot be less than 1");
            size = 0;
            capacity = capacity_;
            my_vector = new Object[capacity];
        }


        /**
         * Returns an iterator over the elements in the vector.
         *
         * @return an iterator for JavaVector
         */
        @Override  
        public Myiterator<E>  getIterator() {
            return new Myiterator<E>(my_vector);
        }

        /**
         * Setter for capacity
         * @param _capacity the specified value for capacity
         */
        @Override
        public void set_capacity(int _capacity){
            capacity = _capacity;
        }

        /**
         * Adds the specified element to the vector.
         *
         * @param element the element to be added
         */
        @Override  
        public void add(E element) {
            check_capacity();
            my_vector[size++] = element;
        }

        /**
     * Checks the capacity of the vector and doubles it if the current size is about to reach the capacity.
     * If the size plus one equals the capacity, the capacity is doubled and the array is copied to accommodate the increased size.
     */
    private void check_capacity() {

        if (size + 1 == capacity) {
            capacity *= 2;
            copy_array();
        }
    }

    /**
     * Copies the elements from the existing vector to a new vector with twice the capacity.
     * This method is called when the vector needs to be resized to accommodate more elements.
     * The newly created vector becomes the updated vector for the data structure.
     */
    private void copy_array() {
        // Create a new vector with doubled capacity
        @SuppressWarnings("unchecked")
        var  new_vector = (E[]) new Object[capacity];
        // Copy existing elements to the new vector
        var iter = getIterator();
        int i = 0;
        while(iter.hasNext()){
           new_vector[i] = iter.next();
           i++;
        }

        // Update the vector reference to the new vector
        my_vector = new_vector;
    }

        /**
         * Removes the specified element from the vector.
         *
         * @param element the element to be removed
         * @throws NoSuchElementException  with proper warning message if there is no  such an element.
         */

        @Override
        public void remove(E element) {
            int removeindex_at = index_of(element);

            if (removeindex_at != -1) { // -1 means not found;
                for (int i = removeindex_at; i < size - 1; i++) my_vector[i] = my_vector[i + 1];

                my_vector[size - 1] = null;
                size--;
            } else throw new NoSuchElementException( "' " +element+ " '" + " Element could not found in vector to be removed");
        }

        /**
         * Removes the element at the specified index from the vector.
         *
         * @param index the index of the element to be removed
         * @throws IllegalArgumentException if the index is invalid
         */
        @Override
        public void removeElementAt(int index) {

            if (index < 0 || index >= size) throw new IllegalArgumentException("The index is invalid !");
            for (int i = index; i < size - 1; i++) my_vector[i] = my_vector[i + 1];

            my_vector[size - 1] = null;
            size--;
        }

        /**
         * Clears the vector by removing all elements.
         */
        @Override
        public void clear() {
            for (int i = 0; i < size; i++) my_vector[i] = null;
            size = 0;
        }

        /**
         * Returns the first element in the vector.
         *
         * @return the first element
         * @throws NoSuchElementException if the vector is empty
         */
        @Override
        public E firstElement() {
            if (size == 0) throw new NoSuchElementException(); // means no element yet;
            @SuppressWarnings("unchecked")
            E result = (E) my_vector[0];
            return result;
        }

        /**
         * Returns the last element in the vector.
         *
         * @return the last element
         * @throws NoSuchElementException if the vector is empty
         */
        @Override
        public E lastElement() {

            if (isEmpty()) {
                throw new NoSuchElementException("Vector is empty");
            }

            @SuppressWarnings("unchecked")
            E result = (E) my_vector[size - 1]; // to make it clearer returning.
            return result;
        }

        /**
         * Returns the element at the specified index in the vector.
         *
         * @param index the index of the element to be retrieved
         * @return the element at the specified index
         * @throws IndexOutOfBoundsException if the index is invalid
         */
        @Override
        public E get(int index) {

            if (index >= size || index < 0) throw new IndexOutOfBoundsException("Array index out of range: " + index);

            @SuppressWarnings("unchecked")
            E result = (E) my_vector[index];
            return result;
        }

        /**
         * Returns the size of the vector.
         *
         * @return the size of the vector
         */
        @Override
        public int size() {
            return size;
        }

        /**
         * Returns the capacity of the vector.
         *
         * @return the capacity of the vector
         */
        @Override
        public int capacity() {
            return capacity;
        }

        /**
         * Checks if the specified element is present in the vector.
         *
         * @param element the element to search for
         * @return true if the element is found, false otherwise
         */
        @Override
        public boolean is_find(E element) {

            if (isEmpty()) return false;

            var iter = this.getIterator();

            while(iter.hasNext()){
                if(iter.next().equals(element)) return true;
            }
            return false;
            }
        

        /**
         * Checks if the vector is empty.
         *
         * @return true if the vector is empty, false otherwise
         */
        @Override
        public boolean isEmpty() {
            return size == 0;
        }

        /**
         * Returns the index of the specified element in the vector.
         *
         * @param element the element to find the index of
         * @return the index of the element, or -1 if not found
         */
        @Override
        public int index_of(E element) {

            // if I check is_find before the for loop, then there would be 2 for loops which makes my code slower.

            for (int i = 0; i < size; i++) {
                if (my_vector[i].equals(element))
                    return i;
            }
            return -1;
        }

        /**
         * Saves the vector to a file.
         */
       @Override
    public void save_file() {
        String filename = "JavaVector.txt";
        
        try (BufferedWriter outfile = new BufferedWriter(new FileWriter(filename, true))) {
            // Write the content to the file
            for (var element : my_vector) {
                if (element != null) {
                    outfile.write(element.toString() + " ");
                }
            }
            // Flush the buffer to ensure data is written immediately
            outfile.newLine();
            System.out.println("The Vector has been written to the JavaVector.txt successfully in append mode.");
        } catch (IOException e) {
            e.printStackTrace();
        } finally {
            // No need to close anything related to the scanner since you don't have a scanner in this method
        }
    }


        /**
     * Loads the vector from a file specified by the given file name.
     *
     * @param fileName the name of the file from which to load the vector
     */
        @Override
        public void load_file(String fileName) {
            try (Scanner scanner = new Scanner(new File(fileName))) {
                while (scanner.hasNext()) {
                    try {
                        if (scanner.hasNextInt()) {
                            int intValue = scanner.nextInt();
                            add(createElement(Integer.valueOf(intValue)));
                        } else if (scanner.hasNextDouble()) {
                            double doubleValue = scanner.nextDouble();
                            add(createElement(Double.valueOf(doubleValue)));
                        } else {
                            String stringValue = scanner.next();
                            add(createElement(stringValue));
                        }
                    } catch (InputMismatchException e) {
                        System.err.println("Error: Input mismatch.");
                        scanner.next(); // Consume the non-integer value
                    }
                }
            } catch (FileNotFoundException e) {
                System.err.println("Error: File not found.");
            }
        }


        /**
         * Creates an element of type E from the provided value.
         *
         * @param value the value to create the element from
         * @return the created element
         */
        private E createElement(Object value) {
            @SuppressWarnings("unchecked")
            E element = (E) value;
            return element;
        }



        /**
         * Implements the clone method for JavaVector.
         *
         * @return the cloned JavaVector object
         * @throws CloneNotSupportedException if cloning is not supported
         */
        @Override  
        protected Object clone() throws CloneNotSupportedException {
            
            try {

                @SuppressWarnings("unchecked")
                var cloned = (JavaVector<E>) super.clone();
                cloned.my_vector = new Object[this.capacity];
                
                for (int i = 0; i < this.size; i++){
                    cloned.my_vector[i] = this.my_vector[i];

                }
                if(cloned.my_vector ==null) System.err.printf("!");
                return cloned;

            } catch (CloneNotSupportedException e) {
                throw new AssertionError(); // won't ever happen
            }
        }


        /**
         * Checks if the current vector is equal to another JavaVector.
         *
         * @param obj the object to compare
         * @return true if the vectors are equal, false otherwise
         */
        @Override

        public boolean equals(Object obj) {

            if (this == obj) return true;
            if (obj == null || getClass() != obj.getClass()) return false;

            var other = (JavaVector<?>) obj;

            if (size != other.size) return false;

            for (int i = 0; i < size; i++){
             if (!Objects.equals(my_vector[i], other.my_vector[i]))
              return false;
            }
            return true;
        }

        /**
         * Returns a string representation of the vector.
         *
         * @return a string representation of the vector
         */
        @Override
        public String toString() {

            StringBuilder str_builder = new StringBuilder(); // it is mutable and provides more efficiency

            str_builder.append(String.format("Size : %d , Capacity : %d , vector : [ ", size(), capacity()));
            Myiterator<E> myiterator = getIterator();
            while(myiterator.hasNext()){
                str_builder.append(myiterator.next());
                if(myiterator.hasNext()) str_builder.append(" , ");
            }

            str_builder.append(" ]\n");
            return str_builder.toString();
        }

    }
