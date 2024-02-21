package org.example;

import com.github.alexdlaird.ngrok.conf.JavaNgrokConfig;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.context.event.EventListener;
import org.springframework.core.env.Environment;
import org.springframework.stereotype.Component;
import org.springframework.boot.web.context.WebServerInitializedEvent;
import com.github.alexdlaird.ngrok.NgrokClient;
import com.github.alexdlaird.ngrok.NgrokConfiguration;
import com.github.alexdlaird.ngrok.protocol.CreateTunnel;
import com.github.alexdlaird.ngrok.protocol.Tunnel;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;

@Component
public class NgrokWebServerEventListener {
    private static final Logger LOGGER = LoggerFactory.getLogger(NgrokWebServerEventListener.class);

    private final Environment environment;
    private final NgrokConfiguration ngrokConfiguration;
    private final NgrokProperties ngrokProperties = new NgrokProperties(

    );
    @Autowired
    public NgrokWebServerEventListener(Environment environment, NgrokConfiguration ngrokConfiguration) {
        this.environment = environment;
        this.ngrokConfiguration = ngrokConfiguration;
    }

    @EventListener
    public void onApplicationEvent(WebServerInitializedEvent event) {
        if (ngrokConfiguration.isEnabled() && System.getenv("NGROK_AUTHTOKEN") != null) {
            NgrokConfiguration javaNgrokConfiguration = new JavaNgrokConfig.Builder()
                .withNgrokPath(ngrokBinaryPath)
                .withoutMonitoring()
                .build();
            NgrokClient ngrokClient = new NgrokClient.Builder()
                    .withJavaNgrokConfig(javaNgrokConfiguration)
                    .build();

            int port = event.getWebServer().getPort();
            CreateTunnel createTunnel = new CreateTunnel.Builder()
                    .withAddr(port)
                    .build();

            Tunnel tunnel = ngrokClient.connect(createTunnel);
            LOGGER.info(String.format("ngrok tunnel \"%s\" -> [^1^][4]://%d", tunnel.getPublicUrl(), port));

            // Update any base URLs or webhooks to use the public ngrok URL
            initWebhooks(tunnel.getPublicUrl());
        }
    }

    private void initWebhooks(String publicUrl) {
        // Update inbound traffic via APIs to use the public-facing ngrok URL
    }
}