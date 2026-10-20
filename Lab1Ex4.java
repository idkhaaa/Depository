package Homework;
import java.util.Scanner;


public class Lab1Ex4 {
    public static void main(String[] args) {
        Scanner sc = new Scanner (System.in);
        int yyyy, mm, dd;
        System.out.println("Input your birth date:");
        System.out.println("Input Year:");
        yyyy = sc.nextInt();
        System.out.println("Input Month:");
        mm = sc.nextInt();
        System.out.println("Input Day:");
        dd = sc.nextInt();

        System.out.println(yyyy + "-" + mm + "-" +dd + " (Year/Month/Day)");
        if (yyyy < 1900 & yyyy > 2026) {
        System.out.println("Output: Invalid");
        } else if (mm < 1 & mm > 12) {
        System.out.println("Output: Invalid");
        }else if (dd < 1 & dd > 31) {
        System.out.println("Output: Invalid");
        } else {
        System.out.println("Output: Valid");
        sc.close();
        }
    
    }
}