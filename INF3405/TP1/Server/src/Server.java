import java.io.*;
import java.net.InetAddress;
import java.net.InetSocketAddress;
import java.net.ServerSocket;
import java.net.Socket;
import java.util.ArrayList;
import java.util.Arrays;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.text.SimpleDateFormat;
import java.util.Date;
import java.util.Scanner;


public class Server {

	
	/*
		une thread qui s'en charge de traiter le demande de chaque client sur un socket
	 */
	private static ServerSocket listener;
	public static void main(String[] args) throws Exception
	{
		int clientNumber=0;
		String serverAddress = "";
		int serverPort = 0;

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
			serverPort = scan.nextInt();

			if (serverPort >= 5000 && serverPort <= 5050)
				validPort = true;
		}

		listener = new ServerSocket();
		listener.setReuseAddress(true);
		InetAddress serverIP =InetAddress.getByName(serverAddress);
		listener.bind(new InetSocketAddress(serverIP,serverPort));
		System.out.format("The Server is running on %s:%d%n", serverAddress, serverPort);

		try
		{
			while(true)
			{
				new ClientHandler(listener.accept(), clientNumber++).start();
			}
		}
		finally
		{
			listener.close();
		}

	}

	static class ClientHandler extends Thread {

		private Socket socket;
		private int clientNumber;
		private Logger logger;
		private CommandHandler commandHandler;
		private File curDir = new File("./Root");

		public ClientHandler(Socket socket, int clientNumber){
			this.socket = socket;
			this.clientNumber = clientNumber;
			this.logger = new Logger();
			this.commandHandler = new CommandHandler(this);
			curDir.mkdir();
			System.out.println("New connection with client# " + clientNumber + " at " + socket);
		}

		public void run(){
			try{
				//creation canal sortant pour send messages
				DataOutputStream out = new DataOutputStream(socket.getOutputStream());

				//send to client
				out.writeUTF("Hello from server - you are client# " + clientNumber);
				while(readCommands()){}
				socket.close();
				System.out.println("Server terminated");

			} catch (IOException e) {
				System.out.println("Error handling client# " + clientNumber + ": " + e);
			}

			finally {
				try{
					socket.close();
				} catch (IOException e){
					System.out.println("couldn't close socket");
				}

				System.out.println("Connection with client# " + clientNumber + " closed");
			}
		}


		private boolean readCommands() throws IOException {

			DataInputStream in = new DataInputStream(socket.getInputStream());
			DataOutputStream out = new DataOutputStream(socket.getOutputStream());
			InetSocketAddress sockAddr = (InetSocketAddress)socket.getRemoteSocketAddress();

			String input = in.readUTF();
			ArrayList<String> commands = new ArrayList<String>(Arrays.asList(input.split(" ")));
			if(commands.size() == 1) {commands.add(null);}

			logger.logCommand(sockAddr.getAddress().toString(), Integer.toString(sockAddr.getPort()), input);

			try{
				this.commandHandler.handleCommands(
						commands.get(0)
						, out
						, in
						, this.socket
						, this.curDir
						, commands.get(1)
				);
			}catch(Exception e){
				System.out.println(e.getMessage());
			}
			return true;
		}

		public void setDir(File dir){
			this.curDir = dir;
		}

	}
	//Provient du site web https://stackoverflow.com/Questions/5667371/validate-ipv4-address-in-java
	public static boolean validate(final String ip)
	{
		String PATTERN = "^((0|1\\d?\\d?|2[0-4]?\\d?|25[0-5]?|[3-9]\\d?)\\.){3}(0|1\\d?\\d?|2[0-4]?\\d?|25[0-5]?|[3-9]\\d?)$";

		return ip.matches(PATTERN);
	}


	
}
