package org.example;


import lombok.Getter;
import lombok.Setter;
import org.springframework.boot.context.properties.ConfigurationProperties;

@Getter
@Setter
@ConfigurationProperties(prefix = "ngrok")
public class NgrokProperties {
   private String home;
   private String lockFilePath;
   private String permisisonFilePath;
   private String binaryPath;
   private String configPath;
   private String tunnelAddress;
   private String authToken;
}
