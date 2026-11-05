package Lab;

import java.io.File;
import java.util.ArrayList;
import java.util.Scanner;

public class ex4java {
    public static void main(String[]args) {
    File file = new File("Ex3StudentData.csv");
    ArrayList<String> studentList = new ArrayList<>();
    

        try {
            Scanner fileScanner = new Scanner(file);
            if (fileScanner.hasNextLine()) {
                fileScanner.nextLine();
            }
        
        while (fileScanner.hasNextLine()) {
                String line = fileScanner.nextLine();
                studentList.add(line);
           } 
    
        fileScanner.close();
    } catch (Exception e) {
        System.out.println("Error reading the file.");
    }


    System.out.println("Student Data:");
    for (int i = 0; i<studentList.size();i++){
        String data = studentList.get(i);
        System.out.println(data);
        }
    }
}



