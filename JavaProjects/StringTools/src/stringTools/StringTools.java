package stringTools;

/**
 * written in 20 minutes.
 * 
 * A command-line program which takes arguments of the format [switch][string] and does various things to the string based on the switch
 * supported switches: -u: checks to see if the string is all unique chars
 *                     -a: checks if the string is an anagram
 *                     -f: writes the string to a file
 *                     -h: reads a short help message and terminates.
 * @author AMNESIAC
 *
 */
public class StringTools {

	public static void main(String[] args) {
		if (args.length >= 1) {

			if (args[0].compareTo("-h") == 0) {
				System.out
						.println("Command Line args are formatted [switch][string]");
				return;
			}
			if (args.length == 2) {
				if (args[0].compareTo("-u") == 0) {
					StringTool.containsUniqueChar(args[1]);
					return;
				}
				if (args[0].compareTo("-a") == 0) {
					StringTool.anagramFinder(args[1]);
					return;
				}

				if (args[0].compareTo("-f") == 0) {

					try {
						StringTool.toFile(args[1]);
						return;
					} catch (Exception e) {
						System.out
								.println("Error: An error occurred while writing the file");
						return;
					}

				}
			}
		}
		System.out
				.println("Error: Command Line args are formatted [switch][string]");
		return;
	}

}