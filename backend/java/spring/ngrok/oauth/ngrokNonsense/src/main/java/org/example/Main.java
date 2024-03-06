package org.example;

import com.github.alexdlaird.ngrok.NgrokClient;
import com.github.alexdlaird.ngrok.conf.JavaNgrokConfig;
import com.github.alexdlaird.ngrok.protocol.CreateTunnel;
import com.github.alexdlaird.ngrok.protocol.Tunnel;
import com.github.alexdlaird.ngrok.protocol.TunnelOAuth;
import com.github.alexdlaird.ngrok.protocol.Proto;
import com.github.alexdlaird.ngrok.protocol.BindTls;

import java.nio.file.Path;

public class Main {
    public static void main(String[] args) {

        JavaNgrokConfig ngrokConfig = new JavaNgrokConfig.Builder()

                .withNgrokPath(Path.of("/usr/local/bin/ngrok"))
                .build();
        NgrokClient ngrokClient = new NgrokClient.Builder()
                .withJavaNgrokConfig(ngrokConfig)
                .build();
        TunnelOAuth tunnelOAuth = new TunnelOAuth.Builder()
                .withProvider("google")
                .build();
        CreateTunnel createTunnel = new CreateTunnel.Builder()
                .withProto(Proto.TCP)
                .withAddr("http://localhost:8080")
                .withOAuth(tunnelOAuth)
                .build();
        Tunnel tunnel = ngrokClient.connect(createTunnel);
        String pubUrl = tunnel.getPublicUrl();
        System.out.println(pubUrl);
    }
}
