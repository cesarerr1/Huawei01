package com.example.demo;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.StringWriter;
import java.security.KeyManagementException;
import java.security.KeyStoreException;
import java.security.NoSuchAlgorithmException;
import java.security.cert.CertificateException;
import java.security.cert.X509Certificate;
import java.util.HashMap;
import java.util.Map;
import java.util.Map.Entry;
import java.util.Set;

import org.apache.http.Header;
import org.apache.http.HttpEntity;
import org.apache.http.HttpStatus;
import org.apache.http.client.ClientProtocolException;
import org.apache.http.client.methods.CloseableHttpResponse;
import org.apache.http.client.methods.HttpDelete;
import org.apache.http.client.methods.HttpEntityEnclosingRequestBase;
import org.apache.http.client.methods.HttpGet;
import org.apache.http.client.methods.HttpPost;
import org.apache.http.client.methods.HttpPut;
import org.apache.http.client.methods.HttpRequestBase;
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

public class IntegracionIPC {

    protected Logger logger = LoggerFactory.getLogger(IntegracionIPC.class);
    protected String errMsg;
    protected String hostIPC;
    protected int minLocal;

    public IntegracionIPC(String hostIPC, int minLocal) {
        this.hostIPC = hostIPC;
        this.minLocal = minLocal;
    }

    public String getErrMsg() {
        return errMsg;
    }

    public String getHostIPC() {
        return hostIPC;
    }

    public Map<String, String> login(String agentId, String password, String phoneNumber)
            throws NoSuchAlgorithmException, KeyStoreException, KeyManagementException {

        errMsg = "";
        logger.debug("Invocación al método login.");

        String url = hostIPC + "/resource/onlineagent/" + agentId;
        logger.debug("URL a ser invocada: " + url);
        Map<String, Object> loginParam = new HashMap<>();
        loginParam.put("password", password);
        loginParam.put("releasephone", false);
        loginParam.put("phonenum", phoneNumber);
        loginParam.put("autoanswer", false);
        loginParam.put("autoenteridle", false);
        loginParam.put("status", 5);
        return request(RequestType.PUT, url, loginParam, null);
    }

    public Map<String, String> forceLogin(String agentId, String password, String phoneNumber)
            throws NoSuchAlgorithmException, KeyStoreException, KeyManagementException {

        errMsg = "";
        logger.debug("Invocación al método force login.");

        String url = hostIPC + "/resource/onlineagent/" + agentId + "/forcelogin";
        logger.debug("URL a ser invocada: " + url);
        Map<String, Object> loginParam = new HashMap<>();
        loginParam.put("password", password);
        loginParam.put("releasephone", false);
        loginParam.put("phonenum", phoneNumber);
        loginParam.put("autoanswer", false);
        loginParam.put("autoenteridle", false);
        loginParam.put("status", 5);
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
        logger.debug("Invocación al método reset skills: " + agentId);
        String url = hostIPC + "/resource/onlineagent/" + agentId + "/resetskill/" + autoFlag;
        if (skillId != null && skillId != "")
            url = url + "?skillid=" + skillId;
        logger.debug("URL a ser invocada: " + url);
        return request(RequestType.POST, url, null, headers);
    }

    public Map<String, String> getAgentStatus(String agentId, Map<String, String> headers)
            throws NoSuchAlgorithmException, KeyStoreException, KeyManagementException {

        errMsg = "";
        logger.debug("Invocación al método get agent status: " + agentId);
        String url = hostIPC + "/resource/onlineagent/" + agentId + "/agentstatus";
        logger.debug("URL a ser invocada: " + url);
        return request(RequestType.GET, url, null, headers);
    }

    public Map<String, String> setIdle(String agentId, Map<String, String> headers)
            throws NoSuchAlgorithmException, KeyStoreException, KeyManagementException {

        errMsg = "";
        logger.debug("Invocación al método set idle: " + agentId);
        String url = hostIPC + "/resource/onlineagent/" + agentId + "/sayfree";
        logger.debug("URL a ser invocada: " + url);
        return request(RequestType.POST, url, null, headers);
    }

    public Map<String, String> setBusy(String agentId, Map<String, String> headers)
            throws NoSuchAlgorithmException, KeyStoreException, KeyManagementException {

        errMsg = "";
        logger.debug("Invocación al método set busy: " + agentId);
        String url = hostIPC + "/resource/onlineagent/" + agentId + "/saybusy?reason=200";
        logger.debug("URL a ser invocada: " + url);
        return request(RequestType.POST, url, null, headers);
    }

    public Map<String, String> setWorking(String agentId, Map<String, String> headers)
            throws NoSuchAlgorithmException, KeyStoreException, KeyManagementException {

        errMsg = "";
        logger.debug("Invocación al método set working: " + agentId);
        String url = hostIPC + "/resource/onlineagent/" + agentId + "/work";
        logger.debug("URL a ser invocada: " + url);
        return request(RequestType.POST, url, null, headers);
    }

    public Map<String, String> cancelWork(String agentId, Map<String, String> headers)
            throws NoSuchAlgorithmException, KeyStoreException, KeyManagementException {

        errMsg = "";
        logger.debug("Invocación al método cancel work: " + agentId);
        String url = hostIPC + "/resource/onlineagent/" + agentId + "/cancelwork";
        logger.debug("URL a ser invocada: " + url);
        return request(RequestType.POST, url, null, headers);
    }

    public Map<String, String> cancelBusy(String agentId, Map<String, String> headers)
            throws NoSuchAlgorithmException, KeyStoreException, KeyManagementException {

        errMsg = "";
        logger.debug("Invocación al método cancel busy: " + agentId);
        String url = hostIPC + "/resource/onlineagent/" + agentId + "/cancelbusy";
        logger.debug("URL a ser invocada: " + url);
        return request(RequestType.POST, url, null, headers);
    }

    public Map<String, String> getAgentEvent(String agentId, Map<String, String> headers)
            throws NoSuchAlgorithmException, KeyStoreException, KeyManagementException {

        errMsg = "";
        logger.debug("Invocación al método getAgentEvent:" + agentId);
        String url = hostIPC + "/resource/agentevent/" + agentId;
        logger.debug("URL a ser invocada: " + url);
        return request(RequestType.GET, url, null, headers);
    }

    public Map<String, String> answerCall(String agentId, Map<String, String> headers)
            throws NoSuchAlgorithmException, KeyStoreException, KeyManagementException {

        errMsg = "";
        logger.debug("Invocación al método answerCall:" + agentId);
        String url = hostIPC + "/resource/voicecall/" + agentId + "/answer";
        logger.debug("URL a ser invocada: " + url);
        return request(RequestType.PUT, url, null, headers);
    }

    public Map<String, String> releasePhone(String agentId, Map<String, String> headers)
            throws NoSuchAlgorithmException, KeyStoreException, KeyManagementException {

        errMsg = "";
        logger.debug("Invocación al método releasePhone:" + agentId);
        String url = hostIPC + "/resource/voicecall/" + agentId + "/releasephone";
        logger.debug("URL a ser invocada: " + url);
        return request(RequestType.DELETE, url, null, headers);
    }


    public Map<String, String> logout(String agentId, Map<String, String> headers)
            throws NoSuchAlgorithmException, KeyStoreException, KeyManagementException {

        errMsg = "";
        logger.debug("Invocación al método logout.");

        String url = hostIPC + "/resource/onlineagent/" + agentId + "/logout";
        logger.debug("URL a ser invocada: " + url);
        return request(RequestType.DELETE, url, null, headers);
    }

    public Map<String, String> forceLogout(String agentId, Map<String, String> headers)
            throws NoSuchAlgorithmException, KeyStoreException, KeyManagementException {

        errMsg = "";
        logger.debug("Invocación al método force logout.");

        String url = hostIPC + "/resource/onlineagent/" + agentId + "/forcelogout";
        logger.debug("URL a ser invocada: " + url);
        return request(RequestType.DELETE, url, null, headers);
    }

    public Map<String, String> voiceCall(String agentId, String number, Map<String, String> headers)
            throws NoSuchAlgorithmException, KeyStoreException, KeyManagementException {

        errMsg = "";
        logger.debug("Invocación al método voice call.");

        String url = hostIPC + "/resource/voicecall/" + agentId;

        // Se valida si se trata de una llamada interna o externa
        //if (number.length() >= this.minLocal)
            url += "/callout";
        //else
        //    url += "/callinner";

        logger.debug("URL a ser invocada: " + url);
        Map<String, Object> params = new HashMap<String, Object>();
        params.put("called", number);
        return request(RequestType.PUT, url, params, headers);
    }

    public Map<String, String> queryCallInfo(String agentId, String callId, Map<String, String> headers)
            throws NoSuchAlgorithmException, KeyStoreException, KeyManagementException {

        errMsg = "";
        logger.debug("Invocación al método queryCallInfo. " + callId);

        String url = hostIPC + "/resource/calldata/" + agentId + "/callinfobycallid/" + callId;
        logger.debug("URL a ser invocada: " + url);
        return request(RequestType.GET, url, null, headers);
    }

    public Map<String, String> transfer(String agentId, String callId, Map<String, String> headers)
            throws NoSuchAlgorithmException, KeyStoreException, KeyManagementException {

        errMsg = "";
        logger.debug("Se solicita una transferencia al nÃºmero: " + callId);

        String url = hostIPC + "/resource/voicecall/" + agentId + "/transfer";
        logger.debug("URL a ser invocada: " + url);

        int device = 5;

        // Se valida si se trata de una llamada interna o externa
        if (callId.length() >= this.minLocal)
            device = 5;

        Map<String, Object> params = new HashMap<String, Object>();
        params.put("devicetype", device);
        params.put("address", callId);
        params.put("mode", 1);
        return request(RequestType.POST, url, params, headers);
    }

    public Map<String, String> addNumberBlackList(String agentId, String callId, String time, String type,
                                                  Map<String, String> headers)
            throws NoSuchAlgorithmException, KeyStoreException, KeyManagementException {

        errMsg = "";
        logger.debug("Se solicita agregar un numero a la lista negra: " + callId);

        String url = hostIPC + "/resource/eccconfig/" + agentId + "/blacklist";
        logger.debug("URL a ser invocada: " + url);

        Map<String, Object> params = new HashMap<String, Object>();
        params.put("phoneNumber", callId);
        params.put("lockTime", time);
        params.put("fiterMode", type);
        return request(RequestType.POST, url, params, headers);
    }

    public Map<String, String> deleteNumberBlackList(String agentId, String callId, Map<String, String> headers)
            throws NoSuchAlgorithmException, KeyStoreException, KeyManagementException {

        errMsg = "";
        logger.debug("Se solicita eliminar un numero a la lista negra: " + callId);

        String url = hostIPC + "/resource/eccconfig/" + agentId + "/blacklist?phoneNumber=" + callId;
        logger.debug("URL a ser invocada: " + url);

        return request(RequestType.DELETE, url, null, headers);
    }

    public Map<String, String> queryNumbersBlackList(String agentId, Map<String, String> headers)
            throws NoSuchAlgorithmException, KeyStoreException, KeyManagementException {

        errMsg = "";
        logger.debug("Se solicita consultar los nÃºmeros de la lista negra.");

        String url = hostIPC + "/resource/eccconfig/" + agentId + "/allblacklist?isContainInvalid=false";
        logger.debug("URL a ser invocada: " + url);

        return request(RequestType.GET, url, null, headers);
    }

    public Map<String, String> addNumberWhiteList(String agentId, String callId, String level, Map<String, String> headers)
            throws NoSuchAlgorithmException, KeyStoreException, KeyManagementException {

        errMsg = "";
        logger.debug("Se solicita agregar un numero a la lista blanca: " + callId);

        String url = hostIPC + "/resource/eccconfig/" + agentId + "/redlist";
        logger.debug("URL a ser invocada: " + url);

        Map<String, Object> params = new HashMap<String, Object>();
        params.put("phoneNumber", callId);
        params.put("custLevel", level);
        return request(RequestType.POST, url, params, headers);
    }

    public Map<String, String> deleteNumberWhiteList(String agentId, String callId, Map<String, String> headers)
            throws NoSuchAlgorithmException, KeyStoreException, KeyManagementException {

        errMsg = "";
        logger.debug("Se solicita eliminar un numero a la lista blanca: " + callId);

        String url = hostIPC + "/resource/eccconfig/" + agentId + "/redlist?phoneNumber=" + callId;
        logger.debug("URL a ser invocada: " + url);

        return request(RequestType.DELETE, url, null, headers);
    }

    public Map<String, String> queryNumbersWhiteList(String agentId, Map<String, String> headers)
            throws NoSuchAlgorithmException, KeyStoreException, KeyManagementException {

        errMsg = "";
        logger.debug("Se solicita consultar los nÃºmeros registrados en la lista blanca.");

        String url = hostIPC + "/resource/eccconfig/" + agentId + "/allredlist";
        logger.debug("URL a ser invocada: " + url);

        return request(RequestType.GET, url, null, headers);
    }

    public Map<String, String> conference(String agentId, String callId, Map<String, String> headers)
            throws NoSuchAlgorithmException, KeyStoreException, KeyManagementException {

        errMsg = "";
        logger.debug("Se solicita una conferencia " + callId + " / " + agentId);

        String url = hostIPC + "/resource/voicecall/" + agentId + "/confjoin";
        logger.debug("URL a ser invocada: " + url);

        Map<String, Object> params = new HashMap<>();
        params.put("callid", callId);
        params.put("callappdata", "");
        return request(RequestType.POST, url, params, headers);
    }

    public Map<String, String> hold(String agentId, Map<String, String> headers)
            throws NoSuchAlgorithmException, KeyStoreException, KeyManagementException {

        errMsg = "";
        logger.debug("Se solicita hold a la extensión: " + agentId);

        String url = hostIPC + "/resource/voicecall/" + agentId + "/hold";
        logger.debug("URL a ser invocada: " + url);

        return request(RequestType.POST, url, null, headers);
    }

    public Map<String, String> unHold(String agentId, String callId, Map<String, String> headers)
            throws NoSuchAlgorithmException, KeyStoreException, KeyManagementException {

        errMsg = "";
        logger.debug("Se solicita unhold a la extensión: " + agentId + " con la llamada: " + callId);

        String url = hostIPC + "/resource/voicecall/" + agentId + "/gethold?callid=" + callId;
        logger.debug("URL a ser invocada: " + url);

        return request(RequestType.POST, url, null, headers);
    }

    public Map<String, String> intrusion(String agentId, String supId, Map<String, String> headers)
            throws NoSuchAlgorithmException, KeyStoreException, KeyManagementException {

        errMsg = "";
        logger.debug("Se solicita una intrusón: " + supId + "/" + agentId);

        String url = hostIPC + "/resource/qualitycontrol/" + supId + "/addsupervise/" + agentId;
        logger.debug("URL a ser invocada: " + url);

        return request(RequestType.PUT, url, null, headers);
    }

    public Map<String, String> coaching(String agentId, String supId, Map<String, String> headers)
            throws NoSuchAlgorithmException, KeyStoreException, KeyManagementException {

        errMsg = "";
        logger.debug("Se solicita un coaching: " + supId + "/" + agentId);

        String url = hostIPC + "/resource/qualitycontrol/" + supId + "/intercept/" + agentId;
        logger.debug("URL a ser invocada: " + url);

        return request(RequestType.PUT, url, null, headers);
    }

    public Map<String, String> queryQueue(String agentId, String skillId, Map<String, String> headers)
            throws NoSuchAlgorithmException, KeyStoreException, KeyManagementException {

        errMsg = "";
        logger.trace("Se solicita la información de la cola de llamadas: " + agentId);

        String url = hostIPC + "/resource/calldata/" + agentId + "/waitcallinfo/" + skillId;
        logger.trace("URL a ser invocada: " + url);
        return request(RequestType.GET, url, null, headers);
    }

    public Map<String, String> isInspector(String agentId, Map<String, String> headers)
            throws NoSuchAlgorithmException, KeyStoreException, KeyManagementException {

        errMsg = "";
        logger.trace("Se solicita validar si el agente es un inspector: " + agentId);

        String url = hostIPC + "/resource/agentgroup/" + agentId + "/iscensor";
        logger.trace("URL a ser invocada: " + url);
        return request(RequestType.GET, url, null, headers);
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
                Set<Entry<String, String>> headersSet = headers.entrySet();
                for (Entry<String, String> entry : headersSet) {
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
                String guid = "", cookie = "";
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
                                logger.debug("Cambio en la GUID: " + guid);
                            }
                            break;
                        }
                        else if (header.getName().equals("Set-Cookie")) 
                        {
                        	String setCookie = header.getValue();
                        	if (setCookie != null)
                        	{
                        		cookie = setCookie;//.replace("loadbalance=", "");
                        		logger.debug("Cambio en la cookie: " + cookie);
                        	}
                        }
                    }
                }
                resultMap = new HashMap<String, String>();
                resultMap.put("guid", guid);
                resultMap.put("cookie", cookie);
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

    @SuppressWarnings("unchecked")
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
            e.printStackTrace();
            return null;
        }
        catch (JsonMappingException e)
        {
        	e.printStackTrace();
            return null;
        }
        catch (IOException e)
        {
        	e.printStackTrace();
            return null;
        }
    }


}
