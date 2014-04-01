package stringTools;

import java.io.FileNotFoundException;
import java.io.PrintWriter;
import java.io.UnsupportedEncodingException;

/**
 * A class which has basic interview questions built as a toolset. Fun!
 * 
 * @author Coleman
 * 
 */
public class StringTool {

	/**
	 * A method which takes a string and returns true if the string is an
	 * anagram, false otherwise.
	 * 
	 * @param s
	 *            The string to check.
	 * @return true if string is an anagram, false otherwise.
	 */
	public static boolean anagramFinder(String s) {
		String sReverse = reverse(s);
		if (sReverse.compareTo(s) != 0) {
			return false;
		}
		return true;
	}

	/**
	 * A method to check if the string contains all unique characters
	 * 
	 * @param s
	 *            The string to check.
	 * @return true if the string contains all unique chars, false otherwise.
	 */
	public static boolean containsUniqueChar(String s) {
		if (s == null)
			return false;
		String letters = "";

		for (int i = 0; i < s.length(); i++) {

			for (int j = 0; j < letters.length(); j++) {
				if (s.charAt(i) == letters.charAt(j)) {
					return false;
				}
			}
			letters += s.charAt(i);
		}
		return true;
	}

	/**
	 * A method which writes a string to a file.
	 * 
	 * @param s
	 *            the string to be written.
	 * @throws FileNotFoundException
	 *             thrown if for some reason the file is not there.
	 * @throws UnsupportedEncodingException
	 *             Thrown if the encoding of the file is not supported.
	 */
	public static void toFile(String s) throws FileNotFoundException,
			UnsupportedEncodingException {
		PrintWriter writer = new PrintWriter("outfile.txt", "UTF-8");
		writer.println(s);
		writer.close();

	}

	/**
	 * Reverses a given string
	 * 
	 * @param s
	 *            the string to be reversed
	 * @return the reversed string
	 */
	public static String reverse(String s) {
		String retVal = "";
		for (int i = s.length() - 1; i >= 0; i--) {
			retVal += s.charAt(i);
		}
		return retVal;

	}

}