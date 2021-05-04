import java.text.SimpleDateFormat;
import java.util.Date;

public class Logger {

    void logCommand(String ip, String port, String command){
        String timeStampDate = new SimpleDateFormat("yyyy.MM.dd").format(new Date());
        String timeStampTime = new SimpleDateFormat("HH.mm.ss").format(new Date());
        System.out.println("[" + ip + ":" + port + " - " + timeStampDate + "@" + timeStampTime + "]: " + command);
    }
}
