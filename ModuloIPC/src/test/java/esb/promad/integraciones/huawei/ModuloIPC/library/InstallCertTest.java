package esb.promad.integraciones.huawei.ModuloIPC.library;

import esb.promad.integraciones.huawei.moduloipc.library.InstallCert;
import org.junit.Before;
import org.junit.Test;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;

import static org.junit.Assert.*;

public class InstallCertTest {

    protected Logger logger = LoggerFactory.getLogger(InstallCertTest.class);
    protected InstallCert target;
    protected String host = "173.20.1.18";
    protected int port = 8043;

    @Before
    public void setUp() throws Exception {

        target = new InstallCert();
    }

    @Test
    public void validarCertificado() throws Exception {

        logger.debug("Validando el certificado de: " + host + ":" + port);
        int resp = target.validarCertificado(host, port, "");
        if (resp == 0)
            logger.debug("Ya se cuenta con el certificado en el repositorio.");
        else
            logger.debug(target.getErrMsg());
    }

    @Test
    public void instalarCertificado() throws Exception {

        logger.debug("Intentando registrar el certificado de: " + host + ":" + port);
        int resp = target.instalarCertificado(host, port, "");
        if (resp == 0)
            logger.debug("Ya se cuenta con el certificado en el repositorio.");
        else
            logger.debug(target.getErrMsg());
    }

}