package esb.promad.integraciones.huawei.moduloipc.library;

import org.slf4j.Logger;
import org.slf4j.LoggerFactory;

import javax.net.ssl.*;
import java.io.*;
import java.security.KeyStore;
import java.security.MessageDigest;
import java.security.cert.CertificateException;
import java.security.cert.X509Certificate;

public class InstallCert {

    protected Logger logger = LoggerFactory.getLogger(InstallCert.class);
    protected String errMsg;

    private final char[] HEXDIGITS = "0123456789abcdef".toCharArray();

    public String getErrMsg() {
        return errMsg;
    }

    public int validarCertificado(String host, int port, String passphrase) throws Exception {

        errMsg = "";
        logger.debug("Iniciando instalación de certificado: " + host + ":" + port);

        if (passphrase.length() <= 0)
            passphrase = "changeit";

        File file = readCacertFile("jssecacerts");
        logger.debug("Loading KeyStore " + file + "...");
        InputStream in = new FileInputStream(file);
        KeyStore ks = KeyStore.getInstance(KeyStore.getDefaultType());
        ks.load(in, passphrase.toCharArray());
        in.close();

        SSLContext context = SSLContext.getInstance("TLS");
        TrustManagerFactory tmf = TrustManagerFactory.getInstance(TrustManagerFactory.getDefaultAlgorithm());
        tmf.init(ks);
        X509TrustManager defaultTrustManager = (X509TrustManager) tmf.getTrustManagers()[0];
        SavingTrustManager tm = new SavingTrustManager(defaultTrustManager);
        context.init(null, new TrustManager[]{tm}, null);
        SSLSocketFactory factory = context.getSocketFactory();

        logger.debug("Opening connection to " + host + ":" + port + "...");
        SSLSocket socket = (SSLSocket) factory.createSocket(host, port);
        socket.setSoTimeout(10000);
        try {
            logger.debug("Starting SSL handshake...");
            socket.startHandshake();
            socket.close();
            logger.debug("No errors, certificate is already trusted");
        } catch (SSLException e) {
            errMsg = "SSLException: " + e.getMessage();
            logger.error(errMsg);
            return -1;
        }

        return 0;
    }

    public int instalarCertificado(String host, int port, String passphrase) throws Exception {

        errMsg = "";
        logger.debug("Iniciando instalación de certificado: " + host + ":" + port);

        if (passphrase.length() <= 0)
            passphrase = "changeit";

        File file = readCacertFile("jssecacerts");
        logger.debug("Loading KeyStore " + file + "...");
        InputStream in = new FileInputStream(file);
        KeyStore ks = KeyStore.getInstance(KeyStore.getDefaultType());
        ks.load(in, passphrase.toCharArray());
        in.close();

        SSLContext context = SSLContext.getInstance("TLS");
        TrustManagerFactory tmf = TrustManagerFactory.getInstance(TrustManagerFactory.getDefaultAlgorithm());
        tmf.init(ks);
        X509TrustManager defaultTrustManager = (X509TrustManager) tmf.getTrustManagers()[0];
        SavingTrustManager tm = new SavingTrustManager(defaultTrustManager);
        context.init(null, new TrustManager[]{tm}, null);
        SSLSocketFactory factory = context.getSocketFactory();

        logger.debug("Opening connection to " + host + ":" + port + "...");
        SSLSocket socket = (SSLSocket) factory.createSocket(host, port);
        socket.setSoTimeout(10000);
        try {
            logger.debug("Starting SSL handshake...");
            socket.startHandshake();
            socket.close();
            logger.debug("No errors, certificate is already trusted");
            return 0;
        } catch (SSLException e) {
            errMsg = "SSLException: " + e.getMessage();
            logger.error(errMsg);
        }

        X509Certificate[] chain = tm.chain;
        if (chain == null) {
            errMsg = "Could not obtain server certificate chain";
            logger.error(errMsg);
            return -1;
        }

        BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
        logger.debug("Server sent " + chain.length + " certificate(s):");
        MessageDigest sha1 = MessageDigest.getInstance("SHA1");
        MessageDigest md5 = MessageDigest.getInstance("MD5");
        for (int i = 0; i < chain.length; i++) {
            X509Certificate cert = chain[i];
            logger.debug(" " + (i + 1) + " Subject " + cert.getSubjectDN());
            logger.debug("   Issuer  " + cert.getIssuerDN());
            sha1.update(cert.getEncoded());
            logger.debug("   sha1    " + toHexString(sha1.digest()));
            md5.update(cert.getEncoded());
            logger.debug("   md5     " + toHexString(md5.digest()));
        }

        int k = 0;
        X509Certificate cert = chain[k];
        String alias = host + "-" + (k + 1);
        ks.setCertificateEntry(alias, cert);

        OutputStream out = new FileOutputStream("jssecacerts");
        ks.store(out, passphrase.toCharArray());
        out.close();
        logger.debug("Added certificate to keystore 'jssecacerts' using alias '" + alias + "'");

        return 0;
    }

    private File readCacertFile(String path) {
        File file = new File("jssecacerts");
        if (file.isFile() == false) {
            char SEP = File.separatorChar;
            File dir = new File(System.getProperty("java.home") + SEP
                    + "lib" + SEP + "security");
            file = new File(dir, "jssecacerts");
            if (file.isFile() == false) {
                file = new File(dir, "cacerts");
            }
        }
        return file;
    }

    private String toHexString(byte[] bytes) {
        StringBuilder sb = new StringBuilder(bytes.length * 3);
        for (int b : bytes) {
            b &= 0xff;
            sb.append(HEXDIGITS[b >> 4]);
            sb.append(HEXDIGITS[b & 15]);
            sb.append(' ');
        }
        return sb.toString();
    }

    private class SavingTrustManager implements X509TrustManager {

        private final X509TrustManager tm;
        private X509Certificate[] chain;

        SavingTrustManager(X509TrustManager tm) {
            this.tm = tm;
        }

        public X509Certificate[] getAcceptedIssuers() {
            throw new UnsupportedOperationException();
        }

        public void checkClientTrusted(X509Certificate[] chain, String authType)
                throws CertificateException {
            throw new UnsupportedOperationException();
        }

        public void checkServerTrusted(X509Certificate[] chain, String authType)
                throws CertificateException {
            this.chain = chain;
            tm.checkServerTrusted(chain, authType);
        }
    }
}
