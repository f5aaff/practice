package org.example;

import java.io.*;


public class Main {

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
            line = line.replaceAll("\\*:","TRUE:");
            line = line.replaceAll("\\s:", "FALSE:");
            //replace address ':' with '_' for meantime
            line = line.replaceAll("\\\\:","_");
            //replace ':' delimiter with valid json delimit
            line = line.replaceAll(":","','");
            //sub ':' back in for '_' placeholder
            line = line.replaceAll("_",":");
            System.out.println(line);
            s.append(stdOutput.readLine());
        }
    }
    return s.toString();
}

    public static void main(String[] args) throws IOException, InterruptedException {
        getOutput();
    //System.out.println(getOutput());
    }
}