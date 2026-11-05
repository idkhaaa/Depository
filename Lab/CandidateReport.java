package Lab;

import java.io.File;
import java.util.ArrayList;
import java.util.Scanner;

class Candidate {
    String gender;
    String group; 
    double math;
    double science; 
    double english; 

    public Candidate(String gender, String group, double math, double science, double english) {
        this.gender = gender;
        this.group = group;
        this.math = math;
        this.science = science;
        this.english = english;
    }

    public double Average() {
        return (math + science + english) / 3;
    }
}

public class CandidateReport {
    public static void main(String[] args) {
        ArrayList<Candidate> candidates = loadCSV("/Users/pimea/Downloads/CandidatePerformanceTest.csv");

        System.out.println("Question 1");
        printBasicStats(candidates);

        System.out.println("\n Question 2");
        printTopPerformersStats(candidates);

        System.out.println("\n Question 3");
        printAllSubjectExcellence(candidates);

        System.out.println("\n Question 4");
        printGroupBreakdown(candidates);
    }

    public static ArrayList<Candidate> loadCSV(String filename) {
        ArrayList<Candidate> list = new ArrayList<>();
        try {
            Scanner fileScanner = new Scanner(new File(filename));
            
            while (fileScanner.hasNextLine()) {
                String line = fileScanner.nextLine();
                if (line.trim().isEmpty()) continue;

                String[] tokens = line.split(",");
                
                if (tokens.length >= 8) {
                    String gender = tokens[1].replace("\"", "").trim();
                    String group = tokens[2].replace("\"", "").trim(); 
    
                    double math = Double.parseDouble(tokens[5].replace("\"", "").trim()); 
                    double science = Double.parseDouble(tokens[6].replace("\"", "").trim()); 
                    double english = Double.parseDouble(tokens[7].replace("\"", "").trim()); 

                    list.add(new Candidate(gender, group, math, science, english));
                }
            }
            fileScanner.close();
        } catch (Exception e) {
            System.out.println("File processing error: " + e.getMessage());
        }
        return list;
    }

    public static void printBasicStats(ArrayList<Candidate> list) {
        int total = list.size();
        int male = 0;
        int female = 0;

        for (int i = 0; i < list.size(); i++) {
            if (list.get(i).gender.equalsIgnoreCase("male")) male++;
            else if (list.get(i).gender.equalsIgnoreCase("female")) female++;
        }

        double malePct = total > 0 ? ((double) male / total) * 100 : 0;
        double femalePct = total > 0 ? ((double) female / total) * 100 : 0;

        System.out.println("Total Candidates: " + total);
        System.out.printf("Male Percentage: %.2f%%\n", malePct);
        System.out.printf("Female Percentage: %.2f%%\n", femalePct);
    }

    public static void printTopPerformersStats(ArrayList<Candidate> list) {
        int points = 0;
        int male = 0;
        int female = 0;

        for (int i = 0; i < list.size(); i++) {
            Candidate c = list.get(i);
            if (c.Average() >= 90) {
                points++;
                if (c.gender.equalsIgnoreCase("male")) male++;
                else if (c.gender.equalsIgnoreCase("female")) female++;
            }
        }

        System.out.println("Candidates with Avg Score >= 90: " + points);
        if (points > 0) {
            System.out.printf("  Male Percentage among them: %.2f%%\n", ((double) male / points) * 100);
            System.out.printf("  Female Percentage among them: %.2f%%\n", ((double) female / points) * 100);
        } else {
            System.out.println("  No candidates reached this score tier.");
        }
    }

    public static void printAllSubjectExcellence(ArrayList<Candidate> list) {
        int score = 0;
        for (int i = 0; i < list.size(); i++) {
            Candidate c = list.get(i);
            if (c.math >= 85 && c.science >= 85 && c.english >= 85) {
                score++;
            }
        }
        System.out.println("Candidates getting score >= 85 for EACH subject: " + score);
    }

    public static void printGroupBreakdown(ArrayList<Candidate> list) {
        ArrayList<String> distinctGroups = new ArrayList<>();
        for (int i = 0; i < list.size(); i++) {
            String g = list.get(i).group;
            if (!distinctGroups.contains(g)) {
                distinctGroups.add(g);
            }
        }

        for (int i = 0; i < distinctGroups.size(); i++) {
            String currentGroup = distinctGroups.get(i);
            int totalInGroup = 0;
            int groupMale = 0;
            int groupFemale = 0;

            for (int j = 0; j < list.size(); j++) {
                Candidate c = list.get(j);
                if (c.group.equalsIgnoreCase(currentGroup)) {
                    totalInGroup++;
                    if (c.gender.equalsIgnoreCase("male")) groupMale++;
                    else if (c.gender.equalsIgnoreCase("female")) groupFemale++;
                }
            }

            System.out.println("Group: " + currentGroup + " -> Total Students: " + totalInGroup);
            if (totalInGroup > 0) {
                double mPct = ((double) groupMale / totalInGroup) * 100;
                double fPct = ((double) groupFemale / totalInGroup) * 100;
                System.out.printf("  Male Percentage: %.2f%% | Female Percentage: %.2f%%\n", mPct, fPct);
            } else {
                System.out.println("  No students found in this group.");
            }
        }
    }
}
