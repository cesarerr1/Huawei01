package esb.promad.integraciones.huawei.moduloelte.service;

import esb.promad.integraciones.huawei.moduloelte.models.BrokerInfo;
import esb.promad.integraciones.huawei.moduloelte.models.GroupInfo;
import esb.promad.integraciones.huawei.moduloelte.models.StatusInfo;
import esb.promad.integraciones.huawei.moduloelte.models.UserInfo;
import esb.promad.integraciones.huawei.moduloelte.models.api.RespuestaInvocacion;
import esb.promad.integraciones.huawei.moduloelte.utils.ClienteBroker;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;
import org.springframework.beans.factory.annotation.Value;
import org.springframework.stereotype.Service;

import java.util.List;

@Service
public class ServicioeLTE {

    protected Logger logger = LoggerFactory.getLogger(ServicioeLTE.class);

    @Value("${broker.elte.port}")
    protected Integer port;
    @Value("${broker.elte.service}")
    protected String service;

    public StatusInfo consultarStatus(String ipBroker) {

        logger.debug("Se solicita consultar el status de uno de los brokers: " + ipBroker);
        ClienteBroker cliente = new ClienteBroker(
                ipBroker + ":" + port,
                service
        );
        return cliente.consultarStatus();
    }

    public BrokerInfo consultarVersion(String ipBroker) {

        logger.debug("Se solicita consultar la versión de uno de los brokers: " + ipBroker);
        ClienteBroker cliente = new ClienteBroker(
                ipBroker + ":" + port,
                service
        );
        return cliente.consultarVersion();
    }

    public List<UserInfo> listarUsuarios(String ipBroker) {

        logger.debug("Se solicita listar los usuarios registrados en la plataforma.");
        ClienteBroker cliente = new ClienteBroker(
                ipBroker + ":" + port,
                service
        );
        return cliente.listarUsuarios();
    }

    public List<GroupInfo> listarGrupos(String ipBroker) {

        logger.debug("Se solicita listar los grupos registrados en la plataoforma.");
        ClienteBroker cliente = new ClienteBroker(
                ipBroker + ":" + port,
                service
        );
        return cliente.listarGrupos();
    }

    public RespuestaInvocacion llamadaDirecta(String ipBroker, String recurso) {

        logger.debug("Se solicita generar una llamada directa al recurso: " + recurso);
        ClienteBroker cliente = new ClienteBroker(
                ipBroker + ":" + port,
                service
        );
        return cliente.llamadaDirecta(recurso);
    }

    public RespuestaInvocacion liberarLlamadaDirecta(String ipBroker, String recurso) {

        logger.debug("Se solicita liberar una llamada directa al recurso: " + recurso);
        ClienteBroker cliente = new ClienteBroker(
                ipBroker + ":" + port,
                service
        );
        return cliente.liberarLlamadaDirecta(recurso);
    }

    public RespuestaInvocacion llamadaGrupo(String ipBroker, String recurso) {

        logger.debug("Se solicita generar una llamada al grupo: " + recurso);
        ClienteBroker cliente = new ClienteBroker(
                ipBroker + ":" + port,
                service
        );
        return cliente.llamadaGrupo(recurso);
    }

    public RespuestaInvocacion liberarLlamadaGrupo(String ipBroker, String recurso) {

        logger.debug("Se solicita liberar una llamada al grupo: " + recurso);
        ClienteBroker cliente = new ClienteBroker(
                ipBroker + ":" + port,
                service
        );
        return cliente.liberarLlamadaGrupo(recurso);
    }

    public RespuestaInvocacion cerrarLlamadaGrupo(String ipBroker, String recurso) {

        logger.debug("Se solicita cerrar una llamada al grupo: " + recurso);
        ClienteBroker cliente = new ClienteBroker(
                ipBroker + ":" + port,
                service
        );
        return cliente.cerrarLlamadaGrupo(recurso);
    }

    public RespuestaInvocacion mensajeTexto(String ipBroker, String recurso, String mensaje) {

        logger.debug("Se solicita enviar un mensaje de texto al recurso: " + recurso);
        ClienteBroker cliente = new ClienteBroker(
                ipBroker + ":" + port,
                service
        );
        return cliente.mensajeTexto(recurso, mensaje);
    }

    public RespuestaInvocacion llamadaVideo(String ipBroker, String recurso) {

        logger.debug("Se solicita generar una llamada de video al recurso: " + recurso);
        ClienteBroker cliente = new ClienteBroker(
                ipBroker + ":" + port,
                service
        );
        return cliente.llamadaVideo(recurso);
    }
}
