package esb.promad.integraciones.huawei.moduloipc.models;

public class Agente {

    public String numeroAgente;
    public String nombreAgente;

    public Agente() {
    }

    public Agente(String numeroAgente, String nombreAgente) {
        this.numeroAgente = numeroAgente;
        this.nombreAgente = nombreAgente;
    }

    public String getNumeroAgente() {
        return numeroAgente;
    }

    public void setNumeroAgente(String numeroAgente) {
        this.numeroAgente = numeroAgente;
    }

    public String getNombreAgente() {
        return nombreAgente;
    }

    public void setNombreAgente(String nombreAgente) {
        this.nombreAgente = nombreAgente;
    }

    @Override
    public String toString() {
        return "Agente{" +
                "numeroAgente='" + numeroAgente + '\'' +
                ", nombreAgente='" + nombreAgente + '\'' +
                '}';
    }
}
