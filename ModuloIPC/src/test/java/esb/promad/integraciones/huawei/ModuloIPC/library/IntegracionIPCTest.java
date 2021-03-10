package esb.promad.integraciones.huawei.ModuloIPC.library;

import esb.promad.integraciones.huawei.moduloipc.library.IntegracionIPC;
import org.junit.Before;
import org.junit.Test;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;

import java.util.Map;

import static org.junit.Assert.*;

public class IntegracionIPCTest {

    protected Logger logger = LoggerFactory.getLogger(IntegracionIPCTest.class);
    protected IntegracionIPC target;

    @Before
    public void setUp() throws Exception {

        logger.debug("Generación de la interface de pruebas.");
        target = new IntegracionIPC("https://173.20.1.18:8043/agentgateway");
    }

    @Test
    public void login() throws Exception {

        logger.debug("Generación de invocación a login.");
        Map<String, String> resp = target.login("103", "", "20001");
        logger.debug(resp.toString());
    }

    @Test
    public void forceLogin() throws Exception {

        logger.debug("Generación de invocación a force login.");
        Map<String, String> resp = target.forceLogin("103", "", "20001");
        logger.debug(resp.toString());
    }

    @Test
    public void querySkills() throws Exception {

        logger.debug("Generación de invocación a query skills.");
        Map<String, String> resp = target.querySkills("103");
        logger.debug(resp.toString());
    }

    @Test
    public void logout() throws Exception {

        logger.debug("Generación de invocación a logout.");
        Map<String, String> resp = target.logout("103");
        logger.debug(resp.toString());
    }

    @Test
    public void forceLogout() throws Exception {

        logger.debug("Generación de invocación a force logout.");
        Map<String, String> resp = target.forceLogout("103");
        logger.debug(resp.toString());
    }

}