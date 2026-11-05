package Lab;
import java.io.File;
import java.io.FileWriter;
import java.io.IOException;
import java.util.Random;


public class Hw1 {
    public static void main(String[] args) {
    File f = new File ("LuckyNumber.csv");
    try {
        Random rand = new Random();
        FileWriter fw = new FileWriter (f, true);
        for (int i = 0; i < 500; i++){
            int num = rand.nextInt(1000);
            fw.write("Lucky Number:" + num + "\n");
          
        }
         fw.close();
    } catch (IOException e) {
        e.printStackTrace();
     }
    }
}
