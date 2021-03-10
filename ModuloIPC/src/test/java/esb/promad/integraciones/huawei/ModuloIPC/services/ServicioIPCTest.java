package esb.promad.integraciones.huawei.ModuloIPC.services;

import esb.promad.integraciones.huawei.moduloipc.library.IntegracionIPC;
import esb.promad.integraciones.huawei.moduloipc.models.AsociacionAgente;
import esb.promad.integraciones.huawei.moduloipc.services.ServicioIPC;
import org.junit.Before;
import org.junit.Test;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;
import org.springframework.test.util.ReflectionTestUtils;

import static org.junit.Assert.*;

public class ServicioIPCTest {

    protected Logger logger = LoggerFactory.getLogger(ServicioIPCTest.class);
    protected ServicioIPC target;

    @Before
    public void setUp() throws Exception {

        logger.debug("Inicializando pruebas IPC.");
        target = new ServicioIPC();
        IntegracionIPC ipc = new IntegracionIPC("https://173.20.1.18:8043/agentgateway");
        ReflectionTestUtils.setField(target, "ipc", ipc);
    }

    @Test
    public void asociaAgente() throws Exception {

        AsociacionAgente agente = new AsociacionAgente("103", "20003", "1.2.3.4");
        logger.debug("Iniciando prueba de asociación de agente: " + agente);
        Object[] resp = target.asociaAgente(agente);

        String msg = "Respuesta: ";
        for (Object item : resp)
            msg += ((String) item) + ",";
        logger.debug(msg);
    }

    @Test
    public void desasociaAgente() throws Exception {
    }

    @Test
    public void cambioEstadoAgente() throws Exception {
    }

}