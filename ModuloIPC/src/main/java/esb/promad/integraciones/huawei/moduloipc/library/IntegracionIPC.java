package esb.promad.integraciones.huawei.moduloipc.library;

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
import java.util.HashMap;
import java.util.Map;
import java.util.Map.Entry;
import java.util.Set;

public class IntegracionIPC {

    protected static Logger logger = LoggerFactory.getLogger(IntegracionIPC.class);
    protected String errMsg;
    protected String hostIPC;

    public IntegracionIPC(String hostIPC) {
        this.hostIPC = hostIPC;
    }

    public String getErrMsg() {
        return errMsg;
    }

    public Map<String, String> login(String agentId, String password, String phoneNumber)
            throws NoSuchAlgorithmException, KeyStoreException, KeyManagementException {

        errMsg = "";
        logger.debug("Invocación al método login.");

        String url = hostIPC + "/resource/onlineagent/" + agentId;
        logger.debug("URL a ser invocada: " + url);
        Map<String, Object> loginParam = new HashMap<String, Object>();
        loginParam.put("password", password);
        loginParam.put("phonenum", phoneNumber);
        return request(RequestType.PUT, url, loginParam, null);
    }

    public Map<String, String> forceLogin(String agentId, String password, String phoneNumber)
            throws NoSuchAlgorithmException, KeyStoreException, KeyManagementException {

        errMsg = "";
        logger.debug("Invocación al método force login.");

        String url = hostIPC + "/resource/onlineagent/" + agentId + "/forcelogin";
        logger.debug("URL a ser invocada: " + url);
        Map<String, Object> loginParam = new HashMap<String, Object>();
        loginParam.put("password", password);
        loginParam.put("phonenum", phoneNumber);
        return request(RequestType.PUT, url, loginParam, null);
    }

    public Map<String, String> querySkills(String agentId)
            throws NoSuchAlgorithmException, KeyStoreException, KeyManagementException {

        errMsg = "";
        logger.debug("Invocación al método query skills.");
        String url = hostIPC + "/resource/onlineagent/" + agentId + "/agentskills";
        logger.debug("URL a ser invocada: " + url);
        return request(RequestType.GET, url, null, null);
    }

    public Map<String, String> resetSkills(String agentId, boolean autoFlag, String skillId,
                                           Map<String, String> headers)
            throws NoSuchAlgorithmException, KeyStoreException, KeyManagementException {

        errMsg = "";
        logger.debug("Invocación al método query skills: " + agentId);
        String url = hostIPC + "/resource/onlineagent/" + agentId + "/resetskill/" + autoFlag;
        if (skillId != null && skillId != "")
            url = url + "?skillid=" + skillId;
        logger.debug("URL a ser invocada: " + url);
        return request(RequestType.POST, url, null, null);
    }

    public Map<String, String> getAgentEvent(String agentId, Map<String, String> headers)
            throws NoSuchAlgorithmException, KeyStoreException, KeyManagementException {

        errMsg = "";
        logger.debug("Invocación al método getAgentEvent:" + agentId);
        String url = hostIPC + "/resource/agentevent/" + agentId;
        logger.debug("URL a ser invocada: " + url);
        return request(RequestType.GET, url, null, headers);
    }


    public Map<String, String> logout(String agentId)
            throws NoSuchAlgorithmException, KeyStoreException, KeyManagementException {

        errMsg = "";
        logger.debug("Invocación al método logout.");

        String url = hostIPC + "/resource/onlineagent/" + agentId + "/forcelogout";
        logger.debug("URL a ser invocada: " + url);
        return request(RequestType.DELETE, url, null, null);
    }

    public Map<String, String> forceLogout(String agentId)
            throws NoSuchAlgorithmException, KeyStoreException, KeyManagementException {

        errMsg = "";
        logger.debug("Invocación al método force logout.");

        String url = hostIPC + "/resource/onlineagent/" + agentId + "/logout";
        logger.debug("URL a ser invocada: " + url);
        return request(RequestType.DELETE, url, null, null);
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

    protected Map<String, String> request(RequestType type, String url, Map<String, Object> entityParams, Map<String, String> headers)
            throws KeyStoreException, NoSuchAlgorithmException, KeyManagementException {

        errMsg = "";
        CloseableHttpClient httpClient = generateHttpClient();
        CloseableHttpResponse response = null;
        Map<String, String> resultMap = null;
        try {

            HttpRequestBase httpRequest;
            switch (type) {

                case GET:
                    httpRequest = new HttpGet(url);
                    break;

                case POST:
                    httpRequest = new HttpPost(url);
                    break;

                case PUT:
                    httpRequest = new HttpPut(url);
                    break;

                case DELETE:
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
                logger.debug("JSON: " + jsonString);
            }

            if (headers != null)
            {
                Set<Entry<String, String>> headersSet = headers.entrySet();
                for (Entry<String, String> entry : headersSet)
                {
                    httpRequest.setHeader(entry.getKey(), entry.getValue());
                }
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
                            }
                            break;
                        }
                    }
                }
                resultMap = new HashMap<String, String>();
                resultMap.put("guid", guid);
                resultMap.put("result", buffer.toString());
            }
            else
            {
                logger.debug("RETURN_CODE: " + returnCode);
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
