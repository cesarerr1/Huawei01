package esb.promad.integraciones.huawei.moduloelte.utils;

import esb.promad.integraciones.huawei.moduloelte.models.BrokerInfo;
import esb.promad.integraciones.huawei.moduloelte.models.GroupInfo;
import esb.promad.integraciones.huawei.moduloelte.models.StatusInfo;
import esb.promad.integraciones.huawei.moduloelte.models.UserInfo;
import esb.promad.integraciones.huawei.moduloelte.models.api.RespuestaInvocacion;
import org.apache.http.Header;
import org.apache.http.HttpEntity;
import org.apache.http.HttpStatus;
import org.apache.http.client.ClientProtocolException;
import org.apache.http.client.methods.*;
import org.apache.http.conn.ssl.NoopHostnameVerifier;
import org.apache.http.conn.ssl.SSLConnectionSocketFactory;
import org.apache.http.conn.ssl.TrustStrategy;
import org.apache.http.entity.StringEntity;
import org.apache.http.impl.client.CloseableHttpClient;
import org.apache.http.impl.client.HttpClients;
import org.apache.http.ssl.SSLContextBuilder;
import org.codehaus.jackson.JsonFactory;
import org.codehaus.jackson.JsonGenerator;
import org.codehaus.jackson.JsonParseException;
import org.codehaus.jackson.map.JsonMappingException;
import org.codehaus.jackson.map.ObjectMapper;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;

import java.io.*;
import java.security.KeyManagementException;
import java.security.KeyStoreException;
import java.security.NoSuchAlgorithmException;
import java.security.cert.CertificateException;
import java.security.cert.X509Certificate;
import java.util.*;

public class ClienteBroker {

    protected Logger logger = LoggerFactory.getLogger(ClienteBroker.class);
    protected String errMsg;

    protected String host;
    protected String service;

    public ClienteBroker(String host, String service) {
        this.host = host;
        this.service = service;
    }

    public String getErrMsg() {
        return errMsg;
    }

    public StatusInfo consultarStatus() {

        errMsg = "";
        logger.debug("Se solicita consultar el status de uno de los brokers.");

        String url = String.format("http://%s%s/status", host, service);
        logger.trace("Url a ser utilizada: " + url);
        String result;

        try {
            Map<String, String> resp = request(RequestType.GET, url, null, null);
             if (resp == null) {
                 errMsg = "Respuesta vacia del broker.";
                 logger.error(errMsg);
                 return null;
             }
             result = resp.get("result");
             if (result == null || result.isEmpty()) {
                 errMsg = "No se encontro el campo de resultado en la respuesta del broker.";
                 logger.error(errMsg);
                 return null;
             }
        } catch (KeyStoreException e) {
            errMsg = e.getMessage();
            logger.error("Error de keystore en el request.", e);
            return null;
        } catch (NoSuchAlgorithmException e) {
            errMsg = e.getMessage();
            logger.error("Algoritmo desconocido.", e);
            return null;
        } catch (KeyManagementException e) {
            errMsg = e.getMessage();
            logger.error("Error en el manejador de llaves.", e);
            return null;
        }

        HashMap<String, Object> map = ClienteBroker.jsonToMap(result);
        return new StatusInfo(
                (String) map.get("status"),
                (String) map.get("errMsg"),
                (Integer) map.get("errCode")
        );
    }

    public BrokerInfo consultarVersion() {

        errMsg = "";
        logger.debug("Se solicita consultar la versión de uno de los brokers.");

        String url = String.format("http://%s%s/version", host, service);
        logger.trace("Url a ser utilizada: " + url);
        String result = null;
        try {
            Map<String, String> resp = request(RequestType.GET, url, null, null);
            result = resp.get("result");
            if (result == null || result.isEmpty()) {
                errMsg = "No se encontro el campo de resultado en la respuesta del broker.";
                logger.error(errMsg);
                return null;
            }
        } catch (KeyStoreException e) {
            errMsg = e.getMessage();
            logger.error("Error de keystore en el request.", e);
        } catch (NoSuchAlgorithmException e) {
            errMsg = e.getMessage();
            logger.error("Algoritmo desconocido.", e);
        } catch (KeyManagementException e) {
            errMsg = e.getMessage();
            logger.error("Error en el manejador de llaves.", e);
        }

        HashMap<String, Object> map = ClienteBroker.jsonToMap(result);
        return new BrokerInfo(
                (String) map.get("broker"),
                (String) map.get("status"),
                (String) map.get("version")
        );
    }

    public List<UserInfo> listarUsuarios() {

        errMsg = "";
        logger.debug("Se solicita listar los usuarios registrados en el sistema.");

        String url = String.format("http://%s%s/usuarios", host, service);
        logger.trace("Url a ser utilizada: " + url);
        String result = null;
        try {
            Map<String, String> resp = request(RequestType.GET, url, null, null);
            result = resp.get("result");
            if (result == null || result.isEmpty()) {
                errMsg = "No se encontro el campo de resultado en la respuesta del broker.";
                logger.error(errMsg);
                return null;
            }
        } catch (KeyStoreException e) {
            errMsg = e.getMessage();
            logger.error("Error de keystore en el request.", e);
        } catch (NoSuchAlgorithmException e) {
            errMsg = e.getMessage();
            logger.error("Algoritmo desconocido.", e);
        } catch (KeyManagementException e) {
            errMsg = e.getMessage();
            logger.error("Error en el manejador de llaves.", e);
        }

        HashMap<String, Object> map = ClienteBroker.jsonToMap(result);
        List<HashMap<String, String>> lista = (List<HashMap<String, String>>) map.get("usuarios");
        List<UserInfo> salida = null;
        if (lista != null && !lista.isEmpty()) {
            salida = new ArrayList<>();
            for (HashMap<String, String> local : lista) {
                UserInfo item = new UserInfo(
                        local.get("UserID"),
                        local.get("UserCategory"),
                        local.get("UserPriority"),
                        local.get("UserName")
                );
                salida.add(item);
            }
        }
        else
            logger.error("No se encontro el elemento usuarios en la respuesta.");

        return salida;
    }

    public List<GroupInfo> listarGrupos() {

        errMsg = "";
        logger.debug("Se solicita listar los grupos registrados en el sistema.");

        String url = String.format("http://%s%s/grupos", host, service);
        logger.trace("Url a ser utilizada: " + url);
        String result = null;
        try {
            Map<String, String> resp = request(RequestType.GET, url, null, null);
            result = resp.get("result");
            if (result == null || result.isEmpty()) {
                errMsg = "No se encontro el campo de resultado en la respuesta del broker.";
                logger.error(errMsg);
                return null;
            }
        } catch (KeyStoreException e) {
            errMsg = e.getMessage();
            logger.error("Error de keystore en el request.", e);
        } catch (NoSuchAlgorithmException e) {
            errMsg = e.getMessage();
            logger.error("Algoritmo desconocido.", e);
        } catch (KeyManagementException e) {
            errMsg = e.getMessage();
            logger.error("Error en el manejador de llaves.", e);
        }

        HashMap<String, Object> map = ClienteBroker.jsonToMap(result);
        List<HashMap<String, String>> lista = (List<HashMap<String, String>>) map.get("grupos");
        List<GroupInfo> salida = null;
        if (lista != null && !lista.isEmpty()) {
            salida = new ArrayList<>();
            for (HashMap<String, String> local : lista) {
                GroupInfo item = new GroupInfo(
                        local.get("GroupID"),
                        local.get("GroupCategory"),
                        local.get("GroupPriority"),
                        local.get("GroupName")
                );
                salida.add(item);
            }
        }
        else
            logger.error("No se encontro el elemento grupos en la respuesta.");
        return salida;
    }

    public RespuestaInvocacion llamadaDirecta(String recurso) {

        errMsg = "";
        logger.debug("Se solicita generar una llamada directa: " + recurso);

        String url = String.format("http://%s%s/llamadaDirecta/generar", host, service);
        logger.trace("Url a ser utilizada: " + url);

        HashMap<String, String> headers = new HashMap<>();
        headers.put("recurso", recurso);

        String result = null;
        try {
            Map<String, String> resp = request(RequestType.POST, url, null, headers);
            result = resp.get("result");
            if (result == null || result.isEmpty()) {
                errMsg = "No se encontro el campo de resultado en la respuesta del broker.";
                logger.error(errMsg);
                return null;
            }
        } catch (KeyStoreException e) {
            errMsg = e.getMessage();
            logger.error("Error de keystore en el request.", e);
        } catch (NoSuchAlgorithmException e) {
            errMsg = e.getMessage();
            logger.error("Algoritmo desconocido.", e);
        } catch (KeyManagementException e) {
            errMsg = e.getMessage();
            logger.error("Error en el manejador de llaves.", e);
        }

        HashMap<String, Object> map = ClienteBroker.jsonToMap(result);
        return new RespuestaInvocacion(
                (Integer) map.get("errCode"),
                (String) map.get("errMsg")
        );
    }

    public RespuestaInvocacion liberarLlamadaDirecta(String recurso) {

        errMsg = "";
        logger.debug("Se solicita liberar una llamada directa: " + recurso);

        String url = String.format("http://%s%s/llamadaDirecta/liberar", host, service);
        logger.trace("Url a ser utilizada: " + url);

        HashMap<String, String> headers = new HashMap<>();
        headers.put("recurso", recurso);

        String result = null;
        try {
            Map<String, String> resp = request(RequestType.POST, url, null, headers);
            result = resp.get("result");
            if (result == null || result.isEmpty()) {
                errMsg = "No se encontro el campo de resultado en la respuesta del broker.";
                logger.error(errMsg);
                return null;
            }
        } catch (KeyStoreException e) {
            errMsg = e.getMessage();
            logger.error("Error de keystore en el request.", e);
        } catch (NoSuchAlgorithmException e) {
            errMsg = e.getMessage();
            logger.error("Algoritmo desconocido.", e);
        } catch (KeyManagementException e) {
            errMsg = e.getMessage();
            logger.error("Error en el manejador de llaves.", e);
        }

        HashMap<String, Object> map = ClienteBroker.jsonToMap(result);
        return new RespuestaInvocacion(
                (Integer) map.get("errCode"),
                (String) map.get("errMsg")
        );
    }

    public RespuestaInvocacion llamadaGrupo(String recurso) {

        errMsg = "";
        logger.debug("Se solicita generar una llamada grupo: " + recurso);

        String url = String.format("http://%s%s/llamadaGrupo/generar", host, service);
        logger.trace("Url a ser utilizada: " + url);

        HashMap<String, String> headers = new HashMap<>();
        headers.put("recurso", recurso);

        String result = null;
        try {
            Map<String, String> resp = request(RequestType.POST, url, null, headers);
            result = resp.get("result");
            if (result == null || result.isEmpty()) {
                errMsg = "No se encontro el campo de resultado en la respuesta del broker.";
                logger.error(errMsg);
                return null;
            }
        } catch (KeyStoreException e) {
            errMsg = e.getMessage();
            logger.error("Error de keystore en el request.", e);
        } catch (NoSuchAlgorithmException e) {
            errMsg = e.getMessage();
            logger.error("Algoritmo desconocido.", e);
        } catch (KeyManagementException e) {
            errMsg = e.getMessage();
            logger.error("Error en el manejador de llaves.", e);
        }

        HashMap<String, Object> map = ClienteBroker.jsonToMap(result);
        return new RespuestaInvocacion(
                (Integer) map.get("errCode"),
                (String) map.get("errMsg")
        );
    }

    public RespuestaInvocacion liberarLlamadaGrupo(String recurso) {

        errMsg = "";
        logger.debug("Se solicita liberar una llamada grupo: " + recurso);

        String url = String.format("http://%s%s/llamadaGrupo/liberar", host, service);
        logger.trace("Url a ser utilizada: " + url);

        HashMap<String, String> headers = new HashMap<>();
        headers.put("recurso", recurso);

        String result = null;
        try {
            Map<String, String> resp = request(RequestType.POST, url, null, headers);
            result = resp.get("result");
            if (result == null || result.isEmpty()) {
                errMsg = "No se encontro el campo de resultado en la respuesta del broker.";
                logger.error(errMsg);
                return null;
            }
        } catch (KeyStoreException e) {
            errMsg = e.getMessage();
            logger.error("Error de keystore en el request.", e);
        } catch (NoSuchAlgorithmException e) {
            errMsg = e.getMessage();
            logger.error("Algoritmo desconocido.", e);
        } catch (KeyManagementException e) {
            errMsg = e.getMessage();
            logger.error("Error en el manejador de llaves.", e);
        }

        HashMap<String, Object> map = ClienteBroker.jsonToMap(result);
        return new RespuestaInvocacion(
                (Integer) map.get("errCode"),
                (String) map.get("errMsg")
        );
    }

    public RespuestaInvocacion cerrarLlamadaGrupo(String recurso) {

        errMsg = "";
        logger.debug("Se solicita cerrar una llamada grupo: " + recurso);

        String url = String.format("http://%s%s/llamadaGrupo/cerrar", host, service);
        logger.trace("Url a ser utilizada: " + url);

        HashMap<String, String> headers = new HashMap<>();
        headers.put("recurso", recurso);

        String result = null;
        try {
            Map<String, String> resp = request(RequestType.POST, url, null, headers);
            result = resp.get("result");
            if (result == null || result.isEmpty()) {
                errMsg = "No se encontro el campo de resultado en la respuesta del broker.";
                logger.error(errMsg);
                return null;
            }
        } catch (KeyStoreException e) {
            errMsg = e.getMessage();
            logger.error("Error de keystore en el request.", e);
        } catch (NoSuchAlgorithmException e) {
            errMsg = e.getMessage();
            logger.error("Algoritmo desconocido.", e);
        } catch (KeyManagementException e) {
            errMsg = e.getMessage();
            logger.error("Error en el manejador de llaves.", e);
        }

        HashMap<String, Object> map = ClienteBroker.jsonToMap(result);
        return new RespuestaInvocacion(
                (Integer) map.get("errCode"),
                (String) map.get("errMsg")
        );
    }

    public RespuestaInvocacion mensajeTexto(String recurso, String mensaje) {

        errMsg = "";
        logger.debug("Se solicita generar un mensaje de texto: " + recurso, " / " + mensaje);

        String url = String.format("http://%s%s/mensajeTexto", host, service);
        logger.trace("Url a ser utilizada: " + url);

        HashMap<String, String> headers = new HashMap<>();
        headers.put("recurso", recurso);
        headers.put("mensaje", mensaje);
        String result = null;
        try {
            Map<String, String> resp = request(RequestType.POST, url, null, headers);
            result = resp.get("result");
            if (result == null || result.isEmpty()) {
                errMsg = "No se encontro el campo de resultado en la respuesta del broker.";
                logger.error(errMsg);
                return null;
            }
        } catch (KeyStoreException e) {
            errMsg = e.getMessage();
            logger.error("Error de keystore en el request.", e);
        } catch (NoSuchAlgorithmException e) {
            errMsg = e.getMessage();
            logger.error("Algoritmo desconocido.", e);
        } catch (KeyManagementException e) {
            errMsg = e.getMessage();
            logger.error("Error en el manejador de llaves.", e);
        }

        HashMap<String, Object> map = ClienteBroker.jsonToMap(result);
        return new RespuestaInvocacion(
                (Integer) map.get("errCode"),
                (String) map.get("errMsg")
        );
    }

    public RespuestaInvocacion llamadaVideo(String recurso) {

        errMsg = "";
        logger.debug("Se solicita generar una llamada de video: " + recurso);

        String url = String.format("http://%s%s/llamadaVideo", host, service);
        logger.trace("Url a ser utilizada: " + url);

        HashMap<String, String> headers = new HashMap<>();
        headers.put("recurso", recurso);
        String result = null;
        try {
            Map<String, String> resp = request(RequestType.POST, url, null, headers);
            result = resp.get("result");
            if (result == null || result.isEmpty()) {
                errMsg = "No se encontro el campo de resultado en la respuesta del broker.";
                logger.error(errMsg);
                return null;
            }
        } catch (KeyStoreException e) {
            errMsg = e.getMessage();
            logger.error("Error de keystore en el request.", e);
        } catch (NoSuchAlgorithmException e) {
            errMsg = e.getMessage();
            logger.error("Algoritmo desconocido.", e);
        } catch (KeyManagementException e) {
            errMsg = e.getMessage();
            logger.error("Error en el manejador de llaves.", e);
        }

        HashMap<String, Object> map = ClienteBroker.jsonToMap(result);
        return new RespuestaInvocacion(
                (Integer) map.get("errCode"),
                (String) map.get("errMsg")
        );
    }

    protected CloseableHttpClient generateHttpClient()
            throws KeyStoreException, NoSuchAlgorithmException, KeyManagementException {

        SSLContextBuilder builder = new SSLContextBuilder();
        builder.loadTrustMaterial(null, new TrustStrategy() {
            @Override
            public boolean isTrusted(X509Certificate[] x509Certificates, String s) throws CertificateException {
                return true;
            }
        });
        SSLConnectionSocketFactory sslf = new SSLConnectionSocketFactory(
                builder.build(),
                NoopHostnameVerifier.INSTANCE);

        return HttpClients
                .custom()
                .setSSLSocketFactory(sslf)
                .build();
    }

    protected enum RequestType {
        GET, POST, PUT, DELETE
    };

    protected Map<String, String> request(RequestType type, String url,
                                          Map<String, Object> entityParams,
                                          Map<String, String> headers)
            throws KeyStoreException, NoSuchAlgorithmException, KeyManagementException {

        errMsg = "";
        CloseableHttpClient httpClient = generateHttpClient();
        CloseableHttpResponse response = null;
        Map<String, String> resultMap = null;
        try {

            HttpRequestBase httpRequest;
            switch (type) {

                case GET:
                    logger.trace("Método a ser utilizado GET.");
                    httpRequest = new HttpGet(url);
                    break;

                case POST:
                    logger.trace("Método a ser utilizado POST.");
                    httpRequest = new HttpPost(url);
                    break;

                case PUT:
                    logger.trace("Método a ser utilizado PUT.");
                    httpRequest = new HttpPut(url);
                    break;

                case DELETE:
                    logger.trace("Método a ser utilizado DELETE.");
                    httpRequest = new HttpDelete(url);
                    break;

                default:
                    errMsg = "Método no implementado.";
                    throw new Exception(errMsg);
            }

            if (entityParams != null && type != RequestType.DELETE)
            {
                String jsonString = beanToJson(entityParams);
                HttpEntity entity = new StringEntity(jsonString);
                ((HttpEntityEnclosingRequestBase)httpRequest).setEntity(entity);
                logger.trace("JSON: " + jsonString);
            }

            if (headers != null)
            {
                Set<Map.Entry<String, String>> headersSet = headers.entrySet();
                for (Map.Entry<String, String> entry : headersSet) {
                    httpRequest.setHeader(entry.getKey(), entry.getValue());
                }
                logger.trace("Headers...");
                for (Header hdr : httpRequest.getAllHeaders())
                    logger.trace(hdr.getName() + "/" + hdr.getValue());
            }
            httpRequest.setHeader("Content-Type", "application/json");
            response = httpClient.execute(httpRequest);
            int returnCode = response.getStatusLine().getStatusCode();
            if (returnCode == HttpStatus.SC_OK)
            {
                InputStream is = response.getEntity().getContent();
                BufferedReader in = new BufferedReader(new InputStreamReader(is));
                StringBuffer buffer = new StringBuffer();
                String line = "";
                while ((line = in.readLine()) != null) {
                    buffer.append(line);
                }

                Header[] allHeaders = response.getAllHeaders();
                String guid = "";
                if (allHeaders != null && allHeaders.length > 0)
                {
                    for (Header header : allHeaders)
                    {
                        if (header.getName().equals("Set-GUID"))
                        {
                            String setGuid = header.getValue();
                            if (setGuid != null)
                            {
                                guid = setGuid.replace("JSESSIONID=", "");
                                logger.trace("Cambio en la GUID: " + guid);
                            }
                            break;
                        }
                    }
                }
                resultMap = new HashMap<String, String>();
                resultMap.put("guid", guid);
                resultMap.put("result", buffer.toString());
                logger.trace("Resultado: " + buffer.toString());
            }
            else
            {
                logger.trace("RETURN_CODE: " + returnCode);
            }
            return resultMap;
        }
        catch (ClientProtocolException e)
        {
            errMsg = "ClientProtocolException: " + e.getMessage();
            logger.error(errMsg, e);
        }
        catch (IOException e)
        {
            errMsg = "IOException: " + e.getMessage();
            logger.error(errMsg, e);
        }
        catch (Exception e)
        {
            errMsg = "Exception: " + e.getMessage();
            logger.error(errMsg, e);
        }
        finally
        {
            try {
                if (response != null)
                    response.close();
            } catch (IOException e) {
                logger.error("IOException: " + e.getMessage(), e);
            }
        }
        return resultMap;
    }

    public static String beanToJson(Object object) throws IOException
    {
        ObjectMapper mapper = new ObjectMapper();
        StringWriter writer = new StringWriter();
        JsonGenerator gen = new JsonFactory().createJsonGenerator(writer);
        mapper.writeValue(gen, object);
        gen.close();
        String json = writer.toString();
        writer.close();
        return json;
    }

    public static HashMap<String, Object> jsonToMap(String json)
    {
        Logger logger = LoggerFactory.getLogger(ClienteBroker.class);
        ObjectMapper objectMapper = new ObjectMapper();
        HashMap<String, Object> result;
        try
        {
            result = objectMapper.readValue(json, HashMap.class);
            return result;
        }
        catch (JsonParseException e)
        {
            logger.error("ClientProtocolException: " + e.getMessage(), e);
            return null;
        }
        catch (JsonMappingException e)
        {
            logger.error("JsonMappingException: " + e.getMessage(), e);
            return null;
        }
        catch (IOException e)
        {
            logger.error("IOException: " + e.getMessage(), e);
            return null;
        }
    }
}
