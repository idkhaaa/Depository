package Homework;
import java.util.Scanner;

public class Lab1Ex5 {
    public static boolean isPrime(int num) {
        if (num <= 1) {
            return false;
        }

        for (int i = 2; i <= Math.sqrt(num); i++) {
            if (num % i == 0) {
                return false;
            }
        }
        return true;
    }

    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        System.out.print("Input n: ");
        int testNum = sc.nextInt();

        System.out.println("Prime numbers between 2 and " + testNum + ":");

        for (int num = 2; num <= testNum; num++) {
            if (isPrime(num)) {
                System.out.print(num + " ");
            }
        }

        System.out.println();
        sc.close();
    }
}