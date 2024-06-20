       
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
     * My JavaSet generic class represents a Set collection of Java with various helper methods.
     * Each method is documented with a Javadoc comment describing its functionality.
     * Please read the Javadoc comments for details of any function.
     * Generic type parameter:
     * @param <E>  the type of elements in the set
     *
     * @author Yusuf Emre Kilicer / 210104004017
     * @version 1.0
     * @since Java 10.0, January 18, 2024
     */
        public class JavaSet<E> implements Javacontainer<E> , Cloneable{

            private int capacity;
            private int size;
            private Object[] container;

            /**
             * Constructs an empty JavaSet with the default initial capacity which is defined in JavaContainer inteface.
             */
            public JavaSet(){
                size = 0;
                capacity = initial_capacity;
                container = new Object[initial_capacity];
            }
            /**
             * Constructs an empty JavaSet with the specified initial capacity.
             * 
             * @param _capacity the initial capacity of the set that user determines.
             * @throws IllegalArgumentException if the specified initial capacity is less than 1 which is invalid.
             */
            public JavaSet(int _capacity){
                if(_capacity <1 ) throw new IllegalArgumentException("Capacity cannot less than 1");

                size = 0;
                this.capacity = _capacity;
                container = new Object[capacity];
            }

      
        
        /**
        * Return the iterator over the set elements.
        @return an iterator for javaset.
        */
        @Override 
        public Myiterator<E> getIterator() {
        return new Myiterator<E>(container);
        }
        /**
         * Setter for capacityi
         * @param _capacity the specified value for capacity
         */
        @Override
        public void set_capacity(int _capacity){
            capacity = _capacity;
        }

            /**
             * Add method adds element to the Setcontainer if it is not used before.
             * Using  isfind method before add to check if it is already valid.
             *
             * @param element the element to be added to the set
             */
            @Override  
            public void add(E element){

                if(is_find(element)) {
                    System.err.print(element + " is already exist !\n"); //just wanted to not throwing exception , warning the user.
                    return;
                }
                check_capacity(); 
                container[size++] = element;
            }

            /**
             * Checks if the capacity of the container needs to be increased and performs the necessary actions.
             */
            private void check_capacity(){

                if(size+1 == capacity){    
                capacity *=2;   
                copy_array(); 
            } 
        }  
            /**
                * copies the content of array.I did not want to use ready deepcopy method from java . I create my own deep copy.
                *I create a temp copied object array , then copy it.
                */
            
            private  void copy_array() {
                @SuppressWarnings("unchecked")
                var  copied = (E[]) new  Object[capacity];
                var iter = getIterator();
                int ind=0;
                while(iter.hasNext()){
                    copied[ind] = iter.next();
                    ind++;
                }
                container = copied;
            }

        /**
         * It removes the element which is send as parameter of the function.
        @param element element to be removed from set.
        */
        @Override  
        public void remove(E element){
            
            if(!is_find(element) || isEmpty()) throw new NoSuchElementException("' " +element+ " '"+"Element could not found to be removed." );

            int removalindex =index_of(element);
            for(int i = removalindex ; i< size-1 ; i++)  container[i] =container[i+1];
            container[size-1 ] = null;
            size--;
        
            }
            
        
        /**
         * Removes the element at the specified index from the set.
         *
         * @param index the index of the element which will be removed
         * @throws IndexOutOfBoundsException if the index is out of range
         * @throws NoSuchElementException if the set is already empty
         */
        
        @Override   
        public void removeElementAt(int index) {

        if(index < 0 || index >=size) throw new IndexOutOfBoundsException("Array index out of range " + index );
        if(isEmpty()) throw new NoSuchElementException("The set is already empty");
        for(int i = index ; i < size-1 ; i++) container[i]= container[i+1];
        container[size-1] = null;
        size--;
        }
        /**
         * Returns the first element in the set.
         *
         * @return the first element
         * @throws NoSuchElementException if the set is empty
         */
        @Override 
        public E firstElement(){

            if(isEmpty()) throw new NoSuchElementException("Set is empty");
            @SuppressWarnings("unchecked")
            E result = (E) container[0];
            return result;
        
        }
        /**
         * Returns the last element in the set.
         *
         * @return the last element
         * @throws NoSuchElementException if the set is empty
         */
        @Override 
        public E lastElement(){
        if(isEmpty()) throw new NoSuchElementException("Set is empty");
        @SuppressWarnings("unchecked")
        E result = (E) container[size-1];
        return result;
        }
        /**
         * Returns the element at the specified index in the set.
         *
         * @param index the index of the element to be retrieved
         * @return the element at the specified index
         * @throws IndexOutOfBoundsException if the index is invalid value.
         */
        @Override 
        public E get(int index){

            if(index >=size || index <0)   throw new IndexOutOfBoundsException("Array index out of range: " + index);

            @SuppressWarnings("unchecked")
            E result  =(E)container[index];
            return result;
        }


        /**
         * Returns the current capacity of the set.
         * @return current capacity of the set.
         */
        @Override 
        public int capacity() {
            return capacity;
        }

        /**
             * Returns the current size of the set.
             * @return current size of the set.
             */

            @Override   
            public int size(){  return  size; } 
        /**
         * Clears the set , assignes size to 0.
         * @throws NoSuchElementException if the set is already empty.
         */

        @Override 
        public void clear() {

            if(isEmpty()) throw new NoSuchElementException("The set is already empty");
       for(int i = 0 ; i < size ; i++) container[i] = null;
            size = 0;
        }

            /**
             * Checks if the specified element is exist in the set.
             * @param element the element to be cheched if it is already exist.
             * @return true if the element is found, false if it is not found.
             */
        @Override   
        public boolean is_find(E element){
            
            if(isEmpty()) return false;
            var iter = this.getIterator();

            while(iter.hasNext()){
                if(iter.next().equals(element)) return true;
            }
            return false;
            }


        /**
         * Returns the index of the specified element in the set.
         *
         * @param element the element to find the index of
         * @return the index of the element, or -1 if not found
         */
        @Override 
        public int index_of(E element){

    int index = 0;
        var iter = getIterator();
        while(iter.hasNext()){
            if(iter.next().equals(element)){
            return index;
            }
            index++;
        }
        
        return -1;
        }

        /**
         * Checks if the set is empty.
         *
         * @return true if the set is empty, false otherwise
         */
        @Override 
        public boolean isEmpty(){  return size==0;  }

        /**
         * Saves set to the file.
         */
        @Override 

        public void save_file(){

            String filename = "JavaSet.txt";

        try (BufferedWriter outfile = new BufferedWriter(new FileWriter(filename ,true))) {
                // Write the content to the file
            for(var element : container){

                if (element != null) {
                    outfile.write(element.toString() + " ");
                }
            }
             outfile.newLine();
                System.out.println("The set has been written to the JavaSet.txt successfully in append mode.");
            } catch (IOException e) {
                e.printStackTrace();
            } finally {
                
            }


        }

        /**
         * Loads the set from the file with the specified file name as parameter..
         *
         * @param fileName the name of the file to load the set from
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
             * Checks if the current set is equal to another JavaSet.
             *
             * @param obj the object to compare
             * @return true if the sets are equal, false otherwise
             */
        @Override 
        public boolean equals(Object obj){
        
            
            if(this == obj)return true; 

            if(obj == null|| getClass() !=obj.getClass()) return false;
            
            var other = (JavaSet<?>) obj;

            if(other.size != size) return false;


            //THE PLACE DOESNOT HAVE TO BE SAME , JUST CHECKING IF IT EXISTS OR NOT
            for(int i = 0 ; i< size ; i++){
                boolean is_exist = false;
            for(int j = 0 ; j< size ; j++){
                if(Objects.equals(container[i], other.container[j])){
                     is_exist = true;
                     break;
                }
            }
             if( !is_exist ) return false;
        }

                return true;
        }
   /**
     * Implement deep copy of the JavaSet Using Cloneable interface.
     *
     * @return the cloned JavaSet object.
     * @throws CloneNotSupportedException if cloning is not supported
     */
    @Override  
  protected Object clone() throws CloneNotSupportedException {
                
            try {

                @SuppressWarnings("unchecked")
                var cloned = (JavaSet<E>) super.clone();
                cloned.container = new Object[this.capacity];
                
                for (int i = 0; i < this.size; i++){
                    cloned.container[i] = this.container[i];

                }
                if(cloned.container ==null) System.err.printf("!");
                return cloned;

            } catch (CloneNotSupportedException e) {
                throw new AssertionError(); // won't ever happen
            }
        }



        /**
         * It converts set to String format.
         * 
         * @return a string representation of the set
         */
        @Override 
        public String toString(){
            StringBuilder str_builder  = new StringBuilder();
            str_builder.append(String.format("Size : %d , Capacity : %d , Set: [ ",size() , capacity()));

            Myiterator<E> myiterator = getIterator();
            while(myiterator.hasNext()){
                str_builder.append(myiterator.next());
                if(myiterator.hasNext()) str_builder.append(" , ");
            }

            str_builder.append(" ]\n");
            return str_builder.toString();

        }

        }
