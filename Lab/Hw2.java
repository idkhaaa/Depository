package Lab;
import java.io.File;
import java.io.FileWriter;
import java.io.IOException;
import java.util.Random;
public class Hw2 {
    public static void main(String[] args){
        for (int k = 1; k <=100; k++){
            String name = "File" + k + ".txt";

        File f = new File (name);
        try{
            
            Random rand = new Random();
            FileWriter fw = new FileWriter(f);

            for (int i = 0; i < 500; i++){
                int num = rand.nextInt(1000);
                fw.write("Lucky Number:" + num + "\n");
            }
            fw.close();
        } catch (IOException e){
            e.printStackTrace();
        }
    }
}
} 
