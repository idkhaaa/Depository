package Homework;
import java.util.Scanner;

public class Lab1Ex1 {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);

        System.out.print("Enter n: ");
        int n = sc.nextInt();

        if (n < 1 || n > 1000) {
            System.out.println("Invalid input. Please enter a number from 1 to 1000.");
            sc.close();
            return;
        }

        int sum = 0;
        System.out.print("Output: ");

        for (int k = 1000; k >= n; k--) {
            System.out.print(k);
            if (k > n) {
                System.out.print(", ");
            }
            sum += k;
        }
        double avg = (double) sum / (1000 - n + 1);

        System.out.println();
        System.out.println("The sum of 1000 to " + n + " is: " + sum);
        System.out.println("Avg is: " + avg);
        sc.close();
    }

}
