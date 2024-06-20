
import java.util.Locale;
import java.util.NoSuchElementException;
import java.util.Scanner;

import MySource.*; // includes the interface package

/**
 * This is the test code of the containers  that I implemented for JavaSet and JavaVector , Note that not every extra implemented  functions
   are used in testing , but you can try them whichever you want.
 * I used some helper functions to make my test implementation clearer and more readible.
 */
public class Test {

    /**
     * My final variables that I used them in test code.
     * 
     *{@code default_input_capacity }  In any case of invalid capacity input of user, default will be used.
     *{@code {number_of_test } YOU CAN CHANGE THE NUMBER OF TEST ON ADDING ELEMENTS(add to vector , add to set functions.) 
     */
    public static final int default_input_capacity = 10;
    public static final int number_of_test = 5; 
     /**
     * Prompts the user to input the capacity and returns a valid integer value.
     *Only integer value is considered, otherwise , default number will be used.Not that  capacity validity also checks at Consructors.
     * @param inp Scanner object for user input.
     * @return The specified capacity, defaulting to 10 if an invalid input is provided.
     */

    static private int input_capacity(Scanner inp) {

        int capacity = default_input_capacity;
        if (inp.hasNextInt()) {
            capacity = inp.nextInt();
            if (capacity < 1) {
                System.err.printf("\nCapacity cannot less than 1. Default capacity ( 10 ) will be used.\n");
                capacity = default_input_capacity;
            }
        } else {
            System.err.printf("\nYou did not enter integer.Default capacity ( 10 ) will be used.\n");
        }
        return capacity;
    }  

    /**
     * Adds a specified number of integers ( number_of_test )  to the given JavaVector.
     *
     * @param myvector The JavaVector to which integers will be added.
     * @param inp      Scanner object for user input.
     */

    static private void add_to_vector(JavaVector<Integer> myvector, Scanner inp) {
        for (int i = 0; i < number_of_test; i++) {
            if (inp.hasNextInt()) {
                int num = inp.nextInt();
                myvector.add(num);
            } else {
                System.err.printf(" (Enter integer value , not other types)! :");
                inp.next();
                i--;
            }
        }
    }
      /**
     * Some  various operations on JavaVector, including creation, addition, removal, and iteration and also other functions if you want.
     * As I said before , you can change the number of test.
     *
     * @param inp Scanner object for user input.
     */
    static private void test_vector(Scanner inp) {
        int capacity; 
        System.out.printf("\n***********************************************************************************************************************\n");
        System.out.printf("\nWelcome to my Container test code.We will start with integer vector first.Please enter a specified capacity : ");
        capacity = input_capacity(inp);
        JavaVector<Integer> my_int_vec1 = new JavaVector<Integer>(capacity);
        System.out.printf("\nThe Vector 1 has been created! \n%s\nPlease enter %d integers to add : ", my_int_vec1, number_of_test);
        add_to_vector(my_int_vec1, inp);
        System.out.println(my_int_vec1);


        System.out.println("Please enter specified capacity for integer Vector 2 : ");
        capacity = input_capacity(inp);

        JavaVector<Integer> my_int_vec2 = new JavaVector<Integer> (capacity);
        System.out.printf("\nThe Vector 2 has been created! \n %s\nPlease enter %d  integers for new Vector 2  for comparing with Vector 1 : ", my_int_vec2, number_of_test);

        add_to_vector(my_int_vec2, inp);

        System.out.println(my_int_vec2);
        String result = (my_int_vec1.equals(my_int_vec2)) ? " equals" : "not equals";
        System.out.printf("The Vector 1 is %s to Vector 2! \n", result);
         boolean isvalid = false;
        while (!isvalid) {
            System.out.print("Please enter an integer to remove it from the Vector 2 : ");
            if (inp.hasNextInt()) {
                // User entered an integer
                int rm = inp.nextInt();
                my_int_vec2.remove(rm);
                System.out.printf("After removing %d , new Vector 2 is   ->>  %s", rm, my_int_vec2);
                isvalid= true; 

            } else {
                // User did not enter an integer
                System.err.println("Invalid input! Enter an integer.");
                inp.next(); // Consume the invalid input
            }
        }
        JavaVector<String> my_str_vec = new JavaVector <String>();
        System.out.printf("\nThe string vector has been created.Please enter %d strings to test : ", number_of_test);
        for (int i = 0; i < number_of_test; i++) {
            String sn = inp.next();
            my_str_vec.add(sn);
        }
        System.out.println(my_str_vec);
        System.out.println("Please enter a string to remove from the string vector : ");
        String toremoves = inp.next();
        my_str_vec.remove(toremoves);
        System.out.printf("The vector after removing %s   ->>  %s", toremoves, my_str_vec);

                              /*  Usage of iterator :  */
        var myiter = my_str_vec.getIterator();
        System.out.printf("\nIterating over the string Vector :\n");
        int i = 0;
        while (myiter.hasNext()) {
            System.out.printf("Element %d : %s \n", i, myiter.next());
            i++;
        }
        my_int_vec1.save_file();
        my_int_vec2.save_file();
        my_str_vec.save_file();
    }
    /**
     * Adds a specified number of double values ( number_of_test ) to the given JavaSet.
     *
     * @param myset The JavaSet to which double values will be added.
     * @param inp   Scanner object for user input.
     */
    static private void add_to_set(JavaSet<Double> myset, Scanner inp) {
        for (int i = 0; i < number_of_test; i++) {

            if (inp.hasNextDouble()) {
                double num = inp.nextDouble();
                myset.add(num);
            } else {
                System.err.printf("(Enter double value ,not other types ):");
                inp.next();
                i--;
            }
        }
    }
        /**
     * Tests some  operations on JavaSet, including creation, addition, removal, and iteration and other optional functions if you want to use them.
     *
     * @param inp Scanner object for user input.
     */

    static private void test_set(Scanner inp) { // set ile basla
        
        System.out.printf("\n***********************************************************************************************************************\n");
        int capacity = default_input_capacity;
        System.out.printf(" Now it is time to test a Set of double type.Please enter a specified capacity : ");
        capacity = input_capacity(inp);
        JavaSet<Double> myset1 = new JavaSet<Double>(capacity);
        System.out.printf("The Set has ben created succesfully : \n %s\nPlease enter %d double number : ", myset1, number_of_test);
        add_to_set(myset1, inp);
        System.out.println(myset1);

        System.out.printf(" Please enter specified capacity for Double Set 2 :");
        capacity = input_capacity(inp);

        JavaSet<Double> myset2 = new JavaSet<Double> (capacity);

        System.out.printf("\nThe Set 2 has been created! \n %s\nPlease enter %d  double number for new Double Set 2  for comparing with Set1 : ", myset2, number_of_test);
        add_to_set(myset2, inp);

        System.out.println(myset2);
        String result = (myset1.equals(myset2)) ? " equals" : "not equals";
        System.out.printf("The Set 1  %s to  Set 2 !\n", result);

      boolean isvalid =false;
      while(!isvalid){
        System.out.printf("Please enter an double to remove it from Set 2 : ");
        if (inp.hasNextDouble()) {
            double toremove = inp.nextDouble();
            myset2.remove(toremove);
            System.out.printf("After removing %.2f , new Set 2 is     ->> %s", toremove, myset2);
            isvalid = true;

        } else {
            System.err.printf("Invalid input! Enter Double type!!");
            inp.next();
        }
    }   

        JavaSet<String> myset3 = new JavaSet<String>();
        System.out.printf("\nThe string Set has been created.Please enter %d strings to test : ", number_of_test);
        for (int i = 0; i < number_of_test; i++) {
            myset3.add(inp.next());
        }
        System.out.println(myset3);
        System.out.println("Please enter a string to remove from the string Set : ");
        String remove_st = inp.next();
        myset3.remove(remove_st);
        System.out.printf("The vector after removing %s , new string Set is     ->> %s", remove_st, myset3);

                            /*Usage of iterator :  */
        System.out.printf("\nIterating over the string Set :\n");
        var myiter = myset3.getIterator();
        int i = 0;
        while (myiter.hasNext()) {
            System.out.printf("Element %d : %s\n", i, myiter.next());
            i++;
        }
        myset1.save_file(); 
        myset2.save_file();
        myset3.save_file();
    }
     /**
     * The main method that initiates the testing of JavaVector and JavaSet classes.
     *
     * @param args Command-line arguments (not used).
     */
    public static void main(String[] args) {

        try(Scanner inp = new Scanner(System.in).useLocale(Locale.US)) {
            test_vector(inp);  

            test_set(inp);
 
        } catch(NoSuchElementException e ) {
              System.err.printf("No such an element exception in remove : %s!\n",e.getMessage());
              e.printStackTrace();
        
        } catch (Exception e) {
            System.err.printf("\nException caught! : %s\n", e.getMessage());

            e.printStackTrace();
            
        } finally {
            System.out.printf("\n Test code has been completed!Note that there other functions that I did not use in my drive code.\n");
        }

    }

}