package org.example;

import com.github.alexdlaird.ngrok.NgrokClient;
import com.github.alexdlaird.ngrok.conf.JavaNgrokConfig;
import com.github.alexdlaird.ngrok.protocol.CreateTunnel;

import java.nio.file.Path;
import java.nio.file.Paths;

public class Main {
    public static void main(String[] args) {

        JavaNgrokConfig ngrokConfig = new JavaNgrokConfig.Builder()

                .withNgrokPath(Path.of("/usr/local/bin/ngrok"))
                .withoutMonitoring()
                .build();
        NgrokClient ngrokClient = new NgrokClient.Builder()
                .withJavaNgrokConfig(ngrokConfig)
                .build();
        CreateTunnel createTunnel = new CreateTunnel.Builder()
                .build();
        ;
    }
}