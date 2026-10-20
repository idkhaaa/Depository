package Homework;
import java.util.Scanner;

public class Lab1Ex2 {
     public static void main(String[] args) {
        Scanner sc = new Scanner (System.in);
        int a,b,c;
        System.out.println ("==============================");
        System.out.println ("Welcome to our program");
        System.out.println ("'Quadratic Formula Solver ax^2+bx+c'");
        System.out.println ("==============================");
        System.out.println ("Input a:");
        a = sc.nextInt();
        System.out.println ("Input b:");
        b = sc.nextInt();
        System.out.println ("Input c:");
        c = sc.nextInt();
        System.out.println ("------------------------------------------");

        if (a == 0 && b == 0 && c == 0) {
            System.out.println("The equation has infinite solutions.");
        } else if (a == 0 && b == 0) {
            System.out.println("The equation has no solution.");
        } else if (a == 0) {
            double x = -c / (double)b;
            System.out.println("The root is: " + x);
        } else {}
        double delta = b*b - 4*a*c; 

        if (delta > 0) {
            double x1 = (-b + Math.sqrt(delta)) / (2*a);
            double x2 = (-b - Math.sqrt(delta)) / (2*a);
            System.out.println("The roots are: " + x1 + " and " + x2);
        } 
        if (delta == 0) {
            double x = -b / (2*a);
            System.out.println("The root is: " + x);
        }
        if (delta < 0) {
            System.out.println("The equation has no real roots.");  
        }
    sc.close();


}
}

