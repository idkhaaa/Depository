package Lab;

import java.io.File;
import java.io.FileWriter;
import java.util.ArrayList;
import java.util.Collections;
import java.util.Comparator;
import java.util.Scanner;

public class Ex5Lab4 {
    public static void main(String[] args) {
        File file = new File("Ex3StudentData.csv");
        ArrayList<String> studentList = new ArrayList<>();

        try {
            Scanner fileScanner = new Scanner(file);
            
            if (fileScanner.hasNextLine()) {
                fileScanner.nextLine();
            }

            while (fileScanner.hasNextLine()) {
                String line = fileScanner.nextLine();
                if (!line.trim().isEmpty()) {
                    studentList.add(line);
                }
            }
            fileScanner.close();
            System.out.println("Loaded existing data from file.");

        } catch (Exception e) {
            System.out.println("Error reading the file.");
        }

        studentList.add("104, Smith,098765432,Female,IT");
        studentList.add("105, Taylor,087654321,Male,CS");
        studentList.add("106, Jones,076543210,Male,Business");
        System.out.println("Added 3 new team members to the list.");

        Collections.sort(studentList, new Comparator<String>() {
            @Override
            public int compare(String line1, String line2) {

                String name1 = line1.split(",")[1].trim();
                String name2 = line2.split(",")[1].trim();
                
                return name1.compareToIgnoreCase(name2);
            }
        });
        System.out.println("Sorted the list alphabetically by student names.");

        try {
            FileWriter fw = new FileWriter(file);
            
            fw.write("ID,Name,Phoen,Gender,Major\n");
       
            for (int i = 0; i < studentList.size(); i++) {
                fw.write(studentList.get(i) + "\n");
            }
            
            fw.close();
            System.out.println("Successfully saved sorted data back to " + file.getName());

        } catch (Exception e) {
            System.out.println("Error writing back to the file.");
        }
    }
}
