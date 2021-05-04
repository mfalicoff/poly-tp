import org.jetbrains.annotations.Nullable;

import java.io.*;
import java.net.Socket;

public class CommandHandler {
    private Server.ClientHandler server;
    private char sign;
    public CommandHandler(Server.ClientHandler server) {
        // Vérifie quel os est utilisé vu qu'il y a une différence dans les path entre linux et windows
        sign = (System.getProperty("os.name").equals("Linux")) ? '/' : '\\';
        this.server = server;
    }

    boolean handleCommands(
            String command,
            DataOutputStream out,
            DataInputStream in,
            Socket socket,
            File currentDirectory,
            @Nullable String params) throws IOException {

        try {
            String isUplaod = command.contains("upload") ? "upload" : null;
            switch (command){
                case "ls":
                    lsCommand(out, currentDirectory);
                    break;
                case "upload":
                    receiveFile(params, in, out, socket, currentDirectory);
                    break;
                case "download":
                    sendFile(params, out, socket, currentDirectory);
                    break;
                case "cd":
                    assert params != null;
                    cdCommand(params, out, currentDirectory);
                    break;
                case "mkdir":
                    assert params != null;
                    mkdirCommand(out, params, currentDirectory);
                    break;
                case "exit":
                    return false;
                default:
                    return false;

            }
        }catch (Exception e){
            throw e;
        }
        return true;
    }

    private void sendFile(String params, DataOutputStream out, Socket socket, File currentDirectory) throws IOException {
        File file = new File(".", currentDirectory.toString() + sign + params);
        FileInputStream fileInput = new FileInputStream(file);

        int bytes = 0;
        out.writeLong(file.length());
        byte[] buffer = new byte[4*1024];

        while( (bytes = fileInput.read(buffer)) != -1 ){
            out.write(buffer, 0, bytes);
            out.flush();
        }

    }

    private void receiveFile(String params, DataInputStream in, DataOutputStream out, Socket socket, File currentDirectory) throws IOException {
        FileOutputStream fileOutputStream = new FileOutputStream(currentDirectory.toString() + sign + params);
        in = new DataInputStream(socket.getInputStream());

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

        File isFileCreated = new File(".", currentDirectory.toString() + sign + params);
        if(isFileCreated.canRead()){
            out.writeUTF("Le fichier " + params + " a bien ete cree\n");
            out.writeUTF("end");
        }else{
            throw new FileNotFoundException("le fichier n'exsite pas\n");
        }
    }

    void lsCommand(DataOutputStream out, File currentDirectory) throws IOException {

        StringBuilder response = new StringBuilder();

        File[] filesList = currentDirectory.listFiles();

        for(File f : filesList){
            if(f.isDirectory())
                response.append("[Folder] ").append(f.getName()).append("\n");
            if(f.isFile()){
                response.append("[File] ").append(f.getName()).append("\n");
            }
        }
        out.writeUTF(response.toString());
        out.writeUTF("end");
    }

    private void cdCommand(String folderName, DataOutputStream out, File currentDirectory) throws IOException {
        // curDirTemp permet de vérifier si le dossier existe
        File curDirTemp = new File(currentDirectory.toString()+sign+folderName);
        if (folderName.equals("..")){
            int index = currentDirectory.toString().lastIndexOf(sign);
            // Impossible de sortir du dossier Root pour s'assurer de l'encapsulation
            if (currentDirectory.toString().substring(index + 1).equals("Root")){
                out.writeUTF("You cannot go back \n");
                out.writeUTF("You are in the folder Root. \n");
            }
            else{
                currentDirectory = new File(currentDirectory.toString().substring(0, currentDirectory.toString().lastIndexOf(sign)));
                this.server.setDir(currentDirectory);
                out.writeUTF("You are in the folder " + currentDirectory.toString().substring(currentDirectory.toString().lastIndexOf(sign) + 1) + ".\n");
            }
        }
        else if (curDirTemp.exists()){
            currentDirectory = curDirTemp;
            this.server.setDir(curDirTemp);
            out.writeUTF("You are in the folder " + folderName + ".\n");
        }
        else{
            out.writeUTF("The folder doesn't exist.\n");
        }
        out.writeUTF("end");
    }

    private void mkdirCommand(DataOutputStream out, String name, File currentDirectory) throws IOException
    {
        File temp = new File(currentDirectory.toString()+sign+name);
        boolean bool=temp.mkdir();

        if(bool){
            out.writeUTF("Directory created successfully\n");
        }else{
            out.writeUTF("Sorry couldn’t create specified directory\n");
        }
        out.writeUTF(temp.toString() + '\n');
        out.writeUTF("end");
    }
}
