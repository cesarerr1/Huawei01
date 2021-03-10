package esb.promad.integraciones.huawei.moduloipc.services;

import esb.promad.integraciones.huawei.moduloipc.library.IntegracionIPC;
import esb.promad.integraciones.huawei.moduloipc.models.Agente;
import esb.promad.integraciones.huawei.moduloipc.models.AsociacionAgente;
import esb.promad.integraciones.huawei.moduloipc.models.NumeroListaBlanca;
import esb.promad.integraciones.huawei.moduloipc.models.NumeroListaNegra;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;
import org.springframework.beans.factory.InitializingBean;
import org.springframework.stereotype.Service;

import java.security.KeyManagementException;
import java.security.KeyStoreException;
import java.security.NoSuchAlgorithmException;
import java.util.HashMap;
import java.util.Map;

@Service
public class ServicioIPC implements InitializingBean {

    protected String errMsg;
    protected Logger logger = LoggerFactory.getLogger(ServicioIPC.class);
    protected String urlServicio;
    protected String listasBlancas;
    protected String listasNegras;
    protected int timeOut;
    protected IntegracionIPC ipc;
    protected Map<String, Map<String, String>> operacion;

    public String getErrMsg() {
        return errMsg;
    }

    public int getTimeOut() {
        return timeOut;
    }

    public void setTimeOut(int timeOut) {
        this.timeOut = timeOut;
    }

    @Override
    public void afterPropertiesSet() throws Exception {

        logger.debug("Inicializando servicio IPC.");
    }

    public Object[] registraConectividadServidorAE(String cuentaAdministrador, String passwordAdministrador,
                                                   String urlServidor)
    {
        Object[] salida = null;

        errMsg = "";
        logger.debug(String.format("Intentando registrar la conectividad con el servidor AE %s,%s",
                cuentaAdministrador, urlServidor));

        return null;
    }

    public Object[] obtieneConectividadServidorAE(String cuentaAdministrador, String passwordAdministrador)
    {
        Object[] salida = null;
        return null;
    }

    public Object[] obtenerSkillgroups(String cuentaAdministrador, String passwordAdministrador)
    {
        Object[] salida = null;
        return null;
    }

    public Object[] registraAgente(String cuentaAdministrador, String passwordAdministrador, Agente agente)

    {
        Object[] salida = null;
        return null;
    }

    public Object[] desregistraAgente(String cuentaAdministrador, String passwordAdministrador,
                                      String numeroAgente)
    {
        Object[] salida = null;
        return null;
    }

    public Object[] obtieneAgentesRegistrados(String cuentaAdministrador, String passwordAdministrador)
    {
        Object[] salida = null;
        return null;
    }

    public Object[] registraExtensionTelefonica(String cuentaAdministrador, String passwordAdministrador,
                                                String numeroExtension)
    {
        Object[] salida = null;
        return null;
    }

    public Object[] desregistraExtensionTelefonica(String cuentaAdministrador, String passwordAdministrador,
                                                   String numeroExtension)
    {
        Object[] salida = null;
        return null;
    }

    public Object[] obtieneExtensionesRegistradas(String cuentaAdministrador, String passwordAdministrador)
    {
        Object[] salida = null;
        return null;
    }

    public Object[] registraDireccionIP(String cuentaAdministrador, String passwordAdministrador,
                                        String direccionIP)
    {
        Object[] salida = null;
        return null;
    }

    public Object[] desregistraDireccionIP(String cuentaAdministrador, String passwordAdministrador,
                                           String direccionIP)
    {
        Object[] salida = null;
        return null;
    }

    public Object[] obtieneDireccionesIPRegistradas(String cuentaAdministrador, String passwordAdministrador)
    {
        Object[] salida = null;
        return null;
    }

    public Object[] asociaAgente(AsociacionAgente asociacionAgente)
    {
        errMsg = "";
        logger.debug("Solicitando asociar un agente: " + asociacionAgente);

        Object[] salida = null;
        Map<String, String> resp;
        logger.debug("Login del agente. " + asociacionAgente.numeroAgente);
        try {
             resp = ipc.login(
                    asociacionAgente.numeroAgente,
                    "",
                    asociacionAgente.numeroExtension);
        } catch (NoSuchAlgorithmException e) {
            errMsg = "NoSuchAlgorithmException: " + e.getMessage();
            logger.error(errMsg);
            return new Object[] { "1001", errMsg };
        } catch (KeyStoreException e) {
            errMsg = "KeyStoreException: " + e.getMessage();
            logger.error(errMsg);
            return new Object[] { "1001", errMsg };
        } catch (KeyManagementException e) {
            errMsg = "KeyManagementException: " + e.getMessage();
            logger.error(errMsg);
            return new Object[] { "1001", errMsg };
        }

        String localGUID = "";
        if (resp.get("guid").compareTo("") != 0)
            localGUID = resp.get("guid");

        else if (resp.get("result").contains("100-002")) {
            logger.debug("Forzando el login en el IPC.");
            try {
                resp = ipc.forceLogin(
                        asociacionAgente.numeroAgente,
                        "",
                        asociacionAgente.numeroExtension);
            } catch (NoSuchAlgorithmException e) {
                errMsg = "NoSuchAlgorithmException: " + e.getMessage();
                logger.error(errMsg);
                return new Object[] { "1001", errMsg };
            } catch (KeyStoreException e) {
                errMsg = "KeyStoreException: " + e.getMessage();
                logger.error(errMsg);
                return new Object[] { "1001", errMsg };
            } catch (KeyManagementException e) {
                errMsg = "KeyManagementException: " + e.getMessage();
                logger.error(errMsg);
                return new Object[] { "1001", errMsg };
            }

            if (resp.get("guid").compareTo("") != 0)
                localGUID = resp.get("guid");

            else {
                errMsg = "Error en el login del agente. " + resp.get("result");
                logger.error(errMsg);
                return new Object[] { "0001", errMsg};
            }
        }

        else {
            errMsg = "Error en el login del agente. " + resp.get("result");
            logger.error(errMsg);
            return new Object[] { "0001", errMsg};
        }

        //Need to add guid to http request for Authentication after log in
        Map<String, String> headers = new HashMap<String, String>();
        headers.put("guid", localGUID);
        try {
            resp = ipc.resetSkills(asociacionAgente.numeroAgente, true, "", headers);
        } catch (NoSuchAlgorithmException e) {
            errMsg = "NoSuchAlgorithmException: " + e.getMessage();
            logger.error(errMsg);
            return new Object[] { "1001", errMsg };
        } catch (KeyStoreException e) {
            errMsg = "KeyStoreException: " + e.getMessage();
            logger.error(errMsg);
            return new Object[] { "1001", errMsg };
        } catch (KeyManagementException e) {
            errMsg = "KeyManagementException: " + e.getMessage();
            logger.error(errMsg);
            return new Object[] { "1001", errMsg };
        }

        return salida;
    }

    public Object[] desasociaAgente(AsociacionAgente asociacionAgente)
    {
        errMsg = "";
        logger.debug("Solicitando desasociar un agente: " + asociacionAgente);

        Object[] salida = null;
        return null;
    }

    public Object[] obtieneAgentesAsociados(AsociacionAgente asociacionAgente)
    {
        Object[] salida = null;
        return null;
    }

    public Object[] cambioEstadoAgente(AsociacionAgente asociacionAgente, String banderaDisponibilidad)
    {
        errMsg = "";
        logger.debug("Solicitando hacer un cambio de estado a un agente: " + banderaDisponibilidad + "\n" +
                asociacionAgente);

        Object[] salida = null;
        return null;
    }

    public Object[] solicitaReproduccionExtension(AsociacionAgente asociacionAgente, String nombreArchivo,
                                                  String urlArchivo)
    {
        Object[] salida = null;
        return null;
    }

    public Object[] solicitaReproduccionSalaJuntas(AsociacionAgente asociacionAgente, String uniqueId,
                                                   String nombreArchivo, String urlArchivo)
    {
        Object[] salida = null;
        return null;
    }

    public Object[] solicitaCopiaGrabacion(AsociacionAgente asociacionAgente, String nombreArchivo,
                                           String urlArchivo, String urlFTP)
    {
        Object[] salida = null;
        return null;
    }

    public Object[] registraAccionListaNegra(AsociacionAgente asociacionAgente, String idAccion,
                                             String descripcionAccion)
    {
        Object[] salida = null;
        return null;
    }

    public Object[] obtieneAccionesListaNegra(AsociacionAgente asociacionAgente)
    {
        Object[] salida = null;
        return null;
    }

    public Object[] registraNumeroListaNegra(AsociacionAgente asociacionAgente, NumeroListaNegra numeroListaNegra)
    {
        Object[] salida = null;
        return null;
    }

    public Object[] obtieneNumerosListaNegra(AsociacionAgente asociacionAgente)
    {
        Object[] salida = null;
        return null;
    }

    public Object[] registraNumeroListaBlanca(AsociacionAgente asociacionAgente, NumeroListaBlanca numeroListaBlanca)
    {
        Object[] salida = null;
        return null;
    }

    public Object[] obtieneNumerosListaBlanca(AsociacionAgente asociacionAgente)
    {
        Object[] salida = null;
        return null;
    }

    public Object[] solicitaTransferenciaLlamada(AsociacionAgente asociacionAgente, String uniqueId,
                                                 String numeroTransferencia)
    {
        Object[] salida = null;
        return null;
    }

    public Object[] solicitaLlamadaCallBack(AsociacionAgente asociacionAgente, String numeroTelefonico)
    {
        Object[] salida = null;
        return null;
    }

    public Object[] solicitaGrabacionMensaje(AsociacionAgente asociacionAgente, String tipoMensaje)
    {
        Object[] salida = null;
        return null;
    }

    public Object[] solicitaReproduccionMensaje(AsociacionAgente asociacionAgente, String tipoMensaje)
    {
        Object[] salida = null;
        return null;
    }

    public Object[] solicitaContestarTel(AsociacionAgente asociacionAgente)
    {
        Object[] salida = null;
        return null;
    }

    public Object[] solicitaColgarTel(AsociacionAgente asociacionAgente)
    {
        Object[] salida = null;
        return null;
    }

    public Object[] obtieneInfoTroncales(AsociacionAgente asociacionAgente)
    {
        Object[] salida = null;
        return null;
    }

    public Object[] obtieneInfoExtensiones(AsociacionAgente asociacionAgente)
    {
        Object[] salida = null;
        return null;
    }

    public Object[] solicitaIntrusion(AsociacionAgente asociacionAgente, AsociacionAgente asociacionSupervisor)
    {
        Object[] salida = null;
        return null;
    }

    public Object[] solicitaCoaching(AsociacionAgente asociacionAgente, AsociacionAgente asociacionSupervisor)
    {
        Object[] salida = null;
        return null;
    }

    public Object[] solicitaConferencia(AsociacionAgente asociacionAgente, AsociacionAgente asociacionSupervisor)
    {
        Object[] salida = null;
        return null;
    }

    public Object[] desregistraNumeroListaNegra(AsociacionAgente asociacionAgente, String callerId)
    {
        Object[] salida = null;
        return null;
    }
    public Object[] desregistraNumeroListaBlanca(AsociacionAgente asociacionAgente, String callerId)
    {
        Object[] salida = null;
        return null;
    }

}
