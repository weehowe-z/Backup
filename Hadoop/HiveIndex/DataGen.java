package Test;

import java.io.*;
import java.util.Random;

public class DataGen {
	private static final String characters= "1234567890ABCDEFGHIJKLMNOPQRSTUVWXYZ!@#$%^&*()~";

	public static void main(String [] args) throws Exception{
		Writer writer = new BufferedWriter(new OutputStreamWriter(new FileOutputStream("source.txt"), "utf-8"));
		for (int i = 0; i < 2000000; i++) {
			Random rng = new Random();
			writer.write(Integer.toString(i)+'\t'+generateString(rng,characters,20)+'\n');
		}
		writer.close();
	}

	public static String generateString(Random rng, String characters, int length)
	{
	    char[] text = new char[length];
	    for (int i = 0; i < length; i++)
	    {
	        text[i] = characters.charAt(rng.nextInt(characters.length()));
	    }
	    return new String(text);
	}
}


