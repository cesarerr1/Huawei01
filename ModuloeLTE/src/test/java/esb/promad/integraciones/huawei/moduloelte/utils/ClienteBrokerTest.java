package esb.promad.integraciones.huawei.moduloelte.utils;

import esb.promad.integraciones.huawei.moduloelte.models.BrokerInfo;
import esb.promad.integraciones.huawei.moduloelte.models.GroupInfo;
import esb.promad.integraciones.huawei.moduloelte.models.StatusInfo;
import esb.promad.integraciones.huawei.moduloelte.models.UserInfo;
import esb.promad.integraciones.huawei.moduloelte.models.api.RespuestaInvocacion;
import org.junit.Before;
import org.junit.Test;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;

import java.util.List;

import static org.junit.Assert.*;

public class ClienteBrokerTest {

    protected Logger logger = LoggerFactory.getLogger(ClienteBrokerTest.class);
    protected ClienteBroker target;

    @Before
    public void setUp() throws Exception {
        target = new ClienteBroker("localhost:8030", "/server/broker");
    }

    @Test
    public void consultarStatus() {

        logger.debug("Se solicita consultar el status del broker de pruebas.");
        StatusInfo salida = target.consultarStatus();
        assertNotNull(salida);
        logger.debug("Respuesta:\n" + salida);
    }

    @Test
    public void consultarVersion() {

        logger.debug("Se solicita consultar la versión del broker de pruebas.");
        BrokerInfo salida = target.consultarVersion();
        assertNotNull(salida);
        logger.debug("Respuesta:\n" + salida);
    }

    @Test
    public void listarUsuarios() {

        logger.debug("Se solicita listar los usuarios registrados en el sistema.");
        List<UserInfo> lista = target.listarUsuarios();
        assertNotNull(lista);
        for (UserInfo item : lista)
            logger.debug(item.toString());
    }

    @Test
    public void listarGrupos() {

        logger.debug("Se solicita listar los grupos registrados en el sistema.");
        List<GroupInfo> lista = target.listarGrupos();
        assertNotNull(lista);
        for (GroupInfo item : lista)
            logger.debug(item.toString());
    }

    @Test
    public void llamadaDirecta() {

        logger.debug("Se solicita generar una llamada directa.");
        RespuestaInvocacion resp = target.llamadaDirecta("4421");
        assertNotNull(resp);
        logger.debug(resp.toString());
    }

    @Test
    public void llamadaGrupo() {

        logger.debug("Se solicita generar una llamada de grupo.");
        RespuestaInvocacion resp = target.llamadaGrupo("4421");
        assertNotNull(resp);
        logger.debug(resp.toString());
    }

    @Test
    public void mensajeTexto() {

        logger.debug("Se solicita generar un mensaje de Texto.");
        RespuestaInvocacion resp = target.mensajeTexto("9999", "prueba");
        assertNotNull(resp);
        logger.debug(resp.toString());
    }
}