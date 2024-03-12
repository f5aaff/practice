package org.example;

import java.io.*;
import java.util.Arrays;


public class Main {

    private static String[] readFile(String file) throws IOException {

        try (BufferedReader reader = new BufferedReader(new FileReader(file))) {
            String line = null;
            StringBuilder stringBuilder = new StringBuilder();
            StringBuilder unedited = new StringBuilder();
            String ls = System.getProperty("line.separator");
            while ((line = reader.readLine()) != null) {
                unedited.append(line);
                unedited.append(ls);
                line = formatLineToJson(line);
                stringBuilder.append(line);
            }
            return new String[]{unedited.toString() , stringBuilder.toString()};
        }
    }
    public static String formatToJson(String raw) {
        if (raw != null) {
            String[] splitRaw = raw.split("\n");
            raw = "{'" + raw + "',}\n";
            //replace connected '*' with TRUE, blank with FALSE
            raw = raw.replaceAll("\\*:","TRUE:")
                    .replaceAll("\\s:", "FALSE:")
                    //replace address ':' with '@' for meantime
                    .replaceAll("\\\\:","@")
                    //replace ':' delimiter with valid json delimit
                    .replaceAll(":","','")
                    //sub ':' back in for '_' placeholder
                    .replaceAll("@",":");

            return raw;
        }
        return null;
    }

    public static String formatLineToJson(String line) {
        if (line != null) {
            line = "{'" + line + "',}\n";
            //replace connected '*' with TRUE, blank with FALSE
            line = line.replaceAll("\\*:","TRUE:")
                    .replaceAll("\\s:", "FALSE:")
                    //replace address ':' with '@' for meantime
                    .replaceAll("\\\\:","@")
                    //replace ':' delimiter with valid json delimit
                    .replaceAll(":","','")
                    //sub ':' back in for '_' placeholder
                    .replaceAll("@",":");

            return line;
        }
        return null;
    }


public static String getOutput() throws IOException, InterruptedException {
    Runtime rt = Runtime.getRuntime();
    String[] commands = {"nmcli","-t","device", "wifi"};
    Process proc = rt.exec(commands);
    proc.waitFor();
    BufferedReader stdOutput = new BufferedReader(
            new InputStreamReader(proc.getInputStream()));
    StringBuilder s = new StringBuilder();
    while ((stdOutput.readLine())!= null) {
        String line = stdOutput.readLine();
        if (line != null) {

            line = "'" + line + "'";
            //replace connected '*' with TRUE, blank with FALSE
            line = line.replaceAll("\\*:","TRUE:")
                    .replaceAll("\\s:", "FALSE:")
                    //replace address ':' with '@' for meantime
                    .replaceAll("\\\\:","@")
                    //replace ':' delimiter with valid json delimit
                    .replaceAll(":","','")
                    //sub ':' back in for '_' placeholder
                    .replaceAll("@",":");






            System.out.println(line);
            s.append(stdOutput.readLine());
        }
    }
    return s.toString();
}

    public static void main(String[] args) throws IOException, InterruptedException {
    String[] res = readFile("thisIsATestFile");
    String raw = res[0];


    }
}