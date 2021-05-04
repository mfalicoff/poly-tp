import java.io.*;
import java.net.Socket;
import java.util.Scanner;


public class Client
{
	private static Socket socket;

	public static void main(String[] args) throws Exception
	{
		String serverAddress = "xxx.xxx.xxx.xxx";
		int port = -1;
		boolean addressValid = false;
		boolean validPort = false;
		Scanner scan = new Scanner(System.in);

		while(!addressValid)
		{
			System.out.println("Enter the server address:");
			scan = new Scanner(System.in);
			serverAddress = scan.nextLine();

			addressValid = validate(serverAddress);
		}

		while (!validPort)
		{
			System.out.println("Enter the server port (between 5000 and 5050):");
			port = scan.nextInt();

			if (port >= 5000 && port <= 5050)
				validPort = true;
		}

		socket = new Socket(serverAddress, port);

		System.out.println("The server is running on " + serverAddress + ":" + port);

		DataInputStream in = new DataInputStream(socket.getInputStream());
		String message = in.readUTF();
		System.out.println(message);
		while(inputCommands()){}
		socket.close();
		System.out.println("Sessions closed");
	}

	private static boolean inputCommands() throws IOException {

		Scanner input = new Scanner(System.in);
		String command = input.nextLine();

		if(command.equals("exit")){
			return false;
		} else if(command.contains("upload")){
			sendFile(command.split(" ")[1]);
		} else if(command.contains("download")){
			DataOutputStream out = new DataOutputStream(socket.getOutputStream());
			out.writeUTF(command);
			receiveFile(command.split(" ")[1]);
		}
		else {
			DataOutputStream out = new DataOutputStream(socket.getOutputStream());
			out.writeUTF(command);
			while(readResponse()){}
		}
		return true;
	}

	private static void receiveFile(String filename) throws IOException{
		FileOutputStream fileOutputStream = new FileOutputStream(filename);
		DataInputStream in = new DataInputStream(socket.getInputStream());

		long size = in.readLong();
		byte[] buffer = new byte[4*1024];
		int bytes = 0;

		// ici on lit 4kb a la fois tant que le buffer (4kb) soit plus grand que le size du fichier, si le buffer
		// est plus petit que le fichier, on est rendu a la fin du fichier
		while (size > 0 && (bytes = in.read(buffer, 0, (int)Math.min(buffer.length, size))) != -1) {
			fileOutputStream.write(buffer,0,bytes);
			size -= bytes;
		}
		fileOutputStream.close();

		File isFileCreated = new File(".", filename);
		if(isFileCreated.canRead()){
			System.out.println("Le fichier " + filename + " a bien ete telecherge");
		}else{
			throw new FileNotFoundException("le fichier n'exsite pas");
		}
	}

	private static void sendFile(String filename) throws IOException {

		File file = new File(".", filename);
		FileInputStream fileInput = new FileInputStream(file);

		DataOutputStream out = new DataOutputStream((socket.getOutputStream()));
		out.writeUTF("upload " + filename);
		int bytes = 0;
		out.writeLong(file.length());
		byte[] buffer = new byte[4*1024];

		while( (bytes = fileInput.read(buffer)) != -1 ){
			out.write(buffer, 0, bytes);
			out.flush();
		}
		while(readResponse()){}
	}
	private static boolean readResponse() throws IOException {
		DataInputStream in = new DataInputStream(socket.getInputStream());
		String response = in.readUTF();
		if(response.equals("end")){
			return false;
		}else{
			System.out.print(response);
		}
		return true;
	}

	//Provient du site web https://stackoverflow.com/Questions/5667371/validate-ipv4-address-in-java
	public static boolean validate(final String ip)
	{
		String PATTERN = "^((0|1\\d?\\d?|2[0-4]?\\d?|25[0-5]?|[3-9]\\d?)\\.){3}(0|1\\d?\\d?|2[0-4]?\\d?|25[0-5]?|[3-9]\\d?)$";

		return ip.matches(PATTERN);
	}
}
