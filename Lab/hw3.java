package Lab;

import java.io.File;
import java.io.FileWriter;
import java.io.IOException;
import java.util.Scanner;

public class hw3 {
    public static void main(String[] args) {
        File file = new File("Ex3StudentData.csv");
        
        try (FileWriter fw = new FileWriter(file); 
             Scanner input = new Scanner(System.in)) {
            
            fw.write("ID, Name,Phone,Gender,Major\n");
            
            for (int i = 1; i <= 3; i++) {
                System.out.println("\n Entering Details for Student " + i );
                
                System.out.print("Input ID: ");
                int id = input.nextInt();
                input.nextLine(); 

                System.out.print("Input Name: ");
                String name = input.nextLine();

                System.out.print("Input Phone number: ");
                String pn = input.nextLine(); 

                System.out.print("Input Gender: ");
                String gender = input.nextLine();

                System.out.print("Input Major: ");
                String major = input.nextLine();

                fw.write(id + "," + name + "," + pn + "," + gender + "," + major + "\n");
            }
            
            System.out.println("\nData successfully saved to " + file.getName());
            
        } catch (IOException e) {
            System.out.println("An error occurred while handling the file: " + e.getMessage());
        } 
        }
    }
