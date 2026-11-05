package Lab;

import java.io.File;
import java.io.FileWriter;
import java.util.ArrayList;
import java.util.Scanner;

// Renamed class ensures Java drops old compiler definitions completely
class GroupCandidate {
    String id;
    String gender;
    String group; 
    String education;
    String testPrep;
    double math;
    double english; 
    double computer; 
    double totalScore;
    double averageScore;

    public GroupCandidate(String id, String gender, String group, String education, String testPrep, 
                          double math, double english, double computer, double totalScore, double averageScore) {
        this.id = id;
        this.gender = gender;
        this.group = group;
        this.education = education;
        this.testPrep = testPrep;
        this.math = math;
        this.english = english;
        this.computer = computer;
        this.totalScore = totalScore;
        this.averageScore = averageScore;
    }

    public String toCsvRow() {
        return id + "," + gender + "," + group + "," + education + "," + testPrep + "," + 
               math + "," + english + "," + computer + "," + totalScore + "," + averageScore + "\n";
    }
}

public class GroupSplitterReport {
    public static void main(String[] args) {
        ArrayList<GroupCandidate> candidates = loadCSV("/Users/pimea/Downloads/CandidatePerformanceTest.csv");

        String[] targetGroups = {"group A", "group B", "group C", "group D"};

        System.out.println("Report");
        for (int i = 0; i < targetGroups.length; i++) {
            String currentGroup = targetGroups[i];
            String outputFileName = currentGroup.replace(" ", "") + ".csv";
            writeGroupFileWithSummary(candidates, currentGroup, outputFileName);
        }
    }

    public static ArrayList<GroupCandidate> loadCSV(String filename) {
        ArrayList<GroupCandidate> list = new ArrayList<>();
        try {
            Scanner fileScanner = new Scanner(new File(filename));
            
            if (fileScanner.hasNextLine()) fileScanner.nextLine(); // Skip description line
            if (fileScanner.hasNextLine()) fileScanner.nextLine(); // Skip header tokens

            while (fileScanner.hasNextLine()) {
                String line = fileScanner.nextLine();
                if (line.trim().isEmpty()) continue;

                String[] tokens = line.split(",");
                
                if (tokens.length >= 10) {
                    String id = tokens[0].replace("\"", "").trim();
                    String gender = tokens[1].replace("\"", "").trim();
                    String group = tokens[2].replace("\"", "").trim();
                    String education = tokens[3].replace("\"", "").trim();
                    String testPrep = tokens[4].replace("\"", "").trim();
                    
                    double math = Double.parseDouble(tokens[5].replace("\"", "").trim()); 
                    double english = Double.parseDouble(tokens[6].replace("\"", "").trim()); 
                    double computer = Double.parseDouble(tokens[7].replace("\"", "").trim()); 
                    double total = Double.parseDouble(tokens[8].replace("\"", "").trim()); 
                    double average = Double.parseDouble(tokens[9].replace("\"", "").trim()); 

                    list.add(new GroupCandidate(id, gender, group, education, testPrep, math, english, computer, total, average));
                }
            }
            fileScanner.close();
        } catch (Exception e) {
            System.out.println("File processing error: " + e.getMessage());
        }
        return list;
    }

    public static void writeGroupFileWithSummary(ArrayList<GroupCandidate> list, String groupTarget, String outputName) {
        int totalInGroup = 0;
        int groupMales = 0;
        int groupFemales = 0;

        try (FileWriter fw = new FileWriter(outputName)) {
            fw.write("ID,gender,group,Education,test preparation course,Math,English,Computer,Total,Average\n");

            for (int i = 0; i < list.size(); i++) {
                GroupCandidate c = list.get(i);
                if (c.group.equalsIgnoreCase(groupTarget)) {
                    fw.write(c.toCsvRow());
                    totalInGroup++;
                    if (c.gender.equalsIgnoreCase("male")) groupMales++;
                    else if (c.gender.equalsIgnoreCase("female")) groupFemales++;
                }
            }

            double mPct = totalInGroup > 0 ? ((double) groupMales / totalInGroup) * 100 : 0;
            double fPct = totalInGroup > 0 ? ((double) groupFemales / totalInGroup) * 100 : 0;

            System.out.println("Group: " + groupTarget + " -> Total Students: " + totalInGroup);
            System.out.printf("  Male Percentage: %.2f%% | Female Percentage: %.2f%%\n", mPct, fPct);

            fw.write("\n"); 
            fw.write(",,,,,,,,,SUMMARY METRICS\n");
            fw.write(",,,,,,,,,Total Students," + totalInGroup + "\n");
            fw.write(String.format(",,,,,,,,,%% Male,%.2f%%\n", mPct));
            fw.write(String.format(",,,,,,,,,%% Female,%.2f%%\n", fPct));
            
            System.out.println("  -> Saved to: " + outputName);

        } catch (Exception e) {
            System.out.println("Error writing file: " + e.getMessage());
        }
    }
}
