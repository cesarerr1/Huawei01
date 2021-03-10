package esb.promad.integraciones.huawei.moduloipc.models;

public class NumeroListaNegra {

    public String callerId;
    public String fechaIngreso;
    public String motivoIngreso;
    public String descripcion;
    public String idAccion;

    public NumeroListaNegra() {
    }

    public NumeroListaNegra(String callerId, String fechaIngreso, String motivoIngreso, String descripcion,
                            String idAccion) {
        this.callerId = callerId;
        this.fechaIngreso = fechaIngreso;
        this.motivoIngreso = motivoIngreso;
        this.descripcion = descripcion;
        this.idAccion = idAccion;
    }

    public String getCallerId() {
        return callerId;
    }

    public void setCallerId(String callerId) {
        this.callerId = callerId;
    }

    public String getFechaIngreso() {
        return fechaIngreso;
    }

    public void setFechaIngreso(String fechaIngreso) {
        this.fechaIngreso = fechaIngreso;
    }

    public String getMotivoIngreso() {
        return motivoIngreso;
    }

    public void setMotivoIngreso(String motivoIngreso) {
        this.motivoIngreso = motivoIngreso;
    }

    public String getDescripcion() {
        return descripcion;
    }

    public void setDescripcion(String descripcion) {
        this.descripcion = descripcion;
    }

    public String getIdAccion() {
        return idAccion;
    }

    public void setIdAccion(String idAccion) {
        this.idAccion = idAccion;
    }

    @Override
    public String toString() {
        return "NumeroListaNegra{" +
                "callerId='" + callerId + '\'' +
                ", fechaIngreso='" + fechaIngreso + '\'' +
                ", motivoIngreso='" + motivoIngreso + '\'' +
                ", descripcion='" + descripcion + '\'' +
                ", idAccion='" + idAccion + '\'' +
                '}';
    }
}
