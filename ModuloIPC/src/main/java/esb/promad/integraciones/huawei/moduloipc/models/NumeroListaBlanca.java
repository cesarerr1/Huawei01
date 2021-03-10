package esb.promad.integraciones.huawei.moduloipc.models;

public class NumeroListaBlanca {

    public String callerId;
    public String fechaIngreso;
    public String descripcion;

    public NumeroListaBlanca() {
    }

    public NumeroListaBlanca(String callerId, String fechaIngreso, String descripcion) {
        this.callerId = callerId;
        this.fechaIngreso = fechaIngreso;
        this.descripcion = descripcion;
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

    public String getDescripcion() {
        return descripcion;
    }

    public void setDescripcion(String descripcion) {
        this.descripcion = descripcion;
    }

    @Override
    public String toString() {
        return "NumeroListaBlanca{" +
                "callerId='" + callerId + '\'' +
                ", fechaIngreso='" + fechaIngreso + '\'' +
                ", descripcion='" + descripcion + '\'' +
                '}';
    }
}
