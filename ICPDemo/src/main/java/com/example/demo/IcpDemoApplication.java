package com.example.demo;

import java.security.KeyManagementException;
import java.security.KeyStoreException;
import java.security.NoSuchAlgorithmException;
import java.util.HashMap;
import java.util.Map;

import org.slf4j.Logger;
import org.slf4j.LoggerFactory;
import org.springframework.beans.factory.annotation.Value;
import org.springframework.boot.CommandLineRunner;
import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;

@SpringBootApplication
public class IcpDemoApplication implements CommandLineRunner {
	
	private static final String ICP_URL = "icp.url";
	private static final String ICP_TIMEOUT = "icp.timeout";
	private static final String ICP_PASSWORD = "icp.password";
	
	private static final String ICP_IDAGENT = "icp.idAgente";
	private static final String ICP_EXTENSION = "icp.extension";
	private static final String ICP_IP = "icp.ip";
	private static final String ICP_TRY = "icp.try";
	
	private static Logger logger = LoggerFactory.getLogger(IcpDemoApplication.class);
	
	@Value("${icp.url}")		
	private String icpUrl; 
	
	@Value("${icp.timeout}")
	private String icpTimeout;
		
	@Value("${icp.password}")
	private String icpPassword;
	
	@Value("${icp.idAgente}")
	private String icpAgente;
	
	@Value("${icp.extension}")
	private String icpExtension;
	
	@Value("${icp.ip}")
	private String icpIp;
	
	@Value("${icp.try}")
	private String icpTry;
	
	public static void main(String[] args) {
		SpringApplication.run(IcpDemoApplication.class, args);
		
		logger.info("Starting application.");		
		
		logger.info("Closing application.");
	}

	@Override
	public void run(String... args) throws Exception {
		
		logger.info("CLI Request: command line runner.");
		
		for (int i = 0; i < args.length; i+=2 ) {
			
			if (i + 1 > args.length) {
				logger.error("Arg [{}] has no param. [{}]", i, args.length);
				continue;
			}
			
			if (ICP_URL.equals(args[i])) {
				logger.debug("Replacig default {}: {}", ICP_URL, icpUrl);
				icpUrl = args[i + 1];								
			}
			else if (ICP_TIMEOUT.equals(args[i])) {
				logger.debug("Replacing default {}: {}", ICP_TIMEOUT, icpTimeout);
				icpTimeout = args[i + 1];
			}
			else if (ICP_PASSWORD.equals(args[i])) {
				logger.debug("Replacing default {}: {}", ICP_PASSWORD, icpPassword);
				icpPassword = args[i + 1];
			}
			else if (ICP_IDAGENT.equals(args[i])) {
				logger.debug("Replacing default {}: {}", ICP_IDAGENT, icpAgente);
				icpAgente = args[i + 1];
			}
			else if (ICP_EXTENSION.equals(args[i])) {
				logger.debug("Replacing default {}: {}", ICP_EXTENSION, icpExtension);
				icpExtension = args[i + 1];
			}
			else if (ICP_IP.equals(args[i])) {
				logger.debug("Replacing default {}: {}", ICP_IP, icpIp);
				icpIp = args[i + 1];
			}
			else if(ICP_TRY.equals(args[i])) {
				logger.debug("Replacing default {}: {}", ICP_TRY, icpTry);
				icpTry = args[i + 1];
			}
		}
		
		logger.info("ICP URL: {}", icpUrl);
		logger.info("ICP TimeOut: {}", icpTimeout);
		
		logger.info("ICP Password: {}", icpPassword);
		logger.info("ICP Agent: {}", icpAgente);
		logger.info("ICP Extension: {}", icpExtension);
		logger.info("ICP IP: {}", icpIp);
		
		logger.info("ICP Try: {}", icpTry);
		
		if (!"True".equals(icpTry))
			return;		
		
		IntegracionIPC integracion = new IntegracionIPC(icpUrl, 5000);
		Map<String, String> resp = integracion.login(icpAgente, icpPassword, icpExtension);		
		HashMap<String, Object> agwResult = IntegracionIPC.jsonToMap(resp.get("result"));
        if (agwResult == null) {
            String errMsg = "Error en el parseo del resultado.";
            logger.error(errMsg);
            return;
        }
		
        logger.info("LOGIN GUID capture: {}", resp.get("guid"));
        logger.info("LOGIN Cookie capture: {}", resp.get("cookie"));                                
        String localGUID = resp.get("guid");
        String localCookie = resp.get("cookie");

        if ("0".equals(agwResult.get("retcode"))) {

            if (localGUID == null || localGUID.length() <= 0) {
                String errMsg = "Error en la obtención del token para la comunicación con el IPC.";
                logger.error(errMsg);
                return;
            }
            else {
                logger.debug("Se logro completar el login.");
            }
        }

        else if ("100-002".equals(agwResult.get("retcode"))) {
            logger.debug("Forzando el login en el IPC.");
            try {
                resp = integracion.forceLogin(
                        icpAgente,
                        icpPassword,
                        icpExtension);
                agwResult = IntegracionIPC.jsonToMap(resp.get("result"));
                if (agwResult == null) {
                    String errMsg = "Error en el parseo del resultado.";
                    logger.error(errMsg);
                    return;
                }
            } catch (NoSuchAlgorithmException e) {
                String errMsg = "NoSuchAlgorithmException: " + e.getMessage();
                logger.error(errMsg);
                return;
            } catch (KeyStoreException e) {
                String errMsg = "KeyStoreException: " + e.getMessage();
                logger.error(errMsg);
                return;
            } catch (KeyManagementException e) {
                String errMsg = "KeyManagementException: " + e.getMessage();
                logger.error(errMsg);
                return;
            }

            localGUID = resp.get("guid");
            localCookie = resp.get("cookie");
            if ("0".equals(agwResult.get("retcode"))) {

                if (localGUID == null || localGUID.length() <= 0) {
                    String errMsg = "Error en la obtención del token para la comunicación con el IPC.";
                    logger.error(errMsg);
                    return;
                }
                else {
                    logger.debug("Se logro completar el login.");
                }
            }

            else {
                String errMsg = "Error en el login del agente. " + resp.get("result");
                logger.error(errMsg);
                return;
            }
        }

        else {
            String errMsg = "Error en el login del agente. " + resp.get("result");
            logger.error(errMsg);
            return;
        }

        Map<String, String> headers = new HashMap<>();
        headers.put("Cookie", localCookie);
        headers.put("guid", localGUID);        
                
        try {
            resp = integracion.resetSkills(icpAgente, true, "", headers);
            agwResult = IntegracionIPC.jsonToMap(resp.get("result"));
            if (agwResult == null) {
                String errMsg = "Error en el parseo del resultado.";
                logger.error(errMsg);
                return;
            }
        } catch (NoSuchAlgorithmException e) {
            String errMsg = "NoSuchAlgorithmException: " + e.getMessage();
            logger.error(errMsg);
            return;
        } catch (KeyStoreException e) {
            String errMsg = "KeyStoreException: " + e.getMessage();
            logger.error(errMsg);
            return;
        } catch (KeyManagementException e) {
            String errMsg = "KeyManagementException: " + e.getMessage();
            logger.error(errMsg);
            return;
        }
        
        Thread.sleep(2000);
        
        headers = new HashMap<>();
        headers.put("Cookie", localCookie);
        headers.put("guid", localGUID);        
        
        resp = integracion.logout(icpAgente, headers);
        agwResult = IntegracionIPC.jsonToMap(resp.get("result"));
        if (agwResult == null) {
            String errMsg = "Error en el parseo del resultado.";
            logger.error(errMsg);
            return;
        }
        
	}

}
