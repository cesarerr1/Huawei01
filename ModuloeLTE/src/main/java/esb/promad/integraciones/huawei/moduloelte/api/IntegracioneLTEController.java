package esb.promad.integraciones.huawei.moduloelte.api;

import esb.promad.integraciones.huawei.moduloelte.models.BrokerInfo;
import esb.promad.integraciones.huawei.moduloelte.models.GroupInfo;
import esb.promad.integraciones.huawei.moduloelte.models.StatusInfo;
import esb.promad.integraciones.huawei.moduloelte.models.UserInfo;
import esb.promad.integraciones.huawei.moduloelte.models.api.RespuestaInvocacion;
import esb.promad.integraciones.huawei.moduloelte.service.ServicioeLTE;
import io.swagger.annotations.Api;
import io.swagger.annotations.ApiOperation;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.web.bind.annotation.*;

import java.util.List;

@RestController
@RequestMapping ("api/elte")
@Api(value = "API REST para integración de radios eLTE/Huawei.",
        description = "Permite el uso de los radios integrados en el IPC de Huawei.")
public class IntegracioneLTEController {

    private Logger logger = LoggerFactory.getLogger(IntegracioneLTEController.class);

    @Autowired
    private ServicioeLTE servicio;

    @GetMapping(value = "/status")
    @ApiOperation(value = "Consulta el status del broker.")
    public StatusInfo solicitaStatus(
            @RequestParam(name = "ipbroker") String ipBroker
    ) {
        logger.info("Solicitando consultar el status de uno de los brokers: " + ipBroker);
        return servicio.consultarStatus(ipBroker);
    }

    @GetMapping(value = "/info")
    @ApiOperation(value = "Consulta la información del broker.")
    public BrokerInfo solicitaInfo(
            @RequestParam(name = "ipbroker") String ipBroker
    ) {
        logger.info("Solicitando consultar el status de uno de los brokers: " + ipBroker);
        return servicio.consultarVersion(ipBroker);
    }

    @GetMapping(value = "/listUsers")
    @ApiOperation(value = "Lista los usuarios registrados en la plataforma.")
    public List<UserInfo> listarUsuarios(
            @RequestParam(name = "ipbroker") String ipBroker
    ) {
        logger.info("Solicitando listar los usuarios registrados en la plataforma");
        return servicio.listarUsuarios(ipBroker);
    }

    @GetMapping(value = "/listGroups")
    @ApiOperation(value = "Lista los grupos registrados en la plataforma.")
    public List<GroupInfo> listarGrupos(
            @RequestParam(name = "ipbroker") String ipBroker
    ) {
        logger.info("Se solicita listar los grupos registrados. " + ipBroker);
        return servicio.listarGrupos(ipBroker);
    }

    @PostMapping(value = "/directCall/generate")
    @ApiOperation(value = "Genera una llamada directa al recurso especificado.")
    public RespuestaInvocacion llamadaDirecta(
            @RequestParam(name = "ipbroker") String ipBroker,
            @RequestParam(name = "recurso") String recurso
    ) {
        logger.info("Se solicita generar una llamada directa al recurso: " + recurso + " / " + ipBroker);
        return servicio.llamadaDirecta(ipBroker, recurso);
    }

    @PostMapping(value = "/directCall/release")
    @ApiOperation(value = "Libera una llamada directa al recurso especificado.")
    public RespuestaInvocacion liberaLlamadaDirecta(
            @RequestParam(name = "ipbroker") String ipBroker,
            @RequestParam(name = "recurso") String recurso
    ) {
        logger.info("Se solicita liberar una llamada directa al recurso: " + recurso + " / " + ipBroker);
        return servicio.liberarLlamadaDirecta(ipBroker, recurso);
    }

    @PostMapping(value = "/directCall/keepalive")
    @ApiOperation(value = "Mantiene una llamada directa al recurso especificado.")
    public RespuestaInvocacion keepAliveDirecta(
            @RequestParam(name = "ipbroker") String ipBroker,
            @RequestParam(name = "recurso") String recurso
    ) {
        logger.info("Se solicita mantener una llamada directa al recurso: " + recurso + " / " + ipBroker);
        return new RespuestaInvocacion(0, "OK");
    }

    @PostMapping(value = "/groupCall/generate")
    @ApiOperation(value = "Genera una llamada de grupo al recurso especificado.")
    public RespuestaInvocacion llamadaGrupo(
            @RequestParam(name = "ipbroker") String ipBroker,
            @RequestParam(name = "recurso") String recurso
    ) {
        logger.info("Se solicita generar una llamada de grupo al recurso: " + recurso + " / " + ipBroker);
        return servicio.llamadaGrupo(ipBroker, recurso);
    }

    @PostMapping(value = "/groupCall/release")
    @ApiOperation(value = "Libera una llamada de grupo al recurso especificado.")
    public RespuestaInvocacion liberaLlamadaGrupo(
            @RequestParam(name = "ipbroker") String ipBroker,
            @RequestParam(name = "recurso") String recurso
    ) {
        logger.info("Se solicita liberar una llamada de grupo al recurso: " + recurso + " / " + ipBroker);
        return servicio.liberarLlamadaGrupo(ipBroker, recurso);
    }

    @PostMapping(value = "/groupCall/close")
    @ApiOperation(value = "Cierrar una llamada de grupo al recurso especificado.")
    public RespuestaInvocacion cierraLlamadaGrupo(
            @RequestParam(name = "ipbroker") String ipBroker,
            @RequestParam(name = "recurso") String recurso
    ) {
        logger.info("Se solicita cerrar una llamada de grupo al recurso: " + recurso + " / " + ipBroker);
        return servicio.cerrarLlamadaGrupo(ipBroker, recurso);
    }

    @PostMapping(value = "/groupCall/keepalive")
    @ApiOperation(value = "Mantiene una llamada de grupo al recurso especificado.")
    public RespuestaInvocacion keepAliveGrupo(
            @RequestParam(name = "ipbroker") String ipBroker,
            @RequestParam(name = "recurso") String recurso
    ) {
        logger.info("Se solicita mantener una llamada de grupo al recurso: " + recurso + " / " + ipBroker);
        return new RespuestaInvocacion(0, "OK");
    }

    @PostMapping(value = "/textMessage")
    @ApiOperation(value = "Genera un mensaje de texto al recurso especificado.")
    public RespuestaInvocacion mensajeTexto(
            @RequestParam(name = "ipbroker") String ipBroker,
            @RequestParam(name = "recurso") String recurso,
            @RequestParam(name = "mensaje") String mensaje
    ) {
        logger.info("Se solicita generar un mensaje de texto al recurso: " + recurso + " / " + ipBroker);
        return servicio.mensajeTexto(ipBroker, recurso, mensaje);
    }

    @PostMapping(value = "/videoCall")
    @ApiOperation(value = "Muestra la interface para generar una llamada de video al recurso especificado.")
    public RespuestaInvocacion videoLlamada(
            @RequestParam(name = "ipbroker") String ipBroker,
            @RequestParam(name = "recurso") String recurso
    ) {
        logger.info("Se solicita generar una llamada de video al recurso: " + recurso + " / " + ipBroker);
        return servicio.llamadaVideo(ipBroker, recurso);
    }
}
