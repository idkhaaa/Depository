package Homework;
import java.util.Scanner;

public class Lab1Ex3 {
     public static void main(String[] args) {
        Scanner in = new Scanner (System.in);
        System.out.println("Input 5 numbers:");
      
        int[] inputtedNumber = new int[5];

        for (int num = 0; num < 5; num += 1) {
            inputtedNumber[num] = in.nextInt();
        }

        System.out.println("Input:");
        for (int num = 0; num < 5; num += 1) {
            System.out.println(inputtedNumber[num]);
        }

        int maxNum = Integer.MIN_VALUE;
        int minNum = Integer.MAX_VALUE;

        for (int checkNum = 0; checkNum < 5; checkNum += 1) {
            maxNum = Math.max(maxNum, inputtedNumber[checkNum]);
            minNum = Math.min(minNum, inputtedNumber[checkNum]);
        }

        System.out.println("Output:");
        System.out.println("The maximum number: " + maxNum);
        System.out.println("The minimum number: " + minNum);
         in.close();
     }
}
