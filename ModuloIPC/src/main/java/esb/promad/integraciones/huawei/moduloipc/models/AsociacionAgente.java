package esb.promad.integraciones.huawei.moduloipc.models;

public class AsociacionAgente {

    public String numeroAgente;
    public String numeroExtension;
    public String direccionIP;

    public AsociacionAgente() {
    }

    public AsociacionAgente(String numeroAgente, String numeroExtension, String direccionIP) {
        this.numeroAgente = numeroAgente;
        this.numeroExtension = numeroExtension;
        this.direccionIP = direccionIP;
    }

    public String getNumeroAgente() {
        return numeroAgente;
    }

    public void setNumeroAgente(String numeroAgente) {
        this.numeroAgente = numeroAgente;
    }

    public String getNumeroExtension() {
        return numeroExtension;
    }

    public void setNumeroExtension(String numeroExtension) {
        this.numeroExtension = numeroExtension;
    }

    public String getDireccionIP() {
        return direccionIP;
    }

    public void setDireccionIP(String direccionIP) {
        this.direccionIP = direccionIP;
    }

    @Override
    public String toString() {
        return "AsociacionAgente{" +
                "numeroAgente='" + numeroAgente + '\'' +
                ", numeroExtension='" + numeroExtension + '\'' +
                ", direccionIP='" + direccionIP + '\'' +
                '}';
    }
}
